#include "CWidget_VATS_Info.h"
#include "Global.h"
#include "Components/Image.h"

void UCWidget_VATS_Info::BeginPlay()
{
	MaxCount = BulletImages.Num();
}
void UCWidget_VATS_Info::SetBulletCount(int32 InCount)
{
	if (InCount < 0)
		InCount = 0;
	if (InCount > MaxCount)
		InCount = MaxCount;
	FSlateColor off;
	off.GetSpecifiedColor()= FLinearColor::Black;
	FSlateColor on;
	on.GetSpecifiedColor() = FLinearColor::White;
	for (int32 i = 0; i < MaxCount; i++)
		BulletImages[i]->SetBrushTintColor(off);
	for (int32 i = 0; i < InCount; i++)
		BulletImages[i]->SetBrushTintColor(on);
}
void UCWidget_VATS_Info::IncreaseBulletCount()
{
	if (BulletCount >= MaxCount)
	{
		BulletCount = MaxCount;
		return;
	}
	FSlateColor on;
	on.GetSpecifiedColor() = FLinearColor::White;
	BulletImages[BulletCount-1]->SetBrushTintColor(on);
	BulletCount++;
}
void UCWidget_VATS_Info::DecreaseBulletCount()
{
	if (BulletCount <=0)
	{
		BulletCount = 0;
		return;
	}
	FSlateColor off;
	off.GetSpecifiedColor() = FLinearColor::Black;
	BulletImages[BulletCount-1]->SetBrushTintColor(off);
	BulletCount--;
}