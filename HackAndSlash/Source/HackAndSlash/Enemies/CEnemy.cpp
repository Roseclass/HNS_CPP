#include "CEnemy.h"
#include "Global.h"
#include "Characters/CPlayerController.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CSkillComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CEquimentComponent.h"
#include "Components/TestComponent.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	//컴포넌트
	CHelpers::CreateComponent(this, &Plane, "Plane", Cast<USceneComponent>(GetCapsuleComponent()));

	//액터컴포넌트
	CHelpers::CreateActorComponent<UCSkillComponent>(this, &Skill, "Skill");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCEquimentComponent>(this, &Equipment, "Equipment");
	CHelpers::CreateActorComponent<UTestComponent>(this, &Test, "Test");

	//Virtual Texture Setting
	UStaticMesh* mesh=nullptr;
	CHelpers::GetAsset(&mesh, "StaticMesh'/Engine/BasicShapes/Plane.Plane'");
	UMaterialInstanceConstant* mat=nullptr;
	CHelpers::GetAsset(&mat, "MaterialInstanceConstant'/Game/Widgets/Textures/MiniMap/VirtualTexture/MAT_Pointer_Red.MAT_Pointer_Red'");
	Plane->SetRelativeLocation(FVector(0, 0, 300.0f));
	Plane->SetStaticMesh(mesh);
	Plane->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	Plane->SetCastShadow(false);
	Plane->SetMaterial(0, mat);

	//Mesh
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88.0f));	
	/*TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/SekeltonLight/SkeletonLight_rig_Skeleton_AnimBlueprint.SkeletonLight_rig_Skeleton_AnimBlueprint_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);*/
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();	
	ACPlayerController* player;
	player= Cast<ACPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	GetCapsuleComponent()->OnClicked.AddDynamic(player, &ACPlayerController::OnClicked);	
}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ACEnemy::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//CLog::Print(this->GetFName().ToString());
	Test->AddCurrentHP(-Damage);
	RefreshHP(Test->GetRatioHP(), Name, Type);
	//CLog::Print(Test->GetCurrentHP());
	if (Test->CheckDead())
	{
		if(DeadMontage)
			PlayAnimMontage(DeadMontage);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		FTimerHandle WaitHandle;
		float WaitTime; //시간을 설정하고
		WaitTime = 5.0f;
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{
				Destroy();		// 여기에 코드를 치면 된다.
			}), WaitTime, false); //반복도 여기서 추가 변수를 선언해 설정가능
	}
	else
	{
		if (HittedMontage)
			PlayAnimMontage(HittedMontage);
	}
	return 0;
}
void ACEnemy::PlaySkill(int32 InIndex)
{
	UCSkillData* data = Skill->GetData(InIndex);
	CheckNull(data);
	CheckTrue(State->IsAttackMode());
	CheckTrue(State->IsEvadeMode());
	State->ChangeWeaponState(data->MontageData.WeaponState);
	State->ChangePlayerState(data->MontageData.PlayerState);
	PlayAnimMontage(data->MontageData.Montage);
	//Skill->PlaySkill(data);
}
/* void CopySkeletalMeshToProcedural(USkeletalMeshComponent* SkeletalMeshComponent, int32 LODIndex, UProceduralMeshComponent* ProcMeshComponent)
 {
 
     FSkeletalMeshRenderData* SkMeshRenderData = SkeletalMeshComponent->GetSkeletalMeshRenderData();
     const FSkeletalMeshLODRenderData& DataArray = SkMeshRenderData->LODRenderData[LODIndex];
     FSkinWeightVertexBuffer& SkinWeights = *SkeletalMeshComponent->GetSkinWeightBuffer(LODIndex);
 
     TArray<FVector> VerticesArray;
     TArray<FVector> Normals;
     TArray<FVector2D> UV;
     TArray<int32> Tris;
     TArray<FColor> Colors;
     TArray<FProcMeshTangent> Tangents;
 
     
     //get num vertices
     int32 NumSourceVertices = DataArray.RenderSections[0].NumVertices;
 
     for (int32 i = 0; i < NumSourceVertices; i++)
     {
         //get skinned vector positions
         FVector SkinnedVectorPos = USkeletalMeshComponent::GetSkinnedVertexPosition(SkeletalMeshComponent, i, DataArray, SkinWeights);
         VerticesArray.Add(SkinnedVectorPos);
 
         //Calc normals and tangents from the static version instead of the skeletal one
         FVector ZTangentStatic = DataArray.StaticVertexBuffers.StaticMeshVertexBuffer.VertexTangentZ(i);
         FVector XTangentStatic = DataArray.StaticVertexBuffers.StaticMeshVertexBuffer.VertexTangentX(i);
 
         //add normals from the static mesh version instead because using the skeletal one doesn't work right.
         Normals.Add(ZTangentStatic);
 
         //add tangents
         Tangents.Add(FProcMeshTangent(XTangentStatic, false));
 
         //get UVs
         FVector2D uvs = DataArray.StaticVertexBuffers.StaticMeshVertexBuffer.GetVertexUV(i, 0);
         UV.Add(uvs);
 
         //dummy vertex colors
         Colors.Add(FColor(0, 0, 0, 255));
     }
 
 
     //get index buffer
     FMultiSizeIndexContainerData indicesData;
     DataArray.MultiSizeIndexContainer.GetIndexBuffer(indicesData.Indices);
 
     //iterate over num indices and add traingles
     for (int32 i = 0; i < indicesData.Indices.Num(); i++)
     {
         uint32 a = 0;
         a = indicesData.Indices[i];
         Tris.Add(a);
     }
 
     //Create the procedural mesh
     ProcMeshComponent->CreateMeshSection(0, VerticesArray, Tris, Normals, UV, Colors, Tangents, true);
 }*/