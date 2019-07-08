#ifndef SYNTAX_TREE_COMPOUND_EXP_HPP
#define SYNTAX_TREE_COMPOUND_EXP_HPP

#include <memory>
#include <variant>

// #include "../atomic_exps/atomic_exps.hpp"

namespace syntax_tree::atomic_exps
{
    class AtomicExp;
}

namespace syntax_tree::compound_exp
{
    class PrefixedExp;
    class SuffixedExp;

    class AtomicExpHolder
    {
    public:
        AtomicExpHolder(atomic_exps::AtomicExp atomic_exp);
        AtomicExpHolder(const AtomicExpHolder & holder);
        ~AtomicExpHolder();
        const atomic_exps::AtomicExp & atomic_exp() const;
    private:
        std::unique_ptr<atomic_exps::AtomicExp> _atomic_exp;
    };

    class NonCompoundExp
    {
    public:
        typedef std::variant<
            PrefixedExp,
            SuffixedExp,
            AtomicExpHolder
        > VariantPrefixedOrSuffixedOrAtomic;

        NonCompoundExp(VariantPrefixedOrSuffixedOrAtomic contained);
        NonCompoundExp(const NonCompoundExp & exp);
        ~NonCompoundExp();

        const VariantPrefixedOrSuffixedOrAtomic & contained() const;
    private:
        const std::unique_ptr<VariantPrefixedOrSuffixedOrAtomic> _contained;
    };

    class PrefixedExp
    {
    public:
        enum PrefixType
        {
            Increment,
            Decrement,
        };

        PrefixedExp(PrefixType prefix_type, NonCompoundExp contained);
        PrefixType prefix_type() const;
        const NonCompoundExp & contained() const;
    private:
        const PrefixType _prefix_type;
        const NonCompoundExp _contained;
    };

    class SuffixedExp
    {
    public:
        enum SuffixType
        {
            Increment,
            Decrement,
        };

        SuffixedExp(SuffixType suffix_type, NonCompoundExp contained);
        SuffixType suffix_type() const;
        const NonCompoundExp & contained() const;
    private:
        const SuffixType _suffix_type;
        const NonCompoundExp _contained;
    };

    class CompoundExp
    {
    public:
        enum BinaryOpType
        {
            PLUS,
            MINUS,
        };

        CompoundExp(NonCompoundExp lhs,  BinaryOpType op_type, NonCompoundExp rhs);

        const NonCompoundExp & lhs() const;
        BinaryOpType op_type() const;
        const NonCompoundExp & rhs() const;
    private:
        const NonCompoundExp _lhs;
        const BinaryOpType _op_type;
        const NonCompoundExp _rhs;
    };
}

#endif
