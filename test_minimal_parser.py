#!/usr/bin/env python3
"""
Simple test script for the minimal ClickHouse SQL parser bindings.
"""

import _clickhouse_sql

def test_query_parsing():
    """Test parsing different types of SQL queries."""
    
    test_queries = [
        ("SELECT * FROM table", "SELECT"),
        ("INSERT INTO table VALUES (1, 'test')", "INSERT"),
        ("CREATE TABLE test (id INT)", "CREATE"),
        ("DROP TABLE test", "DROP"),
        ("ALTER TABLE test ADD COLUMN name STRING", "ALTER"),
        ("SHOW TABLES", "SHOW"),
        ("USE database", "USE"),
        ("SET max_threads = 4", "SET"),
        ("EXPLAIN SELECT * FROM table", "EXPLAIN"),
    ]
    
    # Print available query kind constants
    print("Available Query Kind Constants:")
    for attr in dir(_clickhouse_sql):
        if attr.startswith("QUERY_KIND_"):
            value = getattr(_clickhouse_sql, attr)
            print(f"  {attr} = {value}")
    print()
    
    # Test parsing queries
    print("Testing Query Parsing:")
    for query, expected_type in test_queries:
        try:
            query_kind = _clickhouse_sql.parse_sql_query_kind(query)
            query_id = _clickhouse_sql.get_sql_query_id(query)
            print(f"Query: {query}")
            print(f"  Kind: {query_kind} (expected: {expected_type})")
            print(f"  ID: {query_id}")
            print()
        except Exception as e:
            print(f"Error parsing '{query}': {e}")
            print()

if __name__ == "__main__":
    test_query_parsing()
