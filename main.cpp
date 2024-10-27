#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

enum Difficulty
{
  None,
  Easy,
  Normal,
  Hard
};

struct Word
{
  string kr;
  string en;
  Difficulty difficulty;
};

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

Word set_word(string text)
{
  Word w;
  string temp = "", str;
  int count = 0;
  int re = 0;
  for (string::iterator it = text.begin(); it != text.end(); it++)
  {
    if (*it == '"')
    {
      it++;
      while (*it != '"')
      {
        temp += *it;
      }
    }

    if (*it== ',')
    {
      switch (count++)
      {
      default:
        str = temp;
        temp = "";
      case 0:
        w.en = str;
        break;
      case 1:
        w.kr = str;
        break;
      case 2:
        if (str == "초등")
          w.difficulty = Difficulty::Easy;
        else if (str == "중고")
          w.difficulty = Difficulty::Normal;
        else if(str == "전문")
          w.difficulty = Difficulty::Hard;
        else
          w.difficulty = Difficulty::None;
        break;
      }
    }
    else
      temp += *it;
  }
}

int main()
{
  vector<Word> words;
  ifstream ifs("words.txt");
  if (ifs.is_open())
  {
    while (!ifs.eof())
    {
      string str;
      getline(ifs, str);
      words.push_back(set_word(str));
    }
  }
  return 0;
}
