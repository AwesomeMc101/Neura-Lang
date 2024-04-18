#include "stack_function.hpp"


void neuras_settop(NeuraData* ND, Stack* stk, int value)
{
	stk->top = value;
}

static bool neuras_checktop(int top) {
	return (top >= 0); //>= 0, its valid
}

int neuras_gettop(NeuraData*, Stack* stk)
{
	return (stk->stack.size() - 1);
	//return (stk->top);
}

void neuras_settype(NeuraData* ND, Stack* stk, NEURA_OBJ_TYPE ttype)
{
	stk->top_type = ttype;
}
NEURA_OBJ_TYPE neuras_gettype(NeuraData* ND, Stack* stk)
{
	return (stk->top_type);
}

Neura_Object neuras_safefakeobj()
{
	Neura_Object nobj;
	nobj.obj_const = false;
	nobj.obj_data = "";
	nobj.obj_name = "";
	nobj.obj_type = 0;
	return nobj;
}

Neura_Object neuras_pop(NeuraData* ND, Stack* stk)
{
	int top = neuras_gettop(ND, stk);
	if (top >= (stk->stack.size())) {
		printf("\n[6707-A] (stack_function.cpp) Stack top too large to safely index in stack range.\n");
		signed int stack_idx = signed(stk->stack.size() - 1);
		switch (stack_idx >= 0) {
		case true:
			printf("[6707-C] (stack_function.cpp) Stack top is mismatched with true size. Ensure it is being incremented and decremented accordingly.\n");
			return stk->stack[stack_idx];
		case false:
			//empty vector
			printf("[6707-B] (stack_function.cpp) Attempt to pop an empty stack.\n");
			return neuras_safefakeobj();
		}
		
	}

	if (neuras_checktop(top) == false) {
		printf("[9902] (stack_function.cpp) Stack top was a negative index. Is stack empty?\n");
		
	}

	Neura_Object return_value = stk->stack[top];
	stk->stack.erase(stk->stack.begin() + top);
	return return_value;

}
std::string neuras_popvalue(NeuraData* ND, Stack* stk)
{
	//printf("pop");
	Neura_Object stk_data = neuras_pop(ND, stk);
	return neura_getobjectdata(ND, stk_data);
}
NEURA_OBJ_TYPE neuras_poptype(NeuraData* ND, Stack* stk)
{
	Neura_Object stk_data = neuras_pop(ND, stk);
	return neura_getobjecttype(ND, stk_data);
}

void neuras_push(NeuraData* ND, Stack* stk, Neura_Object obj)
{
	stk->stack.emplace_back(obj);
	if (stk->stack.size() > 1) {
		stk->top++;
	}
}
void neuras_pushnew(NeuraData* ND, Stack* stk, std::string name, std::string data, NEURA_OBJ_TYPE objtype)
{
	Neura_Object new_obj;
	new_obj.obj_name = name;
	new_obj.obj_const = false;
	new_obj.obj_data = data;
	new_obj.obj_type = objtype;
	neuras_push(ND, stk, new_obj);
}

Stack* neuras_newstack()
{
	Stack* ptr = new Stack;
	ptr->base = 0;
	ptr->top = 0;
	ptr->top_type = 0;
	ptr->stack = {};
	return ptr;
}

Neura_Object neuras_getvarobject(Stack* stk, std::string varname)
{
	Neura_Object vptr = stk->var_data[varname];
	if (vptr.obj_name == "nil") {
		printf("[5555] (stack_function.cpp) No such variable.");
		return neuras_safefakeobj();
	}

	return vptr;
}
std::string neuras_getvarvalue(Stack* stk, std::string varname)
{
	return neuras_getvarobject(stk, varname).obj_data;
}

NEURA_OBJ_TYPE neuras_getvartype(Stack* stk, std::string varname)
{
	return neuras_getvarobject(stk, varname).obj_type;
}

void neuras_setglobal(Stack* stk, Neura_Object variable)
{
	stk->var_data[variable.obj_name] = variable; //var_data is an ordered map
}
void neuras_setnewglobal(Stack* stk, std::string name, std::string data, NEURA_OBJ_TYPE type)
{
	Neura_Object new_var;
	new_var.obj_name = name;
	new_var.obj_type = type;
	new_var.obj_data = data;
	new_var.obj_const = neura_isconst(type);
	neuras_setglobal(stk, new_var);
}