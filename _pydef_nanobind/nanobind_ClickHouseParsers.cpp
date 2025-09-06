#include <nanobind/nanobind.h>
#include <nanobind/trampoline.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/shared_ptr.h>
#include <nanobind/stl/unique_ptr.h>
#include <nanobind/stl/map.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/ndarray.h>

// Prevent Python macro conflicts with ClickHouse
#ifdef READONLY
#undef READONLY
#endif

// ClickHouse Headers
#include <Parsers/parseQuery.h>
#include <Parsers/ParserQuery.h>
#include <Parsers/IAST.h>

// Core AST Headers
#include <Parsers/ASTWithAlias.h>
#include <Parsers/ASTWithElement.h>
#include <Parsers/ASTQueryWithOutput.h>
#include <Parsers/ASTQueryWithTableAndOutput.h>

// Expression and Literal Headers
#include <Parsers/ASTLiteral.h>
#include <Parsers/ASTIdentifier.h>
#include <Parsers/ASTFunction.h>
#include <Parsers/ASTSubquery.h>
#include <Parsers/ASTQueryParameter.h>
#include <Parsers/ASTAsterisk.h>
#include <Parsers/ASTQualifiedAsterisk.h>

// Column and Table Structure Headers
#include <Parsers/ASTExpressionList.h>
#include <Parsers/ASTColumnDeclaration.h>
#include <Parsers/ASTNameTypePair.h>
#include <Parsers/ASTDataType.h>
#include <Parsers/ASTCollation.h>
#include <Parsers/ASTConstraintDeclaration.h>
#include <Parsers/ASTIndexDeclaration.h>
#include <Parsers/ASTForeignKeyDeclaration.h>
#include <Parsers/ASTProjectionDeclaration.h>
#include <Parsers/ASTStatisticsDeclaration.h>
#include <Parsers/ASTDictionaryAttributeDeclaration.h>

// Column Matchers and Transformers
#include <Parsers/ASTColumnsMatcher.h>
#include <Parsers/ASTColumnsTransformers.h>

// Query Headers
#include <Parsers/ASTSelectQuery.h>
#include <Parsers/ASTSelectWithUnionQuery.h>
#include <Parsers/ASTSelectIntersectExceptQuery.h>
#include <Parsers/ASTProjectionSelectQuery.h>

// DDL Query Headers
#include <Parsers/ASTCreateQuery.h>
#include <Parsers/ASTCreateIndexQuery.h>
#include <Parsers/ASTCreateFunctionQuery.h>
#include <Parsers/ASTCreateWorkloadQuery.h>
#include <Parsers/ASTCreateResourceQuery.h>
#include <Parsers/ASTCreateNamedCollectionQuery.h>
#include <Parsers/ASTDropQuery.h>
#include <Parsers/ASTDropIndexQuery.h>
#include <Parsers/ASTDropFunctionQuery.h>
#include <Parsers/ASTDropWorkloadQuery.h>
#include <Parsers/ASTDropResourceQuery.h>
#include <Parsers/ASTDropNamedCollectionQuery.h>
#include <Parsers/ASTAlterQuery.h>
#include <Parsers/ASTAlterNamedCollectionQuery.h>
#include <Parsers/ASTRenameQuery.h>

// DML Query Headers
#include <Parsers/ASTInsertQuery.h>
#include <Parsers/ASTUpdateQuery.h>
#include <Parsers/ASTDeleteQuery.h>

// Utility Query Headers
#include <Parsers/ASTUseQuery.h>
#include <Parsers/ASTSetQuery.h>
#include <Parsers/ASTSystemQuery.h>
#include <Parsers/ASTOptimizeQuery.h>
#include <Parsers/ASTKillQueryQuery.h>
#include <Parsers/ASTExplainQuery.h>
#include <Parsers/ASTDescribeCacheQuery.h>
#include <Parsers/ASTUndropQuery.h>
#include <Parsers/ASTWatchQuery.h>
#include <Parsers/ASTExternalDDLQuery.h>
#include <Parsers/ASTTransactionControl.h>

// SHOW Query Headers
#include <Parsers/ASTShowTablesQuery.h>
#include <Parsers/ASTShowColumnsQuery.h>
#include <Parsers/ASTShowIndexesQuery.h>
#include <Parsers/ASTShowFunctionsQuery.h>
#include <Parsers/ASTShowSettingQuery.h>
#include <Parsers/TablePropertiesQueriesASTs.h>

// Access Control Headers
#include <Parsers/Access/ASTCreateUserQuery.h>
#include <Parsers/Access/ASTCreateRoleQuery.h>
#include <Parsers/Access/ASTCreateQuotaQuery.h>
#include <Parsers/Access/ASTCreateRowPolicyQuery.h>
#include <Parsers/Access/ASTCreateSettingsProfileQuery.h>
#include <Parsers/Access/ASTDropAccessEntityQuery.h>
#include <Parsers/Access/ASTGrantQuery.h>
#include <Parsers/Access/ASTSetRoleQuery.h>
#include <Parsers/Access/ASTCheckGrantQuery.h>
#include <Parsers/Access/ASTMoveAccessEntityQuery.h>
#include <Parsers/Access/ASTShowAccessEntitiesQuery.h>
#include <Parsers/Access/ASTShowGrantsQuery.h>
#include <Parsers/Access/ASTShowCreateAccessEntityQuery.h>
#include <Parsers/Access/ASTUserNameWithHost.h>
#include <Parsers/Access/ASTRolesOrUsersSet.h>
#include <Parsers/Access/ASTRowPolicyName.h>
#include <Parsers/Access/ASTSettingsProfileElement.h>
#include <Parsers/Access/ASTAuthenticationData.h>
#include <Parsers/Access/ASTPublicSSHKey.h>

// Storage and Engine Headers
#include <Parsers/ASTDictionary.h>
#include <Parsers/ASTPartition.h>
#include <Parsers/ASTTTLElement.h>
#include <Parsers/ASTSQLSecurity.h>
#include <Parsers/ASTRefreshStrategy.h>

// Backup Headers
#include <Parsers/ASTBackupQuery.h>

// Utility Component Headers
#include <Parsers/ASTAssignment.h>
#include <Parsers/ASTOrderByElement.h>
#include <Parsers/ASTSampleRatio.h>
#include <Parsers/ASTTimeInterval.h>
#include <Parsers/ASTInterpolateElement.h>
#include <Parsers/ASTParallelWithQuery.h>
#include <Parsers/ASTViewTargets.h>
#include <Parsers/ASTTableOverrides.h>
#include <Parsers/ASTDatabaseOrNone.h>
#include <Parsers/ASTObjectTypeArgument.h>
#include <Parsers/ASTFunctionWithKeyValueArguments.h>

// MySQL Compatibility Headers
#include <Parsers/MySQL/ASTCreateQuery.h>
#include <Parsers/MySQL/ASTAlterQuery.h>
#include <Parsers/MySQL/ASTAlterCommand.h>
#include <Parsers/MySQL/ASTDropQuery.h>
#include <Parsers/MySQL/ASTCreateDefines.h>
#include <Parsers/MySQL/ASTDeclareColumn.h>
#include <Parsers/MySQL/ASTDeclareIndex.h>
#include <Parsers/MySQL/ASTDeclareConstraint.h>
#include <Parsers/MySQL/ASTDeclarePartition.h>
#include <Parsers/MySQL/ASTDeclarePartitionOptions.h>
#include <Parsers/MySQL/ASTDeclareSubPartition.h>
#include <Parsers/MySQL/ASTDeclareReference.h>
#include <Parsers/MySQL/ASTDeclareOption.h>

// Prepared Statement Headers
#include <Parsers/ParserPreparedStatement.h>

namespace nb = nanobind;

// Simple wrapper function for parsing queries
int parse_sql_query_kind(const std::string& query) {
    try {
        const char* query_begin = query.c_str();
        const char* query_end = query_begin + query.size();
        DB::ParserQuery parser(query_end);
        auto ast = DB::parseQuery(parser, query, 1000000, 1000, 1000);
        return static_cast<int>(ast->getQueryKind());
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to parse query: " + std::string(e.what()));
    }
}

// Get AST ID for a query
std::string get_sql_query_id(const std::string& query) {
    try {
        const char* query_begin = query.c_str();
        const char* query_end = query_begin + query.size();
        DB::ParserQuery parser(query_end);
        auto ast = DB::parseQuery(parser, query, 1000000, 1000, 1000);
        return ast->getID('_');
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to parse query: " + std::string(e.what()));
    }
}

// Parse query and return IAST node
std::shared_ptr<DB::IAST> parse_query(const std::string& query) {
    try {
        const char* query_begin = query.c_str();
        const char* query_end = query_begin + query.size();
        DB::ParserQuery parser(query_end);
        auto ast = DB::parseQuery(parser, query, 1000000, 1000, 1000);
        return ast;
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to parse query: " + std::string(e.what()));
    }
}

// Expose QueryKind enum values as constants
NB_MODULE(_clickhouse_sql, m) {
    m.doc() = "Minimal ClickHouse SQL parser bindings";

    // Expose the simple parse function
    m.def("parse_sql_query_kind", &parse_sql_query_kind,
          nb::arg("query"),
          "Parse a SQL query string and return the query kind as an integer");

    // Expose the get_sql_query_id function
    m.def("get_sql_query_id", &get_sql_query_id,
          nb::arg("query"),
          "Parse a SQL query string and return the AST ID as a string");

    // Expose the parse_query function
    m.def("parse_query", &parse_query,
          nb::arg("query"),
          "Parse a SQL query string and return the IAST node");

    // Expose QueryKind enum values as module constants
    m.attr("QUERY_KIND_NONE") = static_cast<int>(DB::IAST::QueryKind::None);
    m.attr("QUERY_KIND_SELECT") = static_cast<int>(DB::IAST::QueryKind::Select);
    m.attr("QUERY_KIND_INSERT") = static_cast<int>(DB::IAST::QueryKind::Insert);
    m.attr("QUERY_KIND_DELETE") = static_cast<int>(DB::IAST::QueryKind::Delete);
    m.attr("QUERY_KIND_UPDATE") = static_cast<int>(DB::IAST::QueryKind::Update);
    m.attr("QUERY_KIND_CREATE") = static_cast<int>(DB::IAST::QueryKind::Create);
    m.attr("QUERY_KIND_DROP") = static_cast<int>(DB::IAST::QueryKind::Drop);
    m.attr("QUERY_KIND_ALTER") = static_cast<int>(DB::IAST::QueryKind::Alter);
    m.attr("QUERY_KIND_SHOW") = static_cast<int>(DB::IAST::QueryKind::Show);
    m.attr("QUERY_KIND_USE") = static_cast<int>(DB::IAST::QueryKind::Use);
    m.attr("QUERY_KIND_SET") = static_cast<int>(DB::IAST::QueryKind::Set);
    m.attr("QUERY_KIND_EXPLAIN") = static_cast<int>(DB::IAST::QueryKind::Explain);

    // Base AST Classes
    nb::class_<DB::IAST>(m, "IAST")
        .def("getID", [](const DB::IAST& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTWithAlias, DB::IAST>(m, "ASTWithAlias")
        .def("getID", [](const DB::ASTWithAlias& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTQueryWithOutput, DB::IAST>(m, "ASTQueryWithOutput")
        .def("getID", [](const DB::ASTQueryWithOutput& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTQueryWithTableAndOutput, DB::ASTQueryWithOutput>(m, "ASTQueryWithTableAndOutput")
        .def("getID", [](const DB::ASTQueryWithTableAndOutput& self) { return self.getID('_'); }, "Get AST node ID");

    // Expression and Literal Nodes
    nb::class_<DB::ASTLiteral, DB::ASTWithAlias>(m, "ASTLiteral")
        .def("getID", [](const DB::ASTLiteral& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTIdentifier, DB::ASTWithAlias>(m, "ASTIdentifier")
        .def("getID", [](const DB::ASTIdentifier& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTTableIdentifier, DB::ASTIdentifier>(m, "ASTTableIdentifier")
        .def("getID", [](const DB::ASTTableIdentifier& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTFunction, DB::ASTWithAlias>(m, "ASTFunction")
        .def("getID", [](const DB::ASTFunction& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTSubquery, DB::ASTWithAlias>(m, "ASTSubquery")
        .def("getID", [](const DB::ASTSubquery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTQueryParameter, DB::ASTWithAlias>(m, "ASTQueryParameter")
        .def("getID", [](const DB::ASTQueryParameter& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTAsterisk, DB::IAST>(m, "ASTAsterisk")
        .def("getID", [](const DB::ASTAsterisk& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTQualifiedAsterisk, DB::IAST>(m, "ASTQualifiedAsterisk")
        .def("getID", [](const DB::ASTQualifiedAsterisk& self) { return self.getID('_'); }, "Get AST node ID");

    // Column and Table Structure
    nb::class_<DB::ASTExpressionList, DB::IAST>(m, "ASTExpressionList")
        .def("getID", [](const DB::ASTExpressionList& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTColumnDeclaration, DB::IAST>(m, "ASTColumnDeclaration")
        .def("getID", [](const DB::ASTColumnDeclaration& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTNameTypePair, DB::IAST>(m, "ASTNameTypePair")
        .def("getID", [](const DB::ASTNameTypePair& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDataType, DB::IAST>(m, "ASTDataType")
        .def("getID", [](const DB::ASTDataType& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTCollation, DB::IAST>(m, "ASTCollation")
        .def("getID", [](const DB::ASTCollation& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTConstraintDeclaration, DB::IAST>(m, "ASTConstraintDeclaration")
        .def("getID", [](const DB::ASTConstraintDeclaration& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTIndexDeclaration, DB::IAST>(m, "ASTIndexDeclaration")
        .def("getID", [](const DB::ASTIndexDeclaration& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTForeignKeyDeclaration, DB::IAST>(m, "ASTForeignKeyDeclaration")
        .def("getID", [](const DB::ASTForeignKeyDeclaration& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTProjectionDeclaration, DB::IAST>(m, "ASTProjectionDeclaration")
        .def("getID", [](const DB::ASTProjectionDeclaration& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTStatisticsDeclaration, DB::IAST>(m, "ASTStatisticsDeclaration")
        .def("getID", [](const DB::ASTStatisticsDeclaration& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDictionaryAttributeDeclaration, DB::IAST>(m, "ASTDictionaryAttributeDeclaration")
        .def("getID", [](const DB::ASTDictionaryAttributeDeclaration& self) { return self.getID('_'); }, "Get AST node ID");

    // Column Matchers and Transformers
    nb::class_<DB::ASTColumnsRegexpMatcher, DB::IAST>(m, "ASTColumnsRegexpMatcher")
        .def("getID", [](const DB::ASTColumnsRegexpMatcher& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTColumnsListMatcher, DB::IAST>(m, "ASTColumnsListMatcher")
        .def("getID", [](const DB::ASTColumnsListMatcher& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTQualifiedColumnsRegexpMatcher, DB::IAST>(m, "ASTQualifiedColumnsRegexpMatcher")
        .def("getID", [](const DB::ASTQualifiedColumnsRegexpMatcher& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTQualifiedColumnsListMatcher, DB::IAST>(m, "ASTQualifiedColumnsListMatcher")
        .def("getID", [](const DB::ASTQualifiedColumnsListMatcher& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTColumnsTransformerList, DB::IAST>(m, "ASTColumnsTransformerList")
        .def("getID", [](const DB::ASTColumnsTransformerList& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::IASTColumnsTransformer, DB::IAST>(m, "IASTColumnsTransformer")
        .def("getID", [](const DB::IASTColumnsTransformer& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTColumnsApplyTransformer, DB::IASTColumnsTransformer>(m, "ASTColumnsApplyTransformer")
        .def("getID", [](const DB::ASTColumnsApplyTransformer& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTColumnsExceptTransformer, DB::IASTColumnsTransformer>(m, "ASTColumnsExceptTransformer")
        .def("getID", [](const DB::ASTColumnsExceptTransformer& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTColumnsReplaceTransformer, DB::IASTColumnsTransformer>(m, "ASTColumnsReplaceTransformer")
        .def("getID", [](const DB::ASTColumnsReplaceTransformer& self) { return self.getID('_'); }, "Get AST node ID");

    // Query Types - SELECT
    nb::class_<DB::ASTSelectQuery, DB::IAST>(m, "ASTSelectQuery")
        .def("getID", [](const DB::ASTSelectQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTSelectWithUnionQuery, DB::ASTQueryWithOutput>(m, "ASTSelectWithUnionQuery")
        .def("getID", [](const DB::ASTSelectWithUnionQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTSelectIntersectExceptQuery, DB::ASTSelectQuery>(m, "ASTSelectIntersectExceptQuery")
        .def("getID", [](const DB::ASTSelectIntersectExceptQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTProjectionSelectQuery, DB::IAST>(m, "ASTProjectionSelectQuery")
        .def("getID", [](const DB::ASTProjectionSelectQuery& self) { return self.getID('_'); }, "Get AST node ID");

    // DDL Queries
    nb::class_<DB::ASTStorage, DB::IAST>(m, "ASTStorage")
        .def("getID", [](const DB::ASTStorage& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTColumns, DB::IAST>(m, "ASTColumns")
        .def("getID", [](const DB::ASTColumns& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTCreateQuery, DB::ASTQueryWithTableAndOutput>(m, "ASTCreateQuery")
        .def("getID", [](const DB::ASTCreateQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTCreateIndexQuery, DB::ASTQueryWithTableAndOutput>(m, "ASTCreateIndexQuery")
        .def("getID", [](const DB::ASTCreateIndexQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTCreateFunctionQuery, DB::IAST>(m, "ASTCreateFunctionQuery")
        .def("getID", [](const DB::ASTCreateFunctionQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTCreateWorkloadQuery, DB::IAST>(m, "ASTCreateWorkloadQuery")
        .def("getID", [](const DB::ASTCreateWorkloadQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTCreateResourceQuery, DB::IAST>(m, "ASTCreateResourceQuery")
        .def("getID", [](const DB::ASTCreateResourceQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTCreateNamedCollectionQuery, DB::IAST>(m, "ASTCreateNamedCollectionQuery")
        .def("getID", [](const DB::ASTCreateNamedCollectionQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDropQuery, DB::ASTQueryWithTableAndOutput>(m, "ASTDropQuery")
        .def("getID", [](const DB::ASTDropQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDropIndexQuery, DB::ASTQueryWithTableAndOutput>(m, "ASTDropIndexQuery")
        .def("getID", [](const DB::ASTDropIndexQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDropFunctionQuery, DB::IAST>(m, "ASTDropFunctionQuery")
        .def("getID", [](const DB::ASTDropFunctionQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDropWorkloadQuery, DB::IAST>(m, "ASTDropWorkloadQuery")
        .def("getID", [](const DB::ASTDropWorkloadQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDropResourceQuery, DB::IAST>(m, "ASTDropResourceQuery")
        .def("getID", [](const DB::ASTDropResourceQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDropNamedCollectionQuery, DB::IAST>(m, "ASTDropNamedCollectionQuery")
        .def("getID", [](const DB::ASTDropNamedCollectionQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTAlterCommand, DB::IAST>(m, "ASTAlterCommand")
        .def("getID", [](const DB::ASTAlterCommand& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTAlterQuery, DB::ASTQueryWithTableAndOutput>(m, "ASTAlterQuery")
        .def("getID", [](const DB::ASTAlterQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTAlterNamedCollectionQuery, DB::IAST>(m, "ASTAlterNamedCollectionQuery")
        .def("getID", [](const DB::ASTAlterNamedCollectionQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTRenameQuery, DB::ASTQueryWithOutput>(m, "ASTRenameQuery")
        .def("getID", [](const DB::ASTRenameQuery& self) { return self.getID('_'); }, "Get AST node ID");

    // DML Queries
    nb::class_<DB::ASTInsertQuery, DB::IAST>(m, "ASTInsertQuery")
        .def("getID", [](const DB::ASTInsertQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTUpdateQuery, DB::ASTQueryWithTableAndOutput>(m, "ASTUpdateQuery")
        .def("getID", [](const DB::ASTUpdateQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDeleteQuery, DB::ASTQueryWithTableAndOutput>(m, "ASTDeleteQuery")
        .def("getID", [](const DB::ASTDeleteQuery& self) { return self.getID('_'); }, "Get AST node ID");

    // Utility Queries
    nb::class_<DB::ASTUseQuery, DB::IAST>(m, "ASTUseQuery")
        .def("getID", [](const DB::ASTUseQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTSetQuery, DB::IAST>(m, "ASTSetQuery")
        .def("getID", [](const DB::ASTSetQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTSystemQuery, DB::IAST>(m, "ASTSystemQuery")
        .def("getID", [](const DB::ASTSystemQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTOptimizeQuery, DB::ASTQueryWithTableAndOutput>(m, "ASTOptimizeQuery")
        .def("getID", [](const DB::ASTOptimizeQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTKillQueryQuery, DB::ASTQueryWithOutput>(m, "ASTKillQueryQuery")
        .def("getID", [](const DB::ASTKillQueryQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTExplainQuery, DB::ASTQueryWithOutput>(m, "ASTExplainQuery")
        .def("getID", [](const DB::ASTExplainQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDescribeCacheQuery, DB::ASTQueryWithOutput>(m, "ASTDescribeCacheQuery")
        .def("getID", [](const DB::ASTDescribeCacheQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTUndropQuery, DB::ASTQueryWithTableAndOutput>(m, "ASTUndropQuery")
        .def("getID", [](const DB::ASTUndropQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTWatchQuery, DB::ASTQueryWithTableAndOutput>(m, "ASTWatchQuery")
        .def("getID", [](const DB::ASTWatchQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTExternalDDLQuery, DB::IAST>(m, "ASTExternalDDLQuery")
        .def("getID", [](const DB::ASTExternalDDLQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTTransactionControl, DB::IAST>(m, "ASTTransactionControl")
        .def("getID", [](const DB::ASTTransactionControl& self) { return self.getID('_'); }, "Get AST node ID");

    // SHOW Queries
    nb::class_<DB::ASTShowTablesQuery, DB::ASTQueryWithOutput>(m, "ASTShowTablesQuery")
        .def("getID", [](const DB::ASTShowTablesQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTShowColumnsQuery, DB::ASTQueryWithOutput>(m, "ASTShowColumnsQuery")
        .def("getID", [](const DB::ASTShowColumnsQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTShowIndexesQuery, DB::ASTQueryWithOutput>(m, "ASTShowIndexesQuery")
        .def("getID", [](const DB::ASTShowIndexesQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTShowFunctionsQuery, DB::ASTQueryWithOutput>(m, "ASTShowFunctionsQuery")
        .def("getID", [](const DB::ASTShowFunctionsQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTShowSettingQuery, DB::ASTQueryWithOutput>(m, "ASTShowSettingQuery")
        .def("getID", [](const DB::ASTShowSettingQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDescribeQuery, DB::ASTQueryWithOutput>(m, "ASTDescribeQuery")
        .def("getID", [](const DB::ASTDescribeQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTExistsDatabaseQuery, DB::ASTQueryWithTableAndOutput>(m, "ASTExistsDatabaseQuery")
        .def("getID", [](const DB::ASTExistsDatabaseQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTShowCreateDatabaseQuery, DB::ASTQueryWithTableAndOutput>(m, "ASTShowCreateDatabaseQuery")
        .def("getID", [](const DB::ASTShowCreateDatabaseQuery& self) { return self.getID('_'); }, "Get AST node ID");

    // Utility Components
    nb::class_<DB::ASTWithElement, DB::IAST>(m, "ASTWithElement")
        .def("getID", [](const DB::ASTWithElement& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTAssignment, DB::IAST>(m, "ASTAssignment")
        .def("getID", [](const DB::ASTAssignment& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTOrderByElement, DB::IAST>(m, "ASTOrderByElement")
        .def("getID", [](const DB::ASTOrderByElement& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTStorageOrderByElement, DB::IAST>(m, "ASTStorageOrderByElement")
        .def("getID", [](const DB::ASTStorageOrderByElement& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTSampleRatio, DB::IAST>(m, "ASTSampleRatio")
        .def("getID", [](const DB::ASTSampleRatio& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTTimeInterval, DB::IAST>(m, "ASTTimeInterval")
        .def("getID", [](const DB::ASTTimeInterval& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTInterpolateElement, DB::IAST>(m, "ASTInterpolateElement")
        .def("getID", [](const DB::ASTInterpolateElement& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTParallelWithQuery, DB::IAST>(m, "ASTParallelWithQuery")
        .def("getID", [](const DB::ASTParallelWithQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTViewTargets, DB::IAST>(m, "ASTViewTargets")
        .def("getID", [](const DB::ASTViewTargets& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTTableOverride, DB::IAST>(m, "ASTTableOverride")
        .def("getID", [](const DB::ASTTableOverride& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTTableOverrideList, DB::IAST>(m, "ASTTableOverrideList")
        .def("getID", [](const DB::ASTTableOverrideList& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDatabaseOrNone, DB::IAST>(m, "ASTDatabaseOrNone")
        .def("getID", [](const DB::ASTDatabaseOrNone& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTObjectTypeArgument, DB::IAST>(m, "ASTObjectTypeArgument")
        .def("getID", [](const DB::ASTObjectTypeArgument& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTPair, DB::IAST>(m, "ASTPair")
        .def("getID", [](const DB::ASTPair& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTFunctionWithKeyValueArguments, DB::IAST>(m, "ASTFunctionWithKeyValueArguments")
        .def("getID", [](const DB::ASTFunctionWithKeyValueArguments& self) { return self.getID('_'); }, "Get AST node ID");

    // Storage and Engine Components
    nb::class_<DB::ASTDictionary, DB::IAST>(m, "ASTDictionary")
        .def("getID", [](const DB::ASTDictionary& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDictionaryLifetime, DB::IAST>(m, "ASTDictionaryLifetime")
        .def("getID", [](const DB::ASTDictionaryLifetime& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDictionaryLayout, DB::IAST>(m, "ASTDictionaryLayout")
        .def("getID", [](const DB::ASTDictionaryLayout& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDictionaryRange, DB::IAST>(m, "ASTDictionaryRange")
        .def("getID", [](const DB::ASTDictionaryRange& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDictionarySettings, DB::IAST>(m, "ASTDictionarySettings")
        .def("getID", [](const DB::ASTDictionarySettings& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTPartition, DB::IAST>(m, "ASTPartition")
        .def("getID", [](const DB::ASTPartition& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTTTLElement, DB::IAST>(m, "ASTTTLElement")
        .def("getID", [](const DB::ASTTTLElement& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTSQLSecurity, DB::IAST>(m, "ASTSQLSecurity")
        .def("getID", [](const DB::ASTSQLSecurity& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTRefreshStrategy, DB::IAST>(m, "ASTRefreshStrategy")
        .def("getID", [](const DB::ASTRefreshStrategy& self) { return self.getID('_'); }, "Get AST node ID");

    // Backup and Restore
    nb::class_<DB::ASTBackupQuery, DB::ASTQueryWithOutput>(m, "ASTBackupQuery")
        .def("getID", [](const DB::ASTBackupQuery& self) { return self.getID('_'); }, "Get AST node ID");

    // Access Control (RBAC) - Major classes
    nb::class_<DB::ASTCreateUserQuery, DB::IAST>(m, "ASTCreateUserQuery")
        .def("getID", [](const DB::ASTCreateUserQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTCreateRoleQuery, DB::IAST>(m, "ASTCreateRoleQuery")
        .def("getID", [](const DB::ASTCreateRoleQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTCreateQuotaQuery, DB::IAST>(m, "ASTCreateQuotaQuery")
        .def("getID", [](const DB::ASTCreateQuotaQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTCreateRowPolicyQuery, DB::IAST>(m, "ASTCreateRowPolicyQuery")
        .def("getID", [](const DB::ASTCreateRowPolicyQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTCreateSettingsProfileQuery, DB::IAST>(m, "ASTCreateSettingsProfileQuery")
        .def("getID", [](const DB::ASTCreateSettingsProfileQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDropAccessEntityQuery, DB::IAST>(m, "ASTDropAccessEntityQuery")
        .def("getID", [](const DB::ASTDropAccessEntityQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTGrantQuery, DB::IAST>(m, "ASTGrantQuery")
        .def("getID", [](const DB::ASTGrantQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTSetRoleQuery, DB::IAST>(m, "ASTSetRoleQuery")
        .def("getID", [](const DB::ASTSetRoleQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTCheckGrantQuery, DB::IAST>(m, "ASTCheckGrantQuery")
        .def("getID", [](const DB::ASTCheckGrantQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTMoveAccessEntityQuery, DB::IAST>(m, "ASTMoveAccessEntityQuery")
        .def("getID", [](const DB::ASTMoveAccessEntityQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTShowAccessEntitiesQuery, DB::ASTQueryWithOutput>(m, "ASTShowAccessEntitiesQuery")
        .def("getID", [](const DB::ASTShowAccessEntitiesQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTShowGrantsQuery, DB::ASTQueryWithOutput>(m, "ASTShowGrantsQuery")
        .def("getID", [](const DB::ASTShowGrantsQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTShowCreateAccessEntityQuery, DB::ASTQueryWithOutput>(m, "ASTShowCreateAccessEntityQuery")
        .def("getID", [](const DB::ASTShowCreateAccessEntityQuery& self) { return self.getID('_'); }, "Get AST node ID");

    // Access Control - Support classes
    nb::class_<DB::ASTUserNameWithHost, DB::IAST>(m, "ASTUserNameWithHost")
        .def("getID", [](const DB::ASTUserNameWithHost& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTUserNamesWithHost, DB::IAST>(m, "ASTUserNamesWithHost")
        .def("getID", [](const DB::ASTUserNamesWithHost& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTRolesOrUsersSet, DB::IAST>(m, "ASTRolesOrUsersSet")
        .def("getID", [](const DB::ASTRolesOrUsersSet& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTRowPolicyName, DB::IAST>(m, "ASTRowPolicyName")
        .def("getID", [](const DB::ASTRowPolicyName& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTRowPolicyNames, DB::IAST>(m, "ASTRowPolicyNames")
        .def("getID", [](const DB::ASTRowPolicyNames& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTSettingsProfileElement, DB::IAST>(m, "ASTSettingsProfileElement")
        .def("getID", [](const DB::ASTSettingsProfileElement& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTSettingsProfileElements, DB::IAST>(m, "ASTSettingsProfileElements")
        .def("getID", [](const DB::ASTSettingsProfileElements& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTAlterSettingsProfileElements, DB::IAST>(m, "ASTAlterSettingsProfileElements")
        .def("getID", [](const DB::ASTAlterSettingsProfileElements& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTAuthenticationData, DB::IAST>(m, "ASTAuthenticationData")
        .def("getID", [](const DB::ASTAuthenticationData& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTPublicSSHKey, DB::IAST>(m, "ASTPublicSSHKey")
        .def("getID", [](const DB::ASTPublicSSHKey& self) { return self.getID('_'); }, "Get AST node ID");

    // Prepared Statements
    nb::class_<DB::ASTPreparedStatement, DB::IAST>(m, "ASTPreparedStatement")
        .def("getID", [](const DB::ASTPreparedStatement& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTExecute, DB::IAST>(m, "ASTExecute")
        .def("getID", [](const DB::ASTExecute& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::ASTDeallocate, DB::IAST>(m, "ASTDeallocate")
        .def("getID", [](const DB::ASTDeallocate& self) { return self.getID('_'); }, "Get AST node ID");

    // MySQL Compatibility
    nb::class_<DB::MySQLParser::ASTCreateQuery, DB::IAST>(m, "MySQLASTCreateQuery")
        .def("getID", [](const DB::MySQLParser::ASTCreateQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::MySQLParser::ASTAlterQuery, DB::IAST>(m, "MySQLASTAlterQuery")
        .def("getID", [](const DB::MySQLParser::ASTAlterQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::MySQLParser::ASTAlterCommand, DB::IAST>(m, "MySQLASTAlterCommand")
        .def("getID", [](const DB::MySQLParser::ASTAlterCommand& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::MySQLParser::ASTDropQuery, DB::IAST>(m, "MySQLASTDropQuery")
        .def("getID", [](const DB::MySQLParser::ASTDropQuery& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::MySQLParser::ASTCreateDefines, DB::IAST>(m, "MySQLASTCreateDefines")
        .def("getID", [](const DB::MySQLParser::ASTCreateDefines& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::MySQLParser::ASTDeclareColumn, DB::IAST>(m, "MySQLASTDeclareColumn")
        .def("getID", [](const DB::MySQLParser::ASTDeclareColumn& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::MySQLParser::ASTDeclareIndex, DB::IAST>(m, "MySQLASTDeclareIndex")
        .def("getID", [](const DB::MySQLParser::ASTDeclareIndex& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::MySQLParser::ASTDeclareConstraint, DB::IAST>(m, "MySQLASTDeclareConstraint")
        .def("getID", [](const DB::MySQLParser::ASTDeclareConstraint& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::MySQLParser::ASTDeclarePartition, DB::IAST>(m, "MySQLASTDeclarePartition")
        .def("getID", [](const DB::MySQLParser::ASTDeclarePartition& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::MySQLParser::ASTDeclarePartitionOptions, DB::IAST>(m, "MySQLASTDeclarePartitionOptions")
        .def("getID", [](const DB::MySQLParser::ASTDeclarePartitionOptions& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::MySQLParser::ASTDeclareSubPartition, DB::IAST>(m, "MySQLASTDeclareSubPartition")
        .def("getID", [](const DB::MySQLParser::ASTDeclareSubPartition& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::MySQLParser::ASTDeclareReference, DB::IAST>(m, "MySQLASTDeclareReference")
        .def("getID", [](const DB::MySQLParser::ASTDeclareReference& self) { return self.getID('_'); }, "Get AST node ID");

    nb::class_<DB::MySQLParser::ASTDeclareOptions, DB::IAST>(m, "MySQLASTDeclareOptions")
        .def("getID", [](const DB::MySQLParser::ASTDeclareOptions& self) { return self.getID('_'); }, "Get AST node ID");
}