#ifndef SYNTAX_TREE_ATOMIC_EXPs
#define SYNTAX_TREE_ATOMIC_EXPs

#include <variant>
#include <string>

namespace syntax_tree::atomic_exps
{
    class NumberExp
    {
    public:
        NumberExp(const std::string & number_str, bool is_float);
        const std::string & number_str() const;
        bool is_float() const;
    private:
        std::string _number_str;
        bool _is_float;
    };

    class IdentifierExp
    {
    public:
        IdentifierExp(const std::string & identifier_str);
        const std::string & identifier_str() const;
    private:
        std::string _identifier_str;
    };

    class AtomicExp
    {
    public:
        typedef std::variant<
            NumberExp,
            IdentifierExp
        > VariantAtomicExp;
    private:
    };
}

#endif
