#include "soundex.h"
#include <unordered_map>

const int maxLength{4};
const std::string NotADigit("*");

std::string Soundex::encode(const std::string &word) const
{
  return padZero(upperFront(head(word)) + tail(encodedDigits(word)));
}

std::string padZero(const std::string &str)
{
  if (str.size() < 4) return str + std::string(maxLength - str.size(), '0');
  return str;
}

std::string head(const std::string &word) { return word.substr(0, 1); }
std::string tail(const std::string &word) { return word.substr(1); }
char lower(char ch) { return std::tolower(static_cast<unsigned char>(ch)); }

std::string Soundex::encodedDigit(char letter) const
{
  // clang-format off
  const std::unordered_map<char, std::string> encodings{
      {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},
      {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"},
      {'q', "2"}, {'s', "2"}, {'x', "2"}, {'z', "2"},
      {'d', "3"}, {'t', "3"},
      {'l', "4"},
      {'m', "5"}, {'n', "5"},
      {'r', "6"}};
  // clang-format on
  auto it = encodings.find(lower(letter));
  return it == encodings.end() ? NotADigit : it->second;
}

bool Soundex::IsComplete(std::string word) const
{
  return word.size() == maxLength;
}

std::string lastDigit(const std::string str)
{
  if (str.empty()) return NotADigit;
  return std::string(1, str.back());
}

void Soundex::encodeHead(std::string &result, const std::string &word)const
{
  result += encodedDigit(word.front());
}

bool isVowel(char ch)
{
  return std::string("aeiouAEIOU").find(ch) != std::string::npos;
}

void Soundex::encodeLetter(std::string &result, char letter) const
{
  static char lastLetter = '\0';
  auto digit = encodedDigit(letter);
  if (digit != NotADigit and
      (isVowel(lastLetter) or digit != lastDigit(result)))
    result += digit;
  lastLetter = letter;
}

void Soundex::encodeTail(std::string &result, const std::string &word) const
{
  for (auto it = word.begin(); it != word.end(); ++it) {
    if (IsComplete(result)) break;

    encodeLetter(result, *it);
  }
}

std::string Soundex::encodedDigits(const std::string &word) const
{
  std::string result;
  encodeHead(result, word);
  encodeTail(result, word);
  return result;
}

std::string upperFront(const std::string &string)
{
  return std::string(1,
                     std::toupper(static_cast<unsigned char>(string.front())));
}
