#include <iostream>

#include "boost/json/src.hpp"

int main(int argc, char* argv[]) {
  // Empty object, the same with string.
  boost::json::object obj1;
  boost::json::object obj({{"key1", "value1"}, {"key2", 42}});

  obj.emplace("key3", true);
  obj["key4"] = false;

  std::cout << obj["key1"].as_string() << " " << obj["key2"].as_int64() << " "
            << obj["key3"].as_bool() << std::endl;

  return 0;
}
