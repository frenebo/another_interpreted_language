#include "./atomic_exps.hpp"

namespace syntax_tree::atomic_exps
{
    AtomicExp::AtomicExp(VariantAtomicExp contained)
    : _contained(contained)
    {
    }

    const AtomicExp::VariantAtomicExp & AtomicExp::contained() const
    {
        return _contained;
    }
}