#include "CPlayer.h"
#include "Global.h"
#include "AIController.h"
#include "CGameMode.h"
#include "CPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/CSkillComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CEquimentComponent.h"
#include "Components/TestComponent.h"
#include "Datas/CSkillData.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//컴포넌트
	CHelpers::CreateComponent(this, &SpringArm, "SpringArm", Cast<USceneComponent>(GetCapsuleComponent()));
	CHelpers::CreateComponent(this, &Camera, "Camera", SpringArm);
	CHelpers::CreateComponent(this, &SceneSpringArm, "SceneSpringArm", Cast<USceneComponent>(GetCapsuleComponent()));
	CHelpers::CreateComponent(this, &SceneCaptureCamera, "SceneCaptureCamera", SceneSpringArm);

	//액터컴포넌트
	CHelpers::CreateActorComponent<UCSkillComponent>(this, &Skill, "Skill");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCEquimentComponent>(this, &Equipment, "Equipment");
	CHelpers::CreateActorComponent<UTestComponent>(this, &Test, "Status");

	//메시설정
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//스프링암 설정
	SpringArm->TargetArmLength = CameraArmLength;

	//신캡쳐 스프링암 설정
	SceneSpringArm->TargetArmLength = SceneCaptureArmLength;
	SceneSpringArm->SetRelativeLocation(SceneCaptureLocation);
	SceneSpringArm->SetRelativeRotation(SceneCaptureRotation);

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	//플레이어 컨트롤러 얻어오기
	Controller = Cast<ACPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	//컨트롤러 설정
	Controller->SetViewTarget(this);
	Controller->bShowMouseCursor = true;
	Controller->SetPlayCharacter(this);

	//키바인딩 CPlayerController	
	Controller->OnKey_Z.AddDynamic(this, &ACPlayer::ChangeWeapon);
	Controller->OnKey_1.AddDynamic(this, &ACPlayer::DoITEM_1);
	Controller->OnKey_2.AddDynamic(this, &ACPlayer::DoITEM_2);
	Controller->OnKey_3.AddDynamic(this, &ACPlayer::DoITEM_3);
	Controller->OnKey_4.AddDynamic(this, &ACPlayer::DoITEM_4);
	Controller->OnKey_5.AddDynamic(this, &ACPlayer::DoITEM_5);

	Controller->OnPlaySkill.AddDynamic(this, &ACPlayer::PlaySkill);

	State->OnChangeToEquipment.AddDynamic(Equipment, &UCEquimentComponent::ChangeToEquiment);
	State->OnChangeToOriginal.AddDynamic(Equipment, &UCEquimentComponent::ChangeToOriginal);

	SetIdleMode();
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//카메라 시점 고정
	if(CameraLock)
		SpringArm->SetWorldRotation(FRotator(-55.0f ,  -90.0f, 0.0f));
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	/*PlayerInputComponent->BindAction("Skill_A", EInputEvent::IE_Pressed, this, &ACPlayer::DoSkill_A);
	PlayerInputComponent->BindAction("Skill_S", EInputEvent::IE_Pressed, this, &ACPlayer::DoSkill_S);
	PlayerInputComponent->BindAction("Skill_D", EInputEvent::IE_Pressed, this, &ACPlayer::DoSkill_D);
	PlayerInputComponent->BindAction("Skill_F", EInputEvent::IE_Pressed, this, &ACPlayer::DoSkill_F);
	PlayerInputComponent->BindAction("Skill_G", EInputEvent::IE_Pressed, this, &ACPlayer::DoSkill_G);
	PlayerInputComponent->BindAction("ChangeWeapon", EInputEvent::IE_Pressed, this, &ACPlayer::ChangeWeapon);*/
}

FGenericTeamId ACPlayer::GetGenericTeamId() const
{
	return FGenericTeamId(TeamID);
}

void ACPlayer::ChangeWeapon()
{
	//CLog::Print("ChangeWeapon");
	CheckTrue(State->IsAttackMode());
	CheckTrue(State->IsEvadeMode());	
	if (State->IsOriginalWeaponMode())
	{
		Equipment->ChangeToEquiment();
		State->ChangeWeaponState(EWeaponState::Equiment);
		return;
	}
	Equipment->ChangeToOriginal();
	State->ChangeWeaponState(EWeaponState::Original);	
}

void ACPlayer::PlaySkill(class UCSkillData* InData)
{
	//CLog::Print("ACPlayer::PlaySkill(class UCSkillData* InData)");
	CheckNull(InData);
	CheckTrue(State->IsAttackMode());
	CheckTrue(State->IsEvadeMode());
	State->ChangeWeaponState(InData->MontageData.WeaponState);
	State->ChangePlayerState(InData->MontageData.PlayerState);
	Skill->PlaySkill(InData);	
}

void ACPlayer::DoITEM_1()
{
	CLog::Print("Slot1");
	//CheckNull(Status);
	AddCurrentHP(25.0f);
}

void ACPlayer::DoITEM_2()
{
	CLog::Print("Slot2");
	/*CLog::Print(GetRatioMP());*/
	AddCurrentMP(5.0f);
}

void ACPlayer::DoITEM_3()
{
	CLog::Print("Slot3");
}

void ACPlayer::DoITEM_4()
{
	CLog::Print("Slot4");
}

void ACPlayer::DoITEM_5()
{
	CLog::Print("Slot5");
}

void ACPlayer::SetHideWeapon()
{
	HideWeapon();
}

void ACPlayer::SetRevealWeapon()
{
	RevealWeapon();
}

void ACPlayer::MoveToLocation(FVector inLocation)
{
	CheckFalse(State->IsCanMove());
	GetController<AAIController>()->MoveToLocation(inLocation);
	if (State->IsRunMode())
		return;	
	State->ChangePlayerState(EPlayerState::Run);
}

void ACPlayer::MoveEnd()
{
	CheckTrue(State->IsAttackMode());
	CheckTrue(State->IsEvadeMode());
	State->ChangePlayerState(EPlayerState::Idle);
}

void ACPlayer::SetCanMove(bool InBool)
{
	State->ChangeCanMove(InBool);
}

void ACPlayer::SetMove()
{
	State->ChangeCanMove(true);
}

void ACPlayer::SetStop()
{
	State->ChangeCanMove(false);
	GetCharacterMovement()->StopMovementImmediately();
}

void ACPlayer::SetIdleMode()
{
	State->ChangePlayerState(EPlayerState::Idle);
}

void ACPlayer::SetAttackMode()
{
	State->ChangePlayerState(EPlayerState::Attack);
}

void ACPlayer::SetEvadeMode()
{
	State->ChangePlayerState(EPlayerState::Evade);
}

void ACPlayer::SetRunMode()
{
	State->ChangePlayerState(EPlayerState::Run);
}

void ACPlayer::SetWalkMode()
{
	State->ChangePlayerState(EPlayerState::Walk);
}

void ACPlayer::ZoomIN()
{
	SceneCaptureArmLength -= 10.0f;
	SceneCaptureArmLength = UKismetMathLibrary::Clamp(SceneCaptureArmLength, 90.0f, 180.0f);
	SceneSpringArm->TargetArmLength = SceneCaptureArmLength;
}

void ACPlayer::ZoomOUT()
{
	SceneCaptureArmLength += 10.0f;
	SceneCaptureArmLength = UKismetMathLibrary::Clamp(SceneCaptureArmLength, 90.0f, 180.0f);
	SceneSpringArm->TargetArmLength = SceneCaptureArmLength;
}

void ACPlayer::LeftAngle()
{
	SceneCaptureRotation = FRotator(0.0f, SceneCaptureRotation.Yaw + 30.0f, 0.0f);
	SceneSpringArm->SetRelativeRotation(SceneCaptureRotation);
}

void ACPlayer::RightAngle()
{
	SceneCaptureRotation = FRotator(0.0f, SceneCaptureRotation.Yaw - 30.0f, 0.0f);
	SceneSpringArm->SetRelativeRotation(SceneCaptureRotation);
}

void ACPlayer::OnCollision()
{
	Equipment->OnCollision();
}

void ACPlayer::OffCollision()
{
	Equipment->OffCollision();
}

void ACPlayer::EndAction()
{
	Equipment->ResetTarget();
}