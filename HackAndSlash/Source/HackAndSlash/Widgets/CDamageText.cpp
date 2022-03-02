#include "CDamageText.h"
#include "Global.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_Damage.h"

ACDamageText::ACDamageText()
{
	CHelpers::CreateComponent(this, &Widget, "Widget");
	TSubclassOf<UUserWidget> widget;
	CHelpers::GetClass(&widget, "WidgetBlueprint'/Game/Widgets/Damage/WB_Damage.WB_Damage_C'");
	Widget->SetWidgetClass(widget);
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ACDamageText::BeginPlay()
{
	Super::BeginPlay();	

	UCWidget_Damage* obj;
	obj = Cast<UCWidget_Damage>(Widget->GetUserWidgetObject());
	if (obj)
		obj->SetDamageText(Damage);
	PlayDamageText();
}

void ACDamageText::SetDamageText(float InDamage)
{
	Damage = InDamage;
}

void ACDamageText::Update(float InOpacity)
{
	Widget->GetUserWidgetObject()->SetRenderOpacity(InOpacity);
}

