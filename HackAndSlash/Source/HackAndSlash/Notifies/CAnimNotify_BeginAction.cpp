#include "CAnimNotify_BeginAction.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Components/CStateComponent.h"

FString UCAnimNotify_BeginAction::GetNotifyName_Implementation() const
{
	return "BeginAction";
}

void UCAnimNotify_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	
	ACPlayer* owner = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(owner);
	//��ų ���� ������ �� ���ٸ� ����
	//owner->SetCanMove(false);
	//��ų���� �ൿ ������ ���� ���º���
	//owner->SetAttackMode();
	//�浹ü ���ֱ�
	if(!owner->IsOriginalWeaponMode())
		owner->OnCollision();
}