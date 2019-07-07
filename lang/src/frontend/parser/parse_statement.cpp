#include "./parser.hpp"

namespace parser
{
    std::variant<ParseResult<syntax_tree::statements::Statement>, ParseError>
    parse_statement(const std::vector<tokens::Token> tokens, unsigned long start_idx)
    {

    }
}