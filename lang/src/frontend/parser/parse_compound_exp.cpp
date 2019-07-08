#include "./parser.hpp"

namespace parser
{
    std::variant<ParseResult<syntax_tree::compound_exp::CompoundExp::BinaryOpType>, ParseError>
    parse_operator(const std::vector<tokens::Token> & tokens, unsigned long start_idx)
    {
        const tokens::Token & next_tok = tokens[start_idx];

        if (next_tok.tok_type() == tokens::TokenType::PLUS_SIGN)
        {
            return ParseResult<syntax_tree::compound_exp::CompoundExp::BinaryOpType>(
                syntax_tree::compound_exp::CompoundExp::BinaryOpType::PLUS,
                1
            );
        }
        else if (next_tok.tok_type() == tokens::TokenType::MINUS_SIGN)
        {
            return ParseResult<syntax_tree::compound_exp::CompoundExp::BinaryOpType>(
                syntax_tree::compound_exp::CompoundExp::BinaryOpType::MINUS,
                1
            );
        }
        else
        {
            return ParseError(
                tokens[start_idx],
                "Expected binary operator"
            );
        }
    }

    std::variant<ParseResult<syntax_tree::compound_exp::CompoundExp>, ParseError>
    parse_compound_exp(const std::vector<tokens::Token> & tokens, unsigned long start_idx, tokens::TokenType stop_tok_type)
    {

    }
}