import sqlmodel
import fastapi
from typing import Annotated
import pwdlib
import jwt
import datetime

from app.core.database import get_db_session
from app.core.settings import get_environment_settings, EnvironmentSettings
from app.modules.identity.models import Identity, PasswordCredential
from app.modules.common.exceptions import InternalServerErrorException
from .schemas import SignupRequest, SignupResponse, SigninRequest, JWTUserDataPayload, JWTPayload, SigninResponse
from .exceptions import UserExistsException, UserDoesNotExistException, InvalidCredentialsException

__JWT_LEEWAY: float = 60
__JWT_ALGORITHM: str = 'HS256'

class SecurityService:

    def __init__(self, db_session: sqlmodel.Session, env_settings: EnvironmentSettings):
        self.__db_session = db_session
        self.__env_settings = env_settings

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
        #TODO: When a user fails the password too many times, login for the user needs to be time-suspended(env variable LOGIN_SUSPENSION_TIME).
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
            self.handle_password_attempt_failure(pwd_credential)
            raise InvalidCredentialsException()

        jwt_user_data: JWTUserDataPayload = JWTUserDataPayload(email=identity.email, first_name=identity.first_name, last_name=identity.last_name)

        self.handle_password_attempt_success(pwd_credential)
        return SigninResponse(
            access_token=self.generate_jw_token(identity_id=str(identity.id), user_data=jwt_user_data),
            refresh_token=self.generate_jw_token(identity_id=str(identity.id), user_data=jwt_user_data),
            expires_in=self.__env_settings.JWT_EXPIRATION_SECONDS,
        )

    def handle_password_attempt_failure(self, credential: PasswordCredential) -> None:
        try:
            credential.failed_attempts = credential.failed_attempts + 1
            self.__db_session.add(credential)
            self.__db_session.commit()
        except:
            raise InternalServerErrorException()

    def handle_password_attempt_success(self, credential: PasswordCredential) -> None:
        try:
            credential.failed_attempts = 0
            self.__db_session.add(credential)
            self.__db_session.commit()
        except:
            raise InternalServerErrorException()

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
        jwt_exp: datetime.datetime = jwt_iat + datetime.timedelta(minutes=self.__env_settings.JWT_EXPIRATION_SECONDS)
        jwt_payload: JWTPayload = JWTPayload(
            sub=str(identity_id),
            exp=int(jwt_exp.timestamp()),
            iat=int(jwt_iat.timestamp()),
            user_data=user_data
        )

        token: str = jwt.encode(
            jwt_payload.model_dump(mode='json'),
            algorithm=__JWT_ALGORITHM,
            key=self.__env_settings.JWT_SECRET_KEY
        )

        return token

    def decode_jwt(self, token) -> dict[str, str]:
        try:
            return jwt.decode(token, algorithms=[__JWT_ALGORITHM], key=self.__env_settings.JWT_SECRET_KEY, leeway=__JWT_LEEWAY)
        except jwt.exceptions.PyJWTError:
            #NOTE: I think exception management related to jwt decoding can be left as this for now. If the token is invalid or an error occured,
            #      an error is returned to the client and a retry can be sent by the User itself.
            #      Though, in the future, this might need a better handler.
            return {}

# Security Service Dependency
def get_security_service(
    db_session: Annotated[sqlmodel.Session, fastapi.Depends(get_db_session)],
    env_settings: Annotated[EnvironmentSettings, fastapi.Depends(get_environment_settings)]
):
    return SecurityService(
        db_session=db_session,
        env_settings=env_settings
    )