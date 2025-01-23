#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzlePlatform.generated.h"

class UPuzzlePlatformComponent;

UCLASS()
class CH3_PUZZLESTAGE_API APuzzlePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	APuzzlePlatform();

	// 컴포넌트 목록에 추가
	void AddComponent(UActorComponent* InComponent);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// 씬 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "PuzzlePlatform|Components")
	USceneComponent* SceneRoot;

	// 스테틱 메시 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzlePlatform|Components")
	UStaticMeshComponent* StaticMeshComp;

	// 동적으로 등록된 컴포넌트 목록
	UPROPERTY(EditAnywhere, Category = "PuzzlePlatform|Components");
	TArray<UActorComponent*> ComponentArray;
};
