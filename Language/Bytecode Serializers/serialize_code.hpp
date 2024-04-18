#pragma once
#include "tokens.h"
#include "neura.hpp"
#include "scan.hpp"
#include "opcodes.h"


void neurab_writebyte(Chunk*, OpCode, std::string); //write byte to bytecode list
Token neurab_peek(AST tree, int iterator, int amount); //peek to next token in list (safely)
void neurab_serializedatatype(Chunk* chunk_data, Token tok, bool is_global, AST tree, int iterator); //serialize token into byte
Chunk* neurab_serialize(NeuraData* nD, AST tree, int lines, bool is_global); //serialize list of tokens in AST tree