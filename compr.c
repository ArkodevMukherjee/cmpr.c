#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_EQUALS,
    TOKEN_PLUS,
    TOKEN_PRINT,
    TOKEN_EOF,
    TOKEN_NEWLINE
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[64]; // stores the actual text of the token
    int value; // stores the value if it's a number
} Token;

Token tokens[256]; // simple token list, static for this example
int token_count = 0;

// Tokenizer function to create tokens from source code
void tokenize(const char *source) {
    const char *p = source;
    while (*p != '\0') {
        if (isspace(*p)) {
            if (*p == '\n') {
                tokens[token_count++] = (Token){TOKEN_NEWLINE, "\n", 0};
            }
            p++;
            continue;
        } else if (isdigit(*p)) {
            Token token;
            token.type = TOKEN_NUMBER;
            token.value = strtol(p, (char**)&p, 10);
            sprintf(token.lexeme, "%d", token.value);
            tokens[token_count++] = token;
            continue;
        } else if (isalpha(*p)) {
            Token token;
            if (strncmp(p, "print", 5) == 0) {
                token.type = TOKEN_PRINT;
                strcpy(token.lexeme, "print");
                p += 5;
            } else {
                token.type = TOKEN_IDENTIFIER;
                int i = 0;
                while (isalnum(*p) && i < 63) token.lexeme[i++] = *p++;
                token.lexeme[i] = '\0';
            }
            tokens[token_count++] = token;
            continue;
        } else if (*p == '=') {
            tokens[token_count++] = (Token){TOKEN_EQUALS, "=", 0};
            p++;
        } else if (*p == '+') {
            tokens[token_count++] = (Token){TOKEN_PLUS, "+", 0};
            p++;
        } else {
            fprintf(stderr, "Unexpected character: %c\n", *p);
            exit(1);
        }
    }
    tokens[token_count++] = (Token){TOKEN_EOF, "EOF", 0};
}

// Utility function to print tokens for debugging
void print_tokens() {
    for (int i = 0; i < token_count; i++) {
        printf("Token: { type: %d, lexeme: '%s', value: %d }\n", tokens[i].type, tokens[i].lexeme, tokens[i].value);
    }
}
