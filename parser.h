#pragma once
#include <string>
#include <vector>
#include "token.h"

// Thrown when the parser finds the first syntax error.
struct SyntaxError {
    std::string message;
};

// Recursive-descent parser for the LearnCompiler grammar.
// One member function per grammar rule.
class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    // Returns true if the program is valid. Otherwise returns false and
    // fills errorMessage with a description of the first syntax error.
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
