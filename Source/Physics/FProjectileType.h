// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FProjectileType.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PHYSICS_API FProjectileType
{
	GENERATED_BODY()

public:
	// Damage dealt by projectile.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage{ 100.f };
	
	// Radius to apply damage. Negative values means only affects hit actors.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Radius{ -1.f };

	// Damage type class to apply damage using unreal system.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UDamageType> DamageTypeClass{ nullptr };
};
