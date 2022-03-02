#include "CWeaponData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Characters/CEquipment.h"

void UCWeaponData::BeginPlay(class ACharacter* InOwnerCharacter, class ACEquipment** OutAction)
{
	FTransform transform;
	ACEquipment* Attachment = nullptr;
	if (WeaponData.EquimentClass)
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(WeaponData.EquimentClass, transform, InOwnerCharacter);
		//Attachment->SetActorLabel(GetLabelName(InOwnerCharacter, "Attachment"));
		UGameplayStatics::FinishSpawningActor(Attachment, transform);
		*OutAction = Attachment;
	}	
}