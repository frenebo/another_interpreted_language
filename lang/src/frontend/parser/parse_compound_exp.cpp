#include "./parser.hpp"

namespace parser
{
    std::variant<ParseResult<syntax_tree::compound_exp::CompoundExp>, ParseError>
    parse_compound_exp(const std::vector<tokens::Token> tokens, unsigned long start_idx, tokens::TokenType stop_tok_type)
    {

    }
}