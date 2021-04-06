#include <iostream>

#include "boost/json/src.hpp"

int main(int argc, char* argv[]) {
  boost::json::value jv1;
  boost::json::value jv2(nullptr);

  assert(jv1.is_null());
  assert(jv2.is_null());

  // Note:
  // The kind of emplace_* function return a reference of the type.
  // For later inspection and modification.

  auto& str = jv1.emplace_string();
  str = "Hello, world";
  std::cout << jv1.as_string() << std::endl;

  str = "How are you!";
  std::cout << jv1.as_string() << std::endl;

  int64_t& num = jv2.emplace_int64();

  num = 1;
  assert(jv2.is_int64());
  std::cout << jv2.as_int64() << std::endl;

  num = 2;
  std::cout << jv2.as_int64() << std::endl;

	return 0;
}
