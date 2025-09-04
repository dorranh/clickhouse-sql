# Adapted from the litgen template here:
# https://github.com/pthom/litgen_template/blob/5764d94634d8aed49e8d82e07123e63f7b7aec46/tools/autogenerate_bindings.py

import litgen
import os
from pathlib import Path

def my_litgen_options() -> litgen.LitgenOptions:
    # configure your options here
    options = litgen.LitgenOptions()

    options.bind_library = litgen.BindLibraryType.nanobind

    # ///////////////////////////////////////////////////////////////////
    #  Root namespace
    # ///////////////////////////////////////////////////////////////////
    # The namespace DB is the C++ root namespace for ClickHouse
    # (i.e. no submodule will be generated for it in the python bindings)
    options.namespaces_root = ["ClickhouseSql"]

    # //////////////////////////////////////////////////////////////////
    # Basic functions bindings
    # ////////////////////////////////////////////////////////////////////
    # No specific option is needed for these basic bindings
    # litgen will add the docstrings automatically in the python bindings

    # //////////////////////////////////////////////////////////////////
    # Classes and structs bindings
    # //////////////////////////////////////////////////////////////////
    # No specific option is needed for these bindings.
    # - Litgen will automatically add a default constructor with named parameters
    #   for structs that have no constructor defined in C++.
    #  - A class will publish only its public methods and members

    # ///////////////////////////////////////////////////////////////////
    #  Exclude functions and/or parameters from the bindings
    # ///////////////////////////////////////////////////////////////////
    # We want to exclude `inline void priv_SetOptions(bool v) {}` from the bindings
    # priv_ is a prefix for private functions that we don't want to expose
    # options.fn_exclude_by_name__regex = "^priv_"

    # Inside `inline void SetOptions(bool v, bool priv_param = false) {}`,
    # we don't want to expose the private parameter priv_param
    # (it is possible since it has a default value)
    options.fn_params_exclude_names__regex = "^priv_"

            # Exclude everything except essential parsing functions
    options.fn_exclude_by_name__regex = "^(priv_|operator|.*Template.*|.*Buffer.*|.*State.*|format.*|dump.*|clone|children|size|begin|end|.*Internal.*|parseQuery)"

    # Exclude everything except essential parsing classes
    options.class_exclude_by_name__regex = "^(.*Template.*|.*Iterator.*|.*Buffer.*|.*State.*|.*Settings.*|.*Exception.*|Expected|Pos|.*Visitor.*)"

    # Skip files that cause parsing issues
    options.srcmlcpp_options.ignored_warning_parts = [
        "LitgenTemplateFunctionIgnore",      # Ignore template function warnings
        "LitgenClassMemberException",        # Ignore operator= and other unsupported members
        "SrcmlcppIgnoreElement"
    ]

    # Configure namespace handling for ClickHouse types
    options.namespaces_root = ["DB"]
    options.original_location_flag_show = False

    # Exclude FormattingBuffer specifically - it has reference members that can't be bound
    options.class_exclude_by_name__regex = "^(.*Template.*|.*Iterator.*|.*Buffer.*|.*State.*|.*Settings.*|.*Exception.*|Expected|Pos|.*Visitor.*|.*FormattingBuffer.*)"

    # # Be more permissive with parsing errors
    # options.srcmlcpp_options.functions_api_prefixes = []


        # ////////////////////////////////////////////////////////////////////
    # Class inheritance configuration - simplified approach
    # ////////////////////////////////////////////////////////////////////
    # Focus on concrete classes only to avoid inheritance complexity
    options.class_create_default_named_ctor__regex = "^ParserQuery$"

    # ////////////////////////////////////////////////////////////////////
    # Override virtual methods in python
    # ////////////////////////////////////////////////////////////////////
    # The virtual methods of this class can be overriden in python
    # options.class_override_virtual_methods_in_python__regex = "^Animal$"

    # ////////////////////////////////////////////////////////////////////
    # Publish bindings for template functions
    # ////////////////////////////////////////////////////////////////////
    #  template<typename T> T MaxValue(const std::vector<T>& values);
    # will be published as: max_value_int and max_value_float
    # options.fn_template_options.add_specialization("^MaxValue$", ["int", "float"], add_suffix_to_function_name=True)
    #  template<typename T> T MaxValue(const std::vector<T>& values);
    # will be published as: max_value_int and max_value_float
    # options.fn_template_options.add_specialization("^MinValue$", ["int", "float"], add_suffix_to_function_name=False)
    # options.fn_template_options.add_specialization("^reset$", ["DB::IAST*", "DB::ASTPtr"], add_suffix_to_function_name=True)
    # ////////////////////////////////////////////////////////////////////
    # Return values policy
    # ////////////////////////////////////////////////////////////////////
    # `Widget& GetWidgetSingleton()` returns a reference, that python should not free,
    # so we force the reference policy to be 'reference' instead of 'automatic'
    # options.fn_return_force_policy_reference_for_references__regex = "Singleton$"

    # ////////////////////////////////////////////////////////////////////
    #  Boxed types
    # ////////////////////////////////////////////////////////////////////
    # Adaptation for `inline void SwitchBoolValue(bool &v) { v = !v; }`
    # SwitchBoolValue is a C++ function that takes a bool parameter by reference and changes its value
    # Since bool are immutable in python, we can to use a BoxedBool instead
    # options.fn_params_replace_modifiable_immutable_by_boxed__regex = "^SwitchBoolValue$"

    # ////////////////////////////////////////////////////////////////////
    #  Published vectorized math functions and namespaces
    # ////////////////////////////////////////////////////////////////////
    # The functions in the MathFunctions namespace will be also published as vectorized functions
    # options.fn_namespace_vectorize__regex = r"^DaftLib::MathFunctions$"  # Do it in this namespace only
    # options.fn_vectorize__regex = r".*"  # For all functions

    # ////////////////////////////////////////////////////////////////////
    # Format the python stubs with black
    # ////////////////////////////////////////////////////////////////////
    # Set to True if you want the stub file to be formatted with black
    # options.python_run_black_formatter = True

    return options


def autogenerate() -> None:
    repository_dir = os.path.realpath(os.path.dirname(__file__) + "/../")

    # Set by parent cmake build
    # header_search_dir = Path(
    #     os.environ.get("CLICKHOUSE_HEADERS_DIR")
    # )

    # print(header_search_dir)

    # header_files = list(header_search_dir.glob("*.h"))
    # # Remove some problematic headers for now...
    # header_files = [h for h in header_files if h.name != "ASTRenameQuery.h"]
    header_files = []

    # # For now, use the dummy library headers for testing
    # header_search_dir = Path(repository_dir + "/DummyLib")
    # header_files = list(header_search_dir.glob("*.h"))

    # Now add in the ClickHouse headers from tmp/ClickHouse/src/Parsers as well
    header_search_dir = Path(repository_dir + "/tmp/ClickHouse/src/Parsers")
    header_files.extend(list(header_search_dir.glob("IParser.h")))       # IParser base class needed for parseQuery
    header_files.extend(list(header_search_dir.glob("ParserQuery.h")))   # Parser class with constructor
    header_files.extend(list(header_search_dir.glob("parseQuery.h")))
    header_files.extend(list(header_search_dir.glob("IAST.h")))          # Base AST for getID() method
    # Include just the AST types you need to identify query types
    header_files.extend(list(header_search_dir.glob("ASTCreateQuery.h")))
    header_files.extend(list(header_search_dir.glob("ASTSelectQuery.h")))


    print(f"Processing headers: {header_files}")

    output_cpp_pydef_file = (
        repository_dir + "/_pydef_nanobind/nanobind_ClickHouseParsers.cpp"
    )
    os.makedirs(os.path.dirname(output_cpp_pydef_file), exist_ok=True)
    Path(output_cpp_pydef_file).touch()

    litgen.write_generated_code_for_files(
        options=my_litgen_options(),
        input_cpp_header_files=[str(p) for p in header_files],
        output_cpp_pydef_file=output_cpp_pydef_file,
        output_stub_pyi_file=repository_dir + "/_stubs/clickhouse_sql/__init__.pyi",
    )

    # # Post-processing -> Adding #include statements rather than doing it manually
    # with open(output_cpp_pydef_file) as f:
    #     content = f.readlines()
    # start_header_section = None
    # end_header_section = None
    # for i, line in enumerate(content):
    #     if "AUTOGENERATED - INCLUDES FOR CLICKHOUSE PARSER LIB" in line:
    #         start_header_section = i
    #     if "END AUTOGENERATION FOR CLICKHOUSE INCLUDES" in line:
    #         end_header_section = i
    #         break
    # if start_header_section is None:
    #     raise Exception("Failed to find comment identifying start of section to write ClickHouse Parser include statements")
    # if end_header_section is None:
    #     raise Exception("Failed to find comment identifying end of section to write ClickHouse Parser include statements")
    # extra_includes = [
    #     f"#include <{os.path.basename(h)}>\n" for h in header_files
    # ]
    # updated_content = content[0:start_header_section+1] + extra_includes + content[end_header_section:]
    # with open(output_cpp_pydef_file, "w") as f:
    #     f.writelines(updated_content)

if __name__ == "__main__":
    autogenerate()
