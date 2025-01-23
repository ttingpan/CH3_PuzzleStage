# CH3_PuzzleStage
## [6번 과제] 회전 발판과 움직이는 장애물 퍼즐 스테이지
---
## 필수 과제 (기본 요구 사항)

### **필수 과제 1번 - 서로 다른 Actor 클래스 2개 이상 구현**

- 메시가 정상적으로 표시되고, 서로 다른 동작 로직(회전 vs 이동)을 수행해야 합니다.

### **필수 과제 2번 - Tick 함수 기반 동적 Transform 변경**

- **회전**: `AddActorLocalRotation()` 사용하여 초당 일정 각도 회전
- **이동**: `SetActorLocation()` 또는 `AddActorLocalOffset()` 등을 통해 왕복 이동 구현
- **DeltaTime** 적용으로 프레임별 움직임을 보정합니다.

### **필수 과제 3번 - 리플렉션 적용**

- 주요 변수 (회전 속도, 이동 속도, 이동 범위 등)를 `UPROPERTY`로 선언, 에디터에서 조절 가능하게 만들어야 합니다.
- 카테고리(`Category=""`)와 `EditAnywhere`, `BlueprintReadWrite` 등을 적절히 활용하세요.
- 플레이 도중 Details 패널에서 값 조정 시 즉시 반영되는지 확인합니다.

---
## 도전 과제 (선택 요구 사항)

### **도전 과제 1번 - 시간 제한과 카운트다운 활용**

- N초 후 발판이 사라지거나, N초마다 발판이 교체되는 식의 타이머를 제한한 액터를 구현합니다.
- `FTimerHandle`과 타이머 함수(`GetWorld()->GetTimerManager().SetTimer(...)`)를 적용해보세요.
- 매 프레임 Tick 대신, 타이머로 특정 시점마다 기능을 수행함으로써 퍼포먼스도 개선할 수 있습니다.

### **도전 과제 2번 - 랜덤 퍼즐 생성**

- 게임 시작 시 `SpawnActor`를 통해 **여러 개의 회전 발판/이동 플랫폼**을 **임의 위치**에 배치합니다. ([언리얼 공식 문서 참조](https://dev.epicgames.com/documentation/ko-kr/unreal-engine/spawning-and-destroying-unreal-engine-actors))
- 랜덤 범위, 각도 등을 설정해 매번 다른 퍼즐 코스를 생성해보세요.
- 로그라이크나 프로시저럴 스테이지의 기초를 체험할 수 있습니다.

---
---
## **필수 과제**

- **필수 과제 1번 - 서로 다른 Actor 클래스 2개 이상 구현**
  
  - 이동, 회전, 크기 변화 등 각 기능을 컴포넌트로 만들어서 다른 액터에 부착하여 사용 가능하도록 함.

  ![image](https://github.com/user-attachments/assets/c3adb0ec-6708-4f8a-a3be-8e160f8befd8)

- **필수 과제 2번 - Tick 함수 기반 동적 Transform 변경**
  
  - 각 컴포넌트의 부모 컴포넌트에서 `PlatformAction(float DeltaTime)`를 선언하고
  - 자식 컴포넌트에서 `PlatformAction(float DeltaTime)`를 `override`하여 각 기능을 구현하고
  - 부모 컴포넌트에서 `Tick`함수에서 호출하여 기능을 사용함.
 
- 부모 컴포넌트(PuzzlePlatformComponent.cpp)

```cpp

void UPuzzlePlatformComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bInAction)
	{
		// 동작 실행
		PlatformAction(DeltaTime);
	}
}

```

<details>
<summary>작동 영상</summary>


- 이동
  
https://github.com/user-attachments/assets/3880e872-62c3-4ded-851e-2f99e4b7dbff

- 회전

https://github.com/user-attachments/assets/a683e71c-d144-468d-a3c6-dbbde1e7f7bb

- 크기 변화

https://github.com/user-attachments/assets/bda5f4c4-2b92-45b5-9c06-25bb4d98e5af

</details>


- **필수 과제 3번 - 리플렉션 적용**
  
  - 직접 수정이 가능하도록 하기 위한 변수는 `UPROPERTY(EditAnywhere)`를 적용하고 블루프린트에서도 읽고 쓰기가 가능하게 하려면 `BlueprintReadWrite`를 추가 적용함.
  - 단순히 값이 어떻게 변하는지 확인하는 용도로 사용 하기 위해서는 `UPROPERTY(VisibleAnywhere)`를 적용함.

- PuzzlePlatformComponent.h 일부

![image](https://github.com/user-attachments/assets/04032879-0c84-43f4-ac61-ba2b09592ee9)


- 에디터 디테일 창

![image](https://github.com/user-attachments/assets/2a596348-ac69-47f2-ab60-2c81a6b91ffe)

---

## **도전 과제**

- **도전 과제 1번 - 시간 제한과 카운트다운 활용**
  
  - 각 컴포넌트의 부모 컴포넌트에서 `PlatformAction(float DeltaTime)`를 선언하고
  - 자식 컴포넌트에서 `PlatformAction(float DeltaTime)`를 `override`하여 각 기능을 구현하고
  - 부모 컴포넌트에서 `Tick`함수에서 호출하여 기능을 사용함.







