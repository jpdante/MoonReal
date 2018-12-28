// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaEngine.h"

// luaL_Reg printlib[] = {
// 	{ "print", ALuaEngine::lua_print },
// 	{ "UE_LOG", ALuaEngine::lua_uelog },
//     { "drawdebug", ALuaEngine::lua_drawdebug },
// 	{ NULL, NULL }
// };

luaL_Reg UnrealSearchLib[] = {
	{ "FindActor", ALuaEngine::USL_FindActor },
	{ NULL, NULL }
};

UWorld *ALuaEngine::StaticWorld = nullptr;

// int ALuaEngine::lua_drawdebug(lua_State* L) {
// 	int nargs = lua_gettop(L);
// 	if (nargs == 2) {
// 		const float time = lua_tointeger(L, 1);
// 		const char *msg = lua_tostring(L, 2);
// 		FString fmsg(msg);
// 		GEngine->AddOnScreenDebugMessage(-1, time, FColor::White, fmsg);
// 	}
// 	return 0;
// }
// 
// int ALuaEngine::lua_print(lua_State* L) {
// 	int nargs = lua_gettop(L);
// 	for (int i = 1; i <= nargs; ++i) {
// 		const char *msg = lua_tostring(L, i);
// 		FString fmsg(msg);
// 		UE_LOG(LogTemp, Log, TEXT("%s"), *fmsg);
// 	}
// 	return 0;
// }
// 
// int ALuaEngine::lua_uelog(lua_State* L) {
// 	int nargs = lua_gettop(L);
// 	if (nargs == 2) {
// 		const char *msg = lua_tostring(L, 1);
// 		FString fmsg(msg);
// 		const int level = lua_tointeger(L, 2);
// 		switch (level) {
// 		case 0:
// 			UE_LOG(LogTemp, Log, TEXT("%s"), *fmsg);
// 			break;
// 		case 1:
// 			UE_LOG(LogTemp, Display, TEXT("%s"), *fmsg);
// 			break;
// 		case 2:
// 			UE_LOG(LogTemp, Warning, TEXT("%s"), *fmsg);
// 			break;
// 		case 3:
// 			UE_LOG(LogTemp, Error, TEXT("%s"), *fmsg);
// 			break;
// 		case 4:
// 			UE_LOG(LogTemp, Fatal, TEXT("%s"), *fmsg);
// 			break;
// 		case 5:
// 			UE_LOG(LogTemp, Verbose, TEXT("%s"), *fmsg);
// 			break;
// 		case 6:
// 			UE_LOG(LogTemp, VeryVerbose, TEXT("%s"), *fmsg);
// 			break;
// 		default:
// 			UE_LOG(LogTemp, Log, TEXT("%s"), *fmsg);
// 			break;
// 		}
// 	}
// 	return 0;
// }

int ALuaEngine::USL_FindActor(lua_State* L) {
	int nargs = lua_gettop(L);
	UE_LOG(LogTemp, Error, TEXT("ALOOOOOOOOOOOOOOOOO"));
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

// void ALuaEngine::BeginPlay()
// {
// 	Super::BeginPlay();
// 	// Memory violations are occurring (Maybe the reading is violating the memory ???)
// // 	if (!IsValid(StaticWorld) || StaticWorld != GetWorld()) {
// // 		UE_LOG(LogTemp, Warning, TEXT("Setting static world"));
// // 		StaticWorld = GetWorld();
// // 	}
// 	StaticWorld = GetWorld();
// 	if (IsValid(SourceScript)) {
// 		LuaState = luaL_newstate();
// 		luaL_openlibs(LuaState);
// 		FString tempData = SourceScript->LuaScript.ToString();
// 		luaL_loadstring(LuaState, TCHAR_TO_UTF8(*tempData));
// // 		lua_getglobal(LuaState, "_G");
// // 		if (IsValid(GetParentActor())) {
// // 			lua_pushstring(LuaState, TCHAR_TO_UTF8(*GetParentActor()->GetName()));
// // 			lua_setglobal(LuaState, "ActorParentName");
// // 		}
// // 		lua_pushstring(LuaState, TCHAR_TO_UTF8(*this->GetName()));
// // 		lua_setglobal(LuaState, "ActorName");
//  		RegisterMethods();
// 		if (lua_pcall(LuaState, 0, LUA_MULTRET, 0)) {
// 			FString msg(lua_tostring(LuaState, -1));
// 			UE_LOG(LogTemp, Error, TEXT("Failed to execute Lua: %s"), *msg);
// 			return;
// 		}
// 		lua_getglobal(LuaState, "BeginPlay");
// 		if (lua_pcall(LuaState, 0, 0, 0)) {
// 			FString msg(lua_tostring(LuaState, -1));
// 			UE_LOG(LogTemp, Error, TEXT("Failed to execute BeginPlay: %s"), *msg);
// 			return;
// 		}
// // 		ScriptOK = true;
// 	}
// 	else {
// 		UE_LOG(LogTemp, Error, TEXT("Failed to execute Lua: SourceScript is invalid!"));
// 	}
// }

void ALuaEngine::BeginPlay()
{
	Super::BeginPlay();
	StaticWorld = GetWorld();
	if (IsValid(SourceScript))
	{
		LuaState = ULuaUtils::GetNewState();
		ULuaUtils::OpenLibs(LuaState);
		/*ULuaUtils::RegisterFunc(LuaState, UnrealSearchLib);*/
		lua_settop(LuaState, 0);
		if (luaL_newmetatable(LuaState, "UEShared")) {
			luaL_setfuncs(LuaState, UnrealSearchLib, 0);
			lua_pop(LuaState, 1);
			//luaL_newlib(LuaState, UnrealSearchLib);
		}
		ULuaUtils::LoadFromFString(LuaState, SourceScript->LuaScript.ToString());
		ULuaUtils::LuaCall(LuaState, 0, -1, 0);
	}
	else
	{

	}
}

void ALuaEngine::Tick(float DeltaTime)
{

}
// void ALuaEngine::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// 	if (ScriptOK) {
// 		lua_getglobal(LuaState, "Tick");
// 		lua_pushnumber(LuaState, DeltaTime);
// 		if (lua_pcall(LuaState, 1, 0, 0)) {
// 			FString msg(lua_tostring(LuaState, -1));
// 			UE_LOG(LogTemp, Error, TEXT("Failed to execute Tick: %s"), *msg);
// 			return;
// 		}
// 	}
// }

// void ALuaEngine::RegisterMethods() {
// 	UE_LOG(LogTemp, Error, TEXT("Registering uesearch..."));
// 	lua_newtable(LuaState);
// 	luaL_setfuncs(LuaState, UnrealSearchLib, 0);
// 	lua_setglobal(LuaState, "uesearch");
// 	lua_getglobal(LuaState, "uesearch");
// 	if (lua_isnil(LuaState, -1)) {
// 		lua_pop(LuaState, 1);
// 		lua_newtable(LuaState);
// 	}
// 	luaL_setfuncs(LuaState, UnrealSearchLib, 0);
// 	lua_setglobal(LuaState, "uesearch");
// }