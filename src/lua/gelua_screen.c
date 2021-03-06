/*
	The Gamma Engine Library is a multiplatform library made to make games
	Copyright (C) 2012  Aubry Adrien (dridri85)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ge_lua.c"

UserdataStubs(Color, u32)

static int Color_colors(lua_State *L){
	int argc = lua_gettop(L);
	if(argc != 1) return luaL_error(L, "Argument error: color:colors() takes no arguments, and must be called from an instance with a colon.");
	u32* color = toColor(L, 1);
	int r = R(*color); 
	int g = G(*color);
	int b = B(*color);
	int a = A(*color);

	lua_newtable(L);
	lua_pushstring(L, "r"); lua_pushnumber(L, r); lua_settable(L, -3);
	lua_pushstring(L, "g"); lua_pushnumber(L, g); lua_settable(L, -3);
	lua_pushstring(L, "b"); lua_pushnumber(L, b); lua_settable(L, -3);
	lua_pushstring(L, "a"); lua_pushnumber(L, a); lua_settable(L, -3);

	return 1;
}

static int Color_new(lua_State *L){
//	lua_lock(L);

	int argc = lua_gettop(L); 
	if (argc != 3 && argc != 4) return luaL_error(L, "Argument error: Color.New(r, g, b, [a]) takes either three color arguments or three color arguments and an alpha value.");

	u8 r = (u8)luaL_checkint(L, 1);
	u8 g = (u8)luaL_checkint(L, 2);
	u8 b = (u8)luaL_checkint(L, 3);
	u8 a = 0xff;
	if(argc == 4){
		a = (u8)luaL_checkint(L, 4);
	}
	*pushNewColor(L) = RGBA(r, g, b, a);

//	lua_unlock(L);
	return 1;
}

static int Color_set(lua_State *L){
	int argc = lua_gettop(L); 
	if (argc != 3 && argc != 4) return luaL_error(L, "Argument error: Color:Set(r, g, b, [a]) takes either three color arguments or three color arguments and an alpha value, and must be with a colon");
	
	u32* color = selfPtrColor(L, &argc);

	u8 r = (u8)lua_tointeger(L, 1);
	u8 g = (u8)lua_tointeger(L, 2);
	u8 b = (u8)lua_tointeger(L, 3);
	u8 a = 255;
	if(argc == 4){
		a = (u8)lua_tointeger(L, 4);
	}

	*color = RGBA(r, g, b, a);

	return 1;
}

static int Color_r(lua_State *L){
	int argc = lua_gettop(L); 
	u32* color = selfPtrColor(L, &argc);
	if(argc == 1){
		u8 r = (u8)lua_tointeger(L, 1);
		*color = RGBA(r, G(*color), B(*color), A(*color));
	}else{
		lua_pushinteger(L, R(*color));
	}
	return 1;
}

static int Color_g(lua_State *L){
	int argc = lua_gettop(L); 
	u32* color = selfPtrColor(L, &argc);
	if(argc == 1){
		u8 g = (u8)lua_tointeger(L, 1);
		*color = RGBA(R(*color), g, B(*color), A(*color));
	}else{
		lua_pushinteger(L, G(*color));
	}
	return 1;
}

static int Color_b(lua_State *L){
	int argc = lua_gettop(L); 
	u32* color = selfPtrColor(L, &argc);
	if(argc == 1){
		u8 b = (u8)lua_tointeger(L, 1);
		*color = RGBA(R(*color), G(*color), b, A(*color));
	}else{
		lua_pushinteger(L, B(*color));
	}
	return 1;
}

static int Color_a(lua_State *L){
	int argc = lua_gettop(L); 
	u32* color = selfPtrColor(L, &argc);
	if(argc == 1){
		u8 a = (u8)lua_tointeger(L, 1);
		if(a == 0){
			a = (u8)lua_tonumber(L, 1);
		}
		*color = RGBA(R(*color), G(*color), B(*color), a);
	}else{
		lua_pushinteger(L, A(*color));
	}
	return 1;
}

static int Color_tostring(lua_State *L){
	Color_colors(L);
	lua_pushstring(L, "r"); lua_gettable(L, -2); int r = luaL_checkint(L, -1); lua_pop(L, 1);
	lua_pushstring(L, "g"); lua_gettable(L, -2); int g = luaL_checkint(L, -1); lua_pop(L, 1);
	lua_pushstring(L, "b"); lua_gettable(L, -2); int b = luaL_checkint(L, -1); lua_pop(L, 1);
	lua_pushstring(L, "a"); lua_gettable(L, -2); int a = luaL_checkint(L, -1); lua_pop(L, 1);
	lua_pop(L, 1); // pop the table
	lua_pushfstring(L, "Color (r %d, g %d, b %d, a %d)", r, g, b, a);
	return 1;
}

static int Color_equal(lua_State *L){
	u32 a = *toColor(L, 1);
	u32 b = *toColor(L, 2);
	lua_pushboolean(L, a == b);
	return 1;
}

static const luaL_Reg Color_methods[] = {
	{ "new", Color_new },
	{ "set", Color_set },
	{ "r", Color_r },
	{ "g", Color_g },
	{ "b", Color_b },
	{ "a", Color_a },
	{ NULL, NULL }
};
static const luaL_Reg Color_meta[] = {
	{ "__tostring", Color_tostring },
	{ "__eq", Color_equal },
	{ NULL, NULL }
};

UserdataRegister(Color, Color_methods, Color_meta)

int geLuaInit_screen(lua_State* L){
	Color_register(L);
	return 0;
}
