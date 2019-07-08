#ifndef SYNTAX_TREE_ATOMIC_EXPs
#define SYNTAX_TREE_ATOMIC_EXPs

#include <variant>
#include <string>
#include <memory>

namespace syntax_tree::compound_exp
{
    class CompoundExp;
}

namespace syntax_tree::atomic_exps
{
    class ParenthesizedExp
    {
    public:
        ParenthesizedExp(syntax_tree::compound_exp::CompoundExp contained);
        ParenthesizedExp(const ParenthesizedExp & par_exp);
        ~ParenthesizedExp();

        const syntax_tree::compound_exp::CompoundExp & contained() const;
    private:
        const std::unique_ptr<syntax_tree::compound_exp::CompoundExp> _contained;
    };

    class NumberExp
    {
    public:
        NumberExp(const std::string & number_str, bool is_float);
        const std::string & number_str() const;
        bool is_float() const;
    private:
        const std::string _number_str;
        const bool _is_float;
    };

    class IdentifierExp
    {
    public:
        IdentifierExp(const std::string & identifier_str);
        const std::string & identifier_str() const;
    private:
        const std::string _identifier_str;
    };

    class AtomicExp
    {
    public:
        typedef std::variant<
            NumberExp,
            IdentifierExp,
            ParenthesizedExp
        > VariantAtomicExp;
        AtomicExp(VariantAtomicExp contained);
        const VariantAtomicExp & contained() const;
    private:
        const VariantAtomicExp _contained;
    };
}

#endif
