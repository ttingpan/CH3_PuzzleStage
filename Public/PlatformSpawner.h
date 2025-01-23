#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

class APuzzlePlatform;

UCLASS()
class CH3_PUZZLESTAGE_API APlatformSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	APlatformSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// 랜덤 스폰
	UFUNCTION(BlueprintCallable)
	void RandomSpawnActor();

	// 랜덤 좌표
	FVector GetRandomLocation(int Index);

	// 랜덤 각도
	FRotator GetRandomRotation();

	// 랜덤 스케일
	FVector GetRandomScale();

	// 랜덤 컴포넌트 추가
	void AddRandomComponent(APuzzlePlatform* Platform);

private:

	// 랜덤 컴포넌트 종류 개수
	int GetRandomTypeCount();

protected:
	// 씬 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "PlatformSpawner|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformSpawner|Components")
	class UBoxComponent* SpawnVolume;

	// 스폰 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformSpawner|Properties")
	FVector SpawnArea;

	// 스폰 대상 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformSpawner|Properties")
	int PlatformCount;

	// 스폰 대상 액터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformSpawner|Properties")
	TSubclassOf<APuzzlePlatform> SpawnActor;

	// 스폰 대상 머티리얼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlatformSpawner|Properties")
	TArray<UMaterialInstance*> SpawnActorMaterialArray;

	// 타이머
	FTimerHandle TimerHandle;
};
