#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzlePlatformComponent.generated.h"

class APuzzlePlatform;

UENUM()
enum class EPlatformRepeatType
{
	// 정해진 순서대로 마지막 순번까지 진행 후 시작 순번부터 다시 진행
	REPEAT,
	// 마지막 순번까지 진행 후 역순으로 시작 순번까지 진행
	REVERSE
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CH3_PUZZLESTAGE_API UPuzzlePlatformComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPuzzlePlatformComponent();

	// 컴포넌트 등록 후 랜덤화
	void RandomizeAfterRegistration(APuzzlePlatform* Platform);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 초기화
	virtual void Initialize();

	// 랜덤화
	virtual void Randomize();

	// 동작 여부 반전
	void ChangeInAction();

	// 실제로 동작할 액션
	virtual void PlatformAction(float DeltaTime);

	// 순서대로 동작
	void RepeatAction();

	// 역순으로 동작
	void ReverseAction();

protected:
	// 반복 타입
	UPROPERTY(EditAnywhere, Category = "PuzzlePlatformComponent|Properties")
	EPlatformRepeatType RepeatType;

	// 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzlePlatformComponent|Properties")
	float Speed;

	// 역순 확인
	UPROPERTY(VisibleAnywhere, Category = "PuzzlePlatformComponent|Properties")
	bool bIsReverse;

	// 동작 여부
	UPROPERTY(EditAnywhere, Category = "PuzzlePlatformComponent|Properties")
	bool bInAction;

	// 현재 목표 인덱스
	UPROPERTY(VisibleAnywhere, Category = "PuzzlePlatformComponent|Properties")
	int CurrentTargetIndex;

	// 현재 목표 개수
	UPROPERTY(VisibleAnywhere, Category = "PuzzlePlatformComponent|Properties")
	int SizeOfTargetArray;

	// 시작 딜레이
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzlePlatformComponent|Timer|Properties")
	float StartDelay;

	// 목표 딜레이 - 각 목표 사이의 딜레이
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzlePlatformComponent|Timer|Properties")
	float TargetDelay;

	// 타이머
	FTimerHandle TimerHandle;
	
	// 부모 액터
	AActor* Owner;

	// 랜덤 목표 개수
	int RandomTargetCount;
};
