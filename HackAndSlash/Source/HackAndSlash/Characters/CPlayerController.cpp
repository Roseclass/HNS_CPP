#include "CPlayerController.h"
#include "Global.h"
#include "Kismet/GameplayStatics.h"
#include "CPlayer.h"
#include "Widgets/CVATS_Text_Actor.h"
#include "Widgets/CVATS_Info_Actor.h"
#include "Components/CSkillComponent.h"
#include "Datas/CSkillData.h"

ACPlayerController::ACPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetPlayCharacter(Cast<ACPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass())));
}

void ACPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayCharacter)
	{		
		if (bClick)
		{
			FHitResult result;
			GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, result);
			PlayCharacter->MoveToLocation(result.Location);
		}
		if (PlayCharacter->GetVelocity().IsNearlyZero())
		{
			PlayCharacter->MoveEnd();
		}
	}
}

void ACPlayerController::SetPlayCharacter(ACPlayer* InPlayer)
{
	PlayCharacter = InPlayer;
	CheckNull(PlayCharacter);
	CheckDataSize();
	CLog::Print(DataSize);
}

void ACPlayerController::PressLeftClick()//
{
	if (VATS)
		return;
	bClick = true;
}

void ACPlayerController::PressKey_Z()//무기교체
{
	//CLog::Print("PlayerController->PressKey_Z");
	if (OnKey_Z.IsBound())
		OnKey_Z.Broadcast();
}
void ACPlayerController::PressKey_1()//아이템슬롯1
{
	if (OnKey_1.IsBound())
		OnKey_1.Broadcast();
}
void ACPlayerController::PressKey_2()//아이템슬롯2
{
	if (OnKey_2.IsBound())
		OnKey_2.Broadcast();
}
void ACPlayerController::PressKey_3()//아이템슬롯3
{
	if (OnKey_3.IsBound())
		OnKey_3.Broadcast();
}
void ACPlayerController::PressKey_4()//아이템슬롯4
{
	if (OnKey_4.IsBound())
		OnKey_4.Broadcast();
}
void ACPlayerController::PressKey_5()//아이템슬롯5
{
	if (OnKey_5.IsBound())
		OnKey_5.Broadcast();
}
void ACPlayerController::PlaySkill(int32 InIndex)//스킬시전
{
	CurrentSlot = InIndex;
	if (OnPlaySkill.IsBound())
		OnPlaySkill.Broadcast(GetSlotData(InIndex));
}

void ACPlayerController::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	//DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FComponentOnClickedSignature, UPrimitiveComponent, OnClicked, UPrimitiveComponent*, TouchedComponent, FKey, ButtonPressed);
	UCSkillData* data = PlayCharacter->GetSlotData(5);
	CheckNull(data);
	FVector location = TouchedComponent->GetOwner()->GetActorLocation();
	float distance = FVector::Dist2D(location, PlayCharacter->GetActorLocation());
	if (data->MontageData.Range >= distance)
	{
		/*CLog::Print(PlayCharacter->IsAttackMode());*/
		FRotator rot= UKismetMathLibrary::MakeRotFromX(location - PlayCharacter->GetActorLocation());
		FRotator actorRot = PlayCharacter->GetActorRotation();
		PlayCharacter->SetActorRotation(FRotator(actorRot.Pitch,rot.Yaw, actorRot.Roll));
		PlaySkill(5);
		/*CLog::Print(PlayCharacter->IsAttackMode());*/
	}	
}
UCSkillData* ACPlayerController::GetSlotData(int32 InIndex)
{
	if (InIndex >= 8 || InIndex < 0)
		return nullptr;
	return PlayCharacter->GetSlotData(InIndex);
}
UMaterialInstance* ACPlayerController::GetSlotMaterialData(int32 InIndex)
{
	if (InIndex >= 8 || InIndex < 0)
		return nullptr;
	UCSkillData* data = PlayCharacter->GetSlotData(InIndex);
	if(data)
		return data->MontageData.SkillImage;
	return nullptr;
}
UMaterialInstance* ACPlayerController::GetMaterialData(int32 InIndex)
{
	if (InIndex >= DataSize || InIndex < 0)
		return nullptr;
	return PlayCharacter->GetData(InIndex)->MontageData.SkillImage;
}

FText ACPlayerController::GetTooltipName(int32 InIndex)
{
	FText result;
	if (InIndex >= DataSize || InIndex < 0)
		return result;
	return PlayCharacter->GetData(InIndex)->MontageData.Name;
}

FText ACPlayerController::GetTooltipDescription(int32 InIndex)
{
	FText result;
	if (InIndex >= DataSize || InIndex < 0)
		return result;
	return PlayCharacter->GetData(InIndex)->MontageData.Description;
}

void ACPlayerController::CheckDataSize()
{
	DataSize = PlayCharacter->GetDataSize();
}

void ACPlayerController::ChangeSlotData(int32 SkillIndex, int32 SlotIndex)
{ 	
	PlayCharacter->ChangeSlotData(SkillIndex, SlotIndex);
	for (int i = 0; i < 8; i++)
		RefreshSkillSlot(i);	
}

void ACPlayerController::StartVATS()
{
	VATS = true;
	//GetWorld()->SpawnActorDeferred<ACDamageText>(DamageTextClass, transform);
}

void ACPlayerController::FinishVATS()
{
	VATS = false;
}

void ACPlayerController::SetVATS_Text(FName InMeshName, float InRate)
{
	CheckNull(VATS_Text);
	VATS_Text->SetText(InMeshName, InRate);
}

void ACPlayerController::SetVATS_Text_Actor(class ACVATS_Text_Actor* InVATS_Text)
{
	VATS_Text = InVATS_Text;
}

void ACPlayerController::SetVATS_Text_ActorLocation(FVector InLocation)
{
	CheckNull(VATS_Text);
	VATS_Text->SetActorLocation(InLocation);
}
void ACPlayerController::SetVATS_Text_ActorRotation(FRotator InRotation)
{
	CheckNull(VATS_Text);
	VATS_Text->SetActorRotation(InRotation);
}

void ACPlayerController::SetVATS_Info_Actor(class ACVATS_Info_Actor* InVATS_Info)
{
	VATS_Info = InVATS_Info;
}

void ACPlayerController::SetBulletCount(int32 InCount)
{
	VATS_Info->SetBulletCount(InCount);
}
void ACPlayerController::IncreaseBulletCount()
{
	VATS_Info->IncreaseBulletCount();
}
void ACPlayerController::DecreaseBulletCount()
{
	VATS_Info->DecreaseBulletCount();
}