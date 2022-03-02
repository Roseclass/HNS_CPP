#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEquipment.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEquipmentBeginOverlap, class ACharacter*, InAttacker, class AActor*, InAttackCauser, class ACharacter*, InOtherCharacter);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEquipmentEndOverlap, class ACharacter*, InAttacker, class AActor*, InAttackCauser, class ACharacter*, InOtherCharacter);


UCLASS()
class HACKANDSLASH_API ACEquipment : public AActor
{
	GENERATED_BODY()

	//property
private:
	TArray<class UShapeComponent*> ShapeComponents;//캡슐컴포넌트가 들어올 예정
	TArray<class ACharacter*> HittedCharacter;
	UPROPERTY(EditAnywhere)
		float Power;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	TSubclassOf<class ACDamageText> DamageTextClass;
protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;
public:

	//function
private:
	UFUNCTION()//this->beginplay OnComponentBeginOverlap.bind
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void AttachTo(FName InSocketName);
public:
	ACEquipment();

	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();

	void OnCollision();
	void OffCollision();	
	void ResetTarget();//HittedActor배열 초기화
};