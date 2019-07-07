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
        case SEMICOLON:
            return "Semicolon";
        case IF_KEYWORD:
            return "If Keyword";
        case FOR_KEYWORD:
            return "For Keyword";
        case OPEN_PARENTHESIS:
            return "Open Parenthesis";
        case CLOSE_PARENTHESIS:
            return "Close Parenthesis";
        case OPEN_BRACE:
            return "Open BRACE";
        case CLOSE_BRACE:
            return "Close BRACE";
        case WHITESPACE:
            return "Whitespace";
        default:
            return "unimplented token type to string";
        }
    }
}