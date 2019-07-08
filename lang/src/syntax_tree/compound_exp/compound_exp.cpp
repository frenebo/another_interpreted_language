#include "./compound_exp.hpp"

namespace syntax_tree::compound_exp
{
    CompoundExp::CompoundExp(NonCompoundExp lhs, BinaryOpType op_type, NonCompoundExp rhs)
    : _lhs(lhs),
    _op_type(op_type),
    _rhs(rhs)
    {
    }

    const NonCompoundExp & CompoundExp::lhs() const
    {
        return _lhs;
    }

    CompoundExp::BinaryOpType CompoundExp::op_type() const
    {
        return _op_type;
    }

    const NonCompoundExp & CompoundExp::rhs() const
    {
        return _rhs;
    }
}