#include "serialize_code.hpp"

void neurab_writebyte(Chunk* chunk, OpCode op, std::string data)
{
	Byte byte;
	byte.op = op;
	byte.data = data;
	chunk->bytecode.push_back(byte);
}

Token neurab_peek(AST tree, int iterator, int amount) //peek at future token
{
	Token return_token;
	size_t max = tree.tokens.size();
	iterator += amount;
	if (iterator >= max) {
		return_token.type = TOKEN_NIL;
		return return_token;
	}

	return tree.tokens[iterator];
}

void neurab_serializedatatype(Chunk* chunk_data, Token tok, bool is_global, AST tree, int iterator)
{
	TOKEN_TYPE ttype = tok.type;
	int line = tok.lineinfo;
	std::string data = tok.data;

	switch (ttype) {
	case TOKEN_TRUE:
		neurab_writebyte(chunk_data, OP_PUSH, "1");
		neurab_writebyte(chunk_data, OP_LITERALCALL, data);
		break;
	case TOKEN_FALSE:
		neurab_writebyte(chunk_data, OP_PUSH, "0");
		neurab_writebyte(chunk_data, OP_LITERALCALL, data);
		break;
	case TOKEN_NUMBER:
		neurab_writebyte(chunk_data, OP_SETTYPE, "20"); //20->integer
		neurab_writebyte(chunk_data, OP_PUSH, data);
		neurab_writebyte(chunk_data, OP_LITERALCALL, data);
		break;
	case TOKEN_STRING:
		neurab_writebyte(chunk_data, OP_SETTYPE, "10"); //10->string
		neurab_writebyte(chunk_data, OP_PUSH, data);
		neurab_writebyte(chunk_data, OP_LITERALCALL, data);
		break;
	case TOKEN_CONST:
		neurab_writebyte(chunk_data, OP_SETTYPE, "300"); //300-> const
		break;
	case TOKEN_TNUMBER:
		neurab_writebyte(chunk_data, OP_SETTYPE, "20"); //20->integer
		break;
	case TOKEN_TSTRING:
		neurab_writebyte(chunk_data, OP_SETTYPE, "10"); //10->string
		break;
	//case TOKEN_EQUALS:
	//	switch (is_global) {
	//	case true: //global env
	//		neurab_writebyte(chunk_data, OP_SETGLOBAL, data);
	//		break;
	//	case false: //local env
	//		neurab_writebyte(chunk_data, OP_SETLOCAL, data);
	//		break;
	//	}
	//	break;
	case TOKEN_IDENTIFIER: {
		//neurab_writebyte(chunk_data, OP_PUSH, data); //push var name
		Token peeked_token = neurab_peek(tree, iterator, 1); //peek 1 val ahead
		if (peeked_token.type == TOKEN_OPENPARENTHESIS) { //identifier is a function call 
			neurab_writebyte(chunk_data, OP_PRECALL, data);
			neurab_writebyte(chunk_data, OP_CALL, data);
			neurab_writebyte(chunk_data, OP_TAILCALL, data);
			break;
		}

		//not a call, variable
		if (peeked_token.type == TOKEN_EQUALS) {
			//neurab_writebyte(chunk_data, OP_SETTYPE, data);
			switch (is_global) {
			case true:
				neurab_writebyte(chunk_data, OP_SETGLOBAL, data);
				break;
			case false:
				neurab_writebyte(chunk_data, OP_SETLOCAL, data);
				break;
			}
			break;
		}
		//neurab_writebyte(chunk_data, OP_GETTYPE, data);
		neurab_writebyte(chunk_data, OP_GETVALUE, data);
		break;
	}
	case TOKEN_CLOSEPARENTHESIS:
		neurab_writebyte(chunk_data, OP_TRUECALL, data); //hopefully i remember to make it check if its really a function call, but im tired asf rn 
		break;
	case TOKEN_PLUS:
		neurab_writebyte(chunk_data, OP_ADD, data);
		break;
	case TOKEN_MINUS:
		neurab_writebyte(chunk_data, OP_SUB, data);
		break;
	case TOKEN_ASTERISK:
		neurab_writebyte(chunk_data, OP_MUL, data);
		break;
	case TOKEN_FORWARDSLASH:
		neurab_writebyte(chunk_data, OP_DIV, data);
		break;
	case TOKEN_CARET:
		neurab_writebyte(chunk_data, OP_POW, data);
		break;
	case TOKEN_ROUND:
		neurab_writebyte(chunk_data, OP_ROUND, data);
		break;
	case TOKEN_ROUNDDOWN:
		neurab_writebyte(chunk_data, OP_ROUNDDOWN, data);
		break;
	case TOKEN_ROUNDUP:
		neurab_writebyte(chunk_data, OP_ROUNDUP, data);
		break;
	case TOKEN_PRINT:
		neurab_writebyte(chunk_data, OP_PRECALL, "1"); //1 arg
		neurab_writebyte(chunk_data, OP_NATIVECALL, "print");
		//no tailcall
		break;
	case TOKEN_RETURN:
		neurab_writebyte(chunk_data, OP_PRECALL, "1"); //1 arg
		neurab_writebyte(chunk_data, OP_CALL, "return");
		neurab_writebyte(chunk_data, OP_TAILCALL, "return");
		break;

	}
}

Chunk* neurab_serialize(NeuraData* nD, AST tree, int lines, bool is_global)
{
	Chunk* chunk_data = new Chunk;
	for (int i = 0; i < tree.tokens.size(); i++)
	{
		//Token tok 
		neurab_serializedatatype(chunk_data, tree.tokens[i], is_global, tree, i);
	}
	return chunk_data;
}