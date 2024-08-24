#include "../src/Lexer.hpp" // Adjust the include path as needed
#include "llvm/ADT/StringRef.h"
#include <gtest/gtest.h>

// Test fixture for Lexer tests
class LexerTest : public ::testing::Test {
protected:
  LexerTest() {}

  // Utility function to get the next token from the lexer
  Token getNextToken(Lexer &lexer) {
    Token token;
    lexer.next(token);
    return token;
  }
};

// Test: Lexer should recognize identifiers
TEST_F(LexerTest, RecognizesTokens) {
  llvm::StringRef buffer = "with a, b: a * (4 + b) / 6";
  Lexer lexer(buffer);

  Token token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::KW_with);
  EXPECT_EQ(token.getText(), "with");

  token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::ident);
  EXPECT_EQ(token.getText(), "a");

  token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::comma);
  EXPECT_EQ(token.getText(), ",");

  token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::ident);
  EXPECT_EQ(token.getText(), "b");

  token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::colon);
  EXPECT_EQ(token.getText(), ":");

  token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::ident);
  EXPECT_EQ(token.getText(), "a");

  token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::star);
  EXPECT_EQ(token.getText(), "*");

  token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::l_paren);
  EXPECT_EQ(token.getText(), "(");

  token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::number);
  EXPECT_EQ(token.getText(), "4");

  token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::plus);
  EXPECT_EQ(token.getText(), "+");

  token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::ident);
  EXPECT_EQ(token.getText(), "b");

  token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::r_paren);
  EXPECT_EQ(token.getText(), ")");

  token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::slash);
  EXPECT_EQ(token.getText(), "/");

  token = getNextToken(lexer);
  EXPECT_EQ(token.getKind(), Token::number);
  EXPECT_EQ(token.getText(), "6");
}

// Additional tests can be added here following the same pattern

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
