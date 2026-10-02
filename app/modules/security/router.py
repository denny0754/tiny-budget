import fastapi
from typing import Annotated

from .service import SecurityService, get_security_service
from .schemas import SignupRequest

class SecurityRouter(fastapi.APIRouter):

    def __init__(
        self
    ):
        super().__init__(
            prefix='/security'
        )

        self.add_api_route(
            methods=['POST'],
            path='/sign-up',
            endpoint=self.sign_up
        )

        self.add_api_route(
            methods=['POST'],
            path='/sign-in',
            endpoint=self.sign_in
        )

    def sign_up(
        self,
        data: SignupRequest,
        security_srv: Annotated[SecurityService, fastapi.Depends(get_security_service)]
    ):
        ...

    def sign_in(
        self
    ):
        ...