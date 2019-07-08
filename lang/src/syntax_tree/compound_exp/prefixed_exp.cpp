#include "./compound_exp.hpp"

namespace syntax_tree::compound_exp
{
    PrefixedExp::PrefixedExp(PrefixType prefix_type, NonCompoundExp contained)
    : _prefix_type(prefix_type),
    _contained(contained)
    {
    }

    PrefixedExp::PrefixType PrefixedExp::prefix_type() const
    {
        return _prefix_type;
    }

    const NonCompoundExp & PrefixedExp::contained() const
    {
        return _contained;
    }
}