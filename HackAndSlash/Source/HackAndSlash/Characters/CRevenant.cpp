#include "CRevenant.h"
#include "Global.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CSkillComponent.h"
#include "Components/CStateComponent.h"

ACRevenant::ACRevenant()
{	
	//레버넌트 메쉬 생성
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/ParagonRevenant/Characters/Heroes/Revenant/Meshes/Revenant.Revenant'");
	GetMesh()->SetSkeletalMesh(mesh);

	MaterialNumber = 3;
	GlowMaterialNumber = 6;
}

void ACRevenant::BeginPlay()
{
	Super::BeginPlay();
	//무기교체를 위한 머티리얼 장전
	/*UMaterialInstanceConstant* weapon[2];
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&weapon[0], "MaterialInstanceConstant'/Game/Revenant/MAT_Revenant_Gun_Inst_Normal.MAT_Revenant_Gun_Inst_Normal'");
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&weapon[1], "MaterialInstanceConstant'/Game/Revenant/MAT_Revenant_Gun_Inst_Masked.MAT_Revenant_Gun_Inst_Masked'");
	WeaponMaterial[0] = UMaterialInstanceDynamic::Create(weapon[0], this);
	WeaponMaterial[1] = UMaterialInstanceDynamic::Create(weapon[1], this);*/
	//Glow머티리얼
	/*UMaterialInstanceConstant* glow[2];
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&glow[0], "MaterialInstanceConstant'/Game/Revenant/MAT_Revenant_GlowGun_Normal.MAT_Revenant_GlowGun_Normal'");
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&glow[1], "MaterialInstanceConstant'/Game/Revenant/MAT_Revenant_GlowGun_Masked.MAT_Revenant_GlowGun_Masked'");
	GlowWeaponMaterial[0] = UMaterialInstanceDynamic::Create(glow[0], this);
	GlowWeaponMaterial[1] = UMaterialInstanceDynamic::Create(glow[1], this);*/

	GetMesh()->SetMaterial(MaterialNumber, WeaponMaterial[0]);
	GetMesh()->SetMaterial(GlowMaterialNumber, GlowWeaponMaterial[0]);

}

void ACRevenant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACRevenant::HideWeapon()
{	
	GetMesh()->SetMaterial(MaterialNumber, WeaponMaterial[1]);
	GetMesh()->SetMaterial(GlowMaterialNumber, GlowWeaponMaterial[1]);
}
void ACRevenant::RevealWeapon()
{	
	GetMesh()->SetMaterial(MaterialNumber, WeaponMaterial[0]);
	GetMesh()->SetMaterial(GlowMaterialNumber, GlowWeaponMaterial[0]);
}
void ACRevenant::StartVATS()
{
	CameraLock = false;
}
void ACRevenant::UpdateVATS(float InTimeRatio)
{
	float reverse = (1 - InTimeRatio);
	SpringArm->TargetArmLength = reverse * 400.0f + (InTimeRatio * CameraArmLength);
	SpringArm->SetRelativeRotation(FQuat(FRotator(InTimeRatio * -55.0f, (reverse * 180.f) + (InTimeRatio * -90.0f), 0.0f)));
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, InTimeRatio * 50.0f));

	Camera->SetRelativeRotation(FQuat(FRotator(0.0f, (reverse * 180.f), 0.0f)));
}
void ACRevenant::FinishVATS()
{
	/*CameraLock = true;
	SpringArm->TargetArmLength = CameraArmLength;
	SpringArm->SetRelativeRotation(FQuat(FRotator(-55.0f, -90.0f, 0.0f)));
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));*/
}