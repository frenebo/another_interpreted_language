#include "./parser.hpp"

namespace parser
{
    std::variant<ParseResult<syntax_tree::statement_series::StatementSeries>, ParseError>
    parse_statement_series(const std::vector<tokens::Token> tokens, unsigned long start_idx, tokens::TokenType stop_tok_type)
    {
        std::vector<syntax_tree::statements::Statement> statements;

        unsigned long consumed_count;

        while (tokens[start_idx + consumed_count].tok_type() != stop_tok_type)
        {
            auto try_parse_next_statement = parse_statement(tokens, start_idx + consumed_count);

            if (std::holds_alternative<ParseError>(try_parse_next_statement))
            {
                return std::get<ParseError>(try_parse_next_statement);
            }

            const auto & next_statement_parsed = std::get<ParseResult<syntax_tree::statements::Statement>>(try_parse_next_statement);

            consumed_count += next_statement_parsed.consumed_count();
            statements.push_back(next_statement_parsed.contained());
        }

        return ParseResult<syntax_tree::statement_series::StatementSeries>(
            syntax_tree::statement_series::StatementSeries(statements),
            consumed_count
        );
    }
}