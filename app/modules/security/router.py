import fastapi
from typing import Annotated

from .service import SecurityService, get_security_service
from .schemas import SignupRequest, SignupResponse
from .exceptions import UserExistsException
from app.modules.common.exceptions import InternalServerErrorException
from app.modules.common.schemas import ErrorResponse

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
            endpoint=self.sign_up,
            status_code=fastapi.status.HTTP_201_CREATED
        )

        self.add_api_route(
            methods=['POST'],
            path='/sign-in',
            endpoint=self.sign_in,
            status_code=fastapi.status.HTTP_200_OK
        )

    def sign_up(
        self,
        data: SignupRequest,
        security_srv: Annotated[SecurityService, fastapi.Depends(get_security_service)]
    ):
        try:
            _response: SignupResponse = security_srv.sign_up(
                data=data
            )
        except InternalServerErrorException:
            raise fastapi.HTTPException(
                status_code=fastapi.status.HTTP_500_INTERNAL_SERVER_ERROR,
                detail=ErrorResponse(
                    message='An unknown error occured. Please, retry!'
                ).model_dump_json()
            )
        
        except UserExistsException:
            raise fastapi.HTTPException(
                status_code=fastapi.status.HTTP_409_CONFLICT,
                detail=ErrorResponse(
                    message='A User with the given e-mail already exists! Try to login instead.'
                )
            )
        
        return _response

    def sign_in(
        self
    ):
        ...