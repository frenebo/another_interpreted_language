#ifndef SYNTAX_TREE_STATEMENT_SERIES
#define SYNTAX_TREE_STATEMENT_SERIES

#include <vector>

#include "../statements/statements.hpp"

namespace syntax_tree::statement_series
{
    class StatementSeries
    {
    public:
        StatementSeries(std::vector<syntax_tree::statements::Statement> statements);
        const std::vector<syntax_tree::statements::Statement> & statements() const;
    private:
        const std::vector<syntax_tree::statements::Statement> _statements;
    };
}

#endif
