from sqlmodel import SQLModel, Field
from uuid import UUID, uuid4
from .common import AuditMetadata

class TransactionAttachment(AuditMetadata, SQLModel, table=True):
    __tablename__: str = 'transaction_attachment'  # type: ignore

    guid: UUID = Field(
        default_factory=uuid4,
        primary_key=True
    )
    transaction_guid: UUID | None = Field(
        default=None,
        foreign_key="transaction.guid",
        nullable=True
    )
    name: str | None = Field(
        max_length=100,
        nullable=True
    )
    data: bytes | None = Field(
        default=None,
        nullable=True
    )
    file_type_guid: UUID | None = Field(
        default=None,
        foreign_key="code_list.guid",
        nullable=True
    )