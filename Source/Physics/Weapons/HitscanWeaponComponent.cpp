// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/HitscanWeaponComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "PhysicsCharacter.h"
#include "PhysicsWeaponComponent.h"
#include "Camera/CameraComponent.h"

void UHitscanWeaponComponent::Fire()
{
	Super::Fire();

	FHitResult hit{};
	FVector start{ Character->FirstPersonCameraComponent->GetComponentLocation() };
	FVector dir{ Character->FirstPersonCameraComponent->GetForwardVector() };
	FVector end{ start + dir * 1000000};
	FCollisionQueryParams queryParams{};
	queryParams.AddIgnoredActor(GetOwner());
	bool hasHitSomething = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, queryParams);
	if (hasHitSomething && IsValid(hit.GetActor()))
	{
		UGameplayStatics::ApplyPointDamage(hit.GetActor(),
			ProjectileType.Damage,
			dir,
			hit,
			Character->GetController(),
			Character,
			ProjectileType.DamageTypeClass
		);
	}
}
