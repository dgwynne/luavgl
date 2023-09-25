#include "luavgl.h"
#include "private.h"

static int
luavgl_bar_create(lua_State *L)
{
	return luavgl_obj_create_helper(L, lv_bar_create);
}

static void
_lv_bar_set_value(void *obj, lua_State *L)
{
	if (!lua_isinteger(L, -1)) {
		luaL_argerror(L, -1, "only support integer for value.");
		return;
	}

	lv_bar_set_value(obj, lua_tointeger(L, -1),
	    lua_toboolean(L, -2) ? LV_ANIM_ON : LV_ANIM_OFF);
}

static void
_lv_bar_set_min(void *obj, lua_State *L)
{
	if (!lua_isinteger(L, -1)) {
		luaL_argerror(L, -1, "only support integer for min.");
		return;
	}

	lv_bar_set_range(obj,
	    lua_tointeger(L, -1), lv_bar_get_max_value(obj));
}

static void
_lv_bar_set_max(void *obj, lua_State *L)
{
	if (!lua_isinteger(L, -1)) {
		luaL_argerror(L, -1, "only support integer for max.");
		return;
	}

	lv_bar_set_range(obj,
	    lv_bar_get_min_value(obj), lua_tointeger(L, -1));
}

static void
_lv_bar_set_range(void *obj, lua_State *L)
{
	int32_t min, max;

	if (!lua_istable(L, -1)) {
		luaL_argerror(L, -1, "only support table for range.");
		return;
	}

	lua_rawgeti(L, -1, 1);
	min = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_rawgeti(L, -1, 2);
	max = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lv_bar_set_range(obj, min, max);
}

static const luavgl_value_setter_t bar_property_table[] = {
	{
		"min",		SETTER_TYPE_STACK,
		{ .setter_stack = _lv_bar_set_min }
	},
	{
		"max",		SETTER_TYPE_STACK,
		{ .setter_stack = _lv_bar_set_max }
	},
	{
		"range",	SETTER_TYPE_STACK,
		{ .setter_stack = _lv_bar_set_range }
	},

	{
		"value",	SETTER_TYPE_STACK,
		{ .setter_stack = _lv_bar_set_value }
	},
};

LUALIB_API int
luavgl_bar_set_property_kv(lua_State *L, void *data)
{
	lv_obj_t *obj = data;
	int ret;

	ret = luavgl_set_property(L, obj, bar_property_table);
	if (ret == 0)
		return 0;

	/* a base obj property? */
	ret = luavgl_obj_set_property_kv(L, obj);
	if (ret != 0) {
		debug("unkown property for bar.\n");
	}

	return ret;
}

static int
luavgl_bar_set(lua_State *L)
{
	lv_obj_t *obj = luavgl_to_obj(L, 1);

	if (!lua_istable(L, -1)) {
		luaL_error(L, "expect a table on 2nd para.");
		return 0;
	}

	luavgl_iterate(L, -1, luavgl_bar_set_property_kv, obj);

	return 0;
}

static int
luavgl_bar_value(lua_State *L)
{
	lv_obj_t *obj = luavgl_to_obj(L, 1);
	int32_t v;

	if (lua_gettop(L) > 1) {
		/* set */
		v = luaL_checkinteger(L, 2);
		lv_bar_set_value(obj, v,
		    lua_toboolean(L, 3) ? LV_ANIM_ON : LV_ANIM_OFF);
	} else {
		/* get */
		v = lv_bar_get_value(obj);
	}

	lua_pushinteger(L, v);
	return (1);
}

static int
luavgl_bar_get_value(lua_State *L)
{
	lv_obj_t *obj = luavgl_to_obj(L, 1);
	lua_pushinteger(L, lv_bar_get_value(obj));
	return (1);
}

static int
luavgl_bar_set_value(lua_State *L)
{
	lv_obj_t *obj = luavgl_to_obj(L, 1);
	lv_bar_set_value(obj, luaL_checkinteger(L, 2),
	    lua_toboolean(L, 3) ? LV_ANIM_ON : LV_ANIM_OFF);
	return (0);
}

static int
luavgl_bar_get_min(lua_State *L)
{
	lv_obj_t *obj = luavgl_to_obj(L, 1);
	lua_pushinteger(L, lv_bar_get_min_value(obj));
	return (1);
}

static int
luavgl_bar_get_max(lua_State *L)
{
	lv_obj_t *obj = luavgl_to_obj(L, 1);
	lua_pushinteger(L, lv_bar_get_max_value(obj));
	return (1);
}

static const luaL_Reg luavgl_bar_methods[] = {
	{ "set",		luavgl_bar_set },

	{ "value",		luavgl_bar_value },
	{ "get_value",		luavgl_bar_get_value },
	{ "set_value",		luavgl_bar_set_value },

	{ "get_min",		luavgl_bar_get_min },
	{ "get_max",		luavgl_bar_get_max },

	{ NULL,			NULL }
};

static void
luavgl_bar_init(lua_State *L)
{
	luavgl_obj_newmetatable(L,
	    &lv_bar_class, "lv_bar", luavgl_bar_methods);
	lua_pop(L, 1);
}
