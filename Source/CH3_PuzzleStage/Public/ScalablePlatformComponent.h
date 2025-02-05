#pragma once

#include "CoreMinimal.h"
#include "PuzzlePlatformComponent.h"
#include "ScalablePlatformComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CH3_PUZZLESTAGE_API UScalablePlatformComponent : public UPuzzlePlatformComponent
{
	GENERATED_BODY()

public:	
	UScalablePlatformComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 초기화
	virtual void Initialize() override;

	// 랜덤화
	virtual void Randomize() override;

	// 크기 변화
	virtual void PlatformAction(float DeltaTime) override;

protected:
	// 묙표 크기 배열
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScalablePlatform|Properties")
	TArray<FVector> ScaleValueArray;
};
