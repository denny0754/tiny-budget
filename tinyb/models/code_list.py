from sqlmodel import SQLModel, Field
from uuid import UUID, uuid4

from .common import AuditMetadata


class CodeList(AuditMetadata, SQLModel, table=True):
    __tablename__: str = 'code_list'  # type: ignore

    guid: UUID = Field(
        default_factory=uuid4,
        primary_key=True
    )
    list_code: str | None = Field(
        max_length=3,
        nullable=True
    )
    code: str | None = Field(
        max_length=3,
        nullable=True
    )
    label: str | None = Field(
        max_length=200,
        nullable=True
    )
    is_active: bool | None = Field(
        default=None,
        nullable=True
    )
    is_deprecated: bool | None = Field(
        default=None,
        nullable=True
    )
    is_deleted: bool | None = Field(
        default=None,
        nullable=True
    )