#ifndef LEXER_H
#define LEXER_H

typedef enum {
    NAME,
    NUM,
	LPARENTHESIS,
	RPARENTHESIS,
	END_OF_FILE,
	NEW_LINE,
	COMMAS,
} TokenKind;

typedef struct {
	TokenKind kind;
	char text[64];
	int line;
} Token;

typedef struct {
	char* text;
	int  current_position;
	int   line;
} Lexer;

Token lexer_next(Lexer* l);

#endif
