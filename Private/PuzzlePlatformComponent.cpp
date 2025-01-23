#include "PuzzlePlatformComponent.h"
#include "PuzzlePlatform.h"

UPuzzlePlatformComponent::UPuzzlePlatformComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	RepeatType = EPlatformRepeatType::REPEAT;
	Speed = 0.0f;
	CurrentTargetIndex = 0;
	SizeOfTargetArray = 0;
	StartDelay = 0.0f;
	TargetDelay = 0.0f;
	bIsReverse = false;
	bInAction = false;

	Owner = GetOwner();
}

void UPuzzlePlatformComponent::BeginPlay()
{
	Initialize();

	Super::BeginPlay();

	if (StartDelay > 0.0f)
	{
		// StartDelay 시간 동안 기다렸다가 PlatformAction 실행
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPuzzlePlatformComponent::ChangeInAction, StartDelay);
	}
	else
	{
		ChangeInAction();
	}
}

void UPuzzlePlatformComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bInAction)
	{
		// 동작 실행
		PlatformAction(DeltaTime);
	}
}

void UPuzzlePlatformComponent::Initialize()
{
}

void UPuzzlePlatformComponent::RandomizeAfterRegistration(APuzzlePlatform* Platform)
{
	Platform->AddComponent(this);

	this->RegisterComponent();

	Randomize();
}

void UPuzzlePlatformComponent::ChangeInAction()
{
	bInAction = !bInAction;
}

void UPuzzlePlatformComponent::PlatformAction(float DeltaTime)
{
	switch (RepeatType)
	{
	case EPlatformRepeatType::REPEAT:
		RepeatAction();
		break;
	case EPlatformRepeatType::REVERSE:
		ReverseAction();
		break;
	default:
		break;
	}
}

void UPuzzlePlatformComponent::RepeatAction()
{
	CurrentTargetIndex = (CurrentTargetIndex + 1) % SizeOfTargetArray;
}

void UPuzzlePlatformComponent::ReverseAction()
{
	if (!bIsReverse)
	{
		CurrentTargetIndex++;

		// 마지막 목표까지 가면 역순으로 진행
		if (CurrentTargetIndex >= SizeOfTargetArray)
		{
			CurrentTargetIndex = SizeOfTargetArray - 2;
			bIsReverse = true;
		}
	}
	else
	{
		CurrentTargetIndex--;

		// 처음 목표까지 돌아오면 원래 순서대로 진행
		if (CurrentTargetIndex < 0)
		{
			CurrentTargetIndex = 1;
			bIsReverse = false;
		}
	}
}

void UPuzzlePlatformComponent::Randomize()
{
	bInAction = false;
	RepeatType = FMath::RandRange(0, 1) == 0 ? EPlatformRepeatType::REPEAT : EPlatformRepeatType::REVERSE;
	StartDelay = 3.0f;
	TargetDelay = FMath::RandRange(0.0f, 5.0f);
	RandomTargetCount = FMath::RandRange(0, 100);

	// 0 ~ 60 => 60%
	if (RandomTargetCount <= 60)
	{
		RandomTargetCount = 1;
	}
	// 61 ~ 90 => 30%
	else if (RandomTargetCount <= 90)
	{
		RandomTargetCount = 2;
	}
	// 91 ~ 100 => 10%
	else
	{
		RandomTargetCount = 3;
	}
}

