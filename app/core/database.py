from __future__ import annotations
from functools import lru_cache
from collections.abc import Generator
from sqlmodel import Session as DatabaseSession, create_engine

from .settings import get_environment_settings

def get_db_session() -> Generator[DatabaseSession]:
    @lru_cache
    def get_db_engine():  # type: ignore[no-untyped-def]
        """Process-wide cached SQLAlchemy engine for the Control Plane DB."""
        return create_engine(get_environment_settings().DB_CONNECTION_STRING)

    with DatabaseSession(get_db_engine()) as session:
        yield session

