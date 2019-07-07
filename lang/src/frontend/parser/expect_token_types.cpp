#include "./parser.hpp"

namespace parser
{
    std::variant<unsigned long, ParseError> expect_token_types(std::vector<tokens::TokenType> tok_types, std::vector<tokens::Token> tokens, unsigned long start_idx)
    {
        for (unsigned long i = 0; i < tok_types.size(); i++)
        {
            const tokens::Token & tok = tokens[start_idx + i];
            tokens::TokenType expected_tok_type = tok_types[i];
            tokens::TokenType actual_tok_type = tok.tok_type();

            if (actual_tok_type != expected_tok_type)
            {
                return ParseError(
                    tok,
                    "Expected " + tokens::tok_type_to_string(expected_tok_type) +
                    ", got " + tokens::tok_type_to_string(actual_tok_type)
                );
            }
        }

        return tok_types.size();
    }
}