#include "CStateComponent.h"
#include "Global.h"
#include "Characters/CPlayer.h"


UCStateComponent::UCStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();
	
	owner = Cast<ACPlayer>(GetOwner());
	ChangeWeaponState(EWeaponState::Original);
}

void UCStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCStateComponent::ChangeState(EWeaponState InWeaponState, EPlayerState InPlayerState)
{
	//CLog::Print("ChangeState");
	ChangeWeaponState(InWeaponState);
	ChangePlayerState(InPlayerState);
}

void UCStateComponent::ChangeWeaponState(EWeaponState InWeaponState)
{
	if (InWeaponState == WeaponState)
		return;
	switch (InWeaponState)
	{
	case EWeaponState::Original:
		SetOriginalWeaponMode();
		break;
	case EWeaponState::Equiment:
		SetEquimentWeaponMode();
		break;
	default:
		break;
	}
}

void UCStateComponent::ChangePlayerState(EPlayerState InPlayerState)
{
	if (InPlayerState == ActionState)
		return;
	switch (InPlayerState)
	{
	case EPlayerState::Idle:
		SetIdleMode();
		break;
	case EPlayerState::Attack:
		SetAttackMode();
		break;
	case EPlayerState::Evade:
		SetEvadeMode();
		break;
	case EPlayerState::Run:	
		SetRunMode();
		break;
	case EPlayerState::Walk:
		SetWalkMode();
		break;	
	case EPlayerState::Dead:
		SetDeadMode();
		break;
	default:
		break;
	}
}

void UCStateComponent::ChangeCanMove(bool InMove)
{
	bCanMove = InMove;
	/*if (bCanMove)
		CLog::Print("true");
	else
		CLog::Print("false");*/
}

void UCStateComponent::SetIdleMode()
{
	ActionState = EPlayerState::Idle;
}

void UCStateComponent::SetAttackMode()
{
	ActionState = EPlayerState::Attack;
}

void UCStateComponent::SetEvadeMode()
{
	ActionState = EPlayerState::Evade;
}

void UCStateComponent::SetRunMode()
{
	ActionState = EPlayerState::Run;
}

void UCStateComponent::SetWalkMode()
{
	ActionState = EPlayerState::Walk;
}

void UCStateComponent::SetDeadMode()
{
	ActionState = EPlayerState::Dead;
}

void UCStateComponent::SetOriginalWeaponMode()
{
	//CLog::Print("OriginalMode");
	if (OnChangeToOriginal.IsBound())
		OnChangeToOriginal.Broadcast();
	SetWeaponMode(EWeaponState::Original);
}

void UCStateComponent::SetEquimentWeaponMode()
{
	//CLog::Print("EquipmentMode");
	if (OnChangeToEquipment.IsBound())
		OnChangeToEquipment.Broadcast();
	SetWeaponMode(EWeaponState::Equiment);
}

void UCStateComponent::SetPlayerMode(EPlayerState InPlayerState)
{
	ActionState = InPlayerState;
}

void UCStateComponent::SetWeaponMode(EWeaponState InWeaponState)
{
	if (InWeaponState == EWeaponState::Flex)
		return;
	WeaponState = InWeaponState;	
	if (InWeaponState == EWeaponState::Original)
	{
		owner->SetRevealWeapon();
		return;
	}
	owner->SetHideWeapon();
}
