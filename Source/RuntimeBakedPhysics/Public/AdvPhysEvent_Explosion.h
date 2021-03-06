// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvPhysDataTypes.h"
#include "AdvPhysEventBase.h"
#include "AdvPhysEvent_Explosion.generated.h"

UCLASS()
class RUNTIMEBAKEDPHYSICS_API AAdvPhysEvent_Explosion : public AAdvPhysEventBase
{
	GENERATED_BODY()
	
public:

	AAdvPhysEvent_Explosion();
	
	UPROPERTY(EditAnywhere)
		float Impulse;
	UPROPERTY(EditAnywhere)
		float FallOffMinDistance;
	UPROPERTY(EditAnywhere)
		float FallOffMaxDistance;

protected:
	virtual void DoEventPhysX(std::vector<physx::PxRigidDynamic*>& Bodies) override;
	virtual void DoEventUE(TArray<FPhysObject>& Dynamics) override;
};
