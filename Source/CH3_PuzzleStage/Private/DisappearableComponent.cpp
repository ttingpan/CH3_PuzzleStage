#include "DisappearableComponent.h"
#include "PuzzlePlatform.h"

UDisappearableComponent::UDisappearableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bIsLoop = true;
	bIsDisappeared = false;
	StartCollisionProfileName = "";
	StartDelay = 0.0f;
	DisappearDelay = 1.0f;

	Owner = GetOwner();
}

void UDisappearableComponent::RandomizeAfterRegistration(APuzzlePlatform* Platform)
{
	Platform->AddComponent(this);

	this->RegisterComponent();

	Randomize();
}

void UDisappearableComponent::BeginPlay()
{
	Super::BeginPlay();

	// 시작 콜리전 프로필 저장
	StartCollisionProfileName = Owner->GetComponentByClass<UStaticMeshComponent>()->GetCollisionProfileName();

	// 사라진 상태 체크하고 시작하면 시작시 사라지도록 설정
	if (bIsDisappeared)
	{
		ChangeVisibleActor();
	}

	if (StartDelay > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDisappearableComponent::ChangeVisibleActor, DisappearDelay, bIsLoop, StartDelay);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDisappearableComponent::ChangeVisibleActor, DisappearDelay, bIsLoop);
	}
}

void UDisappearableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDisappearableComponent::ChangeVisibleActor()
{
	bIsDisappeared = !bIsDisappeared;

	Owner->SetActorHiddenInGame(bIsDisappeared);

	FName NewCollisionProfileName = bIsDisappeared ? "No Collision" : StartCollisionProfileName;
	Owner->GetComponentByClass<UStaticMeshComponent>()->SetCollisionProfileName(NewCollisionProfileName);
}

void UDisappearableComponent::Randomize()
{
	StartDelay = 1.0f;
	DisappearDelay = FMath::RandRange(0.5f, 3.0f);
}

