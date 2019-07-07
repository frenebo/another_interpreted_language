#include "./statements.hpp"

namespace syntax_tree::statements
{
    Statement::Statement(VariantStatement contained_statement)
    : _contained_statement(contained_statement)
    {
    }

    const Statement::VariantStatement & Statement::contained_statement() const
    {
        return _contained_statement;
    }
}