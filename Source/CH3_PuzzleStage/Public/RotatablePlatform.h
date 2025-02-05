#pragma once

#include "CoreMinimal.h"
#include "PuzzlePlatformComponent.h"
#include "RotatablePlatform.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CH3_PUZZLESTAGE_API URotatablePlatformComponent : public UPuzzlePlatformComponent
{
	GENERATED_BODY()

public:	
	URotatablePlatformComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 초기화
	virtual void Initialize() override;

	// 랜덤화
	virtual void Randomize() override;

	// 각도 변화
	virtual void PlatformAction(float DeltaTime) override;

protected:
	// 추가 각도 배열 - 이전 각도에서 다음 각도까지의 각도만 입력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotatablePlatform|Properties")
	TArray<FRotator> RotateValueArray;

	// 목표 각도 배열 - 실제 각도가 반영된 각도 배열
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RotatablePlatform|Properties")
	TArray<FRotator> RotationArray;
};
