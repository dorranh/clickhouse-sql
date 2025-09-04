"""
Minimal ClickHouse SQL parser bindings.
"""

# Query Kind Constants
QUERY_KIND_NONE: int
QUERY_KIND_SELECT: int
QUERY_KIND_INSERT: int
QUERY_KIND_DELETE: int
QUERY_KIND_UPDATE: int
QUERY_KIND_CREATE: int
QUERY_KIND_DROP: int
QUERY_KIND_ALTER: int
QUERY_KIND_SHOW: int
QUERY_KIND_USE: int
QUERY_KIND_SET: int
QUERY_KIND_EXPLAIN: int

def parse_sql_query_kind(query: str) -> int:
    """Parse a SQL query string and return the query kind as an integer."""
    ...

def get_sql_query_id(query: str) -> str:
    """Parse a SQL query string and return the AST ID as a string."""
    ...