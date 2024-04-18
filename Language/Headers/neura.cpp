#include "neura.hpp"

CallChunk* neura_getcallchunk(NeuraData* ND, std::string chunkname)
{
	return (ND->function_chunks[chunkname]);
}

NEURA_OBJ_TYPE neura_getobjecttype(NeuraData* ND, Neura_Object nobj)
{
	return nobj.obj_type;
}
std::string neura_getobjectname(NeuraData* ND, Neura_Object nobj)
{
	return nobj.obj_name;
}
bool neura_isobjectconst(NeuraData* ND, Neura_Object nobj)
{
	return nobj.obj_const;
}
std::string neura_getobjectdata(NeuraData* ND, Neura_Object nobj)
{
	return nobj.obj_data;
}

Neura_Object neura_getobject(NeuraData* ND, std::string objname)
{
	for (Neura_Object obj : ND->global_objects) {
		if (neura_getobjectname(ND, obj) == objname) {
			return obj;
		}
	}

	return *(new Neura_Object); //rip

}

bool neura_isconst(NEURA_OBJ_TYPE nobj)
{
	if ((nobj % 2) == 1) {
		return true;
	}
	return (nobj == NEURA_OBJ_CONST);
}
