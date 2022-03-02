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
	//스킬 사용시 움직일 수 없다면 정지
	//owner->SetCanMove(false);
	//스킬사용시 행동 제약을 위한 상태변경
	//owner->SetAttackMode();
	//충돌체 켜주기
	if(!owner->IsOriginalWeaponMode())
		owner->OnCollision();
}