#include <iostream>
#include <string>
#include <variant>
#include <map>

using dinamic_value = std::variant<int, double, bool, std::string, dinamic_value>;

