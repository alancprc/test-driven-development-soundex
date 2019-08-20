#include "char-string-util.h"

char lower(char ch) { return std::tolower(static_cast<unsigned char>(ch)); }

bool isVowel(char ch)
{
  return std::string("aeiouAEIOU").find(ch) != std::string::npos;
}

std::string head(const std::string &word) { return word.substr(0, 1); }

std::string tail(const std::string &word) { return word.substr(1); }

std::string paddingChar(const std::string &str, char ch, size_t size)
{
  if (str.size() < 4) return str + std::string(size - str.size(), ch);
  return str;
}

std::string upperFront(const std::string &string)
{
  return std::string(1,
                     std::toupper(static_cast<unsigned char>(string.front())));
}

