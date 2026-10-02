from sqlmodel import SQLModel, Field
from uuid import UUID, uuid4
from .common import AuditMetadata


class FinancialBook(AuditMetadata, SQLModel, table=True):
    __tablename__: str = 'financial_book'  # type: ignore

    guid: UUID = Field(
        default_factory=uuid4,
        primary_key=True
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