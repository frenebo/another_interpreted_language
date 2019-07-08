#include "./atomic_exps.hpp"
#include "../compound_exp/compound_exp.hpp"

namespace syntax_tree::atomic_exps
{
    ParenthesizedExp::ParenthesizedExp(compound_exp::CompoundExp contained)
    : _contained(new compound_exp::CompoundExp(contained))
    {
    }

    ParenthesizedExp::ParenthesizedExp(const ParenthesizedExp & paren_exp)
    : _contained(new compound_exp::CompoundExp(paren_exp.contained()))
    {
    }

    ParenthesizedExp::~ParenthesizedExp() = default;

    const compound_exp::CompoundExp & ParenthesizedExp::contained() const
    {
        return *_contained;
    }
}