// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaEngine.h"

luaL_Reg printlib[] = {
	{ "print", ALuaEngine::lua_print },
	{ "UE_LOG", ALuaEngine::lua_uelog },
	{ NULL, NULL }
};

int ALuaEngine::lua_print(lua_State* L) {
	int nargs = lua_gettop(L);
	for (int i = 1; i <= nargs; ++i) {
		const char *msg = lua_tostring(L, i);
		FString fmsg(msg);
		UE_LOG(LogTemp, Log, TEXT("%s"), *fmsg);
	}
	return 0;
}

int ALuaEngine::lua_uelog(lua_State* L) {
	int nargs = lua_gettop(L);
	if (nargs == 2) {
		const char *msg = lua_tostring(L, 1);
		FString fmsg(msg);
		const int level = lua_tointeger(L, 2);
		switch (level) {
		case 0:
			UE_LOG(LogTemp, Log, TEXT("%s"), *fmsg);
			break;
		case 1:
			UE_LOG(LogTemp, Display, TEXT("%s"), *fmsg);
			break;
		case 2:
			UE_LOG(LogTemp, Warning, TEXT("%s"), *fmsg);
			break;
		case 3:
			UE_LOG(LogTemp, Error, TEXT("%s"), *fmsg);
			break;
		case 4:
			UE_LOG(LogTemp, Fatal, TEXT("%s"), *fmsg);
			break;
		case 5:
			UE_LOG(LogTemp, Verbose, TEXT("%s"), *fmsg);
			break;
		case 6:
			UE_LOG(LogTemp, VeryVerbose, TEXT("%s"), *fmsg);
			break;
		default:
			UE_LOG(LogTemp, Log, TEXT("%s"), *fmsg);
			break;
		}
	}
	return 0;
}

ALuaEngine::ALuaEngine()
{
	PrimaryActorTick.bCanEverTick = true;
	ScriptOK = false;
}

ALuaEngine::~ALuaEngine()
{
	if (LuaState != nullptr)
	{
		lua_close(LuaState);
	}
}

void ALuaEngine::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(SourceScript)) {
		LuaState = luaL_newstate();
		luaL_openlibs(LuaState);
		//luaL_loadstring(LuaState, TCHAR_TO_UTF8(*SourceScript->LuaScript));
		FString tempData = SourceScript->LuaScript.ToString();
		luaL_loadstring(LuaState, TCHAR_TO_UTF8(*tempData));
		lua_getglobal(LuaState, "_G");
		luaL_setfuncs(LuaState, printlib, 0);
		lua_pop(LuaState, 1);
		if (lua_pcall(LuaState, 0, LUA_MULTRET, 0)) {
			FString msg(lua_tostring(LuaState, -1));
			UE_LOG(LogTemp, Error, TEXT("Failed to execute Lua: %s"), *msg);
			return;
		}
		lua_getglobal(LuaState, "BeginPlay");
		if (lua_pcall(LuaState, 0, 0, 0)) {
			FString msg(lua_tostring(LuaState, -1));
			UE_LOG(LogTemp, Error, TEXT("Failed to execute BeginPlay: %s"), *msg);
			return;
		}
		ScriptOK = true;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Failed to execute Lua: SourceScript is invalid!"));
	}
}

void ALuaEngine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ScriptOK) {
		lua_getglobal(LuaState, "Tick");
		lua_pushnumber(LuaState, DeltaTime);
		if (lua_pcall(LuaState, 1, 0, 0)) {
			FString msg(lua_tostring(LuaState, -1));
			UE_LOG(LogTemp, Error, TEXT("Failed to execute Tick: %s"), *msg);
			return;
		}
	}
}

