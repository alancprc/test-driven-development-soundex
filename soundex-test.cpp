#include <string>
#include "gmock/gmock.h"

using namespace testing;

std::string padZero(const std::string &str)
{
    const int maxLength{4};
    if (str.length() < 4)
      return str + std::string(maxLength - str.length(), '0');
    return str;
}
class Soundex
{
 public:
  std::string encode(const std::string &word) const
  {
    auto encoded = word.substr(0, 1);
    if (word.size() > 1) encoded += "1";
    return padZero(encoded);
  }
};

class SoundexEncoding : public testing::Test
{
 public:
  Soundex soundex;
};

TEST_F(SoundexEncoding, RetainSoleLetterOfOneLetterWord)
{
  ASSERT_THAT(soundex.encode("Ab"), Eq("A100"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits)
{
  ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}
