#include "vm.hpp"


ERROR_CODE neurav_execute(Chunk* chunk)
{
	NeuraData* ND = new NeuraData;
	Stack* stk = neuras_newstack();
	Callstack* cs = new Callstack;

	for (int i = 0; i < chunk->bytecode.size(); i++)
	{
		Byte byte = chunk->bytecode[i];
		OpCode instr = byte.op;
		std::string data = byte.data;

		/* std::cout << "OP_" << instr << " | " << data << "\n"; */

		//main execution
		switch (instr) {
		case OP_PUSH:
			neuras_pushnew(ND, stk, "", data, neuras_gettype(ND, stk));
			break;
		case OP_SETTYPE: {
			NEURA_OBJ_TYPE old_type = neuras_gettype(ND, stk);
			neuras_settype(ND, stk, 0); //reset type
			switch (data[0]) {
			case '1': //->string:
				switch (old_type == NEURA_OBJ_CONST) {
				case true:
					neuras_settype(ND, stk, NEURA_OBJ_STRING_CONST);
					break;
				case false:
					neuras_settype(ND, stk, NEURA_OBJ_STRING);
					break;
				}
				break;
			case '2':
				switch (old_type == NEURA_OBJ_CONST) {
				case true:
					neuras_settype(ND, stk, NEURA_OBJ_NUMBER_CONST);
					break;
				case false:
					neuras_settype(ND, stk, NEURA_OBJ_NUMBER);
					break;
				}
				break;
			case '3': //push const
				neuras_settype(ND, stk, NEURA_OBJ_CONST);
				break;
			}
			break;
		}
		case OP_GETTYPE: //i dont like this opcode ngl, idk if i'll ever use it
			neuras_pushnew(ND, stk, "", "", neuras_gettype(ND, stk));
			break;
		case OP_GETVALUE:
		{
			neuras_pushnew(ND, stk, data, neuras_getvarvalue(stk, data), neuras_getvartype(stk, data));
			break;
		}
		case OP_SETGLOBAL:
		{
			NEURA_OBJ_TYPE vtype = neuras_gettype(ND, stk);
			Neura_Object v_data;
			v_data.obj_const = neura_isconst(vtype);
			if (vtype == 300) {
				printf("const err");
				break; 
			}

			v_data.obj_name = data;
			v_data.obj_type = vtype;
		//	neurac_v
			neurac_vardefcall(cs, v_data);
			
		}

		case OP_CALL:
			
			break;
		case OP_ADD:
		case OP_SUB:
		case OP_MUL:
		case OP_DIV:
		case OP_POW:
		{
			//add function
			int code = (instr - 18); //think about it like this:
			/*
			OP_ADD defined as value 19
			ARITH_CALL_ADD defined as 1

			both go up by 1 so
			OP_SUB = 20
			ARITH_CALL_SUB = 2
			
			*/


			neurac_arithcall(cs, code);
			break;
		}
		case OP_NATIVECALL:
			neurac_nativecall(cs, data);
			break;
		case OP_LITERALCALL:
			if (neurac_callonstack(cs)) {
				//arg check unneeded since no function will run
				Call ncall = neurac_popcallstack(cs);
				if (!neurach_lcall(stk, ncall)) {
					//printf("repush call");
					neurac_newcall(cs, ncall); //return call to top if it isnt a literal call :_
				}
			}
			break;
		case OP_TRUECALL:
			neurac_dbg_printcallstack(cs);
			neurach_call(stk, neurac_popcallstack(cs));

			break;
		}


	}
	return 0;
}