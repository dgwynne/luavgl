#include "luavgl.h"
#include "private.h"

static int
luavgl_btn_create(lua_State *L)
{
	return luavgl_obj_create_helper(L, lv_btn_create);
}

static const luaL_Reg luavgl_btn_methods[] = {
	{ NULL,		NULL }
};

static void
luavgl_btn_init(lua_State *L)
{
	luavgl_obj_newmetatable(L,
	    &lv_btn_class, "lv_btn", luavgl_btn_methods);
	lua_pop(L, 1);
}
