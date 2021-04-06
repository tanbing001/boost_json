#include <iostream>

#include "boost/json/src.hpp"

int main(int argc, char* argv[]) {
  // Empty array, uses the default memory resource
  boost::json::array arr1;

  // Empty array, uses a counted monotonic resource
  boost::json::array arr2(
      boost::json::make_shared_resource<boost::json::monotonic_resource>());

  boost::json::array arr({"Hello", 42, true});

  arr.emplace_back("world");

  arr.emplace_back(21);

  arr.emplace_back(false);

  std::cout << arr[0].as_string() << " " << arr[3].as_string() << std::endl;

  std::cout << "Hello" << " " << "world" << std::endl;

  return 0;
}
