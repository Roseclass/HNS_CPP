#include "CWidget_Damage.h"
#include "Global.h"
#include "Kismet/KismetTextLibrary.h"
#include "Components/TextBlock.h"

void UCWidget_Damage::SetDamageText(float InDamage)
{
	TEnumAsByte<ERoundingMode> e;
	e = ERoundingMode::HalfToEven;	
	DamageText->SetText(UKismetTextLibrary::Conv_FloatToText(InDamage, e));
}
