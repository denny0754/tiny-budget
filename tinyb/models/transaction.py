from sqlmodel import SQLModel, Field
from uuid import UUID, uuid4
from .common import AuditMetadata

class Transaction(AuditMetadata, SQLModel, table=True):
    __tablename__: str = 'transaction'  # type: ignore

    guid: UUID = Field(
        default_factory=uuid4,
        primary_key=True
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
    fiscal_period_guid: UUID | None = Field(
        default=None,
        foreign_key="fiscal_period.guid",
        nullable=True
    )