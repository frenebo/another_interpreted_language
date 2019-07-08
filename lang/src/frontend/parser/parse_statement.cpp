#include "./parser.hpp"

namespace parser
{
    std::variant<ParseResult<syntax_tree::statements::Statement>, ParseError>
    parse_compound_exp_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::statements::Statement>, ParseError>
    parse_for_loop_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::statements::Statement>, ParseError>
    parse_if_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx);

    std::variant<ParseResult<syntax_tree::statements::Statement>, ParseError>
    parse_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        auto try_parse_compound_exp_statement = parse_compound_exp_statement(tokens, start_idx);
        auto try_parse_for_loop_statement =     parse_for_loop_statement(tokens, start_idx);
        auto try_parse_if_statement =           parse_if_statement(tokens, start_idx);

        // Return parsed statements if any of these were successful. There should be no overlaps,
        // e.g. a compound expression statement and a for loop statement were both successful
        if (std::holds_alternative<ParseResult<syntax_tree::statements::Statement>>(try_parse_compound_exp_statement))
        {
            return std::get<ParseResult<syntax_tree::statements::Statement>>(try_parse_compound_exp_statement);
        }

        if (std::holds_alternative<ParseResult<syntax_tree::statements::Statement>>(try_parse_for_loop_statement))
        {
            return std::get<ParseResult<syntax_tree::statements::Statement>>(try_parse_for_loop_statement);
        }

        if (std::holds_alternative<ParseResult<syntax_tree::statements::Statement>>(try_parse_if_statement))
        {
            return std::get<ParseResult<syntax_tree::statements::Statement>>(try_parse_if_statement);
        }

        // Find which parse attempt got the furthest, and return its error message
        const ParseError & compound_exp_err = std::get<ParseError>(try_parse_compound_exp_statement);
        const ParseError & for_loop_err = std::get<ParseError>(try_parse_for_loop_statement);
        const ParseError & if_statement_err = std::get<ParseError>(try_parse_if_statement);

        unsigned long compound_exp_pos = compound_exp_err.problem_token().pos_in_text();
        unsigned long for_loop_pos = for_loop_err.problem_token().pos_in_text();
        unsigned long if_statement_pos = if_statement_err.problem_token().pos_in_text();

        // If all of them got equally far, return non-statement type-specific error
        if (compound_exp_pos == for_loop_pos && for_loop_pos == if_statement_pos)
        {
            return ParseError(tokens[compound_exp_pos], "Could not parse statement");
        }

        // Return error of parse attempt that got the furthest
        if (compound_exp_pos > for_loop_pos && compound_exp_pos > if_statement_pos)
        {
            return compound_exp_err;
        }
        if (for_loop_pos > if_statement_pos)
        {
            return for_loop_err;
        }
        else
        {
            return if_statement_err;
        }
    }

    std::variant<ParseResult<syntax_tree::statements::Statement>, ParseError>
    parse_compound_exp_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        const std::string err_prefix = "Error parsing compound expression statement: ";

        unsigned long consumed_count = 0;

        auto try_parse_compound_exp = parse_compound_exp(tokens, start_idx + consumed_count, tokens::TokenType::SEMICOLON);
        if (std::holds_alternative<ParseError>(try_parse_compound_exp))
        {
            return std::get<ParseError>(try_parse_compound_exp).with_added_prefix(err_prefix);
        }

        const auto & compound_exp_parsed = std::get<ParseResult<syntax_tree::compound_exp::CompoundExp>>(try_parse_compound_exp);
        consumed_count += compound_exp_parsed.consumed_count();
        const auto & compound_exp = compound_exp_parsed.contained();

        auto expect_ending_semicolon = expect_token_types(
            {tokens::TokenType::SEMICOLON},
            tokens,
            start_idx + consumed_count
        );

        if (std::holds_alternative<ParseError>(expect_ending_semicolon))
        {
            return std::get<ParseError>(expect_ending_semicolon).with_added_prefix(err_prefix);
        }

        consumed_count += std::get<unsigned long>(expect_ending_semicolon);

        return ParseResult<syntax_tree::statements::Statement>(
            syntax_tree::statements::Statement(
                syntax_tree::statements::CompoundExpStatement(compound_exp)
            ),
            consumed_count
        );
    }

    std::variant<ParseResult<syntax_tree::statements::Statement>, ParseError>
    parse_for_loop_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        const std::string err_prefix = "Error parsing for loop: ";

        unsigned long consumed_count = 0;

        const auto expect_for_and_open_paren = expect_token_types(
            {
                tokens::TokenType::FOR_KEYWORD,
                tokens::TokenType::OPEN_PARENTHESIS,
            },
            tokens,
            start_idx + consumed_count
        );

        if (std::holds_alternative<ParseError>(expect_for_and_open_paren)) {
            return std::get<ParseError>(expect_for_and_open_paren).with_added_prefix(err_prefix);
        }

        consumed_count += std::get<unsigned long>(expect_for_and_open_paren);

        const auto try_parse_initialize_statement = parse_compound_exp(tokens, start_idx + consumed_count, tokens::TokenType::SEMICOLON);
        if (std::holds_alternative<ParseError>(try_parse_initialize_statement)) {
            return std::get<ParseError>(try_parse_initialize_statement).with_added_prefix("Error parsing for loop initializer statement: ");
        }
        const auto & initialize_statement_parsed = std::get<ParseResult<syntax_tree::compound_exp::CompoundExp>>(try_parse_initialize_statement);
        consumed_count += initialize_statement_parsed.consumed_count();

        const auto expect_first_semicolon_separator = expect_token_types(
            { tokens::TokenType::SEMICOLON },
            tokens,
            start_idx + consumed_count
        );
        if (std::holds_alternative<ParseError>(expect_first_semicolon_separator)) {
            return std::get<ParseError>(expect_first_semicolon_separator);
        }
        consumed_count += std::get<unsigned long>(expect_first_semicolon_separator);

        const auto try_parse_condition_statement = parse_compound_exp(tokens, start_idx + consumed_count, tokens::TokenType::SEMICOLON);
        if (std::holds_alternative<ParseError>(try_parse_condition_statement)) {
            return std::get<ParseError>(try_parse_condition_statement).with_added_prefix("Error parsing for loop condition statement: ");;
        }
        const auto & condition_statement_parsed = std::get<ParseResult<syntax_tree::compound_exp::CompoundExp>>(try_parse_condition_statement);
        consumed_count += condition_statement_parsed.consumed_count();

        const auto expect_second_semicolon_separator = expect_token_types(
            { tokens::TokenType::SEMICOLON },
            tokens,
            start_idx + consumed_count
        );
        if (std::holds_alternative<ParseError>(expect_second_semicolon_separator)) {
            return std::get<ParseError>(expect_second_semicolon_separator);
        }
        consumed_count += std::get<unsigned long>(expect_second_semicolon_separator);

        const auto try_parse_increment_statement = parse_compound_exp(tokens, start_idx + consumed_count, tokens::TokenType::CLOSE_PARENTHESIS);
        if (std::holds_alternative<ParseError>(try_parse_increment_statement)) {
            return std::get<ParseError>(try_parse_increment_statement).with_added_prefix("Error parsing for loop increment statement: ");
        }
        const auto & increment_statement_parsed = std::get<ParseResult<syntax_tree::compound_exp::CompoundExp>>(try_parse_increment_statement);
        consumed_count += increment_statement_parsed.consumed_count();

        const auto expect_close_paren_and_open_brace = expect_token_types(
            {
                tokens::TokenType::CLOSE_PARENTHESIS,
                tokens::TokenType::OPEN_BRACE,
            },
            tokens,
            start_idx + consumed_count
        );
        if (std::holds_alternative<ParseError>(expect_close_paren_and_open_brace)) {
            return std::get<ParseError>(expect_close_paren_and_open_brace).with_added_prefix(err_prefix);
        }
        consumed_count += std::get<unsigned long>(expect_close_paren_and_open_brace);

        const auto try_parse_statement_series = parse_statement_series(tokens, start_idx + consumed_count, tokens::TokenType::CLOSE_BRACE);
        if (std::holds_alternative<ParseError>(try_parse_statement_series)) {
            return std::get<ParseError>(try_parse_statement_series);
        }
        const auto & for_loop_body_parsed = std::get<ParseResult<syntax_tree::statement_series::StatementSeries>>(try_parse_statement_series);
        consumed_count += for_loop_body_parsed.consumed_count();

        const auto & initialize_statement = initialize_statement_parsed.contained();
        const auto & condition_statement = condition_statement_parsed.contained();
        const auto & increment_statement = increment_statement_parsed.contained();
        const auto & for_loop_body = for_loop_body_parsed.contained();

        return ParseResult<syntax_tree::statements::Statement>(
            syntax_tree::statements::Statement(
                syntax_tree::statements::ForLoopStatement(
                    initialize_statement,
                    condition_statement,
                    increment_statement,
                    for_loop_body
                )
            ),
            consumed_count
        );
    }

    std::variant<ParseResult<syntax_tree::statements::Statement>, ParseError>
    parse_if_statement(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        const std::string err_prefix = "Error parsing for loop: ";

        unsigned long consumed_count = 0;

        const auto expect_if_and_open_paren = expect_token_types(
            {
                tokens::TokenType::IF_KEYWORD,
                tokens::TokenType::OPEN_PARENTHESIS,
            },
            tokens,
            start_idx + consumed_count
        );
        if (std::holds_alternative<ParseError>(expect_if_and_open_paren)) {
            return std::get<ParseError>(expect_if_and_open_paren).with_added_prefix(err_prefix);
        }
        consumed_count += std::get<unsigned long>(expect_if_and_open_paren);

        const auto try_parse_if_condition = parse_compound_exp(tokens, start_idx + consumed_count, tokens::TokenType::CLOSE_PARENTHESIS);
        if (std::holds_alternative<ParseError>(try_parse_if_condition)) {
            return std::get<ParseError>(try_parse_if_condition).with_added_prefix("Error parsing if condition: ");
        }
        const auto if_condition_parsed = std::get<ParseResult<syntax_tree::compound_exp::CompoundExp>>(try_parse_if_condition);
        consumed_count += if_condition_parsed.consumed_count();

        const auto expect_close_paren_and_open_brace = expect_token_types(
            {
                tokens::TokenType::CLOSE_PARENTHESIS,
                tokens::TokenType::OPEN_BRACE,
            },
            tokens,
            start_idx + consumed_count
        );
        if (std::holds_alternative<ParseError>(expect_close_paren_and_open_brace)) {
            return std::get<ParseError>(expect_close_paren_and_open_brace).with_added_prefix(err_prefix);
        }
        consumed_count += std::get<unsigned long>(expect_close_paren_and_open_brace);

        const auto try_parse_if_body = parse_statement_series(tokens, start_idx + consumed_count, tokens::TokenType::CLOSE_BRACE);
        if (std::holds_alternative<ParseError>(try_parse_if_body))
        {
            return std::get<ParseError>(try_parse_if_body);
        }
        const auto & if_body_parsed = std::get<ParseResult<syntax_tree::statement_series::StatementSeries>>(try_parse_if_body);
        consumed_count += if_body_parsed.consumed_count();

        const auto expect_close_paren_close_brace = expect_token_types(
            { tokens::TokenType::CLOSE_BRACE },
            tokens,
            start_idx + consumed_count
        );
        if (std::holds_alternative<ParseError>(expect_close_paren_close_brace)) {
            return std::get<ParseError>(expect_close_paren_close_brace).with_added_prefix(err_prefix);
        }
        consumed_count += std::get<unsigned long>(expect_close_paren_close_brace);

        const auto & if_condition = if_condition_parsed.contained();
        const auto & if_body = if_body_parsed.contained();

        return ParseResult<syntax_tree::statements::Statement>(
            syntax_tree::statements::Statement(
                syntax_tree::statements::IfStatement(
                    if_condition,
                    if_body
                )
            ),
            consumed_count
        );
    }
}