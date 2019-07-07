#include "./statement_series.hpp"

namespace syntax_tree::statement_series
{
    StatementSeries::StatementSeries(std::vector<syntax_tree::statements::Statement> statements)
    : _statements(statements)
    {
    }

    const std::vector<syntax_tree::statements::Statement> & StatementSeries::statements() const
    {
        return _statements;
    }
}
