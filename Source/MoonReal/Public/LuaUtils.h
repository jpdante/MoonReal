// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "lua.hpp"
#include "CoreMinimal.h"
#include "Engine.h"
#include "LuaUtils.generated.h"

UCLASS()
class MOONREAL_API ULuaUtils : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	static lua_State* GetNewState();
	static void DestroyState(lua_State *L);
	static void OpenLibs(lua_State *L);
	static void RegisterLib(lua_State *L, const char *name, lua_CFunction f);
	static void RegisterFunc(lua_State *L, luaL_Reg lib);
	static void LoadFromFString(lua_State *L, FString script);
	static bool LuaCall(lua_State *L, int arguments, int result, int unknown);
	static void LuaThrowError(lua_State *L);
};