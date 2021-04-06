#include <iostream>
#include <vector>

#include "boost/json/src.hpp"

namespace bj = boost::json;

int main() {
  // TupleLike -> array
  bj::array ja = {true, 2, "hello", nullptr};
  auto ser_ja = bj::serialize(ja);

	// StringLike -> string
  bj::string jstr = "hello,world";
  auto ser_jstr = bj::serialize(jstr);

	//  FromMapLike -> object
  bj::object jobj = {{"mercury", 36}, {"venus", 67}, {"earth", 93}};
  auto ser_jobj = bj::serialize(jobj);

	return 0;
}
