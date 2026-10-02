import pydantic
import uuid

class SignupRequest(pydantic.BaseModel):

    email: pydantic.EmailStr

    password: str

    first_name: str = pydantic.Field(
        max_length=100
    )

    last_name: str = pydantic.Field(
        max_length=100
    )

class SignupResponse(pydantic.BaseModel):

    id: uuid.UUID

    email: str

class SigninRequest(pydantic.BaseModel):

    email: str

    password: str

class SigninResponse(pydantic.BaseModel):

    access_token: str

    refresh_token: str

    expires_in: int

    token_type: str = 'bearer'

class JWTUserDataPayload(pydantic.BaseModel):

    email: str

    first_name: str

    last_name: str

class JWTPayload(pydantic.BaseModel):

    iss: str = 'tiny-budget.it'

    sub: str

    exp: int

    iat: int

    user_data: JWTUserDataPayload