#include "./compound_exp.hpp"
#include "../atomic_exps/atomic_exps.hpp"

namespace syntax_tree::compound_exp
{
    NonCompoundExp::NonCompoundExp(VariantPrefixedOrSuffixedOrAtomic contained)
    : _contained(new VariantPrefixedOrSuffixedOrAtomic(contained))
    {
    }
    NonCompoundExp::NonCompoundExp(const NonCompoundExp & exp)
    : _contained(new VariantPrefixedOrSuffixedOrAtomic(exp.contained()))
    {
    }

    NonCompoundExp::~NonCompoundExp() = default;

    const NonCompoundExp::VariantPrefixedOrSuffixedOrAtomic & NonCompoundExp::contained() const
    {
        return *_contained;
    }
}