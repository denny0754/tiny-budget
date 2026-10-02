import sqlmodel
import fastapi
from typing import Annotated
import pwdlib
import jwt
import datetime

from app.core.database import get_db_session
from app.modules.identity.models import Identity, PasswordCredential
from app.modules.common.exceptions import InternalServerErrorException
from .schemas import SignupRequest, SignupResponse, SigninRequest, JWTUserDataPayload, JWTPayload, SigninResponse
from .exceptions import UserExistsException, UserDoesNotExistException, InvalidCredentialsException

class SecurityService:

    def __init__(self, db_session: sqlmodel.Session):
        self.__db_session = db_session

    def sign_up(self, data: SignupRequest) -> SignupResponse:

        # Error response is handled on the API Layer.
        if self.user_exists(data.email):
            raise UserExistsException()

        try:

            identity: Identity = Identity(
                email=data.email,
                first_name=data.first_name,
                last_name=data.last_name
            )

            self.__db_session.add(identity)
            # Flushing to get identity.id available
            self.__db_session.flush()

            pwd_credential: PasswordCredential = PasswordCredential(
                identity_id=identity.id,
                password_algo='argo2id',
                password_hash=self.hash_password(data.password),
            )
            self.__db_session.add(pwd_credential)

            self.__db_session.commit()
        except:
            raise InternalServerErrorException()

        return SignupResponse(
            id=identity.id,
            email=identity.email
        )

    def sign_in(
        self,
        data: SigninRequest
    ):
        identity: Identity | None = self.__db_session.exec(
            sqlmodel.select(Identity)
            .where(Identity.email == data.email)
        ).one_or_none()

        if not identity:
            raise UserDoesNotExistException()

        pwd_credential: PasswordCredential = self.__db_session.exec(
            sqlmodel.select(PasswordCredential)
            .where(PasswordCredential.identity_id == identity.id)
        ).one()

        if not self.verify_password(
            password=data.password,
            password_hash=pwd_credential.password_hash
        ):
            raise InvalidCredentialsException()

        jwt_user_data: JWTUserDataPayload = JWTUserDataPayload(email=identity.email, first_name=identity.first_name, last_name=identity.last_name)

        #TODO: parameter `expires_in` should be read from env variables
        return SigninResponse(
            access_token=self.generate_jw_token(identity_id=str(identity.id), user_data=jwt_user_data),
            refresh_token=self.generate_jw_token(identity_id=str(identity.id), user_data=jwt_user_data),
            expires_in=15*60,
        )

    def verify_password(self, password, password_hash) -> bool:
        pwd_hasher: pwdlib.PasswordHash = pwdlib.PasswordHash.recommended()
        return pwd_hasher.verify(password, password_hash)

    def hash_password(self, password) -> str:
        pwd_hasher: pwdlib.PasswordHash = pwdlib.PasswordHash.recommended()
        return pwd_hasher.hash(password)

    def user_exists(self, email) -> bool:
        return self.__db_session.exec(
            sqlmodel.select(Identity)
            .where(Identity.email == email)
        ).one_or_none() == None

    def generate_jw_token(self, identity_id: str, user_data: JWTUserDataPayload) -> str:
        jwt_iat: datetime.datetime = datetime.datetime.now(datetime.timezone.utc)
        jwt_exp: datetime.datetime = jwt_iat + datetime.timedelta(minutes=15)
        jwt_payload: JWTPayload = JWTPayload(
            sub=str(identity_id),
            exp=int(jwt_exp.timestamp()),
            iat=int(jwt_iat.timestamp()),
            user_data=user_data
        )

        #TODO: algorithm and key should be read from env variables
        token: str = jwt.encode(
            jwt_payload.model_dump(mode='json'),
            algorithm='HS256',
            key=''
        )

        return token

    def decode_jwt(self, token) -> dict[str, str]:
        #TODO: algorithm and key should be read from env variables
        #TODO: manage PyJWT exceptions
        return jwt.decode(token, algorithms=['HS256'], key='')


# Security Service Dependency
def get_security_service(
    db_session: Annotated[sqlmodel.Session, fastapi.Depends(get_db_session)]
):
    return SecurityService(
        db_session=db_session
    )