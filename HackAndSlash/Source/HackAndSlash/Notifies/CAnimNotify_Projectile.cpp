#include "CAnimNotify_Projectile.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Characters/CPlayerController.h"
#include "Characters/CProjectile.h"
#include "Datas/CSkillData.h"


FString UCAnimNotify_Projectile::GetNotifyName_Implementation() const
{
	return "Projectile";
}

void UCAnimNotify_Projectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* owner = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(owner);
	ACPlayerController* controller = owner->GetPlayerController();
	CheckNull(controller);
	UCSkillData* data = controller->GetCurrentSlotData();
	if (data->MontageData.ProjectileClass)
	{
		FVector location = owner->GetMesh()->GetSocketLocation(data->MontageData.BoneName);
		FVector rotator = (owner->GetActorForwardVector() * (1.0f - data->MontageData.Lerp) + owner->GetActorUpVector() * data->MontageData.Lerp);
		FTransform transform;
		transform.AddToTranslation(location);
		transform.SetRotation(FQuat(UKismetMathLibrary::Conv_VectorToRotator(rotator)));

		ACProjectile* projectileObject = owner->GetWorld()->SpawnActorDeferred<ACProjectile>(data->MontageData.ProjectileClass, transform, owner, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		projectileObject->SetDamage(data->MontageData.Power);
		UGameplayStatics::FinishSpawningActor(projectileObject, transform);
	}
}
