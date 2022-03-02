#include "CAnimNotify_EndAction.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Components/CStateComponent.h"

FString UCAnimNotify_EndAction::GetNotifyName_Implementation() const
{
	return "EndAction";
}

void UCAnimNotify_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	/*UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
	state->
	CheckNull(state);*/

	ACPlayer* owner = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(owner);
	
	//��ų ��� �Ϸ� �̵� ����
	if (owner->IsCanMove() == false)
		owner->SetCanMove(true);
	//��ų ��� �Ϸ� �ൿ ���� ����
	owner->SetIdleMode();
	//�浹ü ���ֱ�
	if (!owner->IsOriginalWeaponMode())
		owner->OffCollision();
	owner->EndAction();
}