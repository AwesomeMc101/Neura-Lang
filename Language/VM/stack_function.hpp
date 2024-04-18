#pragma once
#include "neura.hpp"

void neuras_settop(NeuraData*, Stack*, int);
int neuras_gettop(NeuraData*, Stack*);

void neuras_settype(NeuraData*, Stack*, NEURA_OBJ_TYPE);
NEURA_OBJ_TYPE neuras_gettype(NeuraData*, Stack*);

Neura_Object neuras_pop(NeuraData*, Stack*);
std::string neuras_popvalue(NeuraData*, Stack*);
NEURA_OBJ_TYPE neuras_poptype(NeuraData*, Stack*);

Stack* neuras_newstack();

void neuras_push(NeuraData* ND, Stack* stk, Neura_Object obj);
void neuras_pushnew(NeuraData* ND, Stack* stk, std::string name, std::string data, NEURA_OBJ_TYPE objtype);

Neura_Object neuras_getvarobject(Stack*, std::string varname);
std::string neuras_getvarvalue(Stack*, std::string);
NEURA_OBJ_TYPE neuras_getvartype(Stack*, std::string);

void neuras_setglobal(Stack*, Neura_Object variable);
void neuras_setnewglobal(Stack*, std::string name, std::string data, NEURA_OBJ_TYPE type);
