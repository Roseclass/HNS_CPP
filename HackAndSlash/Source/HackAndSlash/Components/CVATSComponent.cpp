#include "CVATSComponent.h"
#include "Global.h"
#include "Enemies/CEnemy.h"
#include "Characters/CPlayerController.h"
#include "Datas/CVATSData.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

UCVATSComponent::UCVATSComponent()
{	
	PrimaryComponentTick.bCanEverTick = true;	
}

void UCVATSComponent::BeginPlay()
{
	Super::BeginPlay();	
	Owner = Cast<ACEnemy>(GetOwner());
	if (Owner == nullptr)
	{
		CLog::Print("Owner!=Enemy");
		Owner = Cast<ACharacter>(GetOwner());
	}
	/*if(Owner == nullptr)
		CLog::Print("Owner!=Character");	
	else
		CLog::Print("Owner==Character");*/
	CheckNull(Owner);
	ReadBoneData();
	CHelpers::GetComponent<USkeletalMeshComponent>(Owner);
	TArray<UActorComponent*>components = Owner->GetComponentsByClass(USkeletalMeshComponent::StaticClass());
	for (auto component : components)
	{
		USkeletalMeshComponent* temp = Cast<USkeletalMeshComponent>(component);
		if (temp == nullptr)
			continue;
		if (temp->GetNumChildrenComponents() == 0)
			continue;
		PartMesh = Cast<USkeletalMeshComponent>(temp->GetChildComponent(0));
		break;
	}
	/*if (PartMesh == nullptr)
		CLog::Print("PartMesh==nullptr");
	else
		CLog::Print("PartMesh!=nullptr");*/
	CheckNull(PartMesh);
	PartMesh->SetVisibility(false);
	Controller = Cast<ACPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CheckNull(Controller);
	VATS = Controller->GetVATSPointer();
}

void UCVATSComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckFalse(*VATS);
	FName boneName = GetBoneName();
	if (boneName != NAME_None)
	{
		CLog::Print(boneName.ToString() + "'s Parent is " + BoneMap[boneName].ToString(), 0);
		ChangeMesh(boneName);
		Controller->SetVATS_Text
		(
			VATSData->UIPartName[BoneMap[boneName]],
			VATSData->UIPartRate[BoneMap[boneName]]
		);
		FVector loc = Owner->GetMesh()->GetSocketLocation(BoneMap[boneName]);
		FVector offset =Owner->GetActorForwardVector()*50.0f;
		FRotator rot = Owner->GetActorRotation();
		Controller->SetVATS_Text_ActorLocation(loc+offset);
		Controller->SetVATS_Text_ActorRotation(rot);
	}	
}

int32 UCVATSComponent::GetParent(TArray<int32>& NodeList ,int32 InIndex)
{
	if (InIndex == -1)
		return -1;
	if (NodeList[InIndex] == InIndex)
		return InIndex;
	return NodeList[InIndex] = GetParent(NodeList, NodeList[InIndex]);
}

void UCVATSComponent::MergeParent(int32 A, int32 B)
{
	//당장은 사용안함
}

void UCVATSComponent::ReadBoneData()//unionfind
{
	TArray<int32> list;
	TArray<FName> nameList;
	CheckNull(VATSData);
	//CLog::Print("dataon");
	for (FMeshBoneInfo i : Owner->GetMesh()->SkeletalMesh->RefSkeleton.GetRefBoneInfo())
	{
		list.Add(i.ParentIndex);
		nameList.Add(i.Name);
		for (FName name : VATSData->Parent)
		{
			if (name == i.Name)
			{
				list.Last() = list.Num() - 1;
				break;
			}
		}		
	}
	for (int32 i = 0; i < list.Num(); i++)
	{
		int32 parentIdx = GetParent(list, i);
		if (parentIdx == -1)
			BoneMap.Add( nameList[i],NAME_None );
		else
			BoneMap.Add( nameList[i],nameList[parentIdx]);
	}
}

void UCVATSComponent::OnVATS()
{
	//VATS = true;
}

void UCVATSComponent::OffVATS()
{
	//VATS = false;
}

void UCVATSComponent::ChangeMesh(FName BoneName)
{
	FName parentBone = BoneMap[BoneName];
	CheckNull(PartMesh);
	PartMesh->SetSkeletalMesh(VATSData->Part[parentBone]);
	PartMesh->SetVisibility(true);
}

FName UCVATSComponent::GetBoneName()
{
	FHitResult result;
	Controller->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, result);
	return result.BoneName;
}