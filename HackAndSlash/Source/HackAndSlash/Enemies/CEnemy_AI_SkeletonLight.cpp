#include "CEnemy_AI_SkeletonLight.h"
#include "Global.h"

ACEnemy_AI_SkeletonLight::ACEnemy_AI_SkeletonLight()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/SekeltonLight/Meshes/SkeletonLight_rig.SkeletonLight_rig'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

void ACEnemy_AI_SkeletonLight::Attack()
{
	//CLog::Print("Attack");
	int32 index = UKismetMathLibrary::RandomIntegerInRange(AttackIndex[0], AttackIndex[1]);
	PlaySkill(index);
}
