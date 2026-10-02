from pydantic_settings import BaseSettings, SettingsConfigDict
from functools import lru_cache

class EnvironmentSettings(BaseSettings):
    model_config = SettingsConfigDict(
        env_file='.env',
        extra='ignore'
    )

    ENV: str = 'LOCAL'

    DB_CONNECTION_STRING: str = ''

@lru_cache
def get_environment_settings() -> EnvironmentSettings:
    return EnvironmentSettings()

