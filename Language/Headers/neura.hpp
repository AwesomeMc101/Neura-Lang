#pragma once
#include <string>
#include <vector>
#include "opcodes.h"

#include <iostream>

#include <map>
typedef short NEURA_OBJ_TYPE;
const NEURA_OBJ_TYPE NEURA_OBJ_STRING = 10;
const NEURA_OBJ_TYPE NEURA_OBJ_NUMBER = 20;
const NEURA_OBJ_TYPE NEURA_OBJ_STRING_CONST = 15;
const NEURA_OBJ_TYPE NEURA_OBJ_NUMBER_CONST = 25;
const NEURA_OBJ_TYPE NEURA_OBJ_CONST = 300;

bool neura_isconst(NEURA_OBJ_TYPE nobj);

typedef struct Neura_Object { //defined by user, variable or string/digit
	NEURA_OBJ_TYPE obj_type;
	std::string obj_name = "nil"; //optional 
	bool obj_const;
	std::string obj_data; //stored as string even if number for simplicity.
};


class Stack {
public: //not truly public, functions defined in stack_function.cpp/.hpp
	std::vector<Neura_Object> stack{};
	std::map<std::string, Neura_Object> var_data{};
	int top;
	int base = 0;
	NEURA_OBJ_TYPE top_type = 0;
};


struct Byte { //writebyte: serialize_code.hpp
	OpCode op;
	std::string data;
};

struct Chunk {
	size_t lines;
	std::vector<Byte> bytecode{};
	std::vector<Neura_Object> local_objects{};
};

struct CallChunk {
	Chunk* chunk_ptr;

	std::vector<Neura_Object> argument_objects{};

	std::string call_name;
	int arg_count;


};

typedef struct Call {
	CallChunk* serialized_data; //to run
	bool is_cfunction = false; //cfunction is like print("")
};

class Callstack {
public:
	std::vector<Call> calls;
	//std::map<std::string, Call> calls; //call_name, Call
	int top = -1;
};

struct NeuraData {
	//obj data
	std::vector<Neura_Object> global_objects{};
	std::vector<Chunk*> chunk_list{};
	std::map<std::string, CallChunk*> function_chunks{}; //locate chunk by its own data (name)
};

CallChunk* neura_getcallchunk(NeuraData*, std::string);

Neura_Object neura_getobject(NeuraData*, std::string);
NEURA_OBJ_TYPE neura_getobjecttype(NeuraData*, Neura_Object);
std::string neura_getobjectname(NeuraData*, Neura_Object);
bool neura_isobjectconst(NeuraData*, Neura_Object);
std::string neura_getobjectdata(NeuraData*, Neura_Object);


typedef unsigned int ERROR_CODE;
typedef struct Error {
	ERROR_CODE code;
	int lineinfo;
	std::string additional_data;
};
