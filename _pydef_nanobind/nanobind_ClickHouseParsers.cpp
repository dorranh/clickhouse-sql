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

// ClickHouse Headers
#include <Parsers/parseQuery.h>
#include <Parsers/ParserQuery.h>
#include <Parsers/IAST.h>

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
        return ast->getID();
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
}