// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvPhysDataTypes.h"
#include "AdvPhysEventBase.h"
#include "PhysSimulator.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "AdvPhysScene.generated.h"

UENUM(BlueprintType)
enum EAction
{
	Idle = 0,
	Recording,
	Playing
};

struct FStatus
{
	EAction Current;
	float PlayStartTime;
	float PlayLastFrameTime;
	TArray<AAdvPhysEventBase*> PlayEventActors;
};

DECLARE_MULTICAST_DELEGATE(FRecordFinishedDeleagte)

UCLASS()
class RUNTIMEBAKEDPHYSICS_API AAdvPhysScene : public AActor
{
	GENERATED_BODY()
	
public:
	AAdvPhysScene();
	
	UFUNCTION(BlueprintCallable)
		void AddDynamicObject(UStaticMeshComponent* Component);
	UFUNCTION(BlueprintCallable)
		void AddStaticObject(UStaticMeshComponent* Component);
	
	UFUNCTION(BlueprintCallable)
		void ClearPhysObjects();
	
	void Record(const float Interval, const int FrameCount);
	
	UFUNCTION(BlueprintCallable)
		void Play();
	UFUNCTION(BlueprintCallable)
		void Cancel();
	
	UFUNCTION(BlueprintCallable)
		void FreezeDynamicObjects();
	UFUNCTION(BlueprintCallable)
		void UnfreezeDynamicObjects();

	UFUNCTION(BlueprintCallable)
		EAction GetAction() const;

	UFUNCTION(BlueprintCallable)
		float GetRecordProgress() const;

	UFUNCTION(BlueprintCallable)
		float GetPlayFramesPerSecond() const;

	UFUNCTION(BlueprintCallable)
		int GetRecordDataFrameCount() const;

	UFUNCTION(BlueprintCallable)
		float GetRecordDataFrameInterval() const;

	UFUNCTION(BlueprintCallable)
		bool GetRecordDataFinished() const;


	void AddEvent(float Time, std::any Event);
	void ClearEvents();
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float PlayFramesPerSecond = -1;
	
	UPROPERTY(EditAnywhere)
	bool bEnableInterpolation = true;
	
	UPROPERTY(EditAnywhere)
	bool bAddTaggedObjectsOnBeginPlay = false;

	UPROPERTY(EditAnywhere)
	bool bFreezeDynamicObjectOnAdd = true;

	UPROPERTY(EditAnywhere)
	TArray<AAdvPhysEventBase*> EventActors;

	FRecordFinishedDeleagte RecordFinished;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	inline float GetDuration() const;

	void DoRecordTick();
	void DoPlayTick();

	void PlayFrame(float Time);
	void BroadcastEventsToActorsFrame(float Time);

	void AddTaggedObjects();
	void ResetPhysObjectsPosition();

	void CopyObjectsToSimulator();

	PhysSimulator Simulator;
	FStatus Status;
	
	TArray<FPhysObject> DynamicObjEntries;
	TArray<FPhysObject> StaticObjEntries;

	TArray<std::tuple<float, std::any>> EventPairs;
	
	FPhysRecordData RecordData;
	double RecordStartTime;
};
