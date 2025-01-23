#include "PlatformSpawner.h"
#include "Components/BoxComponent.h"
#include "PuzzlePlatform.h"
#include "MovablePlatformComponent.h"
#include "RotatablePlatform.h"
#include "ScalablePlatformComponent.h"
#include "DisappearableComponent.h"

APlatformSpawner::APlatformSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	// 씬 루트 생성
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->AttachToComponent(SceneRoot, FAttachmentTransformRules::KeepRelativeTransform);

	PlatformCount = 0;
}

void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();

	// 개수는 0이상만 허용
	PlatformCount = PlatformCount < 0 ? 0 : PlatformCount;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlatformSpawner::RandomSpawnActor, 3.0f);
}

void APlatformSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlatformSpawner::RandomSpawnActor()
{
	for (int i = 0; i < PlatformCount; i++)
	{
		APuzzlePlatform* Platform = GetWorld()->SpawnActor<APuzzlePlatform>(SpawnActor, GetActorLocation(), GetActorRotation());

		// 랜덤으로 위치 설정
		Platform->SetActorLocation(GetRandomLocation(i));

		// 랜덤 각도 설정
		Platform->SetActorRotation(GetRandomRotation());

		// 랜덤 스케일 설정
		Platform->SetActorScale3D(GetRandomScale());

		// 랜덤 머티리얼 설정
		int RandomIndex = FMath::RandRange(0, SpawnActorMaterialArray.Num() - 1);
		Platform->GetComponentByClass<UStaticMeshComponent>()->SetMaterial(0, SpawnActorMaterialArray[RandomIndex]);

		// 랜덤으로 컴포넌트 추가
		AddRandomComponent(Platform);
	}
}

FVector APlatformSpawner::GetRandomLocation(int Index)
{
	// 최소 위치
	FVector MinLocation = GetActorLocation() - SpawnArea;
	// 최대 위치
	FVector MaxLocation = GetActorLocation() + SpawnArea;

	// X축 기준 구간 별 범위
	float MinRandomX = Index * (SpawnArea.X * 2 / PlatformCount);
	float MaxRandomX = (Index + 1) * (SpawnArea.X * 2 / PlatformCount);

	// X축을 기준으로 나눠서 순서대로 위치하도록 설정
	float RandomX = FMath::RandRange(MinLocation.X + MinRandomX, MinLocation.X + MaxRandomX);
	// YZ축은 최소, 최대 범위 내에서만 위치하도록 설정
	float RandomY = FMath::RandRange(MinLocation.Y, MaxLocation.Y);
	float RandomZ = FMath::RandRange(MinLocation.Z, MaxLocation.Z);

	return FVector(RandomX, RandomY, RandomZ);
}

FRotator APlatformSpawner::GetRandomRotation()
{
	return FRotator(FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f));
}

FVector APlatformSpawner::GetRandomScale()
{
	return FVector(FMath::RandRange(0.5f, 3.0f), FMath::RandRange(0.5f, 3.0f), FMath::RandRange(0.5f, 3.0f));
}

void APlatformSpawner::AddRandomComponent(APuzzlePlatform* Platform)
{
	// 1 ~ 3종류 컴포넌트 추가
	int TypeCount = GetRandomTypeCount();

	// 추가한 컴포넌트 인덱스
	TSet<int> AddedType;

	for (int i = 0; i < TypeCount; i++)
	{
		// 랜덤으로 컴포넌트 인덱스 설정
		int RandomType = FMath::RandRange(0, 2);

		// 해당 인덱스가 이미 추가한 컴포넌트 인덱스일 경우
		while (AddedType.Find(RandomType))
		{
			// 인덱스 재설정
			RandomType = FMath::RandRange(0, 2);
		}

		// 컴포넌트 생성
		UPuzzlePlatformComponent* PlatformComp;

		switch (RandomType)
		{
			// 이동 가능 컴포넌트 추가
		case 0:
		{
			PlatformComp = NewObject<UMovablePlatformComponent>(Platform);
			break;
		}
		// 회전 가능 컴포넌트 추가
		case 1:
		{
			PlatformComp = NewObject<URotatablePlatformComponent>(Platform);

			break;
		}

		// 크기 변화 가능 컴포넌트 추가
		case 2:
		{
			PlatformComp = NewObject<UScalablePlatformComponent>(Platform);
			break;
		}
		default:
			PlatformComp = NULL;
			break;
		}

		if (PlatformComp)
		{
			// 컴포넌트 등록 및 랜덤화
			PlatformComp->RandomizeAfterRegistration(Platform);
		}

		AddedType.Add(RandomType);


		// 사라지는 컴포넌트 랜덤 추가
		int RandomDisapearComp = FMath::RandRange(0, 100);

		// 0 ~ 30 => 30%
		if (RandomDisapearComp <= 30)
		{
			UDisappearableComponent* DisappearableComp = NewObject<UDisappearableComponent>(Platform);
			DisappearableComp->RandomizeAfterRegistration(Platform);
		}
	}
}

int APlatformSpawner::GetRandomTypeCount()
{
	int RandomCount = FMath::RandRange(0, 100);

	// 0 ~ 30 => 30%
	if (RandomCount <= 30)
	{
		RandomCount = 1;
	}
	// 31 ~ 70 => 40%
	else if (RandomCount <= 70)
	{
		RandomCount = 2;
	}
	// 71 ~ 100 => 30%
	else
	{
		RandomCount = 3;
	}

	return RandomCount;
}

