#include "native_calls.hpp"

Call* NEURA_PRINT = new Call;
std::map<std::string, Call*> NATIVE_CALLS{ {"print", NEURA_PRINT} };

void neuranc_initnativecalls() {
	/* neura print */
	NEURA_PRINT->is_cfunction = true;
	NEURA_PRINT->serialized_data = new CallChunk;
	NEURA_PRINT->serialized_data->arg_count = 1;
	NEURA_PRINT->serialized_data->call_name = "print";


}

Call* neuranc_getnativecall(std::string caller)
{
	return NATIVE_CALLS[caller];
}