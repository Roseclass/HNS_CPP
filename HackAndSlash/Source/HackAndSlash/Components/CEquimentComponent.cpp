#include "CEquimentComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Datas/CWeaponData.h"
#include "Characters/CEquipment.h"

UCEquimentComponent::UCEquimentComponent()
{

}

void UCEquimentComponent::BeginPlay()
{
	Super::BeginPlay();
	ACharacter* owner = Cast<ACharacter>(GetOwner());
	for (UCWeaponData* data : EquipmentDatas)
	{
		//CLog::Print(data->GetName()+"EquipCompBeginPlay");
		ACEquipment* equipment;
		data->BeginPlay(owner,&equipment);
		Datas.Add(equipment);
	}
	if (EquipmentDatas.Num())
	{
		Power = EquipmentDatas[WeaponIndex]->WeaponData.Power;
	}
	/*else
	{
		CLog::Print("NULL/EquipmentComponent BeginPlay");
	}*/
}

void UCEquimentComponent::ChangeToOriginal()
{
	ACharacter* owner = Cast<ACharacter>(GetOwner());
	/*if(OriginalData->WeaponData.DrawMontage)
		owner->PlayAnimMontage(OriginalData->WeaponData.DrawMontage);*/
	Datas[WeaponIndex]->OnUnequip();
}

void UCEquimentComponent::ChangeToEquiment()
{
	ACharacter* owner = Cast<ACharacter>(GetOwner());
	/*if(EquipmentDatas[WeaponIndex]->WeaponData.DrawMontage)
		owner->PlayAnimMontage(EquipmentDatas[WeaponIndex]->WeaponData.DrawMontage);*/
	Datas[WeaponIndex]->OnEquip();
}

void UCEquimentComponent::OnCollision()
{
	Datas[WeaponIndex]->OnCollision();
}

void UCEquimentComponent::OffCollision()
{
	Datas[WeaponIndex]->OffCollision();
}

void UCEquimentComponent::ResetTarget()
{
	Datas[WeaponIndex]->ResetTarget();
}