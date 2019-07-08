#include "./atomic_exps.hpp"

namespace syntax_tree::atomic_exps
{
    IdentifierExp::IdentifierExp(const std::string & identifier_str)
    : _identifier_str(identifier_str)
    {
    }

    const std::string & IdentifierExp::identifier_str() const
    {
        return _identifier_str;
    }
}