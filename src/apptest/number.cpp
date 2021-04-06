#include <iostream>

#include "boost/json/src.hpp"

int main() {
  boost::json::value jv1 = 1;
  assert(jv1.is_int64());

  boost::json::value jv2 = 2u;
  assert(jv2.is_uint64());

  boost::json::value jv3 = 3.0;
  assert(jv3.is_double());

  std::cout << "Unsigned int number: " << jv2.as_uint64() << std::endl;
  std::cout << "Number: " << jv1.as_int64() << std::endl;

  return 0;
}
