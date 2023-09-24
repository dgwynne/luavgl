#include "luavgl.h"
#include "private.h"

static int
luavgl_switch_create(lua_State *L)
{
	return luavgl_obj_create_helper(L, lv_switch_create);
}

static const luaL_Reg luavgl_switch_methods[] = {
	{ NULL, NULL }
};

static void
luavgl_switch_init(lua_State *L)
{
	luavgl_obj_newmetatable(L, 
	    &lv_switch_class, "lv_switch", luavgl_switch_methods);
	lua_pop(L, 1);
}
