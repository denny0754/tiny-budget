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