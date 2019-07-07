#include "./lexer.hpp"

#include <ctype.h>
#include <optional>

namespace lexer
{
    std::optional<tokens::Token> parse_next_tok(const std::string & text, unsigned long start_idx);
    std::optional<tokens::Token> try_parse_number(const std::string & text, unsigned long start_idx);

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

            toks.push_back(*try_parse_next_tok);
        }

        // Add end of input token to vector
        toks.push_back(tokens::Token(tokens::TokenType::END_OF_INPUT_PLACEHOLDER, "", consumed_chars));

        return toks;
    }

    std::optional<tokens::Token> parse_next_tok(const std::string & text, unsigned long start_idx)
    {
        std::vector<std::optional<tokens::Token>> all_try_lexes;
        all_try_lexes.push_back(try_parse_number(text, start_idx));

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

    std::optional<tokens::Token> try_parse_number(const std::string & text, unsigned long start_idx)
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
}
