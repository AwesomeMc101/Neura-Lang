#pragma once
#include "neura.hpp"

const int ARITH_CALL_ADD = 1;
const int  ARITH_CALL_SUB = 2;
const int ARITH_CALL_MUL = 3;
const int ARITH_CALL_DIV = 4;
const int ARITH_CALL_POW = 5;

extern std::map<std::string, Call*> ARITH_CALLS;

void neuraah_initarithcalls();
Call* neuraah_getarithcall(int);