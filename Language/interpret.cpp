#include "interpret.hpp"


void neurai_chunkcalls(std::vector<CallChunk*>& call_chunks, AST& tree)
{
	AST function_buffer;
	function_buffer.tokens = {}; //init
	bool serialize_function = false;
	int env_count = 0;
	//int initial_iterator = 0; //for when serialize_function is enabled, so we can erase each value.
	for (int i = 0; i < tree.tokens.size(); i++) {


		if (tree.tokens[i].type == TOKEN_TFUNCTION) { //if word is legit "function" enable serializer
			serialize_function = true;
		}
		/* count our {} */
		else if (tree.tokens[i].type == TOKEN_OPENCURLY && serialize_function) { //
			env_count++;
		}
		else if (tree.tokens[i].type == TOKEN_CLOSECURLY && serialize_function) {
			env_count--;
		}

		if (serialize_function) {
			function_buffer.append_made_token(tree.tokens[i]);
			if (tree.tokens[i].type == TOKEN_CLOSECURLY) {
				if (!env_count) { //closed all environments
					call_chunks.push_back(neurabc_serializecalls(function_buffer));
				}
			}
			tree.tokens.erase(tree.tokens.begin() + i); //get rid of token from original tree since this is for optimization.
			i--; //since we erased, decrement i

		}

	}
}

void interpret_code(AST& tree)
{
	neuranc_initnativecalls(); //enable native functions!
	neuraah_initarithcalls(); //enable arith functions

	std::vector<CallChunk*> call_chunks{};
	neurai_chunkcalls(call_chunks, tree);
	
	std::cout << "Serialized functions. (" << call_chunks.size() << " Total Functions).\n";

	NeuraData* ND = new NeuraData;
	Chunk* main = neurab_serialize(ND, tree,1,true);

	std::cout << "Serialized main data. (" << main->bytecode.size() << " bytes).\n";

	neurav_execute(main);

}
