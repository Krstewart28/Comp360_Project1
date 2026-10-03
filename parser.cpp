#include "parser.h"

Parser::Parser(const std::vector<Token>& toks) : tokens(toks), pos(0) {}

const Token& Parser::current() const {
    return tokens[pos];
}


void Parser::advance() {
    if (pos + 1 < tokens.size()) pos++;
}


void Parser::expect(TokenType type, const std::string& what) {
    if (current().type == type) {
        advance();
        return;
    }
    const Token& t = current();
    std::string found = (t.type == TokenType::END_OF_INPUT)
                            ? "end of input"
                            : "'" + t.lexeme + "'";
    throw SyntaxError{"Syntax error at line " + std::to_string(t.line) +
                      ", column " + std::to_string(t.column) +
                      ": expected " + what + " but found " + found};
}

void Parser::program() {
    expect(TokenType::KEYWORD, "keyword 'float'");
    expect(TokenType::IDENT, "an identifier");
    expect(TokenType::LPAREN, "'('");
    expect(TokenType::KEYWORD, "keyword 'float'");
    expect(TokenType::IDENT, "an identifier");
    expect(TokenType::RPAREN, "')'");
    expect(TokenType::LBRACE, "'{'");
    declares();
    assign();
 
    if (current().type == TokenType::SEMICOLON) advance();
    expect(TokenType::RBRACE, "'}'");
    expect(TokenType::END_OF_INPUT, "end of input");
}


void Parser::declares() {
    do {
        expect(TokenType::KEYWORD, "a declaration starting with 'float'");
        expect(TokenType::IDENT, "an identifier");
        expect(TokenType::SEMICOLON, "';'");
    } while (current().type == TokenType::KEYWORD);
}

void Parser::assign() {
    expect(TokenType::IDENT, "an identifier");
    expect(TokenType::ASSIGN_OP, "'='");
    expr();
}

void Parser::expr() {
    expect(TokenType::IDENT, "an identifier");
    if (current().type == TokenType::MULT_OP ||
        current().type == TokenType::DIV_OP) {
        advance();
        expr();
    }
}

bool Parser::parse(std::string& errorMessage) {
    try {
        program();
        return true;
    } catch (const SyntaxError& e) {
        errorMessage = e.message;
        return false;
    }
}
