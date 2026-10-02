import sqlmodel
import fastapi
from typing import Annotated
import pwdlib

from app.core.database import get_db_session
from app.modules.identity.models import Identity, PasswordCredential
from app.modules.common.exceptions import InternalServerErrorException
from .schemas import SignupRequest, SignupResponse
from .exceptions import UserExistsException

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

    def sign_in(self):
        ...

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


# Security Service Dependency
def get_security_service(
    db_session: Annotated[sqlmodel.Session, fastapi.Depends(get_db_session)]
):
    return SecurityService(
        db_session=db_session
    )