#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <variant>

#include "../../syntax_tree/statement_series/statement_series.hpp"

#include "../tokens/tokens.hpp"
#include "./parse_result.hpp"

namespace parser
{
    class ParseError
    {
    public:
        ParseError(const tokens::Token & problem_token, std::string problem_reason);
        const tokens::Token & problem_token() const;
        const std::string & problem_reason() const;
    private:
        tokens::Token _problem_token;
        std::string _problem_reason;
    };

    std::variant<ParseResult<syntax_tree::statement_series::StatementSeries>, ParseError>
    parse_statement_series(const std::vector<tokens::Token> tokens, unsigned long start_idx, tokens::TokenType stop_tok_type);

    std::variant<ParseResult<syntax_tree::statements::Statement>, ParseError>
    parse_statement(const std::vector<tokens::Token> tokens, unsigned long start_idx);
}

#endif
