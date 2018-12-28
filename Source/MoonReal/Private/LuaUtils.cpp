// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaUtils.h"

ULuaUtils::ULuaUtils(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

lua_State* ULuaUtils::GetNewState()
{
	return luaL_newstate();
}

void ULuaUtils::DestroyState(lua_State * L)
{
	lua_close(L);
}

void ULuaUtils::OpenLibs(lua_State * L)
{
	luaL_requiref(L, "_G", luaopen_base, 1);
	luaL_requiref(L, "package", luaopen_package, 1);
	lua_pop(L, 2); /* remove results from previous calls */
// 	registerlib(L, "coroutine", luaopen_coroutine);
// 	registerlib(L, "table", luaopen_table);
// 	registerlib(L, "io", luaopen_io);
// 	registerlib(L, "os", luaopen_os);
// 	registerlib(L, "string", luaopen_string);
// 	registerlib(L, "math", luaopen_math);
// 	registerlib(L, "utf8", luaopen_utf8);
// 	registerlib(L, "debug", luaopen_debug);
}

void ULuaUtils::RegisterLib(lua_State *L, const char *name, lua_CFunction f)
{
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "preload"); /* get 'package.preload' */
	lua_pushcfunction(L, f);
	lua_setfield(L, -2, name); /* package.preload[name] = f */
	lua_pop(L, 2); /* pop 'package' and 'preload' tables */
}

void ULuaUtils::RegisterFunc(lua_State *L, luaL_Reg lib)
{
	/*luaL_newlib(L, lib);*/
}

void ULuaUtils::LoadFromFString(lua_State *L, FString script)
{
	luaL_loadstring(L, TCHAR_TO_UTF8(*script));
}

bool ULuaUtils::LuaCall(lua_State *L, int arguments = 0, int result = LUA_MULTRET, int unknown = 0)
{
	if (lua_pcall(L, arguments, result, unknown) == LUA_OK)
	{
		return true;
	}
	else
	{
		LuaThrowError(L);
		return false;
	}
}

void ULuaUtils::LuaThrowError(lua_State *L)
{
	const char *chars = lua_tostring(L, -1);
	FString msg(chars);
	UE_LOG(LogTemp, Error, TEXT("%s"), *msg);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, msg);
}

