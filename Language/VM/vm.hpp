#include "neura.hpp"
#include "stack_function.hpp"
#include "callstack.hpp"
#include "call_handler.hpp"
#include <iostream>
typedef struct VM_RETURN {
	std::vector<Error> error_list;
};

ERROR_CODE neurav_execute(Chunk* chunk);
