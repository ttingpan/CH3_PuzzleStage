#include "MovablePlatformComponent.h"

UMovablePlatformComponent::UMovablePlatformComponent()
{
}

void UMovablePlatformComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMovablePlatformComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMovablePlatformComponent::Initialize()
{
	MoveLocationArray.Add(Owner->GetActorLocation());

	for (int i = 0; i < MoveValueArray.Num(); i++)
	{
		MoveLocationArray.Add(MoveLocationArray[i] + MoveValueArray[i]);
	}

	SizeOfTargetArray = MoveLocationArray.Num();

	CurrentTargetIndex = 1;
}

void UMovablePlatformComponent::PlatformAction(float DeltaTime)
{
	FVector CurrentLocation = Owner->GetActorLocation();
	FVector TargetLocation = MoveLocationArray[CurrentTargetIndex];

	/*UE_LOG(LogTemp, Warning, TEXT("%.2f / %.2f"), CurrentLocation.X, TargetLocation.X);*/

	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	FVector NewLocation = CurrentLocation + (Direction * Speed * DeltaTime);

	// 목표 위치에 도달 했는지 확인 - 오차 ScaleSpeed * DeltaTime = 한 프레임에 변화되는 크기량
	if (NewLocation.Equals(TargetLocation, Speed * DeltaTime))
	{
		NewLocation = TargetLocation;

		ChangeInAction();

		// 현재 반복 타입에 따라 동작 실행
		Super::PlatformAction(DeltaTime);

		if (TargetDelay > 0.0f)
		{
			// ChangeScaleDelay 시간 동안 기다렸다가 ChangeInAction 실행
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMovablePlatformComponent::ChangeInAction, TargetDelay);
		}
		else
		{
			ChangeInAction();
		}
	}

	Owner->SetActorLocation(NewLocation);
}

void UMovablePlatformComponent::Randomize()
{
	Super::Randomize();

	Speed = FMath::RandRange(1000.0f, 4000.0f);

	for (int i = 0; i < RandomTargetCount; i++)
	{
		MoveValueArray.Add(FVector(FMath::RandRange(-2000, 2000), FMath::RandRange(-2000, 2000), FMath::RandRange(-2000, 2000)));
	}

	Initialize();

	// StartDelay 시간 동안 기다렸다가 PlatformAction 실행
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMovablePlatformComponent::ChangeInAction, StartDelay);
}

