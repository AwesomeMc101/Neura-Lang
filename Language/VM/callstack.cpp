#include "callstack.hpp"

[[deprecated]]
unsigned int neurac_callstacksize(Callstack* cs)
{
	return cs->top;
}

int neurac_gettop(Callstack* cs)
{
	int top = cs->calls.size();
	return (top - 1);
}

Call neurac_generatefailcall() {
	Call fcall;
	fcall.is_cfunction = false;
	fcall.serialized_data = new CallChunk;
	return fcall;
}

Call neurac_safe_indexcall(Callstack* cs, int top)
{
	if (top > neurac_gettop(cs)) {
		std::cout << "[6708] (callstack.cpp) SAFE Index failure. Provided top was too large.\n";
		return neurac_generatefailcall();
	}
	if (top < 0) {
		std::cout << "[6709] (callstack.cpp) SAFE Index failure. Provided top was a negative index. This means that the callstack was empty when gettop() was called.\n";
		return neurac_generatefailcall();
	}
	
	return cs->calls[top];
}

void neurac_newcall(Callstack* cs, Call call)
{
	cs->calls.emplace_back(call);
}

Call neurac_getnativecall(std::string caller)
{
	return *(neuranc_getnativecall(caller)); //deref nc native call
}
void neurac_nativecall(Callstack* cs, std::string caller)
{
	Call native_call = neurac_getnativecall(caller);

	if (!native_call.is_cfunction) {
		printf("\n[5403] (callstack.cpp) Attempt to call a NATIVE call not defined as a CFunction. Did you call neuranc_initnativecalls() ?\n");
		return;
	}

	//cs->calls[caller] = native_call; //native calls do not have serialized data in a chunk.
	//cs->calls.emplace_back(native_call);
	neurac_newcall(cs, native_call);
}

Call neurac_getarithcall(int type)
{
	return *(neuraah_getarithcall(type));
}

void neurac_arithcall(Callstack* cs, int type)
{
	Call arith_call = neurac_getarithcall(type);
	if (!arith_call.is_cfunction) {
		printf("\n[5403] (callstack.cpp) Attempt to call a ARITH call not defined as a CFunction. Did you call neuraah_initarithcalls() ?\n");
		return;
	}
	//cs->calls.emplace_back(arith_call);
	neurac_newcall(cs, arith_call);
}
//unsafe functioN!
short neurac_gettopargs(Callstack* cs)
{
	int top = neurac_gettop(cs);
	if (top < 0) {
		return 0;
	}

	Call acall = neurac_safe_indexcall(cs, top);
	return acall.serialized_data->arg_count;

	//return cs->calls[top].serialized_data->arg_count;
}

void neurac_dbg_printcallstack(Callstack* cs)
{
	return; //disabled
	std::cout << "\n--Printing call stack data...\n";
	std::cout << "Top: " << cs->top << "\n";
	for(int i = 0; i < cs->calls.size(); i++)
	{
		Call z = cs->calls[i];
		std::cout << "[" << i << "] " << z.serialized_data->call_name << "\n";
	}
}


bool neurac_callonstack(Callstack* cs) { //if top > -1
	//std::cout << "CALLONSTACK: " << neurac_callstacksize(cs) << " > -1" << "\n";
	return (neurac_gettop(cs) >= 0); //returns true is gettop is > -1
}

Call neurac_popcallstack(Callstack* cs)
{

	int top = neurac_gettop(cs);
	if (top < 0) {
		printf("[5534] (callstack.cpp) Pop call stack, gettop returned <0. Call stack is empty.\n");
		return neurac_generatefailcall();
	}

	Call call = neurac_safe_indexcall(cs, top);
	cs->calls.pop_back(); //pop last call out
	return call;

	
}

void neurac_vardefcall(Callstack* cs, Neura_Object generated_data) { //var calls are literal calls
	Call vcall;
	vcall.is_cfunction = true;
	vcall.serialized_data = new CallChunk;
	vcall.serialized_data->call_name = generated_data.obj_name;
	vcall.serialized_data->argument_objects.emplace_back(generated_data);
	vcall.serialized_data->arg_count = -5;

	neurac_newcall(cs, vcall);
}