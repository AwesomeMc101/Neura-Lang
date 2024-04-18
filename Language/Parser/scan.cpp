#include "scan.hpp"

char single_Tokens[] = { '+','-','*','/','^',	'(',')','{','}','"','\'',	'&','>','<','=','!' };
const int single_tokens_size = (sizeof(single_Tokens) / sizeof(char));

char cancelStringEnd = 92; // '\' backslash cancels out quote on string

std::vector<std::string> dual_Tokens = { "++","--",		"+=","-=","*=","/=",	"~~","~+","~-",		">=","<=","==" };
const int dual_tokens_size = dual_Tokens.size();

std::vector<std::string> typedef_tokens = { "int","float","number",	"string","const","constant"};
const int typedef_tokens_size = typedef_tokens.size();

std::vector<std::string> non_function_tokens = { "while","if","elseif","else","for","break" };
const int non_function_tokens_size = non_function_tokens.size();

std::vector<std::string> value_tokens = { "true","false","pi" };
const int value_tokens_size = value_tokens.size();

std::vector<std::string> function_tokens = { "print","return" };
const int function_tokens_Size = function_tokens.size();

void AST::append_token(std::string data, TOKEN_TYPE ttype, int line)
{

	if (ttype == TOKEN_NIL) {
		//printf("AST_TOKEN_APPEND: CANNOT APPEND NIL TOKEN");
		return;
	}
	if (data.empty()) {
		//printf("AST_TOKEN_APPEND: CANNOT APPEND EMPTY DATA TOKEN");
		return;
	}


	Token tok;
	tok.data = data;
	tok.lineinfo = line;
	tok.type = ttype;

	this->tokens.push_back(tok);
}

void AST::append_made_token(Token tok)
{
	this->tokens.push_back(tok);
}

namespace Parser {

	TOKEN_TYPE assert_dual_token(std::string key)
	{
		if (key.length() != 2) { return TOKEN_NIL; }

		switch (key[0])
		{
		case '+':
			switch (key[1]) {
			case '+':
				return TOKEN_INCREMENT;
			case '=':
				return TOKEN_PLUSEQUAL;
			}
			break;
		case '-':
			switch (key[1]) {
			case '-':
				return TOKEN_DECREMENT;
			case '=':
				return TOKEN_MINEQUAL;
			}
			break;
		case '*':
			if (key[1] == '=') { return TOKEN_MULEQUAL; }
			break;
		case '/':
			if (key[1] == '=') { return TOKEN_DIVEQUAL; }
			break;
		case '~':
			switch (key[1]) {
			case '~':
				return TOKEN_ROUND;
			case '+':
				return TOKEN_ROUNDUP;
			case '-':
				return TOKEN_ROUNDDOWN;
			}
			break;
		case 'i':
			switch (key[1]) {
			case 'f':
				return TOKEN_IF;
			}
			break;
		case 'p':
			switch (key[1]) {
			case 'i':
				return TOKEN_PI;
			}
			break;
		}
		
		return TOKEN_NIL;
	}


	TOKEN_TYPE  is_single_type(char c)
	{
		for (int i = 0; i < single_tokens_size; i++)
		{
			if (single_Tokens[i] == c)
			{
				switch (c)
				{
				case '+':
					return TOKEN_PLUS;
				case '-':
					return TOKEN_MINUS;
				case '*':
					return TOKEN_ASTERISK;
				case '/':
					return TOKEN_FORWARDSLASH;
				case '^':
					return TOKEN_CARET;
				case '!':
					return TOKEN_EXCLAMATIONMARK;
				case '&':
					return TOKEN_AMPERSAND;
				case '>':
					return TOKEN_GREATER;
				case '<':
					return TOKEN_LESSER;
				case '=':
					return TOKEN_EQUALS;
				case '(':
					return TOKEN_OPENPARENTHESIS;
				case ')':
					return TOKEN_CLOSEPARENTHESIS;
				case '{':
					return TOKEN_OPENCURLY;
				case '}':
					return TOKEN_CLOSECURLY;
				case '"':
				case '\'':
					return TOKEN_QUOTE;
				case ',':
					return TOKEN_COMMA;
				}
			}
		}
		return TOKEN_IDENTIFIER;
	}
	TOKEN_TYPE is_dual_type(std::string c)
	{
		for (int i = 0; i < dual_tokens_size; i++)
		{
			if (dual_Tokens[i] == c)
			{
				return assert_dual_token(c); //will return TOKEN_NIL if not a dual token after all.
			}
		}
		return TOKEN_IDENTIFIER;
	}

	std::string ignore_whitespace(std::string data)
	{
		bool begin_whitespace = (data[0] == ' ' || data[0] == '	');
		while (begin_whitespace) {

			if (!data.length()) { return data; }

			data.erase(data.begin());
			begin_whitespace = (data[0] == ' ' || data[0] == '	');
		}
		if (!data.size()) { return data; }

		size_t data_Len = (data.size()-1);
		bool end_whitespace = (data[data_Len] == ' ' || data[data_Len] == '	');
		while (end_whitespace) {
			data.pop_back();
			end_whitespace = (data[data_Len] == ' ' || data[data_Len] == '	');
			data_Len--;
			if (data_Len < 0) { return data; }
		}

		return data;
	}

	bool is_double(std::string data) {
		/*bool decimal_passed = false;
		for (char c : data) {

		}*/
		size_t dec_pos = data.find_first_not_of("0123456789");
		if (dec_pos == std::string::npos) {
			return true; //no other digits found, its a number
		}

		if (data[dec_pos] != '.') {
			return false; //another char found, it isnt a NUMBER or DECIMAL
		}

		size_t dec_pos_second = data.find_last_not_of("0123456789");

		return (dec_pos == dec_pos_second);//if both equal and return TRUE, its good because only located one non-digit value. if they do not have the same value, we return false, as its not a double.
	}

	TOKEN_TYPE assert_identifier(std::string data)
	{
		//std::cout << "Assert: " << data << "\n";
		std::string ignored_data = ignore_whitespace(data);
		size_t len = ignored_data.length();
		if (!len) {
			return TOKEN_NIL;
		}
		if (isdigit(ignored_data[0])) { //placed before the dual_check on purpose.
			if (is_double(ignored_data)) {
				return TOKEN_NUMBER;
			}
			return TOKEN_IDENTIFIER; //no need to loop thru, we know that if it starts with a digit it isnt gonna be anything specific.
		}
		if (len == 2) {
			return is_dual_type(ignored_data);
		}
	

		switch (ignored_data[0])
		{
		case 'b':
			if (ignored_data == "break") { return TOKEN_BREAK; }
			break;
		case 'c':
			if (ignored_data == "const" || ignored_data == "constant") {
				return TOKEN_CONST;
			}
			break;
		case 'e':
			if (ignored_data == "else") { return TOKEN_ELSE; }
			if (ignored_data == "elseif") { return TOKEN_ELSEIF; }
			break;
		case 'f':
			if (ignored_data == "for") { return TOKEN_FOR; }
			if (ignored_data == "false") { return TOKEN_FALSE; }
			if (ignored_data == "float") { return TOKEN_TNUMBER; }
			if (ignored_data == "function") { return TOKEN_TFUNCTION; }
			break;
		case 'i': //See: DUAL_TYPE for if
			if (ignored_data == "int") { return TOKEN_TNUMBER; }
			break;
		case 'n':
			if (ignored_data == "number") { return TOKEN_TNUMBER; }
			break;
		case 'p': //See: DUAL_TYPE for pi
			if (ignored_data == "print") { return TOKEN_PRINT; }
			break;
		case 'r':
			if (ignored_data == "return") { return TOKEN_RETURN; }
			break;
		case 's':
			if (ignored_data == "string") { return TOKEN_TSTRING; }
			break;
		case 't':
			if (ignored_data == "true") { return TOKEN_TRUE; }
			break;
		case 'w':
			if (ignored_data == "while") { return TOKEN_WHILE; }
			break;
		}
		return TOKEN_IDENTIFIER;
	}

}

/* find the three tokens " string "*/
void fix_strings(std::vector<Token>& tokens)
{
	bool string = false; //writing string
	bool skip_cancel = false; //if we have a backslash, we push skip_cancel
	size_t pos = -1; //position of element to write to and to delete from
	//std::string buffer{}; //to store string value 
	Token* str_buffer = new Token;
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].type == TOKEN_QUOTE)
		{
			switch (string) {
			case false: //we are not writing string and just began
				delete str_buffer; //deallocate memory in case (should only happen on original time)
				string = true;
				pos = i;

				//define new buffer token
				str_buffer = new Token;
				str_buffer->lineinfo = tokens[i].lineinfo;
				str_buffer->type = TOKEN_STRING;
				break;
			case true: //we are writing string and just ended it.
			{
				if (skip_cancel) { skip_cancel = false; break; }
				size_t iterations = (i - pos)+1; //calculate how many items to DELETE
				for (int z = 0; z < iterations; z++) //z = original quote position ; z is less than CURRENT quote position; z++
				{
					tokens.erase(tokens.begin() + pos); //delete token at original position, 
					//because we are deleting it, pos will always be the position to target.
				}

				//now append new value

				tokens.insert(tokens.begin() + pos, *str_buffer); //dereference and insert new buffer token
				delete str_buffer; //deallocate
				pos = -1; //:)
				string = false;
				break;
			}
			}

		}
		else if (string) { //not quote, now check if we are in the middle of writing a string
			str_buffer->data.append(tokens[i].data);
		}
		skip_cancel = false; //always set to false
		if (((i - 1) >= 0)) { //check if the quote has a backslash preceding it
			Token token_old = tokens[i - 1];
			if (token_old.data.back() == cancelStringEnd) {
				skip_cancel = true;
			}
		}
	}
}

//get rid of whitespace in non-strings
void fix_whitespace(std::vector<Token>& tokens)
{
	for (Token& tok : tokens) {
		if (tok.type != TOKEN_STRING) {
			tok.data = Parser::ignore_whitespace(tok.data);
		}
	}
}

AST scan(std::vector<std::string> lines)
{
	AST tree;
	tree.tokens = {};

	int lineinfo = 0;
	for (std::string line : lines)
	{
		std::string buffer{};
		//for (char c : line)
		for(int i = 0; i < line.size(); i++)
		{
			char c = line[i];
			TOKEN_TYPE char_tok = Parser::is_single_type(c);
			if (char_tok != TOKEN_IDENTIFIER) //token is a single type
			{
				if ((i + 1) < line.size())
				{ //PEEK CLAUSE, ENSURE IT ISNT LIKE +=
					
					char peeked_char = line[i + 1];
					std::string buf{ c, peeked_char };
					TOKEN_TYPE dual_check = Parser::is_dual_type(buf);
					if (dual_check != TOKEN_IDENTIFIER) { //this means that the token is like +=, -=, etc so we fix it fr
						//is dual type, 
						tree.append_token(buffer, Parser::assert_identifier(buffer), lineinfo); //assert_identifier automatically checks dual types.
						buffer.clear();

						std::string buf{ c, peeked_char };
						tree.append_token(buf, dual_check, lineinfo);
						continue;
					}

				}

				tree.append_token(buffer, Parser::assert_identifier(buffer), lineinfo); //assert_identifier automatically checks dual types.
				buffer.clear();

				//append this token to tree after buffer
				std::string buf{c};
				tree.append_token(buf, char_tok, lineinfo);
			}
			else
			{
				buffer.push_back(c);
				if (c == 32) { //char value for ' ' aka empty space!
					tree.append_token(buffer, Parser::assert_identifier(buffer), lineinfo); //assert_identifier automatically checks dual types.
					buffer.clear();
				}
			}

			if ((i == (line.size() - 1)) && buffer.length()) { //flush out the buffer
				
				tree.append_token(buffer, Parser::assert_identifier(buffer), lineinfo); //assert_identifier automatically checks dual types.
				buffer.clear();
				
			}

		}



		lineinfo++;
	}
	fix_strings(tree.tokens);
	fix_whitespace(tree.tokens);
	return tree;
}
