#ifndef DESCENTPARSER_H_INCLUDED
#define DESCENTPARSER_H_INCLUDED

typedef  enum {PLUS, MINUS, DIVIDE, MULT, REMAINDER, POWER, LPAREN, RPAREN,
NUMBER, ERROR, EOL} TokenType;

struct Token {
TokenType type;
int value;
};

int expr(void);
int term(void);
int power(void);
int factor(void);
void parse(void);
void match(TokenType tkType);
void getToken(void);
int main();

#endif
