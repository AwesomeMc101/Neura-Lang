#pragma once
typedef enum {
	/*stack*/
	OP_PUSH, //push data
	OP_POP, //pop data
	OP_PEEK, //peek at top
	OP_DUPLICATE, //pop and dupe top value
	OP_SWAP, //swap two top vals

	/*variables*/
	OP_GETLOCAL, //get a local var
	OP_SETLOCAL, //set a local var
	OP_GETGLOBAL, //get global var
	OP_SETGLOBAL, //set global var
	OP_GETVALUE, //set var, unknown type
	
	OP_SETTYPE, //set next stack type
	OP_GETTYPE,

	/*functions*/
	OP_PRECALL, //check args
	OP_CALL, //do call
	OP_TAILCALL, //verify call success, push return value to next env
	OP_NATIVECALL, //do C call

	OP_TRUECALL, //OP is run when the token ) appears, actually summons the call from the callstack.
	OP_LITERALCALL, //op is run when a literal appears, can call certain calls: for example, when 1 appears, check if we need to run OP_ADD 

	OP_RETURN, //own opcode BECAUSE its easier
	/* math */
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_POW,
	OP_ROUND,
	OP_ROUNDUP,
	OP_ROUNDDOWN,

} OpCode;
