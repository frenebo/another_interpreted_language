#include "./parser.hpp"
#include "../../syntax_tree/atomic_exps/atomic_exps.hpp"

namespace parser
{
    std::variant<ParseResult<syntax_tree::atomic_exps::AtomicExp>, ParseError>
    parse_parenthesized_exp(const std::vector<tokens::Token> & tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::atomic_exps::AtomicExp>, ParseError>
    parse_identifier_exp(const std::vector<tokens::Token> & tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::atomic_exps::AtomicExp>, ParseError>
    parse_number_exp(const std::vector<tokens::Token> & tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::atomic_exps::AtomicExp>, ParseError>
    parse_atomic_exp(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        std::vector<std::variant<ParseResult<syntax_tree::atomic_exps::AtomicExp>, ParseError>> results {
            parse_parenthesized_exp(tokens, start_idx),
            parse_identifier_exp(tokens, start_idx),
            parse_number_exp(tokens, start_idx),
        };

        unsigned long shortest_err_pos = ULONG_MAX;
        std::optional<ParseError> furthest_progress_error;

        for (const std::variant<ParseResult<syntax_tree::atomic_exps::AtomicExp>, ParseError> & result : results)
        {
            if (std::holds_alternative<ParseResult<syntax_tree::atomic_exps::AtomicExp>>(result))
            {
                return std::get<ParseResult<syntax_tree::atomic_exps::AtomicExp>>(result);
            }
            else
            {
                const ParseError & result_err = std::get<ParseError>(result);
                // This is the error of the parse attempt that got the furthest if:
                // 1. This is the first error, or
                // 2. This error got further than the last furthest one
                if (!furthest_progress_error.has_value() ||
                    result_err.problem_token().pos_in_text() > furthest_progress_error->problem_token().pos_in_text())
                {
                    furthest_progress_error = result_err;
                }

                // update shortest error length
                if (result_err.problem_token().pos_in_text() < shortest_err_pos)
                {
                    shortest_err_pos = result_err.problem_token().pos_in_text();
                }
            }
        }

        // If all parse attempts got the same distance
        if (shortest_err_pos == furthest_progress_error->problem_token().pos_in_text())
        {
            return ParseError(
                furthest_progress_error->problem_token(),
                "Could not parse atomic expression"
            );
        }
        else
        {
            return *furthest_progress_error;
        }
    }


    std::variant<ParseResult<syntax_tree::atomic_exps::AtomicExp>, ParseError>
    parse_number_exp(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        const tokens::Token & next_tok = tokens[start_idx];
        if (next_tok.tok_type() == tokens::TokenType::FLOAT_LITERAL)
        {
            return ParseResult<syntax_tree::atomic_exps::AtomicExp>(
                syntax_tree::atomic_exps::AtomicExp(
                    syntax_tree::atomic_exps::NumberExp(next_tok.text(), true)
                ),
                1
            );
        }
        else if (next_tok.tok_type() == tokens::TokenType::INTEGER_LITERAL)
        {
            return ParseResult<syntax_tree::atomic_exps::AtomicExp>(
                syntax_tree::atomic_exps::AtomicExp(
                    syntax_tree::atomic_exps::NumberExp(next_tok.text(), false)
                ),
                1
            );
        }
        else
        {
            return ParseError(
                tokens[start_idx],
                "Expected number"
            );
        }
    }

    std::variant<ParseResult<syntax_tree::atomic_exps::AtomicExp>, ParseError>
    parse_identifier_exp(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        const tokens::Token & next_tok = tokens[start_idx];

        if (next_tok.tok_type() != tokens::TokenType::IDENTIFIER)
        {
            return ParseError(next_tok, "Expected identifier");
        }

        return ParseResult<syntax_tree::atomic_exps::AtomicExp>(
            syntax_tree::atomic_exps::AtomicExp(
                syntax_tree::atomic_exps::IdentifierExp(next_tok.text())
            ),
            1
        );
    }

    std::variant<ParseResult<syntax_tree::atomic_exps::AtomicExp>, ParseError>
    parse_parenthesized_exp(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        const std::string err_prefix = "Problem parsing parenthesized expression: ";

        unsigned long consumed_count = 0;

        auto expect_open_paren = expect_token_types(
            { tokens::TokenType::OPEN_PARENTHESIS },
            tokens,
            start_idx + consumed_count
        );
        if (std::holds_alternative<ParseError>(expect_open_paren)) {
            return std::get<ParseError>(expect_open_paren).with_added_prefix(err_prefix);
        }
        consumed_count += std::get<unsigned long>(expect_open_paren);

        auto try_parse_compound_exp = parse_compound_exp(tokens, start_idx, tokens::TokenType::CLOSE_PARENTHESIS);

        if (std::holds_alternative<ParseError>(try_parse_compound_exp))
        {
            return std::get<ParseError>(try_parse_compound_exp);
        }
        auto parse_compound_exp_result = std::get<ParseResult<syntax_tree::compound_exp::CompoundExp>>(try_parse_compound_exp);
        consumed_count += parse_compound_exp_result.consumed_count();
        const auto & compound_exp = parse_compound_exp_result.contained();

        auto expect_close_paren = expect_token_types(
            { tokens::TokenType::CLOSE_PARENTHESIS },
            tokens,
            start_idx + consumed_count
        );
        if (std::holds_alternative<ParseError>(expect_close_paren)) {
            return std::get<ParseError>(expect_close_paren).with_added_prefix(err_prefix);
        }
        consumed_count += std::get<unsigned long>(expect_close_paren);

        return ParseResult<syntax_tree::atomic_exps::AtomicExp>(
            syntax_tree::atomic_exps::AtomicExp(
                syntax_tree::atomic_exps::ParenthesizedExp(compound_exp)
            ),
            consumed_count
        );
    }
}