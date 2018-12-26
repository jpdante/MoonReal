// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "lua.hpp"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LuaScriptAsset.h"
#include "LuaEngine.generated.h"

UCLASS()
class MOONREAL_API ALuaEngine : public AActor
{
	GENERATED_BODY()

public:
	ALuaEngine();
	~ALuaEngine();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULuaScriptAsset* SourceScript;

private:
	lua_State *LuaState;
	bool ScriptOK;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	static int lua_print(lua_State* L);
	static int lua_uelog(lua_State* L);
};
