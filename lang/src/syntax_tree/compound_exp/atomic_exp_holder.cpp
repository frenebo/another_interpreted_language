#include "./compound_exp.hpp"
#include "../atomic_exps/atomic_exps.hpp"

namespace syntax_tree::compound_exp
{
    AtomicExpHolder::AtomicExpHolder(atomic_exps::AtomicExp atomic_exp)
    : _atomic_exp(new atomic_exps::AtomicExp(atomic_exp))
    {
    }

    AtomicExpHolder::AtomicExpHolder(const AtomicExpHolder & holder)
    : _atomic_exp(new atomic_exps::AtomicExp(holder.atomic_exp()))
    {
    }

    AtomicExpHolder::~AtomicExpHolder() = default;

    const atomic_exps::AtomicExp & AtomicExpHolder::atomic_exp() const
    {
        return *_atomic_exp;
    }
}