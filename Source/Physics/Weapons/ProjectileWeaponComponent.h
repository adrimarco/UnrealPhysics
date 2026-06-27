#pragma once

#include "CoreMinimal.h"
#include "Weapons/PhysicsWeaponComponent.h"
#include "FProjectileType.h"
#include "ProjectileWeaponComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PHYSICS_API UProjectileWeaponComponent : public UPhysicsWeaponComponent
{
	GENERATED_BODY()

public:

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class APhysicsProjectile> m_ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	FProjectileType ProjectileParams;

public:
	/** UPhysicsWeaponComponent **/
	virtual void Fire() override;
};
