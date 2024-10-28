#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "json.hpp"
#include "word.hpp"

using namespace std;
using json = nlohmann::json;

void to_json(json& j, const Word& w)
{
  j = json
  {
    {"한글", w.kr},
    {"영어", w.en},
    {"난이도", w.difficulty}
  };
}

void from_json(const json& j, Word& w)
{
  j.at("한글").get_to(w.kr);
  j.at("영어").get_to(w.en);
  j.at("난이도").get_to(w.difficulty);
}

int main()
{
  json j;
  int count = 0;
  for (auto& w : words)
  {
    if (count++ >= 10)
      break;
    cout << w.kr << ' ' << w.en << '\n';
  }

  return 0;
}
