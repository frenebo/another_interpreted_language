#include "./parser.hpp"


namespace parser
{
    ParseError::ParseError(const tokens::Token & problem_token, const std::string & problem_reason)
    : _problem_token(problem_token),
    _problem_reason(problem_reason)
    {
    }

    const tokens::Token & ParseError::problem_token() const
    {
        return _problem_token;
    }

    const std::string & ParseError::problem_reason() const
    {
        return _problem_reason;
    }

    ParseError ParseError::with_added_prefix(const std::string & prefix) const
    {
        return ParseError(
            _problem_token,
            prefix + _problem_reason
        );
    }
}