from sqlmodel import SQLModel, Field, JSON
from uuid import UUID, uuid4
from .common import AuditMetadata

class Payee(AuditMetadata, SQLModel, table=True):
    __tablename__: str = 'payee'  # type: ignore

    guid: UUID = Field(
        default_factory=uuid4,
        primary_key=True
    )
    business_partner_guid: UUID | None = Field(
        default=None,
        foreign_key="business_partner.guid",
        nullable=True
    )
    type_guid: UUID | None = Field(
        default=None,
        foreign_key="code_list.guid",
        nullable=True
    )
    status_guid: UUID | None = Field(
        default=None,
        foreign_key="code_list.guid",
        nullable=True
    )
    currency_guid: UUID | None = Field(
        default=None,
        foreign_key="code_list.guid",
        nullable=True
    )
    data: dict | None = Field(
        default=None,
        sa_type=JSON,
        nullable=True
    )