#include <string>
#include "gmock/gmock.h"

using namespace testing;

std::string padZero(const std::string &str)
{
  const int maxLength{4};
  if (str.length() < 4) return str + std::string(maxLength - str.length(), '0');
  return str;
}

std::string head(const std::string &word) { return word.substr(0, 1); }

std::string encodedDigits(const std::string &word)
{
  if (word.size() > 1) return "1";
  return "";
}

class Soundex
{
 public:
  std::string encode(const std::string &word) const
  {
    return padZero(head(word) + encodedDigits(word));
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
