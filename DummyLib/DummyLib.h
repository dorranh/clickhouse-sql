#pragma once

#include <string>
#include <vector>
#include <memory>

namespace DummyLib {

/**
 * @brief A simple demonstration class for testing Python bindings
 *
 * This class provides basic functionality to test the nanobind + litgen
 * binding pipeline. It includes various data types and methods that
 * are commonly used in C++ applications.
 */
class DummyClass {
public:
    /**
     * @brief Default constructor
     *
     * Creates a DummyClass with default name "unnamed" and value 0
     */
    DummyClass();

    /**
     * @brief Constructor with custom name
     * @param name The name to assign to this instance
     *
     * Creates a DummyClass with the specified name and default value 0
     */
    DummyClass(const std::string& name);

    /**
     * @brief Destructor
     */
    ~DummyClass();

    /**
     * @brief Get the current name of this instance
     * @return The name as a string
     */
    std::string getName() const;

    /**
     * @brief Set the name of this instance
     * @param name The new name to assign
     */
    void setName(const std::string& name);

    /**
     * @brief Get the current numeric value
     * @return The current value as an integer
     */
    int getValue() const;

    /**
     * @brief Set the numeric value
     * @param value The new value to assign
     */
    void setValue(int value);

    /**
     * @brief Get the list of numbers stored in this instance
     * @return A vector containing all stored numbers
     */
    std::vector<int> getNumbers() const;

    /**
     * @brief Add a number to the internal list
     * @param num The number to add to the list
     */
    void addNumber(int num);

private:
    std::string name_;      ///< The name of this instance
    int value_;             ///< The numeric value
    std::vector<int> numbers_; ///< List of stored numbers
};

/**
 * @brief A simple struct for testing struct bindings
 *
 * This struct demonstrates how to bind C++ structs with public members
 * to Python. All members are public and can be accessed directly.
 */
struct DummyStruct {
    std::string name;  ///< The name of this struct instance
    int value;         ///< A numeric value
    bool flag;         ///< A boolean flag

    /**
     * @brief Default constructor
     *
     * Creates a DummyStruct with default values: name="default", value=0, flag=false
     */
    DummyStruct() : name("default"), value(0), flag(false) {}

    /**
     * @brief Constructor with custom values
     * @param n The name to assign
     * @param v The numeric value to assign
     * @param f The boolean flag to assign
     */
    DummyStruct(const std::string& n, int v, bool f) : name(n), value(v), flag(f) {}
};

// Some free functions

/**
 * @brief Generate a greeting message
 * @param name The name to greet
 * @return A greeting string in the format "Hello, {name}!"
 *
 * This function demonstrates simple string manipulation and return values
 */
std::string greet(const std::string& name);

/**
 * @brief Add two integers
 * @param a First integer
 * @param b Second integer
 * @return The sum of a and b
 *
 * Basic arithmetic function to test numeric parameter passing
 */
int add(int a, int b);

/**
 * @brief Multiply two floating-point numbers
 * @param a First number
 * @param b Second number
 * @return The product of a and b
 *
 * Demonstrates floating-point arithmetic and different numeric types
 */
double multiply(double a, double b);

/**
 * @brief Create a range of integers
 * @param start The starting value (inclusive)
 * @param end The ending value (inclusive)
 * @return A vector containing integers from start to end
 *
 * This function demonstrates returning containers and range-based logic
 */
std::vector<int> createRange(int start, int end);

// Template function example

/**
 * @brief Find the maximum value in a vector
 * @tparam T The type of elements in the vector (must support comparison)
 * @param values The vector to search through
 * @return The maximum value found, or default-constructed T if vector is empty
 *
 * This template function demonstrates generic programming and works with
 * any type that supports the > operator. It's useful for testing template
 * binding generation in litgen.
 */
template<typename T>
T maxValue(const std::vector<T>& values) {
    if (values.empty()) return T{};
    T max = values[0];
    for (const auto& val : values) {
        if (val > max) max = val;
    }
    return max;
}

} // namespace DummyLib
