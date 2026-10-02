from sqlmodel import SQLModel, Field

from uuid import UUID, uuid4

from .common import AuditMetadata

class IdentityAccess(AuditMetadata, SQLModel, table=True):
    __tablename__: str = 'identity_access'  # type: ignore

    guid: UUID = Field(
        default_factory=uuid4,
        primary_key=True
    )
    identity_guid: UUID | None = Field(
        default=None,
        foreign_key="identity.guid",
        nullable=True
    )
    financial_book_guid: UUID | None = Field(
        default=None,
        foreign_key="financial_book.guid",
        nullable=True
    )
    role_guid: UUID | None = Field(
        default=None,
        foreign_key="role.guid",
        nullable=True
    )