#include "./tokens.hpp"

namespace tokens
{
    Token::Token(TokenType tok_type, std::string text, unsigned long pos_in_text)
    : _text(text),
    _tok_type(tok_type),
    _pos_in_text(pos_in_text)
    {
    }

    const std::string & Token::text() const
    {
        return _text;
    }

    TokenType Token::tok_type() const
    {
        return _tok_type;
    }

    unsigned long Token::pos_in_text() const
    {
        return _pos_in_text;
    }
}