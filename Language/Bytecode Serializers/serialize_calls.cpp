#include "serialize_calls.hpp"



CallChunk* neurabc_serializecalls(AST tree) //when we write functions, we will serialize the code before hand and just run it when the function is called.
{
	Chunk* chunk_ptr = new Chunk;
	CallChunk* cc_ptr = new CallChunk;

	cc_ptr->chunk_ptr = chunk_ptr;

	std::string function_name{};
	int arg_count = 0;
	bool args_complete = false;

	for (int i = 0; i < tree.tokens.size(); i++)
	{
		Token tok = tree.tokens[i];
		if (!function_name.size() && tok.type == TOKEN_IDENTIFIER) {
			function_name = tok.data;
		}

		//only whilst defining args
		if (!args_complete) {
			/*if (tok.type == TOKEN_CLOSEPARENTHESIS) {
				args_complete = true;
			}
			else if()*/
			switch (tok.type)
			{
			case TOKEN_CLOSEPARENTHESIS:
				args_complete = true;
				break;
			case TOKEN_TNUMBER: {
				//int foo
				Token peeked_token = neurab_peek(tree, i, 1); //should be the name of the variable.
				if (peeked_token.type != TOKEN_IDENTIFIER) {
					std::cout << "[6853] (serialize_calls.cpp) > PEEKED TOKEN IS NOT OF TYPE: IDENTIFIER. UNABLE TO SERIALIZE CALL PARAMETER. (TYPE: INTEGER)\n";
					printf("[6853] (IN ENGLISH) Paramater located in the call serializer was not an identifier. Did you forget to name the variable?");
					continue;
				}
				Neura_Object new_int;
				new_int.obj_name = peeked_token.data;
				new_int.obj_const = false; //cannot be constant as a param
				new_int.obj_type = NEURA_OBJ_NUMBER;
				new_int.obj_data = "";
				/* attempt to find variable value 
				for example:
				function foo(int x = 5) 	*/
				Token dual_peek_token = neurab_peek(tree, i, 2); //peek at value after var name
				if (dual_peek_token.type == TOKEN_EQUALS) { //check if this token is an equals sign
					Token find_tok_value = neurab_peek(tree, i, 3); //it is, so peek for value after equals sign
					if (find_tok_value.type == TOKEN_IDENTIFIER || find_tok_value.type == TOKEN_NUMBER) { //as this is an int, only append an integer or identifier value
						new_int.obj_data = find_tok_value.data; //set obj data to value from peeked data
					}
				}
				cc_ptr->argument_objects.push_back(new_int);
				break;
			}
			case TOKEN_TSTRING: {
				//int foo
				Token peeked_token = neurab_peek(tree, i, 1); //should be the name of the variable.
				if (peeked_token.type != TOKEN_IDENTIFIER) {
					std::cout << "[6853] (serialize_calls.cpp) > PEEKED TOKEN IS NOT OF TYPE: IDENTIFIER. UNABLE TO SERIALIZE CALL PARAMETER. (TYPE: STRING)\n";
					printf("[6853] (IN ENGLISH) Paramater located in the call serializer was not an identifier. Did you forget to name the variable?");
					continue;
				}
				Neura_Object new_string;
				new_string.obj_name = peeked_token.data;
				new_string.obj_const = false; //cannot be constant as a param
				new_string.obj_type = NEURA_OBJ_STRING;
				new_string.obj_data = "";
				/* attempt to find variable value
				for example:
				function foo(int x = 5) 	*/
				Token dual_peek_token = neurab_peek(tree, i, 2); //peek at value after var name
				if (dual_peek_token.type == TOKEN_EQUALS) { //check if this token is an equals sign
					Token find_tok_value = neurab_peek(tree, i, 3); //it is, so peek for value after equals sign
					if (find_tok_value.type == TOKEN_IDENTIFIER || find_tok_value.type == TOKEN_STRING) { //as this is a string, only append a string or identifier value
						new_string.obj_data = find_tok_value.data; //set obj data to value from peeked data
					}
				}
				cc_ptr->argument_objects.push_back(new_string);
				break;
			}
			}

			continue; //do not repeat the rest of the loop.
		}

		// non-parameter data
		neurab_serializedatatype(chunk_ptr, tok, false, tree, i);
		
	}
	return cc_ptr;
}
