#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>

namespace tokens
{
    enum TokenType {
        INTEGER_LITERAL,
        FLOAT_LITERAL,
        END_OF_INPUT_PLACEHOLDER,
    };

    std::string tok_type_to_string(TokenType);

    // @TODO: only store position in text and length, instead of copying whole string?
    class Token {
    public:
        Token(TokenType tok_type, std::string text, unsigned long pos_in_text);

        const std::string & text() const;
        TokenType tok_type() const;
        unsigned long pos_in_text() const;
    private:
        std::string _text;
        TokenType _tok_type;
        unsigned long _pos_in_text;
    };
}

#endif