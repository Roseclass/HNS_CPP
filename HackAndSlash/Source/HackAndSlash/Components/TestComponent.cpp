#include "TestComponent.h"
#include "Global.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/CPlayer.h"

UTestComponent::UTestComponent()
{
}

void UTestComponent::BeginPlay()
{
	Super::BeginPlay();	
	owner = Cast<ACPlayer>(GetOwner());
}

void UTestComponent::SetMaxHP(float InMaxHP)
{
	Max_HP = InMaxHP;
}

void UTestComponent::SetCurrentHP(float InCurrentHP)
{
	Cur_HP = InCurrentHP;
	Cur_HP = UKismetMathLibrary::FClamp(Cur_HP, 0.0f, Max_HP);
}

void UTestComponent::AddMaxHP(float InAdd)
{
	Max_HP += InAdd;
}

void UTestComponent::AddCurrentHP(float InAdd)
{
	Cur_HP += InAdd;
	Cur_HP = UKismetMathLibrary::FClamp(Cur_HP, 0.0f, Max_HP);
}

void UTestComponent::SetMaxMP(float InMaxMP)
{
	Max_MP = InMaxMP;
}

void UTestComponent::SetCurrentMP(float InCurrentMP)
{
	Cur_MP = InCurrentMP;
	Cur_MP = UKismetMathLibrary::FClamp(Cur_MP, 0.0f, Max_MP);
}

void UTestComponent::AddMaxMP(float InAdd)
{
	Max_MP += InAdd;
}

void UTestComponent::AddCurrentMP(float InAdd)
{
	Cur_MP += InAdd;
	Cur_MP = UKismetMathLibrary::FClamp(Cur_MP, 0.0f, Max_MP);
}