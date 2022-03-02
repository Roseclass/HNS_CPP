#include "CSkillComponent.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Components/CStateComponent.h"
#include "Datas/CSkillData.h"

UCSkillComponent::UCSkillComponent()
{
	
}

void UCSkillComponent::BeginPlay()
{
	Super::BeginPlay();
	
	owner = Cast<ACPlayer>(GetOwner());
}

void UCSkillComponent::PlaySkill(UCSkillData* InData)
{
	CheckNull(InData);
	if (InData->MontageData.Montage)
		owner->PlayAnimMontage(InData->MontageData.Montage);
	if (InData->MontageData.bCanMove)
		owner->SetMove();
	else
		owner->SetStop();
}

void UCSkillComponent::ChangeSlotData(int32 SkillIndex, int32 SlotIndex)
{
	for (int i = 0; i < 8; i++)
	{
		if (i == SlotIndex)
			continue;
		if (SlotDatas[i] == Datas[SkillIndex])
			SlotDatas[i] = nullptr;		
	}
	SlotDatas[SlotIndex] = Datas[SkillIndex];
}
