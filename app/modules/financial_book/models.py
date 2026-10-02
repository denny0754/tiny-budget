import sqlmodel
import uuid
import datetime

class FinancialBook(sqlmodel.SQLModel, table=True):

    __tablename__: str = 'financial_book' #type: ignore

    id: uuid.UUID = sqlmodel.Field(
        primary_key=True,
        default_factory=uuid.uuid4
    )

    name: str = sqlmodel.Field(
        max_length=100,
        nullable=False
    )

    description: str = sqlmodel.Field(
        nullable=True
    )

    status_code: uuid.UUID = sqlmodel.Field(
        foreign_key='financial_book_status.code',
        default='OPN'
    )

    created_on: datetime.datetime = sqlmodel.Field(
        default_factory=lambda: datetime.datetime.now(datetime.timezone.utc)
    )

    updated_on: datetime.datetime = sqlmodel.Field(
        default_factory=lambda: datetime.datetime.now(datetime.timezone.utc)
    )

'''
Values for FinancialBookStatus:
    - OPN --> Open --> Data can be viewed, added, modified and deleted
    - CLS --> Closed --> Data can be viewed, not added, modified or deleted.
    - ARC --> Archived --> Data can be viewed in summary. Most have been archived and anonymized(mostly descriptions)
    - DEL --> Deleted --> Data related to the Book has been completely deleted.
'''
class FinancialBookStatus(sqlmodel.SQLModel, table=True):

    __tablename__: str = 'financial_book_status' #type: ignore

    code: str = sqlmodel.Field(
        primary_key=True,
        max_length=3
    )

    label: str = sqlmodel.Field(
        max_length=30
    )

    long_label: str = sqlmodel.Field(
        max_length=100
    )

    created_on: datetime.datetime = sqlmodel.Field(
        default_factory=lambda: datetime.datetime.now(datetime.timezone.utc)
    )

    updated_on: datetime.datetime = sqlmodel.Field(
        default_factory=lambda: datetime.datetime.now(datetime.timezone.utc)
    )