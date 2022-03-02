#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/CStateComponent.h"
#include "Datas/CSkillData.h"
#include "CSkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKANDSLASH_API UCSkillComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
		class UCSkillData* SlotDatas[8];	//0~4:asdfg,5~7:mouse

	UPROPERTY(EditDefaultsOnly)
		TArray<class UCSkillData*> Datas;
public:	
	UCSkillComponent();

protected:
	virtual void BeginPlay() override;	
	class ACPlayer* owner;
public:
	//스킬사용
	UFUNCTION()
		void PlaySkill(UCSkillData* InData);	
	void ChangeSlotData(int32 SkillIndex, int32 SlotIndex);
	UFUNCTION()
		FORCEINLINE UCSkillData* GetSlotData(int32 InIndex) { return SlotDatas[InIndex]; }
	UFUNCTION()
		FORCEINLINE UCSkillData* GetData(int32 InIndex) { return Datas[InIndex]; }
	UFUNCTION()
		FORCEINLINE int32 GetDataSize() { return Datas.Num(); }
};