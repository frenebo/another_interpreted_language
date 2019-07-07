#include "./statements.hpp"
#include "../statement_series/statement_series.hpp"

namespace syntax_tree::statements
{
    IfStatement::IfStatement(
        syntax_tree::compound_exp::CompoundExp condition,
        statement_series::StatementSeries body)
    : _condition(condition),
    _body(new statement_series::StatementSeries(body))
    {
    }

    IfStatement::IfStatement(const IfStatement & if_statement)
    : _condition(if_statement._condition),
    _body(new statement_series::StatementSeries(*if_statement._body))
    {
    }

    IfStatement::~IfStatement() = default;

    const syntax_tree::compound_exp::CompoundExp & IfStatement::condition() const
    {
        return _condition;
    }

    const statement_series::StatementSeries & IfStatement::body() const
    {
        return *_body;
    }
}