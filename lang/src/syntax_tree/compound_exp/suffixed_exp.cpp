#include "./compound_exp.hpp"

namespace syntax_tree::compound_exp
{
    SuffixedExp::SuffixedExp(SuffixType suffix_type, NonCompoundExp contained)
    : _suffix_type(suffix_type),
    _contained(contained)
    {
    }

    SuffixedExp::SuffixType SuffixedExp::suffix_type() const
    {
        return _suffix_type;
    }

    const NonCompoundExp & SuffixedExp::contained() const
    {
        return _contained;
    }
}