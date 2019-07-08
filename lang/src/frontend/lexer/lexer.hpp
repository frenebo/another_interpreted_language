#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>
#include <variant>

#include "../tokens/tokens.hpp"

namespace lexer
{
    class LexerError
    {
    public:
        LexerError(unsigned long problem_pos, const std::string & problem_message);

        unsigned long problem_pos() const;
        const std::string & problem_message() const;
    private:
        const unsigned long _problem_pos;
        const std::string _problem_message;
    };

    std::variant<std::vector<tokens::Token>, LexerError> lex_text(const std::string & text);
}

#endif