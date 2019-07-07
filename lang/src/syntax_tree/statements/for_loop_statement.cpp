#include "./statements.hpp"
#include "../statement_series/statement_series.hpp"

namespace syntax_tree::statements
{
    ForLoopStatement::ForLoopStatement(
        syntax_tree::compound_exp::CompoundExp initializer_exp,
        syntax_tree::compound_exp::CompoundExp condition_exp,
        syntax_tree::compound_exp::CompoundExp increment_exp,
        statement_series::StatementSeries loop_body)
    : _initializer_exp(initializer_exp),
    _condition_exp(condition_exp),
    _increment_exp(increment_exp),
    _loop_body(new statement_series::StatementSeries(loop_body))
    {
    }

    ForLoopStatement::ForLoopStatement(const ForLoopStatement & for_loop_statement)
    : _initializer_exp(for_loop_statement._initializer_exp),
    _condition_exp(for_loop_statement._condition_exp),
    _increment_exp(for_loop_statement._increment_exp),
    _loop_body(new statement_series::StatementSeries(*for_loop_statement._loop_body))
    {
    }

    ForLoopStatement::~ForLoopStatement() = default;

    const syntax_tree::compound_exp::CompoundExp & ForLoopStatement::initializer_exp() const
    {
        return _initializer_exp;
    }

    const syntax_tree::compound_exp::CompoundExp & ForLoopStatement::condition_exp() const
    {
        return _condition_exp;
    }

    const syntax_tree::compound_exp::CompoundExp & ForLoopStatement::increment_exp() const
    {
        return _increment_exp;
    }

    const statement_series::StatementSeries & ForLoopStatement::loop_body() const
    {
        return *_loop_body;
    }
}