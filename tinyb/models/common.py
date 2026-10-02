from sqlmodel import Field, text
from datetime import datetime, timezone

class AuditMetadata:

    created_on: datetime = Field(
        default_factory=lambda: datetime.now(timezone.utc),
        nullable=False,
        sa_column_kwargs={'server_default': text('NOW()')},
    )
    
    updated_on: datetime = Field(
        default_factory=lambda: datetime.now(timezone.utc),
        nullable=False,
        sa_column_kwargs={'server_default': text('NOW()')},
    )
