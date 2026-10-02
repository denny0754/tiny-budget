from sqlmodel import SQLModel, Field

from uuid import UUID, uuid4

from .common import AuditMetadata

class Identity(AuditMetadata, SQLModel, table=True):
    __tablename__: str = 'identity'  # type: ignore

    guid: UUID = Field(
        default_factory=uuid4,
        primary_key=True
    )
    email: str = Field(
        max_length=250,
        unique=True,
        nullable=False
    )
    password_hash: str = Field(
        nullable=False
    )
    first_name: str = Field(
        max_length=100,
        nullable=False
    )
    middle_name: str | None = Field(
        max_length=100,
        nullable=True
    )
    last_name: str = Field(
        max_length=100,
        nullable=False
    )