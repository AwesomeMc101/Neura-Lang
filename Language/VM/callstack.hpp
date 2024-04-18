#pragma once
#include "neura.hpp"
#include "native_calls.hpp"
#include "arith_calls.hpp"
[[deprecated("decided to just make top the stacksize")]]
unsigned int neurac_callstacksize(Callstack*);

int neurac_gettop(Callstack*);

void neurac_newcall(Callstack*, Call);
void neurac_nativecall(Callstack*, std::string);

void neurac_arithcall(Callstack*, int);

Call neurac_popcallstack(Callstack*);
short neurac_gettopargs(Callstack*);

bool neurac_callonstack(Callstack*); //if top > -1

void neurac_dbg_printcallstack(Callstack*);

void neurac_vardefcall(Callstack* cs, Neura_Object generated_data);