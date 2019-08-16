#include <string>
#include <unordered_map>
#include "gmock/gmock.h"

using namespace testing;

const int maxLength{4};

std::string padZero(const std::string &str)
{
  if (str.size() < 4) return str + std::string(maxLength - str.size(), '0');
  return str;
}

std::string head(const std::string &word) { return word.substr(0, 1); }
std::string tail(const std::string &word) { return word.substr(1); }

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
  auto it = encodings.find(letter);
  return it == encodings.end() ? "" : it->second;
}

std::string encodedDigits(const std::string &word)
{
  std::string result;
  for (auto it = word.cbegin(); it != word.cend(); ++it) {
    result += encodedDigit(*it);
  }
  return result.substr(0, maxLength - 1);
}

class Soundex
{
 public:
  std::string encode(const std::string &word) const
  {
    return padZero(head(word) + encodedDigits(tail(word)));
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

TEST_F(SoundexEncoding, IgnoresNonAlphabetics)
{
  ASSERT_THAT(soundex.encode("A#"), Eq("A000"));
}

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits)
{
  ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters)
{
  ASSERT_THAT(soundex.encode("Dcblb").size(), Eq(4u));
}
