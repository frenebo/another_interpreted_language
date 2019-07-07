#include "./lexer.hpp"


namespace lexer
{
    LexerError::LexerError(
        unsigned long problem_pos,
        const std::string & problem_message)
    : _problem_pos(problem_pos),
    _problem_message(problem_message)
    {
    }

    unsigned long LexerError::problem_pos() const
    {
        return _problem_pos;
    }

    const std::string & LexerError::problem_message() const
    {
        return _problem_message;
    }
}