#include "CVATS_Info_Actor.h"
#include "Global.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Characters/CPlayerController.h"
#include "CWidget_VATS_Info.h"

ACVATS_Info_Actor::ACVATS_Info_Actor()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent(this, &Root, "Root");
	CHelpers::CreateComponent(this, &Widget, "Widget",Root);
	Widget->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	Widget->SetTintColorAndOpacity(FLinearColor(0.0f, 2.0f, 0.0f));
	Widget->SetWindowFocusable(0);
	Widget->SetRelativeLocation(Offset);
	Widget->SetRelativeRotation(FRotator(Pitch, Yaw, Roll));
	Widget->SetWorldScale3D(Scale);
}

void ACVATS_Info_Actor::BeginPlay()
{
	Super::BeginPlay();
	Child = Cast<UCWidget_VATS_Info>(Widget->GetUserWidgetObject());
	Child->BeginPlay();
	Player = Cast<ACPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void ACVATS_Info_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Player)
		CLog::Print("ACVATS_Info_Actor::Tick(float DeltaTime) Player==Nullptr");
	if(ViewportSize.IsZero())
		CLog::Print("ACVATS_Info_Actor::Tick(float DeltaTime) ViewportSizeIsZero");
	CheckNull(Player);
	CheckTrue(ViewportSize.IsZero());
	FVector loc,dir;
	Player->DeprojectScreenPositionToWorld(ViewportSize.X, ViewportSize.Y, loc, dir);
	FRotator rot;
	rot = UKismetMathLibrary::Conv_VectorToRotator(-dir);
	loc += ScreenOffset * dir;
	//CLog::Print(loc,5);
	SetActorLocationAndRotation(loc, rot);
	//Root->SetWorldLocationAndRotation(loc, rot);
}

void ACVATS_Info_Actor::SetBulletCount(int32 InCount)
{
	Child->SetBulletCount(InCount);
}
void ACVATS_Info_Actor::IncreaseBulletCount()
{
	Child->IncreaseBulletCount();
}
void ACVATS_Info_Actor::DecreaseBulletCount()
{
	Child->DecreaseBulletCount();
}
void ACVATS_Info_Actor::SetViewportSize(FVector2D InSize)
{
	ViewportSize = InSize*0.5f;
}