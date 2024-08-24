#include "Lexer.hpp"

namespace charinfo {
LLVM_READNONE inline bool isWhiteSpace(char c) {
  return c == ' ' or c == '\t' or c == '\f' or c == '\v' or c == '\r' or
         c == '\n';
}

LLVM_READNONE inline bool isDigit(char c) { return c >= '0' and c <= '9'; }

LLVM_READNONE inline bool isLetter(char c) {
  return (c >= 'A' and c <= 'Z') or (c >= 'a' and c <= 'z');
}
} // namespace charinfo

void Lexer::formToken(Token &tok, const char *tokEnd, Token::TokenKind kind) {
  tok.kind = kind;
  tok.text = llvm::StringRef(bufferPtr, tokEnd - bufferPtr);
  bufferPtr = tokEnd;
}

void Lexer::next(Token &token) {
  while (*bufferPtr && charinfo::isWhiteSpace(*bufferPtr)) {
    ++bufferPtr;
  }

  if (not *bufferPtr) {
    token.kind = Token::eoi;
    return;
  }

  if (charinfo::isLetter(*bufferPtr)) {
    const char *end = bufferPtr + 1;
    while (charinfo::isLetter(*end))
      ++end;
    llvm::StringRef name(bufferPtr, end - bufferPtr);
    Token::TokenKind kind = name == "with" ? Token::KW_with : Token::ident;
    formToken(token, end, kind);
    return;
  } else if (charinfo::isDigit(*bufferPtr)) {
    const char *end = bufferPtr + 1;
    while (charinfo::isDigit(*end))
      ++end;
    formToken(token, end, Token::number);
    return;
  } else {
    switch (*bufferPtr) {
    case '+':
      formToken(token, bufferPtr + 1, Token::plus);
      break;
    case '-':
      formToken(token, bufferPtr + 1, Token::minus);
      break;
    case '*':
      formToken(token, bufferPtr + 1, Token::star);
      break;
    case '/':
      formToken(token, bufferPtr + 1, Token::slash);
      break;
    case '(':
      formToken(token, bufferPtr + 1, Token::l_paren);
      break;
    case ')':
      formToken(token, bufferPtr + 1, Token::r_paren);
      break;
    case ':':
      formToken(token, bufferPtr + 1, Token::colon);
      break;
    case ',':
      formToken(token, bufferPtr + 1, Token::comma);
      break;
    default:
      formToken(token, bufferPtr + 1, Token::unknown);
      break;
    }
    return;
  }
}
