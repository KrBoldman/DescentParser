#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "DescentParser.h"

/*
    DescentParser.C
    ver 1.0
    -Kyle Boldman
*/

struct Token token;
char input[51];
int currentIndex = 0;

int main()
{
    printf("Enter an expression (spaces between tokens): ");
    scanf("%[^\n]s", input);
    parse();
    return 0;
}

void getToken(void)
{
    token.value = 0;

    while (input[currentIndex] == ' ')
    {
        currentIndex++;
    }

    if (isdigit(input[currentIndex]))
    {
        token.type = NUMBER;
        while(isdigit(input[currentIndex]))
        {
            //Convert character in respective digit
            token.value = 10 * token.value + input[currentIndex] - '0';
            // read in next character
            currentIndex++;
        }
    }

    else
    {
        //if not number, find correct token
        switch(input[currentIndex])
        {
            case '+':
                token.type = PLUS;
                break;
            case '-':
                token.type = MINUS;
                break;
            case '/':
                token.type = DIVIDE;
                break;
            case '*':
                token.type = MULT;
                break;
            case '%':
                token.type = REMAINDER;
                break;
            case '^':
                token.type = POWER;
                break;
            case '(':
                token.type = LPAREN;
                break;
            case ')':
                token.type = RPAREN;
                break;
            case '\n':
                token.type = EOL;
                break;
            default:
                token.type = ERROR;
        }
    }
}

void parse(void)
{
    getToken();
    command();
}

void command(void)
{
    int result = expr();

    printf("\n\nResult: %d\n", result);
}

int expr(void)
{
    int result = term();

    while(token.type == PLUS || token.type == MINUS)
    {
        if (token.type == PLUS)
        {
            match(PLUS);
            result += term();
        }

        else if(token.type == MINUS)
        {
            match(MINUS);
            result -= term();
        }
    }

    if (token.type == RPAREN)
    {
        match(RPAREN);
    }
    return result;
}

int term(void)
{
    int result = power();

    while (token.type == MULT || token.type == DIVIDE || token.type == REMAINDER)
    {
        if (token.type == MULT)
        {
            match(MULT);
            result *= power();
        }

        else if (token.type == DIVIDE)
        {
            match(DIVIDE);
            result /= power();
        }

        else if (token.type == REMAINDER)
        {
            match(REMAINDER);
            result %= power();
        }
    }

    return result;
}

int power(void)
{
    int result = factor();

    while (token.type == POWER)
    {
        match(POWER);
        result = pow(result, factor());
    }

    return result;
}

int factor(void)
{
    int result;

    //check for parenthesis, if found, start new experession
    if (token.type == LPAREN)
    {
        match(LPAREN);
        result = expr();
        return result;
    }

    //end of the line, type must be number or error
    if(token.type == NUMBER)
    {
        result = token.value;
        match(NUMBER);
    }

    else if (token.type == ERROR)
    {
        match(ERROR);
    }

    return result;
}

void match(TokenType tkType)
{
    if (token.type == tkType)
    {
        //prints the matched token
        switch(token.type)
        {
            case PLUS:
                printf("%c     PLUS\n", input[currentIndex]);
                break;
            case MINUS:
                printf("%c     MINUS\n", input[currentIndex]);
                break;
            case DIVIDE:
                printf("%c     DIVIDE\n", input[currentIndex]);
                break;
            case MULT:
                printf("%c     MULT\n", input[currentIndex]);
                break;
            case REMAINDER:
                printf("%c     REMAINDER\n", input[currentIndex]);
                break;
            case POWER:
                printf("%c     POWER\n", input[currentIndex]);
                break;
            case LPAREN:
                printf("%c     LPAREN\n", input[currentIndex]);
                break;
            case RPAREN:
                printf("%c     RPAREN\n", input[currentIndex]);
                break;
            case NUMBER:
                printf("%d     NUMBER\n", token.value);
                break;
            case ERROR:
            default:
                printf("%c     ERROR\nEXITING PROGRAM\n", input[currentIndex]);
                exit(0);
        }
        //increment index, getToken with next index
        currentIndex++;
        getToken();
    }
}
