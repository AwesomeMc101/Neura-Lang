#pragma once
#include "neura.hpp"

extern Call* NEURA_PRINT;

extern std::map<std::string, Call*> NATIVE_CALLS;

void neuranc_initnativecalls();
Call* neuranc_getnativecall(std::string);
