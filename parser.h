#pragma once
#include <string>
#include <vector>
#include "token.h"


struct SyntaxError {
    std::string message;
};


class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    
    bool parse(std::string& errorMessage);

private:
    const std::vector<Token>& tokens;
    size_t pos;

    const Token& current() const;
    void advance();
    void expect(TokenType type, const std::string& what);

    void program();   // <program> -> <keyword> <ident> (<keyword><ident>) { <declares> <assign> }
    void declares();  // <declares> -> <keyword> <ident> ; | <keyword> <ident> ; <declares>
    void assign();    // <assign>   -> <ident> = <expr>
    void expr();      // <expr>     -> <ident> {*|/} <expr> | <ident>
};
