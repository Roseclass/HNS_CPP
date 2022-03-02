#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Datas/CSkillData.h"
#include "CPlayerController.generated.h"

//CPlayer->BeginPlay

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKey_Z);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKey_1);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKey_2);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKey_3);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKey_4);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKey_5);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlaySkill, UCSkillData*, InData);


UCLASS()
class HACKANDSLASH_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

	//property
private:
	class ACVATS_Text_Actor* VATS_Text=nullptr;
	class ACVATS_Info_Actor* VATS_Info=nullptr;
	
	int32 CurrentSlot= -1;
	int32 DataSize = -1;
	bool VATS = false;
protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class ACPlayer* PlayCharacter;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool bClick = false;	
public:
	//CPlayer->BeginPlay()
	UPROPERTY(BlueprintAssignable)
		FPlaySkill OnPlaySkill;
	UPROPERTY(BlueprintAssignable)
		FKey_Z OnKey_Z;

	UPROPERTY(BlueprintAssignable)
		FKey_1 OnKey_1;
	UPROPERTY(BlueprintAssignable)
		FKey_2 OnKey_2;
	UPROPERTY(BlueprintAssignable)
		FKey_3 OnKey_3;
	UPROPERTY(BlueprintAssignable)
		FKey_4 OnKey_4;
	UPROPERTY(BlueprintAssignable)
		FKey_5 OnKey_5;
	//function
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void StartVATS();
	UFUNCTION(BlueprintCallable)
		void FinishVATS();
	UFUNCTION(BlueprintCallable)
		void PressLeftClick();
	UFUNCTION(BlueprintCallable)
		void PressKey_Z();
	UFUNCTION(BlueprintCallable)
		void PressKey_1();
	UFUNCTION(BlueprintCallable)
		void PressKey_2();
	UFUNCTION(BlueprintCallable)
		void PressKey_3();
	UFUNCTION(BlueprintCallable)
		void PressKey_4();
	UFUNCTION(BlueprintCallable)
		void PressKey_5();
	UFUNCTION(BlueprintCallable)
		void PlaySkill(int32 InIndex);
	
	UFUNCTION(BlueprintCallable)
		UCSkillData* GetSlotData(int32 InIndex);
	UFUNCTION(BlueprintCallable)
		class UMaterialInstance* GetSlotMaterialData(int32 InIndex);
	UFUNCTION(BlueprintCallable)
		class UMaterialInstance* GetMaterialData(int32 InIndex);
	UFUNCTION(BlueprintCallable)
		FText GetTooltipName(int32 InIndex);
	UFUNCTION(BlueprintCallable)
		FText GetTooltipDescription(int32 InIndex);
	UFUNCTION(BlueprintCallable)
		void ChangeSlotData(int32 SkillIndex, int32 SlotIndex);

	void CheckDataSize();
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void RefreshSkillSlot(int32 SlotIndex);
public:
	ACPlayerController();
	void SetPlayCharacter(class ACPlayer* InPlayer);
	UFUNCTION()//Enemy->BeginPlay
		void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	FORCEINLINE UCSkillData* GetCurrentSlotData() { return CurrentSlot==-1 ? nullptr : GetSlotData(CurrentSlot); }

	//VATS
	FORCEINLINE bool* GetVATSPointer() { return &VATS; }
	FORCEINLINE ACVATS_Text_Actor* GetVATS_Text_Actor() { return VATS_Text; }
	FORCEINLINE ACVATS_Info_Actor* GetVATS_Info_Actor() { return VATS_Info; }
	
	void SetVATS_Text(FName InMeshName, float InRate);

	UFUNCTION(BlueprintCallable)
		void SetVATS_Text_Actor(class ACVATS_Text_Actor* InVATS_Text);
	UFUNCTION(BlueprintCallable)
		void SetVATS_Text_ActorLocation(FVector InLocation);
	UFUNCTION(BlueprintCallable)
		void SetVATS_Text_ActorRotation(FRotator InRotation);
	UFUNCTION(BlueprintCallable)
		void SetVATS_Info_Actor(class ACVATS_Info_Actor* InVATS_Info);
	UFUNCTION(BlueprintCallable)
		void SetBulletCount(int32 InCount);
	UFUNCTION(BlueprintCallable)
		void IncreaseBulletCount();
	UFUNCTION(BlueprintCallable)
		void DecreaseBulletCount();

};
