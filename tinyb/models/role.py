from sqlmodel import SQLModel, Field
from uuid import UUID, uuid4
from sqlalchemy.types import JSON

from .common import AuditMetadata

class Role(AuditMetadata, SQLModel, table=True):
    __tablename__: str = 'role'  # type: ignore

    guid: UUID = Field(
        default_factory=uuid4,
        primary_key=True
    )
    financial_book_guid: UUID | None = Field(
        default=None,
        foreign_key="financial_book.guid",
        nullable=True
    )
    data: dict | None = Field(
        default=None,
        sa_type=JSON,
        nullable=True
    )