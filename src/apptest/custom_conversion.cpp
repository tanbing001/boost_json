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

vec3 tag_invoke(const bj::value_to_tag<vec3>&, const bj::value& jv) {
  bj::object obj = jv.get_object();

  int x = obj["x"].as_int64();
  int y = obj["y"].as_int64();
  int z = obj["z"].as_int64();

  return vec3{x, y, z};
}

class customer {
 public:
  explicit customer(std::uint64_t i, const std::string& n, bool l,
                    const vec3& p)
      : customer_id_(i), customer_name_(n), late_(l), position_(p) {
  }

  std::uint64_t customer_id() const { return customer_id_; }

  const std::string& customer_name() const { return customer_name_; }

  bool late() const { return late_; }

  const vec3& position() const { return position_; }

 private:
  std::uint64_t customer_id_;

  std::string customer_name_;

  bool late_;

  vec3 position_;
};

void tag_invoke(const bj::value_from_tag&, bj::value& jv, customer co) {
  jv = {
    {"id", co.customer_id()},
    {"name", co.customer_name()},
    {"late", co.late()},
    {"position", co.position()}
  };
}

customer tag_invoke(bj::value_to_tag<customer>&, const bj::value& jv) {
  std::uint64_t id = jv.at("id").as_uint64();

  std::string name = bj::value_to<std::string>(jv.get_object().at("name"));

  bool late = jv.get_object().at("late").as_bool();

  vec3 position = bj::value_to<vec3>(jv.get_object().at("position"));

  return customer(id, name, late, position);
}

int main() {
  customer cus(3, "Tom", true, vec3{4, 1, 4});

  bj::value jv = bj::value_from(cus);

  assert(jv.is_object());

  auto ser = bj::serialize(jv);

  customer cus2 = bj::value_to<customer>(jv);

  assert(cus.customer_name() == cus2.customer_name());

  std::cout << "Hello, world!" << std::endl;

  return 0;
}
