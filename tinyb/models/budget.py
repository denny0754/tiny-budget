from sqlmodel import SQLModel, Field

from datetime import datetime

from uuid import UUID, uuid4

from .common import AuditMetadata

class Budget(AuditMetadata, SQLModel, table=True):
    __tablename__: str = 'budget'  # type: ignore

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
    validity_period_range_guid: UUID | None = Field(
        default=None,
        foreign_key="code_list.guid",
        nullable=True
    )
    validity_period_type_guid: UUID | None = Field(
        default=None,
        foreign_key="code_list.guid",
        nullable=True
    )
    valid_from: datetime | None = Field(
        default=None,
        nullable=True
    )
    valid_to: datetime | None = Field(
        default=None,
        nullable=True
    )
    parent_guid: UUID | None = Field(
        default=None,
        foreign_key="budget.guid",
        nullable=True
    )