#pragma once
#include <vector>
#include <string>
#include "tokens.h"

#include <iostream>

typedef short TOKEN_TYPE;

struct Token {
	TOKEN_TYPE type;
	std::string data;
	int lineinfo;
};

class AST {
public:
	std::vector<Token> tokens{};
	void append_token(std::string data, TOKEN_TYPE ttype, int line);
	void append_made_token(Token);
};

void fix_strings(std::vector<Token>&);
void fix_whitespace(std::vector<Token>&);
AST scan(std::vector<std::string>);
