from sqlmodel import SQLModel, Field
from uuid import UUID, uuid4
from decimal import Decimal
from .common import AuditMetadata

class Product(AuditMetadata, SQLModel, table=True):
    __tablename__: str = 'product'  # type: ignore

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
    payee_guid: UUID | None = Field(
        default=None,
        foreign_key="business_partner.guid",
        nullable=True
    )
    gross_value: Decimal | None = Field(
        default=None,
        nullable=True
    )