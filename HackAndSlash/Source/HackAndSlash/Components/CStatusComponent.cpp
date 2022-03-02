#include "CStatusComponent.h"
#include "Global.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/CPlayer.h"

UCStatusComponent::UCStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	owner = Cast<ACPlayer>(GetOwner());
}

void UCStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCStatusComponent::SetMaxHP(float InMaxHP)
{
	Max_HP = InMaxHP;
	RefreshHP();
}

void UCStatusComponent::SetCurrentHP(float InCurrentHP)
{
	Cur_HP = InCurrentHP;
	Cur_HP = UKismetMathLibrary::FClamp(Cur_HP, 0.0f, Max_HP);
	RefreshHP();
}

void UCStatusComponent::AddMaxHP(float InAdd)
{
	Max_HP += InAdd;
	RefreshHP();
}

void UCStatusComponent::AddCurrentHP(float InAdd)
{
	Cur_HP += InAdd;
	Cur_HP = UKismetMathLibrary::FClamp(Cur_HP, 0.0f, Max_HP);
	RefreshHP();
}

void UCStatusComponent::SetMaxMP(float InMaxMP)
{
	Max_MP = InMaxMP;
	RefreshMP();
}

void UCStatusComponent::SetCurrentMP(float InCurrentMP)
{
	Cur_MP = InCurrentMP;
	Cur_MP = UKismetMathLibrary::FClamp(Cur_MP, 0.0f, Max_MP);
	RefreshMP();
}

void UCStatusComponent::AddMaxMP(float InAdd)
{
	Max_MP += InAdd;
	RefreshMP();
}

void UCStatusComponent::AddCurrentMP(float InAdd)
{
	Cur_MP += InAdd;
	Cur_MP = UKismetMathLibrary::FClamp(Cur_MP, 0.0f, Max_MP);
	RefreshMP();
}