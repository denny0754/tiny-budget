from sqlmodel import SQLModel, Field
from uuid import UUID, uuid4
from decimal import Decimal
from .common import AuditMetadata

class TransactionItem(AuditMetadata, SQLModel, table=True):
    __tablename__: str = 'transaction_item'  # type: ignore

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
    description: str | None = Field(
        default=None,
        nullable=True
    )
    budget_guid: UUID | None = Field(
        default=None,
        foreign_key="budget.guid",
        nullable=True
    )
    product_guid: UUID | None = Field(
        default=None,
        foreign_key="product.guid",
        nullable=True
    )
    status_guid: UUID | None = Field(
        default=None,
        foreign_key="code_list.guid",
        nullable=True
    )
    account_guid: UUID | None = Field(
        default=None,
        foreign_key="account.guid",
        nullable=True
    )
    payee_guid: UUID | None = Field(
        default=None,
        foreign_key="payee.guid",
        nullable=True
    )
    quantity: Decimal | None = Field(
        default=None,
        nullable=True
    )
    gross_value: Decimal | None = Field(
        default=None,
        nullable=True
    )