import fastapi

from app.modules.security.router import SecurityRouter

app = fastapi.FastAPI(
    title='Tiny-Budget API',
    description='Tiny-Budget API',
    root_path='/v1'
)

app.include_router(SecurityRouter())