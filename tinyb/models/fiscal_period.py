from sqlmodel import SQLModel, Field
from uuid import UUID, uuid4
from datetime import date
from .common import AuditMetadata

class FiscalPeriod(AuditMetadata, SQLModel, table=True):
    __tablename__: str = 'fiscal_period'  # type: ignore

    guid: UUID = Field(
        default_factory=uuid4,
        primary_key=True
    )
    book_guid: UUID | None = Field(
        default=None,
        foreign_key="financial_book.guid",
        nullable=True
    )
    name: str | None = Field(
        max_length=100,
        nullable=True
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
    start_date: date | None = Field(
        default=None,
        nullable=True
    )
    end_date: date | None = Field(
        default=None,
        nullable=True
    )
    parent_guid: UUID | None = Field(
        default=None,
        foreign_key="fiscal_period.guid",
        nullable=True
    )