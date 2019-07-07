#include "./statements.hpp"

namespace syntax_tree::statements
{
    CompoundExpStatement::CompoundExpStatement(syntax_tree::compound_exp::CompoundExp compound_exp)
    : _compound_exp(compound_exp)
    {
    }

    const syntax_tree::compound_exp::CompoundExp & CompoundExpStatement::compound_exp() const
    {
        return _compound_exp;
    }
}