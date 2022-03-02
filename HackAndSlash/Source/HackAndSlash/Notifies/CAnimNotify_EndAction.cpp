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
	
	//스킬 사용 완료 이동 가능
	if (owner->IsCanMove() == false)
		owner->SetCanMove(true);
	//스킬 사용 완료 행동 제약 해제
	owner->SetIdleMode();
	//충돌체 꺼주기
	if (!owner->IsOriginalWeaponMode())
		owner->OffCollision();
	owner->EndAction();
}