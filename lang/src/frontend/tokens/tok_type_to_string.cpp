#include "./tokens.hpp"

namespace tokens
{
    std::string tok_type_to_string(TokenType tok_type)
    {
        switch (tok_type) {
        case INTEGER_LITERAL:
            return "Integer Literal";
        case FLOAT_LITERAL:
            return "Float Literal";
        case END_OF_INPUT_PLACEHOLDER:
            return "End of Input";
        default:
            return "unimplented token type to string";
        }
    }
}