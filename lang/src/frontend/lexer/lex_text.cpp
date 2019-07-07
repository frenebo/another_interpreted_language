#include "./lexer.hpp"

#include <ctype.h>
#include <optional>

namespace lexer
{
    std::optional<tokens::Token> parse_next_tok(const std::string & text, unsigned long start_idx);
    std::optional<tokens::Token> try_lex_number(const std::string & text, unsigned long start_idx);
    std::optional<tokens::Token> try_lex_whitespace(const std::string & text, unsigned long start_idx);
    std::optional<tokens::Token> try_lex_exact_strings(const std::string & text, unsigned long start_idx);

    std::variant<std::vector<tokens::Token>, LexerError> lex_text(const std::string & text)
    {
        unsigned long consumed_chars = 0;

        std::vector<tokens::Token> toks;

        while (consumed_chars < text.size())
        {
            auto try_parse_next_tok = parse_next_tok(text, consumed_chars);
            if (!try_parse_next_tok.has_value())
            {
                return LexerError(consumed_chars, "Could not lex text");
            }

            // Don't push whitespace to vector
            if (try_parse_next_tok->tok_type() != tokens::TokenType::WHITESPACE)
            {
                toks.push_back(*try_parse_next_tok);
            }
        }

        // Add end of input token to vector
        toks.push_back(tokens::Token(tokens::TokenType::END_OF_INPUT_PLACEHOLDER, "", consumed_chars));

        return toks;
    }

    std::optional<tokens::Token> parse_next_tok(const std::string & text, unsigned long start_idx)
    {
        std::vector<std::optional<tokens::Token>> all_try_lexes {
            try_lex_number(text, start_idx),
            try_lex_exact_strings(text, start_idx),
            try_lex_whitespace(text, start_idx),
        };

        std::optional<tokens::Token> longest_result;

        for (const std::optional<tokens::Token> tok : all_try_lexes)
        {
            if (tok.has_value())
            {
                // If this is either the first match or the longest match so far,
                // set longest_result = tok
                if (!longest_result.has_value() || tok->text().size() > longest_result->text().size())
                {
                    longest_result = tok;
                }
            }
        }

        return longest_result;
    }

    std::optional<tokens::Token> try_lex_number(const std::string & text, unsigned long start_idx)
    {
        unsigned long digits_before_period = 0;
        unsigned long digits_after_period = 0;
        bool seen_period = false;
        unsigned long pos_in_text = start_idx;

        while (pos_in_text < text.size())
        {
            if (isdigit(text[pos_in_text]))
            {
                if (seen_period)
                {
                    digits_after_period++;
                }
                else
                {
                    digits_before_period++;
                }
            }
            else if (text[pos_in_text] == '.')
            {
                if (seen_period) break;
                else seen_period = true;
            }
            else
            {
                break;
            }
        }

        if (digits_before_period + digits_after_period == 0)
        {
            return std::optional<tokens::Token>();
        }

        unsigned long consumed_chars = digits_before_period + digits_after_period + (seen_period ? 1 : 0);

        tokens::TokenType tok_type = seen_period ? tokens::TokenType::FLOAT_LITERAL : tokens::TokenType::INTEGER_LITERAL;

        return tokens::Token(
            tok_type,
            text.substr(start_idx, consumed_chars),
            start_idx
        );
    }

    std::optional<tokens::Token> try_lex_whitespace(const std::string & text, unsigned long start_idx)
    {
        const std::string whitespace_chars = " \n\t";
        unsigned long consumed_count;
        while (consumed_count < text.size() - start_idx &&
            whitespace_chars.find(text[start_idx + consumed_count]) != std::string::npos)
        {
            consumed_count++;
        }

        if (consumed_count == 0) return std::optional<tokens::Token>();

        return tokens::Token(
            tokens::TokenType::WHITESPACE,
            text.substr(start_idx, consumed_count),
            start_idx
        );
    }

    std::optional<tokens::Token> try_lex_exact_strings(const std::string & text, unsigned long start_idx)
    {
        // does the const std::string & do anything?
        const std::vector<std::pair<tokens::TokenType, const std::string>> exact_matches {
            { tokens::TokenType::SEMICOLON, ";" },
            { tokens::TokenType::IF_KEYWORD, "if" },
            { tokens::TokenType::FOR_KEYWORD, "for" },
            { tokens::TokenType::OPEN_PARENTHESIS, "(" },
            { tokens::TokenType::CLOSE_PARENTHESIS, ")" },
            { tokens::TokenType::OPEN_BRACE, "{" },
            { tokens::TokenType::CLOSE_BRACE, "}" },
        };

        std::optional<tokens::Token> longest_match;

        for (const auto & exact_match : exact_matches)
        {
            tokens::TokenType tok_type = exact_match.first;
            const std::string & exact_str = exact_match.second;

            // If there isn't enough room left in the text for an exact match to this string
            if (exact_str.length() > text.size() - start_idx) continue;


            const bool matches = text.compare(start_idx, exact_str.size(), exact_str) == 0;
            if (!matches) continue;

            // If this is the first match found, or the longest match found so far.
            if (!longest_match.has_value() || exact_str.size() > longest_match->text().size())
            {
                longest_match = tokens::Token(tok_type, exact_str, start_idx);
            }
        }

        return longest_match;
    }
}
