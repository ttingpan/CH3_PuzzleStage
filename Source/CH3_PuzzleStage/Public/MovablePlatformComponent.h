#pragma once

#include "CoreMinimal.h"
#include "PuzzlePlatformComponent.h"
#include "MovablePlatformComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CH3_PUZZLESTAGE_API UMovablePlatformComponent : public UPuzzlePlatformComponent
{
	GENERATED_BODY()

public:	
	UMovablePlatformComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 초기화
	virtual void Initialize() override;

	// 랜덤화
	virtual void Randomize() override;

	// 위치 변화
	virtual void PlatformAction(float DeltaTime) override;

protected:
    // 목표 거리 배열 - 이전 위치에서 다음 위치까지의 거리만 입력
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovablePlatform|Properties")
    TArray<FVector> MoveValueArray;

	// 목표 위치 배열 - 실제 거리가 반영된 위치
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MovablePlatform|Properties")
	TArray<FVector> MoveLocationArray;
};
