#include "PuzzlePlatform.h"

APuzzlePlatform::APuzzlePlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	// 씬 루트 생성
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	// 스태틱 매쉬 생성
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
}

void APuzzlePlatform::AddComponent(UActorComponent* InComponent)
{
	ComponentArray.Add(InComponent);
}

void APuzzlePlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void APuzzlePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

