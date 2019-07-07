#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <variant>
#include <optional>

#include "../../syntax_tree/statement_series/statement_series.hpp"

#include "../tokens/tokens.hpp"
#include "./parse_result.hpp"

namespace parser
{
    class ParseError
    {
    public:
        ParseError(const tokens::Token & problem_token, const std::string & problem_reason);
        const tokens::Token & problem_token() const;
        const std::string & problem_reason() const;
        ParseError with_added_prefix(const std::string & prefix) const;
    private:
        tokens::Token _problem_token;
        std::string _problem_reason;
    };

    // Returns number of tokens expected if successful
    std::variant<unsigned long, ParseError>
    expect_token_types(std::vector<tokens::TokenType> tok_types, std::vector<tokens::Token> tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::statement_series::StatementSeries>, ParseError>
    parse_statement_series(const std::vector<tokens::Token> tokens, unsigned long start_idx, tokens::TokenType stop_tok_type);

    std::variant<ParseResult<syntax_tree::statements::Statement>, ParseError>
    parse_statement(const std::vector<tokens::Token> tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::compound_exp::CompoundExp>, ParseError>
    parse_compound_exp(const std::vector<tokens::Token> tokens, unsigned long start_idx, tokens::TokenType stop_tok_type);
}

#endif
