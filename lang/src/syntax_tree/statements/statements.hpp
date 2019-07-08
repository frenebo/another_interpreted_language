#ifndef SYNTAX_TREE_STATEMENTS
#define SYNTAX_TREE_STATEMENTS

#include <variant>
#include <memory>

#include "../compound_exp/compound_exp.hpp"

namespace syntax_tree::statement_series
{
    class StatementSeries;
}

// @TODO check if the pointer stuff works
namespace syntax_tree::statements
{
    class CompoundExpStatement
    {
    public:
        CompoundExpStatement(syntax_tree::compound_exp::CompoundExp compound_exp);
        const syntax_tree::compound_exp::CompoundExp & compound_exp() const;
    private:
        const syntax_tree::compound_exp::CompoundExp _compound_exp;
    };

    class IfStatement
    {
    public:
        IfStatement(
            syntax_tree::compound_exp::CompoundExp condition,
            statement_series::StatementSeries body
        );
        IfStatement(const IfStatement & if_statement);
        ~IfStatement();

        const syntax_tree::compound_exp::CompoundExp & condition() const;
        const statement_series::StatementSeries & body() const;
    private:
        const syntax_tree::compound_exp::CompoundExp _condition;
        const std::unique_ptr<statement_series::StatementSeries> _body;
    };

    class ForLoopStatement
    {
    public:
        ForLoopStatement(
            syntax_tree::compound_exp::CompoundExp initializer_exp,
            syntax_tree::compound_exp::CompoundExp condition_exp,
            syntax_tree::compound_exp::CompoundExp increment_exp,
            statement_series::StatementSeries loop_body
        );
        ForLoopStatement(const ForLoopStatement & for_loop_statement);
        ~ForLoopStatement();

        const syntax_tree::compound_exp::CompoundExp & initializer_exp() const;
        const syntax_tree::compound_exp::CompoundExp & condition_exp() const;
        const syntax_tree::compound_exp::CompoundExp & increment_exp() const;
        const statement_series::StatementSeries & loop_body() const;
    private:
        const syntax_tree::compound_exp::CompoundExp _initializer_exp;
        const syntax_tree::compound_exp::CompoundExp _condition_exp;
        const syntax_tree::compound_exp::CompoundExp _increment_exp;
        const std::unique_ptr<statement_series::StatementSeries> _loop_body;
    };

    class Statement
    {
    public:
        typedef std::variant<
            CompoundExpStatement,
            IfStatement,
            ForLoopStatement
        > VariantStatement;

        Statement(VariantStatement contained_statement);
        const VariantStatement & contained_statement() const;
    private:
        const VariantStatement _contained_statement;
    };
}

#endif
