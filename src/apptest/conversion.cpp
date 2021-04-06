#include <iostream>

#include <vector>

#include "boost/json/src.hpp"

namespace bj = boost::json;

// Note:
// Conversion user-defined type to value: value_from
// The opposite direction: value_to

struct vec3 {
  int x;
  int y;
  int z;
};

void tag_invoke(const bj::value_from_tag&, bj::value& jv, const vec3& vec) {
  jv = {{"x", vec.x}, {"y", vec.y}, {"z", vec.z}};
}

class customer {
 public:
  std::uint64_t id;
  std::string name;
  bool late;

  customer() = default;

  customer(std::uint64_t i, const std::string& n, bool l)
    : id(i), name(n), late(l) {
  }
};

void tag_invoke(const bj::value_from_tag&, bj::value& jv, customer co) {
  jv = {{"id", co.id}, {"name", co.name}, {"late", co.late}};
}

customer tag_invoke(bj::value_to_tag<customer>&, const bj::value& jv) {
  std::uint64_t id = jv.at("id").as_uint64();

  std::string name = bj::value_to<std::string>(jv.get_object().at("name"));

  bool late = jv.get_object().at("late").as_bool();

  return customer(id, name, late);
}

int main() {
  vec3 pos = {4, 1, 4};
  bj::value jv = bj::value_from(pos);

  bj::object obj = jv.get_object();

  std::cout << obj["y"].as_int64() << std::endl;

  // ---------------------------------------------------------------------------

  std::vector<customer> customers = {
      customer(0, "Alison", false), customer(1, "Bill", false),
      customer(3, "Catherine", true), customer(4, "Doug", false)};

  bj::storage_ptr sp = bj::make_shared_resource<bj::monotonic_resource>();

  bj::value jv1 = bj::value_from(customers, sp);

  assert(jv1.storage() == sp);
  assert(jv1.is_array());

  bj::object obj1 = jv1.at(2).get_object();

  std::cout << obj1["id"].as_uint64() << std::endl;
  std::cout << obj1["name"].as_string() << std::endl;
  std::cout << obj1["late"].as_bool() << std::endl;

  // ---------------------------------------------------------------------------

  customer c1(5, "Ed", false);

  bj::value jv2 = bj::value_from(c1);

  customer c2 = bj::value_to<customer>(jv2);

  assert(c1.name == c2.name);

  return 0;
}
