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
    return padZero(word);
  }
};

class SoundexEncoding : public testing::Test
{
 public:
  Soundex soundex;
};

TEST_F(SoundexEncoding, RetainSoleLetterOfOneLetterWord)
{
  ASSERT_THAT(soundex.encode("A"), Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits)
{
  ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}
