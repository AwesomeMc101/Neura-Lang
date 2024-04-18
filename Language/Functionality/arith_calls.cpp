#include "arith_calls.hpp"

std::map<std::string, Call*> ARITH_CALLS{};


static const char* const math_calls[] = { "ARITH_ADD", "ARITH_SUB", "ARITH_MUL","ARITH_DIV","ARITH_POW"};
static const char* const math_calls_names[] = { "+ARITH_ADD", "-ARITH_SUB", "*ARITH_MUL","/ARITH_DIV","^ARITH_POW" };

void neuraah_initarithcalls()
{

	int size = (sizeof(math_calls) / sizeof(const char*));
	for (int i = 0; i < size; i++) {
		Call* temp_call = new Call;
		temp_call->is_cfunction = true;
		temp_call->serialized_data = new CallChunk;
		temp_call->serialized_data->arg_count = 2;
		temp_call->serialized_data->call_name = math_calls_names[i];

		ARITH_CALLS[math_calls[i]] = temp_call; //damn
		std::cout << "INIT: " << math_calls[i] << " @ " << math_calls_names[i] << "\n";
		//delete temp_call; //this caused me problems lol, yk why!!
	}

}	
Call* neuraah_getarithcall(int type)
{
	switch (type) {
	case ARITH_CALL_ADD:
		return ARITH_CALLS["ARITH_ADD"];
		break;
	case ARITH_CALL_SUB:
		return ARITH_CALLS["ARITH_SUB"];
		break;
	case ARITH_CALL_MUL:
		return ARITH_CALLS["ARITH_MUL"];
		break;
	case ARITH_CALL_DIV:
		return ARITH_CALLS["ARITH_DIV"];
		break;
	case ARITH_CALL_POW:
		return ARITH_CALLS["ARITH_POW"];
		break;
	}
	//uh oh...
}