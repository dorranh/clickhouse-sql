"""ClickHouse SQL AST node types"""

# Note: This module re-exports IAST types for convenience. We could
# probably also fix the namespaces in the nanobind module directly
# to make this automatic.

from clickhouse_sql._clickhouse_sql import (
    # Base classes
    IAST,
    ASTWithAlias,
    ASTQueryWithOutput,
    ASTQueryWithTableAndOutput,

    # Expression and literal nodes
    ASTLiteral,
    ASTIdentifier,
    ASTTableIdentifier,
    ASTFunction,
    ASTSubquery,
    ASTQueryParameter,
    ASTAsterisk,
    ASTQualifiedAsterisk,

    # Column and table structure
    ASTExpressionList,
    ASTColumnDeclaration,
    ASTNameTypePair,
    ASTDataType,
    ASTCollation,
    ASTConstraintDeclaration,
    ASTIndexDeclaration,
    ASTForeignKeyDeclaration,
    ASTProjectionDeclaration,
    ASTStatisticsDeclaration,
    ASTDictionaryAttributeDeclaration,

    # Column matchers and transformers
    ASTColumnsRegexpMatcher,
    ASTColumnsListMatcher,
    ASTQualifiedColumnsRegexpMatcher,
    ASTQualifiedColumnsListMatcher,
    ASTColumnsTransformerList,
    IASTColumnsTransformer,
    ASTColumnsApplyTransformer,
    ASTColumnsExceptTransformer,
    ASTColumnsReplaceTransformer,

    # Query types - SELECT
    ASTSelectQuery,
    ASTSelectWithUnionQuery,
    ASTSelectIntersectExceptQuery,
    ASTProjectionSelectQuery,

    # DDL queries
    ASTStorage,
    ASTColumns,
    ASTCreateQuery,
    ASTCreateIndexQuery,
    ASTCreateFunctionQuery,
    ASTCreateWorkloadQuery,
    ASTCreateResourceQuery,
    ASTCreateNamedCollectionQuery,
    ASTDropQuery,
    ASTDropIndexQuery,
    ASTDropFunctionQuery,
    ASTDropWorkloadQuery,
    ASTDropResourceQuery,
    ASTDropNamedCollectionQuery,
    ASTAlterCommand,
    ASTAlterQuery,
    ASTAlterNamedCollectionQuery,
    ASTRenameQuery,

    # DML queries
    ASTInsertQuery,
    ASTUpdateQuery,
    ASTDeleteQuery,

    # Utility queries
    ASTUseQuery,
    ASTSetQuery,
    ASTSystemQuery,
    ASTOptimizeQuery,
    ASTKillQueryQuery,
    ASTExplainQuery,
    ASTDescribeCacheQuery,
    ASTUndropQuery,
    ASTWatchQuery,
    ASTExternalDDLQuery,
    ASTTransactionControl,

    # SHOW queries
    ASTShowTablesQuery,
    ASTShowColumnsQuery,
    ASTShowIndexesQuery,
    ASTShowFunctionsQuery,
    ASTShowSettingQuery,
    ASTDescribeQuery,
    ASTExistsDatabaseQuery,
    ASTShowCreateDatabaseQuery,

    # Utility components
    ASTWithElement,
    ASTAssignment,
    ASTOrderByElement,
    ASTStorageOrderByElement,
    ASTSampleRatio,
    ASTTimeInterval,
    ASTInterpolateElement,
    ASTParallelWithQuery,
    ASTViewTargets,
    ASTTableOverride,
    ASTTableOverrideList,
    ASTDatabaseOrNone,
    ASTObjectTypeArgument,
    ASTPair,
    ASTFunctionWithKeyValueArguments,

    # Storage and engine components
    ASTDictionary,
    ASTDictionaryLifetime,
    ASTDictionaryLayout,
    ASTDictionaryRange,
    ASTDictionarySettings,
    ASTPartition,
    ASTTTLElement,
    ASTSQLSecurity,
    ASTRefreshStrategy,

    # Backup and restore
    ASTBackupQuery,

    # Access control (RBAC)
    ASTCreateUserQuery,
    ASTCreateRoleQuery,
    ASTCreateQuotaQuery,
    ASTCreateRowPolicyQuery,
    ASTCreateSettingsProfileQuery,
    ASTDropAccessEntityQuery,
    ASTGrantQuery,
    ASTSetRoleQuery,
    ASTCheckGrantQuery,
    ASTMoveAccessEntityQuery,
    ASTShowAccessEntitiesQuery,
    ASTShowGrantsQuery,
    ASTShowCreateAccessEntityQuery,
    ASTUserNameWithHost,
    ASTUserNamesWithHost,
    ASTRolesOrUsersSet,
    ASTRowPolicyName,
    ASTRowPolicyNames,
    ASTSettingsProfileElement,
    ASTSettingsProfileElements,
    ASTAlterSettingsProfileElements,
    ASTAuthenticationData,
    ASTPublicSSHKey,

    # Prepared statements
    ASTPreparedStatement,
    ASTExecute,
    ASTDeallocate,

    # MySQL compatibility
    MySQLASTCreateQuery,
    MySQLASTAlterQuery,
    MySQLASTAlterCommand,
    MySQLASTDropQuery,
    MySQLASTCreateDefines,
    MySQLASTDeclareColumn,
    MySQLASTDeclareIndex,
    MySQLASTDeclareConstraint,
    MySQLASTDeclarePartition,
    MySQLASTDeclarePartitionOptions,
    MySQLASTDeclareSubPartition,
    MySQLASTDeclareReference,
    MySQLASTDeclareOptions,
)

# Define __all__ for better IDE support and explicit exports
__all__ = [
    # Base classes
    "IAST",
    "ASTWithAlias",
    "ASTQueryWithOutput",
    "ASTQueryWithTableAndOutput",

    # Expression and literal nodes
    "ASTLiteral",
    "ASTIdentifier",
    "ASTTableIdentifier",
    "ASTFunction",
    "ASTSubquery",
    "ASTQueryParameter",
    "ASTAsterisk",
    "ASTQualifiedAsterisk",

    # Column and table structure
    "ASTExpressionList",
    "ASTColumnDeclaration",
    "ASTNameTypePair",
    "ASTDataType",
    "ASTCollation",
    "ASTConstraintDeclaration",
    "ASTIndexDeclaration",
    "ASTForeignKeyDeclaration",
    "ASTProjectionDeclaration",
    "ASTStatisticsDeclaration",
    "ASTDictionaryAttributeDeclaration",

    # Column matchers and transformers
    "ASTColumnsRegexpMatcher",
    "ASTColumnsListMatcher",
    "ASTQualifiedColumnsRegexpMatcher",
    "ASTQualifiedColumnsListMatcher",
    "ASTColumnsTransformerList",
    "IASTColumnsTransformer",
    "ASTColumnsApplyTransformer",
    "ASTColumnsExceptTransformer",
    "ASTColumnsReplaceTransformer",

    # Query types - SELECT
    "ASTSelectQuery",
    "ASTSelectWithUnionQuery",
    "ASTSelectIntersectExceptQuery",
    "ASTProjectionSelectQuery",

    # DDL queries
    "ASTStorage",
    "ASTColumns",
    "ASTCreateQuery",
    "ASTCreateIndexQuery",
    "ASTCreateFunctionQuery",
    "ASTCreateWorkloadQuery",
    "ASTCreateResourceQuery",
    "ASTCreateNamedCollectionQuery",
    "ASTDropQuery",
    "ASTDropIndexQuery",
    "ASTDropFunctionQuery",
    "ASTDropWorkloadQuery",
    "ASTDropResourceQuery",
    "ASTDropNamedCollectionQuery",
    "ASTAlterCommand",
    "ASTAlterQuery",
    "ASTAlterNamedCollectionQuery",
    "ASTRenameQuery",

    # DML queries
    "ASTInsertQuery",
    "ASTUpdateQuery",
    "ASTDeleteQuery",

    # Utility queries
    "ASTUseQuery",
    "ASTSetQuery",
    "ASTSystemQuery",
    "ASTOptimizeQuery",
    "ASTKillQueryQuery",
    "ASTExplainQuery",
    "ASTDescribeCacheQuery",
    "ASTUndropQuery",
    "ASTWatchQuery",
    "ASTExternalDDLQuery",
    "ASTTransactionControl",

    # SHOW queries
    "ASTShowTablesQuery",
    "ASTShowColumnsQuery",
    "ASTShowIndexesQuery",
    "ASTShowFunctionsQuery",
    "ASTShowSettingQuery",
    "ASTDescribeQuery",
    "ASTExistsDatabaseQuery",
    "ASTShowCreateDatabaseQuery",

    # Utility components
    "ASTWithElement",
    "ASTAssignment",
    "ASTOrderByElement",
    "ASTStorageOrderByElement",
    "ASTSampleRatio",
    "ASTTimeInterval",
    "ASTInterpolateElement",
    "ASTParallelWithQuery",
    "ASTViewTargets",
    "ASTTableOverride",
    "ASTTableOverrideList",
    "ASTDatabaseOrNone",
    "ASTObjectTypeArgument",
    "ASTPair",
    "ASTFunctionWithKeyValueArguments",

    # Storage and engine components
    "ASTDictionary",
    "ASTDictionaryLifetime",
    "ASTDictionaryLayout",
    "ASTDictionaryRange",
    "ASTDictionarySettings",
    "ASTPartition",
    "ASTTTLElement",
    "ASTSQLSecurity",
    "ASTRefreshStrategy",

    # Backup and restore
    "ASTBackupQuery",

    # Access control (RBAC)
    "ASTCreateUserQuery",
    "ASTCreateRoleQuery",
    "ASTCreateQuotaQuery",
    "ASTCreateRowPolicyQuery",
    "ASTCreateSettingsProfileQuery",
    "ASTDropAccessEntityQuery",
    "ASTGrantQuery",
    "ASTSetRoleQuery",
    "ASTCheckGrantQuery",
    "ASTMoveAccessEntityQuery",
    "ASTShowAccessEntitiesQuery",
    "ASTShowGrantsQuery",
    "ASTShowCreateAccessEntityQuery",
    "ASTUserNameWithHost",
    "ASTUserNamesWithHost",
    "ASTRolesOrUsersSet",
    "ASTRowPolicyName",
    "ASTRowPolicyNames",
    "ASTSettingsProfileElement",
    "ASTSettingsProfileElements",
    "ASTAlterSettingsProfileElements",
    "ASTAuthenticationData",
    "ASTPublicSSHKey",

    # Prepared statements
    "ASTPreparedStatement",
    "ASTExecute",
    "ASTDeallocate",

    # MySQL compatibility
    "MySQLASTCreateQuery",
    "MySQLASTAlterQuery",
    "MySQLASTAlterCommand",
    "MySQLASTDropQuery",
    "MySQLASTCreateDefines",
    "MySQLASTDeclareColumn",
    "MySQLASTDeclareIndex",
    "MySQLASTDeclareConstraint",
    "MySQLASTDeclarePartition",
    "MySQLASTDeclarePartitionOptions",
    "MySQLASTDeclareSubPartition",
    "MySQLASTDeclareReference",
    "MySQLASTDeclareOptions",
]
