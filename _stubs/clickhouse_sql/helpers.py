from clickhouse_sql._clickhouse_sql import IAST

from typing import Type, TypeVar

T = TypeVar('T', bound=IAST)

def find_all(ast: IAST, target_type: Type[T]) -> list[T]:
    """
    Recursively find all AST nodes of a given type using iterative traversal.

    Args:
        ast: The root AST node to search from
        target_type: Python class to match against (e.g., _clickhouse_sql.ASTLiteral)

    Returns:
        List of matching AST nodes
    """
    matches = []
    stack = [ast] if ast else []

    while stack:
        node = stack.pop()

        if node is None:
            continue

        # Check if this node is an instance of the target type
        if isinstance(node, target_type):
            matches.append(node)

        # Add children to stack for processing
        try:
            children = node.getChildren()
            stack.extend(children)
        except AttributeError:
            # Node doesn't have getChildren method
            pass

    return matches