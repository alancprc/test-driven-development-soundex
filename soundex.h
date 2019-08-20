#ifndef SOUNDEX_H_
#define SOUNDEX_H_
#include <string>

class Soundex
{
 public:
  std::string encode(const std::string &word) const;
  std::string encodedDigit(char letter) const;
 private:
  std::string encodedDigits(const std::string &word) const;
  bool IsComplete(std::string word) const;
  void encodeHead(std::string &result, const std::string &word) const;
  void encodeTail(std::string &result, const std::string &word) const;
  void encodeLetter(std::string &result, char letter) const;
  std::string lastDigit(const std::string &str) const;

  const size_t maxLength{4};
  const std::string NotADigit{"*"};
  const char padChar{'0'};
};

#endif
