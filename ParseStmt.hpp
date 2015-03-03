#ifndef PARSE_STMT_HPP
#define PARSE_STMT_HPP
#include "ParseExpr.hpp"
namespace spc
{
    ParseResult parseStmt(int index);
    /*
     * assignstmt <- identifier = Expr;
     */
    ParseResult parseAssignStmt(int index)
    {
        IdExpr* lv;
        Expr* rv;
        auto f = Sequence
        (
            {
                hook(parseIdentifierExpr,lv),
                parseEqualSymbol, 
                hook(parseExpr, rv),
                parseSemicolon
            }
        );
        
        auto result = f(index);
        if (!result)
            return result;
        
        return ParseResult(new AssignStmt(lv, rv), result.nextIndex());
    }
    /*
     * declstmt <- auto assignstmt
     */
    ParseResult parseDeclStmt(int index)
    {
        AssignStmt* as;
        auto f = Sequence({parseAuto, hook(parseAssignStmt, as)});
        auto result = f(index);
        if (!result)
            return result;
        return ParseResult(new DeclStmt(as), result.nextIndex());
    }
    
    /*
     * stmtblock <- {stmt*}
     */
    ParseResult parseStmtBlock(int index)
    {
        auto f = Sequence({parseOpenBrace, ZeroOrMore(parseStmt), parseCloseBrace});
        auto result = f(index);
        if (!result)
            return result;
        ASTNodeVector* v = static_cast<ASTNodeVector*>(result.get());
        std::vector<Stmt*> data;
        for (auto x : static_cast<ASTNodeVector*>(v->getData()[1])->getData())
            data.push_back(static_cast<Stmt*>(x));
        return ParseResult(new StmtBlock(data), result.nextIndex());
    }
    /*
     * ifstmt <- if (expression) stmtblock (else stmtblock)? 
     */
    ParseResult parseIfStmt(int index)
    {
        Expr* c = nullptr;
        Stmt* tb = nullptr;
        Stmt* fb = nullptr;
        auto f = Sequence
        (
            {
                parseIf, parseOpenParen, hook(parseExpr, c), parseCloseParen, 
                hook(parseStmtBlock, tb),
                Optional(Sequence({parseElse, hook(parseStmtBlock, fb)}))
            }
        );
        auto result = f(index);
        if (!result)
            return result;
        else return ParseResult(new IfStmt(c, tb, fb), result.nextIndex());
    }
    /*
     * whilestmt <- while (expr) stmtblock
     */
    ParseResult parseWhileStmt(int index)
    {
        Expr* c;
        Stmt* b;
        auto f = Sequence
        (
            {
                parseWhile, 
                parseOpenParen, 
                hook(parseExpr, c),
                parseCloseParen,
                hook(parseStmtBlock, b)
            }
        );
        auto result = f(index);
        if (!result)
            return result;
        else return ParseResult(new WhileStmt(c, b), result.nextIndex());
    }
    
    /*
     * typedef <- (typedef typedef*)@? / identifier
     */
    ParseResult parseTypeDefinition(int index)
    {
        std::vector<TypeDefinition*> v;
        IdExpr* id = nullptr;
        auto f = LinearChoice
            ({
                    Sequence
                    ({
                            parseOpenParen, 
                            ZeroOrMore(parseTypeDefinition), 
                            parseCloseParen, 
                            Optional(parseAlpha)
                    }),
                    hook(parseIdentifierExpr, id)
            });
        auto result = f(index);
        if (!result)
            return result;
        if (id != nullptr)
            return ParseResult(new TypeDefinition({}, id, false), result.nextIndex());
        else
        {
            ASTNodeVector* seq = static_cast<ASTNodeVector*>(result.get());
            ASTNodeVector* rec = static_cast<ASTNodeVector*>(seq->getData()[1]);
            bool hasalpha = seq->getData()[3] != nullptr;
            std::vector<TypeDefinition*> data;
            for (auto node: rec->getData())
                data.push_back(static_cast<TypeDefinition*>(node));
            return ParseResult(new TypeDefinition(data, nullptr, hasalpha), result.nextIndex());
        }
        
    }
    
    ParseResult parseTypeDefinitionStmt(int index)
    {
        IdExpr* id;
        TypeDefinition* td;
        auto f = Sequence
        (
            {
                parseType,
                hook(parseIdentifierExpr, id),
                hook(parseTypeDefinition, td),
                parseSemicolon
            }
        );
        auto result = f(index);
        if (!result)
            return result;
        else 
            return ParseResult(new TypeDefinitionStmt(id, td), result.nextIndex());
    }
    
    ParseResult parseStmt(int index)
    {
        return LinearChoice
        (
            {
                parseAssignStmt,
                parseDeclStmt,
                parseIfStmt,
                parseWhileStmt,
                parseStmtBlock,
            },
            "Expected Expression."
        )
        (index);
    }

}
#endif