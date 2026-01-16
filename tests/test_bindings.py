import pytest

from clickhouse_sql import (
    IAST,
    parse_query,
    parse_sql_query_kind,
    get_sql_query_id,
    QUERY_KIND_SELECT,
    QUERY_KIND_INSERT,
    QUERY_KIND_CREATE,
    QUERY_KIND_DROP,
    QUERY_KIND_ALTER,
    QUERY_KIND_SHOW,
    QUERY_KIND_USE,
    QUERY_KIND_SET,
    QUERY_KIND_EXPLAIN,
)
from clickhouse_sql import nodes
from clickhouse_sql.helpers import find_all


@pytest.mark.parametrize(
    ("query", "expected_kind"),
    [
        ("SELECT * FROM table", QUERY_KIND_SELECT),
        ("CREATE TABLE test (id Int32)", QUERY_KIND_CREATE),
        ("DROP TABLE test", QUERY_KIND_DROP),
        ("ALTER TABLE test ADD COLUMN name String", QUERY_KIND_ALTER),
        ("SHOW TABLES", QUERY_KIND_SHOW),
        ("USE database", QUERY_KIND_USE),
        ("SET max_threads = 4", QUERY_KIND_SET),
        ("EXPLAIN SELECT * FROM table", QUERY_KIND_EXPLAIN),
    ],
)
def test_query_kind_parsing(query: str, expected_kind: int) -> None:
    assert parse_sql_query_kind(query) == expected_kind
    assert get_sql_query_id(query)


def test_parse_query_returns_ast() -> None:
    ast = parse_query("SELECT 1")
    assert isinstance(ast, IAST)


def test_find_table_identifier() -> None:
    ast = parse_query("SELECT * FROM my_db.my_table WHERE foo = 'bar'")
    matches = find_all(ast, nodes.ASTTableIdentifier)
    assert matches


def test_create_table_cluster() -> None:
    ast = parse_query("CREATE TABLE foo ON CLUSTER 'foobar' (a String) ORDER BY a")
    create_nodes = find_all(ast, nodes.ASTCreateQuery)
    assert create_nodes
    assert create_nodes[0].getCluster() == "foobar"
