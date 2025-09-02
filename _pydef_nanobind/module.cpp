#include <nanobind/nanobind.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


namespace nb = nanobind;


void py_init_module_clickhouse_sql(nb::module_& m);


// This builds the native python module `_clickhouse_sql`
// it will be wrapped in a standard python module `clickhouse_sql`
NB_MODULE(_clickhouse_sql, m)
{
    #ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
    #else
    m.attr("__version__") = "dev";
    #endif

    py_init_module_clickhouse_sql(m);
}