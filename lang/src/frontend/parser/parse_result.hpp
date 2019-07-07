#ifndef PARSER_PARSE_RESULT_HPP
#define PARSER_PARSE_RESULT_HPP

namespace parser
{
    template <class T>
    class ParseResult
    {
    public:
        ParseResult(T contained, unsigned long consumed_count)
        : _contained(contained),
        _consumed_count(consumed_count)
        {
        }

        const T & contained() const
        {
            return _contained;
        }

        unsigned long consumed_count() const
        {
            return _consumed_count;
        }
    private:
        T _contained;
        unsigned long _consumed_count;
    };
}

#endif
