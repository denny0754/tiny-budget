import sqlmodel
import uuid
import datetime

class Identity(sqlmodel.SQLModel, table=True):

    __tablename__: str = 'identity' #type: ignore

    id: uuid.UUID = sqlmodel.Field(
        default_factory=uuid.uuid4,
        primary_key=True
    )

    email: str = sqlmodel.Field(
        max_length=254,
        unique=True
    )

    first_name: str = sqlmodel.Field(
        max_length=100,
        nullable=False
    )

    last_name: str = sqlmodel.Field(
        max_length=100,
        nullable=False
    )

    created_on: datetime.datetime = sqlmodel.Field(
        default_factory=lambda: datetime.datetime.now(datetime.timezone.utc),
        nullable=False
    )

    updated_on: datetime.datetime = sqlmodel.Field(
        default_factory=lambda: datetime.datetime.now(datetime.timezone.utc),
        nullable=False
    )

class PasswordCredential(sqlmodel.SQLModel, table=True):

    __tablename__: str = 'password_credential' #type: ignore

    id: uuid.UUID = sqlmodel.Field(
        default_factory=uuid.uuid4,
        primary_key=True
    )

    identity_id: uuid.UUID = sqlmodel.Field(
        foreign_key='identity.id',
        nullable=False
    )

    password_hash: str = sqlmodel.Field(
        nullable=False
    )

    password_algo: str = sqlmodel.Field(
        nullable=False
    )

    failed_attempts: int = sqlmodel.Field(
        nullable=False,
        default=0
    )

    updated_on: datetime.datetime = sqlmodel.Field(
        default_factory=lambda: datetime.datetime.now(datetime.timezone.utc),
        nullable=False
    )