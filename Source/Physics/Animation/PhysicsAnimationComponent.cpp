// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PhysicsAnimationComponent.h"
#include "PhysicsAnimationComponent.h"
#include "PhysicsEngine/ConstraintInstance.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Character.h>
#include "AIController.h"

// Sets default values for this component's properties
UPhysicsAnimationComponent::UPhysicsAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPhysicsAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* OwnerActor = GetOwner())
	{
		m_Mesh = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
		OwnerActor->OnTakePointDamage.AddDynamic(this, &UPhysicsAnimationComponent::OnTakePointDamage);
	}
	
}

void UPhysicsAnimationComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	if (!m_Mesh)
	{
		return;
	}

	if (m_BreakableConstraints.Contains(BoneName))
	{
		m_Mesh->BreakConstraint(FVector::ZeroVector, HitLocation, BoneName);
		m_Mesh->SetBodySimulatePhysics(BoneName, true);
		m_Mesh->OnConstraintBroken.Broadcast(m_Mesh->FindConstraintIndex(BoneName));
	}
	else
	{
		m_AnimatedBone = !m_OverrideAnimatedBone.IsNone() ? m_OverrideAnimatedBone : BoneName;
		m_RemainingBlend = m_BlendDuration;
		m_Mesh->SetAllBodiesBelowSimulatePhysics(m_AnimatedBone, true, true);
	}
}

// Called every frame
void UPhysicsAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_RemainingBlend > 0.f && m_Curve)
	{
		m_RemainingBlend -= DeltaTime;
		float fCurveTime = m_BlendDuration > 0.f ? (1.f - m_RemainingBlend / m_BlendDuration) : 1.f;
		float fBlendWeight = m_Curve->GetFloatValue(fCurveTime);
		m_Mesh->SetAllBodiesBelowPhysicsBlendWeight(m_AnimatedBone, fBlendWeight);
	}
	else
	{
		m_Mesh->SetAllBodiesBelowSimulatePhysics(m_AnimatedBone, false, true);
	}
}

