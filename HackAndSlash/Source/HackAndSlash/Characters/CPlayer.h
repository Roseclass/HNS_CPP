#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "Components/CStateComponent.h"
#include "Components/CSkillComponent.h"
#include "Components/TestComponent.h"
#include "Components/CEquimentComponent.h"
#include "CPlayer.generated.h"

//Item
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FITEM_1);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FITEM_2);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FITEM_3);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FITEM_4);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FITEM_5);

UCLASS()
class HACKANDSLASH_API ACPlayer : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	//property
private:
	class ACPlayerController* Controller;
	UPROPERTY(EditAnywhere)
		uint8 TeamID;
protected:
	//0:노말 1:마스크
	UPROPERTY(EditAnywhere)
		class UMaterialInstance* WeaponMaterial[2];
	UPROPERTY(EditAnywhere)
		int32 MaterialNumber;

	//카메라
	float CameraArmLength = 1500.0f;
	bool CameraLock = true;

	//신캡쳐 카메라
	float SceneCaptureArmLength = 180.0f;
	FVector SceneCaptureLocation = FVector(0, 0, 45.0f);
	FRotator SceneCaptureRotation = FRotator(0, 180.0f, 0);	
public:
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class USceneCaptureComponent2D* SceneCaptureCamera;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
		class USpringArmComponent* SceneSpringArm;

	UPROPERTY(BlueprintAssignable)
		FITEM_1 OnITEM_1;
	UPROPERTY(BlueprintAssignable)
		FITEM_2 OnITEM_2;
	UPROPERTY(BlueprintAssignable)
		FITEM_3 OnITEM_3;
	UPROPERTY(BlueprintAssignable)
		FITEM_4 OnITEM_4;
	UPROPERTY(BlueprintAssignable)
		FITEM_5 OnITEM_5;

	//function
private:
protected:
	virtual void BeginPlay() override;
	virtual void HideWeapon() {};
	virtual void RevealWeapon() {};

	UPROPERTY(VisibleDefaultsOnly)
		class UCSkillComponent* Skill;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCEquimentComponent* Equipment;

	UPROPERTY(VisibleDefaultsOnly)
		class UTestComponent* Test;

	UFUNCTION(BlueprintCallable)
		FORCEINLINE EWeaponState GetWeaponState() { return State->GetWeaponState(); }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE EPlayerState GetPlayerState() { return State->GetPlayerState(); }

	UFUNCTION(BlueprintCallable)
		void ZoomIN();

	UFUNCTION(BlueprintCallable)
		void ZoomOUT();

	UFUNCTION(BlueprintCallable)
		void LeftAngle();

	UFUNCTION(BlueprintCallable)
		void RightAngle();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void RefreshHP();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void RefreshMP();
public:
	ACPlayer();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual FGenericTeamId GetGenericTeamId() const;

	//키바인딩 CPlayerController	
	UFUNCTION()
		void PlaySkill(class UCSkillData* InData);
	FORCEINLINE UCSkillData* GetSlotData(int32 InIndex) { return Skill->GetSlotData(InIndex); }
	FORCEINLINE UCSkillData* GetData(int32 InIndex) { return Skill->GetData(InIndex); }
	FORCEINLINE int32 GetDataSize() { return Skill->GetDataSize(); }
	FORCEINLINE void ChangeSlotData(int32 SkillIndex, int32 SlotIndex) { Skill->ChangeSlotData(SkillIndex, SlotIndex); }

	UFUNCTION()//Z
		void ChangeWeapon();

	UFUNCTION()
		void DoITEM_1();
	UFUNCTION()
		void DoITEM_2();
	UFUNCTION()
		void DoITEM_3();
	UFUNCTION()
		void DoITEM_4();
	UFUNCTION()
		void DoITEM_5();

	void MoveToLocation(FVector inLocation);
	void MoveEnd();


	void SetHideWeapon();
	void SetRevealWeapon();

	void SetMove();
	void SetStop();

	FORCEINLINE class ACPlayerController* GetPlayerController() { return Controller; }

	//State
	FORCEINLINE bool IsCanMove() { return State->IsCanMove(); }
	FORCEINLINE bool IsIdleMode() { return State->IsIdleMode(); }
	FORCEINLINE bool IsAttackMode() { return State->IsAttackMode(); }
	FORCEINLINE bool IsEvadeMode() { return State->IsEvadeMode(); }
	FORCEINLINE bool IsRunMode() { return State->IsRunMode(); }
	FORCEINLINE bool IsWalkMode() { return State->IsWalkMode(); }
	FORCEINLINE bool IsOriginalWeaponMode() { return State->IsOriginalWeaponMode(); }

	void SetCanMove(bool InBool);
	void SetIdleMode();
	void SetAttackMode();
	void SetEvadeMode();
	void SetRunMode();
	void SetWalkMode();

	//HP
	FORCEINLINE float GetCurrentHP() { return Test->GetCurrentHP(); }
	FORCEINLINE float GetMaxHP() { return Test->GetMaxHP(); }
	UFUNCTION(BlueprintPure)
		FORCEINLINE float GetRatioHP() { return Test->GetRatioHP(); }
	FORCEINLINE void SetMaxHP(float InMaxHP) { Test->SetMaxHP(InMaxHP); }
	FORCEINLINE void SetCurrentHP(float InCurrentHP) { Test->SetCurrentHP(InCurrentHP); };
	FORCEINLINE void AddMaxHP(float InAdd) { Test->AddMaxHP(InAdd); }
	FORCEINLINE void AddCurrentHP(float InAdd) { Test->AddCurrentHP(InAdd); }
	//MP
	FORCEINLINE float GetCurrentMP() { return Test->GetCurrentMP(); }
	FORCEINLINE float GetMaxMP() { return Test->GetMaxMP(); }
	UFUNCTION(BlueprintPure)
		FORCEINLINE float GetRatioMP() { return Test->GetRatioMP(); }
	FORCEINLINE void SetMaxMP(float InMaxMP) { Test->SetMaxMP(InMaxMP); }
	FORCEINLINE void SetCurrentMP(float InCurrentMP) { Test->SetCurrentMP(InCurrentMP); }
	FORCEINLINE void AddMaxMP(float InAdd) { Test->AddMaxMP(InAdd); }
	FORCEINLINE void AddCurrentMP(float InAdd) { Test->AddCurrentMP(InAdd); }		

	//Equipment
	FORCEINLINE float GetAttackPower() { return Equipment->GetWeaponPower(); }
	void OnCollision();
	void OffCollision();
	void EndAction();
};
