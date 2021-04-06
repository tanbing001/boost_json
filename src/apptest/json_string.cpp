#include <iostream>
#include <string>

#include "boost/json/src.hpp"

int main(int argc, char* argv[]) {
  // Note:
  // String is not a class template, seem to std::string_view.
  boost::json::string str = "Boost.Json";

  boost::json::string_view sv = str;

  // compare(boost::json::string_view)
  std::cout << "json::string compare with json::string_view: "
            << str.compare(sv) << std::endl;

  std::string sstr = "hello";

  boost::json::string jstr = "hello";
  assert(sstr.append({'w', 'o', 'r', 'l', 'd'}) == "helloworld");

  assert(jstr.append("world") == "helloworld");


  return 0;
}
