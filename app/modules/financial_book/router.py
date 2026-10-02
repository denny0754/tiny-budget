import fastapi

class FinancialBookRouter(fastapi.APIRouter):

    def __init__(self):

        super().__init__(
            prefix='/financial-book'
        )

        self.add_api_route(
            endpoint=self.create_book,
            path='/',
            methods=['POST'],
            status_code=fastapi.status.HTTP_201_CREATED
        )

        self.add_api_route(
            endpoint=self.update_book,
            path='/',
            methods=['PATCH'],
            status_code=fastapi.status.HTTP_200_OK
        )

        self.add_api_route(
            endpoint=self.delete_book,
            path='/',
            methods=['DELETE'],
            status_code=fastapi.status.HTTP_200_OK
        )

    # POST
    def create_book(self):
        ...

    # PATCH
    def update_book(self):
        ...

    # Helper Function
    def close_book(self):
        ...

    # Helper Function
    def archive_book(self):
        ...

    # DELETE
    def delete_book(self):
        ...