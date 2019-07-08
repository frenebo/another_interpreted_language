#include "./atomic_exps.hpp"

namespace syntax_tree::atomic_exps
{
    NumberExp::NumberExp(const std::string & number_str, bool is_float)
    : _number_str(number_str),
    _is_float(is_float)
    {
    }

    const std::string & NumberExp::number_str() const
    {
        return _number_str;
    }

    bool NumberExp::is_float() const
    {
        return _is_float;
    }
}