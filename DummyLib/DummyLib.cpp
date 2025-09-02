#include "DummyLib.h"
#include <algorithm>

namespace DummyLib {

DummyClass::DummyClass() : name_("unnamed"), value_(0) {}

DummyClass::DummyClass(const std::string& name) : name_(name), value_(0) {}

DummyClass::~DummyClass() = default;

std::string DummyClass::getName() const {
    return name_;
}

void DummyClass::setName(const std::string& name) {
    name_ = name;
}

int DummyClass::getValue() const {
    return value_;
}

void DummyClass::setValue(int value) {
    value_ = value;
}

std::vector<int> DummyClass::getNumbers() const {
    return numbers_;
}

void DummyClass::addNumber(int num) {
    numbers_.push_back(num);
}

/**
 * @brief Returns a greeting message for the given name.
 *
 * @param name The name to greet.
 * @return A string containing the greeting message.
 */
std::string greet(const std::string& name) {
    return "Hello, " + name + "!";
}

int add(int a, int b) {
    return a + b;
}

double multiply(double a, double b) {
    return a * b;
}

std::vector<int> createRange(int start, int end) {
    std::vector<int> result;
    for (int i = start; i <= end; ++i) {
        result.push_back(i);
    }
    return result;
}

} // namespace DummyLib
