#include "luavgl.h"
#include "private.h"

static int
luavgl_slider_create(lua_State *L)
{
	return luavgl_obj_create_helper(L, lv_slider_create);
}

static int
luavgl_slider_is_dragged(lua_State *L)
{
	lv_obj_t *obj = luavgl_to_obj(L, 1);
	lua_pushboolean(L, lv_slider_is_dragged(obj));
	return (1);
}

static const luaL_Reg luavgl_slider_methods[] = {
	/* most of these are handled by lv_bar */
	{ "set",		luavgl_bar_set },
	{ "is_dragged",		luavgl_slider_is_dragged },

	{ NULL,			NULL }
};

static void
luavgl_slider_init(lua_State *L)
{
	luavgl_obj_newmetatable(L,
	    &lv_slider_class, "lv_slider", luavgl_slider_methods);
	lua_pop(L, 1);
}
