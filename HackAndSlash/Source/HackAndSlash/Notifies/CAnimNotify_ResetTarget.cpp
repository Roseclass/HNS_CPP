#include "CAnimNotify_ResetTarget.h"
#include "Global.h"
#include "Characters/CPlayer.h"

FString UCAnimNotify_ResetTarget::GetNotifyName_Implementation() const
{
	return "ResetTarget";
}

void UCAnimNotify_ResetTarget::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* owner = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(owner);
	owner->EndAction();
}
