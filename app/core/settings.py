from pydantic_settings import BaseSettings, SettingsConfigDict
from functools import lru_cache

class EnvironmentSettings(BaseSettings):
    model_config = SettingsConfigDict(
        env_file='.env',
        extra='ignore'
    )

    ENV: str = 'LOCAL'

    DB_CONNECTION_STRING: str = ''

    JWT_SECRET_KEY: str = ''

    JWT_EXPIRATION_SECONDS: int = 900

@lru_cache
def get_environment_settings() -> EnvironmentSettings:
    return EnvironmentSettings()

