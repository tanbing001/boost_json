#include <fstream>
#include <iostream>
#include <sstream>

#include "boost/json/src.hpp"

namespace bj = boost::json;

const char* const input_file_path = "G:/json_study/src/source/input.json";
const char* const output_file_path = "G:/json_study/src/source/output.json";

bool LoadJosnFromFile(const char* file_path, bj::value* jv);

bool SaveJsonToFile(const char* file_path, const bj::value& json);

int main(int argc, char* argv[]) {
  bj::value jv;
  LoadJosnFromFile(input_file_path, &jv);

  SaveJsonToFile(output_file_path, jv);

  return 0;
}

bool LoadJosnFromFile(const char* file_path, bj::value* jv) {
  std::ifstream json_file_input;

  json_file_input.open(input_file_path, std::ios::in);
  std::stringstream input_json_str;
  input_json_str << json_file_input.rdbuf();
  json_file_input.close();

  std::string json_str = input_json_str.str();

  try {
    bj::error_code ec;
    *jv = bj::parse(json_str.c_str(), ec);

    if (ec) {
      return false;
    }
    return true;

  } catch (const std::bad_alloc& e) {
    return false;
  }
}

bool SaveJsonToFile(const char* file_path, const bj::value& json) {
  std::ofstream json_file_output;

  json_file_output.open(file_path, std::ios::out);

  std::string json_str = bj::serialize(json);
  json_file_output.write(json_str.c_str(), json_str.size());

  json_file_output.close();

  return true;
}
