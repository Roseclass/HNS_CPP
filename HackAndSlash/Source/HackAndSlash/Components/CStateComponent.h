#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangeToEquipment);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangeToOriginal);

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	Original, Equiment, Flex, Weapon_Max
};

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Idle, Attack, Evade, Run, Walk, Dead,State_Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKANDSLASH_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStateComponent();

	UFUNCTION()
		void ChangeState(EWeaponState InWeaponState, EPlayerState InPlayerState);
	UFUNCTION()
		void ChangeWeaponState(EWeaponState InWeaponState);
	UFUNCTION()
		void ChangePlayerState(EPlayerState InPlayerState);
	UFUNCTION()
		void ChangeCanMove(bool InMove);

protected:
	virtual void BeginPlay() override;

	class ACPlayer* owner;
public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE EWeaponState GetWeaponState() {return WeaponState;}
	FORCEINLINE EPlayerState GetPlayerState() {return ActionState;}
	FORCEINLINE bool IsCanMove() {return bCanMove;}
	FORCEINLINE bool IsIdleMode() {return ActionState == EPlayerState::Idle ? true : false;}
	FORCEINLINE bool IsAttackMode() {return ActionState == EPlayerState::Attack ? true : false;}
	FORCEINLINE bool IsEvadeMode() {return ActionState == EPlayerState::Evade ? true : false;}
	FORCEINLINE bool IsRunMode() {return ActionState == EPlayerState::Run ? true : false;}
	FORCEINLINE bool IsWalkMode() {return ActionState == EPlayerState::Walk ? true : false;}
	FORCEINLINE bool IsDeadMode() {return ActionState == EPlayerState::Dead ? true : false;}
	FORCEINLINE bool IsOriginalWeaponMode() {return WeaponState == EWeaponState::Original ? true : false;}

private:	
	void SetPlayerMode(EPlayerState InPlayerState);

	void SetIdleMode();
	void SetAttackMode();
	void SetEvadeMode();
	void SetRunMode();
	void SetWalkMode();
	void SetDeadMode();

	void SetOriginalWeaponMode();
	void SetEquimentWeaponMode();
	void SetWeaponMode(EWeaponState InPlayerState);

public:
	UPROPERTY(BlueprintAssignable)
		FChangeToEquipment OnChangeToEquipment;
	UPROPERTY(BlueprintAssignable)
		FChangeToOriginal OnChangeToOriginal;
private:
	EWeaponState WeaponState;
	EPlayerState ActionState;
	bool bCanMove=true;
};
