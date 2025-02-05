#include "ScalablePlatformComponent.h"

UScalablePlatformComponent::UScalablePlatformComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UScalablePlatformComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UScalablePlatformComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UScalablePlatformComponent::Initialize()
{
	ScaleValueArray.Add(Owner->GetActorScale3D());

	SizeOfTargetArray = ScaleValueArray.Num();
}

void UScalablePlatformComponent::PlatformAction(float DeltaTime)
{
	Owner->SetActorHiddenInGame(false);

	FVector CurrentScale = Owner->GetActorScale3D();
	FVector TargetScale = ScaleValueArray[CurrentTargetIndex];

	FVector Direction = (TargetScale - CurrentScale).GetSafeNormal();
	FVector NewScale = CurrentScale + (Direction * Speed * DeltaTime);

	// 목표 크기에 도달 했는지 확인 - 오차 ScaleSpeed * DeltaTime = 한 프레임에 변화되는 크기량
	if (NewScale.Equals(TargetScale, Speed * DeltaTime))
	{
		NewScale = TargetScale;

		// 스케일 중 하나라도 0이면 안보이도록 설정
		if (FMath::IsNearlyZero(Owner->GetActorScale3D().X)
			|| FMath::IsNearlyZero(Owner->GetActorScale3D().Y)
			|| FMath::IsNearlyZero(Owner->GetActorScale3D().Z))
		{
			Owner->SetActorHiddenInGame(true);
		}

		ChangeInAction();

		// 현재 반복 타입에 따라 동작 실행
		Super::PlatformAction(DeltaTime);

		if (TargetDelay > 0.0f)
		{
			// ChangeScaleDelay 시간 동안 기다렸다가 ChangeInAction 실행
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UScalablePlatformComponent::ChangeInAction, TargetDelay);
		}
		else
		{
			ChangeInAction();
		}
	}

	Owner->SetActorScale3D(NewScale);
}

void UScalablePlatformComponent::Randomize()
{
	Super::Randomize();

	Speed = FMath::RandRange(0.01f, 50.0f);

	for (int i = 0; i < RandomTargetCount; i++)
	{
		ScaleValueArray.Add(FVector(FMath::RandRange(0.0f, 5.0f), FMath::RandRange(0.0f, 5.0f), FMath::RandRange(0.0f, 5.0f)));
	}

	Initialize();

	// StartDelay 시간 동안 기다렸다가 PlatformAction 실행
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UScalablePlatformComponent::ChangeInAction, StartDelay);
}

