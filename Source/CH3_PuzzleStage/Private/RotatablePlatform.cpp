#include "RotatablePlatform.h"

URotatablePlatformComponent::URotatablePlatformComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Speed = 10;
}

void URotatablePlatformComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URotatablePlatformComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void URotatablePlatformComponent::Initialize()
{
	RotationArray.Add(Owner->GetActorRotation());

	for (int i = 0; i < RotateValueArray.Num(); i++)
	{
		RotationArray.Add(RotationArray[i] + RotateValueArray[i]);
	}

	SizeOfTargetArray = RotationArray.Num();
}

void URotatablePlatformComponent::PlatformAction(float DeltaTime)
{
	FQuat CurrentQuat = Owner->GetActorRotation().Quaternion();
	FQuat TargetQuat = FQuat(RotationArray[CurrentTargetIndex]);

	// 회전 방향 및 속도 계산
	float LerpSpeed = Speed * DeltaTime;
	// 보간 사용으로 쿼터니언 계산을 쉽게 해결함
	FQuat NewQuat = FQuat::Slerp(CurrentQuat, TargetQuat, LerpSpeed);

	// 목표 각도에 도달 했는지 확인 - 오차 ScaleSpeed * DeltaTime = 한 프레임에 변화되는 각도량
	if (NewQuat.Equals(TargetQuat, Speed * DeltaTime))
	{
		NewQuat = TargetQuat;

		ChangeInAction();

		// 현재 반복 타입에 따라 동작 실행
		Super::PlatformAction(DeltaTime);

		if (TargetDelay > 0.0f)
		{
			// ChangeRotateDelay 시간 동안 기다렸다가 ChangeInAction 실행
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &URotatablePlatformComponent::ChangeInAction, TargetDelay);
		}
		else
		{
			ChangeInAction();
		}
	}

	// 새로운 회전값을 적용
	Owner->SetActorRotation(NewQuat);
}

void URotatablePlatformComponent::Randomize()
{
	Super::Randomize();

	Speed = FMath::RandRange(0.01f, 30.0f);

	for (int i = 0; i < RandomTargetCount; i++)
	{
		RotateValueArray.Add(FRotator(FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f)));
	}

	Initialize();

	// StartDelay 시간 동안 기다렸다가 PlatformAction 실행
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &URotatablePlatformComponent::ChangeInAction, StartDelay);
}

