from sqlmodel import SQLModel, Field
from sqlalchemy.types import JSON
from uuid import UUID, uuid4

from .common import AuditMetadata

class BusinessPartner(AuditMetadata, SQLModel, table=True):
    __tablename__: str = 'business_partner'  # type: ignore

    guid: UUID = Field(
        default_factory=uuid4,
        primary_key=True
    )
    book_guid: UUID | None = Field(
        default=None,
        foreign_key="financial_book.guid",
        nullable=True
    )
    name: str = Field(
        nullable=False
    )
    description: str | None = Field(
        default=None,
        nullable=True
    )
    status_guid: UUID | None = Field(
        default=None,
        foreign_key="code_list.guid",
        nullable=True
    )
    bp_type_guid: UUID | None = Field(
        default=None,
        foreign_key="code_list.guid",
        nullable=True
    )
    data: dict | None = Field(
        default=None,
        sa_type=JSON,
        nullable=True
    )