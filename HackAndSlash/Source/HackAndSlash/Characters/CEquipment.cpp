#include "CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CEquimentComponent.h"
#include "Widgets/CDamageText.h"

ACEquipment::ACEquipment()
{
	CHelpers::GetClass(&DamageTextClass, "Blueprint'/Game/Widgets/Damage/BP_CDamageText.BP_CDamageText_C'");
	CHelpers::CreateComponent(this, &Scene, "Scene");
	CHelpers::CreateComponent(this, &SkeletalMesh, "SkeletalMesh", Scene);
}

void ACEquipment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	GetComponents<UShapeComponent>(ShapeComponents);
	for (UShapeComponent* component : ShapeComponents)
	{
		component->OnComponentBeginOverlap.AddDynamic(this, &ACEquipment::OnComponentBeginOverlap);
		//component->OnComponentEndOverlap.AddDynamic(this, &ACEquipment::OnComponentEndOverlap);
	}

	OffCollision();

	/*for (UShapeComponent* i : ShapeComponents)
		CLog::Print(i->GetName());*/

	Super::BeginPlay();
	
}

void ACEquipment::AttachTo(FName InSocketName)
{
	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}

void ACEquipment::OnCollision()
{
	for (UShapeComponent* component : ShapeComponents)
		component->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACEquipment::OffCollision()
{
	for (UShapeComponent* component : ShapeComponents)
		component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void ACEquipment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());	
	ACharacter* InOtherCharacter = Cast<ACharacter>(OtherActor);
	CheckNull(InOtherCharacter);

	//한번 피격된 캐릭터는 충돌 처리에서 제외
	for (const ACharacter* other : HittedCharacter)
	{
		if (other == InOtherCharacter)
			return;
	}
	HittedCharacter.Add(InOtherCharacter);

	////히트 스탑
	//float hitStop = Datas[Index].HitStop;
	//if (FMath::IsNearlyZero(hitStop) == false)
	//{
	//	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 2e-2f);
	//	UKismetSystemLibrary::K2_SetTimer(this, "RestoreGlobalTimeDilation", hitStop * 2e-2f, false);
	//}

	////히트 파티클
	//UParticleSystem* hitEffect = Datas[Index].Effect;
	//if (!!hitEffect)
	//{
	//	FTransform transform = Datas[Index].EffectTransform;
	//	transform.AddToTranslation(InOtherCharacter->GetActorLocation());
	//	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
	//}

	////카메라 쉐이크
	//TSubclassOf<UCameraShake> shake = Datas[Index].ShakeClass;
	//if (!!shake)
	//{
	//	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//	if (!!controller)
	//		controller->PlayerCameraManager->PlayCameraShake(shake);
	//}


	//실제 대미지 전달
	FDamageEvent e;
	UCEquimentComponent* equip;
	equip = CHelpers::GetComponent<UCEquimentComponent>(OwnerCharacter);
	InOtherCharacter->TakeDamage(equip->GetWeaponPower(), e, OwnerCharacter->GetController(), OwnerCharacter);

	//대미지 텍스트 설정
	ACDamageText* DamageText = nullptr;
	FTransform transform;
	transform.SetLocation(InOtherCharacter->GetActorLocation());
	float x = UKismetMathLibrary::RandomFloatInRange(-50.0f, 50.0f);
	float y = UKismetMathLibrary::RandomFloatInRange(-50.0f, 50.0f);
	transform.AddToTranslation(FVector(x, y, 0));
	if (DamageTextClass)
	{
		DamageText = GetWorld()->SpawnActorDeferred<ACDamageText>(DamageTextClass,transform);
		DamageText->SetDamageText(equip->GetWeaponPower());
		UGameplayStatics::FinishSpawningActor(DamageText, transform);
	}
	
}

void ACEquipment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	HittedCharacter.Empty();
}

void ACEquipment::ResetTarget()
{
	HittedCharacter.Empty();
}
