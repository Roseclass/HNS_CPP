#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TestComponent.generated.h"


UCLASS(BlueprintType, ClassGroup = "Custom", meta = (BlueprintSpawnableComponent))
class HACKANDSLASH_API UTestComponent : public UActorComponent
{
	GENERATED_BODY()

		//property
private:
	//HP
	UPROPERTY(EditAnywhere)
		float Max_HP = 500.0f;
	UPROPERTY(EditAnywhere)
		float Cur_HP = 250.0f;
	//MP
	UPROPERTY(EditAnywhere)
		float Max_MP = 100.0f;
	UPROPERTY(EditAnywhere)
		float Cur_MP = 70.0f;
protected:
	class ACPlayer* owner;
public:

	//function
private:
protected:
	virtual void BeginPlay() override;
public:
	UTestComponent();
	//Getter
	//ªÁ∏¡√º≈©
	FORCEINLINE bool CheckDead() { return Cur_HP <= 0.0f ? true : false; }
	//HP
	FORCEINLINE float GetCurrentHP() { return Cur_HP; }
	FORCEINLINE float GetMaxHP() { return Max_HP; }
	FORCEINLINE float GetRatioHP() { return Cur_HP / Max_HP; }
	//MP
	FORCEINLINE float GetCurrentMP() { return Cur_MP; }
	FORCEINLINE float GetMaxMP() { return Max_MP; }
	FORCEINLINE float GetRatioMP() { return Cur_MP / Max_MP; }
	//Setter
	//HP
	void SetMaxHP(float InMaxHP);
	void SetCurrentHP(float InCurrentHP);
	void AddMaxHP(float InAdd);
	void AddCurrentHP(float InAdd);
	//MP
	void SetMaxMP(float InMaxMP);
	void SetCurrentMP(float InCurrentMP);
	void AddMaxMP(float InAdd);
	void AddCurrentMP(float InAdd);
		
};
