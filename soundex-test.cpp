#include <string>
#include "gmock/gmock.h"
#include <unordered_map>

using namespace testing;

std::string padZero(const std::string &str)
{
  const int maxLength{4};
  if (str.size() < 4) return str + std::string(maxLength - str.size(), '0');
  return str;
}

std::string head(const std::string &word) { return word.substr(0, 1); }

std::string encodedDigit(char letter)
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
  return encodings.find(letter)->second;
}

std::string encodedDigits(const std::string &word)
{
  if (word.size() > 1) return encodedDigit(word[1]);
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

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits)
{
  ASSERT_THAT(soundex.encode("Ax"), Eq("A200"));
}
