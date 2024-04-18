#include "call_handler.hpp"


double safe_stoi(std::string val) {
	std::string final_data{};
	bool dot_used = false;
	for (char c : val) {
		if (isdigit(c)) {
			final_data.push_back(c);
		}
		else if (c == '.') {
			switch (dot_used) {
			case false:
				final_data.push_back(c);
				dot_used = true;
				break;
			}
		}
	}
	if (final_data.size()) {
		return std::stod(final_data);
	}
	printf("\n[4409] (call_handler.cpp) safe_stoi() received 0 safe number values.\n");
	return 0;
}
bool arith_call(Call call, Stack* stk) 
{
	char type = call.serialized_data->call_name[0]; //look in: arith_calls.cpp to understand why this works. first char of call_name is +-/*^
	switch (type) {
	case '+':
	{
		//add
		double value_a = safe_stoi(neuras_popvalue(new NeuraData, stk));
		double value_b = safe_stoi(neuras_popvalue(new NeuraData, stk));
		neuras_pushnew(new NeuraData, stk, "ARITH_VALUE", std::to_string(value_a + value_b), NEURA_OBJ_NUMBER);
		return 1;

	}
	case '-':
	{
		//add
		double value_a = safe_stoi(neuras_popvalue(new NeuraData, stk));
		double value_b = safe_stoi(neuras_popvalue(new NeuraData, stk));
		neuras_pushnew(new NeuraData, stk, "ARITH_VALUE", std::to_string(value_b - value_a), NEURA_OBJ_NUMBER);
		return 1;

	}
	case '*':
	{
		//add
		double value_a = safe_stoi(neuras_popvalue(new NeuraData, stk));
		double value_b = safe_stoi(neuras_popvalue(new NeuraData, stk));
		neuras_pushnew(new NeuraData, stk, "ARITH_VALUE", std::to_string(value_a * value_b), NEURA_OBJ_NUMBER);
		return 1;

	}
	case '/':
	{
		//add
		double value_a = safe_stoi(neuras_popvalue(new NeuraData, stk));
		double value_b = safe_stoi(neuras_popvalue(new NeuraData, stk));
		neuras_pushnew(new NeuraData, stk, "ARITH_VALUE", std::to_string(value_b / value_a), NEURA_OBJ_NUMBER);
		return 1;

	}
	case '^':
	{
		//add
		double value_a = safe_stoi(neuras_popvalue(new NeuraData, stk));
		double value_b = safe_stoi(neuras_popvalue(new NeuraData, stk));
		neuras_pushnew(new NeuraData, stk, "ARITH_VALUE", std::to_string(pow(value_b, value_a)), NEURA_OBJ_NUMBER);
		return 1;

	}
	}
}
bool is_arith_call(Call call) {
	return (call.serialized_data->call_name.find("ARITH") != std::string::npos);
}
bool is_var_call(Call call)
{
	return (call.serialized_data->arg_count == -5); //interesting tactic
}
bool native_call(Call call, Stack* stk)
{
	switch (call.serialized_data->call_name[0]) {
	case 'p':
		if (call.serialized_data->call_name == "print") {
			std::cout << "\nPRINTING > " << neuras_popvalue(new NeuraData, stk);
		}
	}
	return 1;
}

bool neurach_call(Stack* stk, Call call)
{
	if (call.is_cfunction) {
		return native_call(call, stk);
	}


	return 1;
}

void neurach_setnewvar(Stack* stk, Call call) {
	neuras_setnewglobal(stk, call.serialized_data->call_name, neuras_popvalue(new NeuraData, stk), call.serialized_data->argument_objects[0].obj_type);
}

bool neurach_lcall(Stack* stk, Call call) { //literal call
	if (is_arith_call(call)) {
		arith_call(call, stk);
		return 1;
	}
	if(is_var_call(call)) {
		//neuras_setnewglobal();
		neurach_setnewvar(stk, call);
		return 1;
	}


	return 0;
}