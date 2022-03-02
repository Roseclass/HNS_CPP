#include "CVATS_Text_Actor.h"
#include "Global.h"
#include "Components/WidgetComponent.h"
#include "CWidget_VATS_Text.h"

ACVATS_Text_Actor::ACVATS_Text_Actor()
{
	CHelpers::CreateComponent(this,&Widget, "Widget");
	Widget->SetVisibility(false);
}

void ACVATS_Text_Actor::BeginPlay()
{
	Super::BeginPlay();
	Child = Cast<UCWidget_VATS_Text>(Widget->GetUserWidgetObject());
}

void ACVATS_Text_Actor::SetText(FName InMeshName, float InRate)
{
	CheckNull(Child);
	Child->SetPartMeshText(InMeshName);
	Child->SetRateText(InRate);
}
