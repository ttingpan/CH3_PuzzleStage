#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DisappearableComponent.generated.h"

class APuzzlePlatform;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CH3_PUZZLESTAGE_API UDisappearableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDisappearableComponent();
	
	// 컴포넌트 등록 후 랜덤화
	void RandomizeAfterRegistration(APuzzlePlatform* Platform);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 사라지고 나타나는 동작
	void ChangeVisibleActor();

	// 랜덤화
	virtual void Randomize();

protected:

	// 반복 동작 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisappearableComponent|Properties")
	bool bIsLoop;

	// 사라진 상태 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisappearableComponent|Properties")
	bool bIsDisappeared;

	// 시작 콜리전 프로필
	UPROPERTY(VisibleAnywhere, Category = "DisappearableComponent|Properties")
	FName StartCollisionProfileName;

	// 시작 딜레이
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisappearableComponent|Properties")
	float StartDelay;

	// 사라지기 전, 나타나기 전 딜레이
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DisappearableComponent|Properties")
	float DisappearDelay;

	// 타이머
	FTimerHandle TimerHandle;

	// 부모 액터
	AActor* Owner;
};
