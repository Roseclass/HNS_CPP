#include "CProjectile.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Widgets/CDamageText.h"

ACProjectile::ACProjectile()
{
	CHelpers::GetClass(&DamageTextClass, "Blueprint'/Game/Widgets/Damage/BP_CDamageText.BP_CDamageText_C'");
	CHelpers::CreateComponent(this, &Sphere, "Sphere");
	CHelpers::CreateComponent(this, &Particle, "Particle", Sphere);

	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	InitialLifeSpan = 3.0f;

	Projectile->InitialSpeed = 4000.0f;
	Projectile->MaxSpeed = 8000.0f;
	Projectile->ProjectileGravityScale = 0.0f;
}

void ACProjectile::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
		CLog::Print(GetName() + "'s Onwer==nullptr");
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACProjectile::OnComponentBeginOverlap);
}

void ACProjectile::SetDamage(float InDamage)
{
	Damage = InDamage;
}

void ACProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OtherActor == OwnerCharacter);
	CheckTrue(OtherActor->GetOwner() == OwnerCharacter);
	CheckTrue(OtherActor == this);

	CLog::Print(OtherActor->GetName());

	if (AOE)
	{
		ACharacter* InOtherCharacter = Cast<ACharacter>(OtherActor);
		CheckNull(InOtherCharacter);
		for (const ACharacter* other : HittedCharacter)
		{
			if (other == InOtherCharacter)
				return;
		}
		HittedCharacter.Add(InOtherCharacter);
	}

	if (!!Explosion)
	{
		FTransform transform = ExplosionTransform;
		transform.AddToTranslation(bFromSweep ? SweepResult.Location : GetActorLocation());
		transform.SetRotation(FQuat(SweepResult.ImpactNormal.Rotation()));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, transform);
		Explosion = nullptr;
	}

	/*if (OnProjectileBeginOverlap.IsBound())
		OnProjectileBeginOverlap.Broadcast(SweepResult);*/

	//실제 대미지 전달
	FDamageEvent e;
	OtherActor->TakeDamage(Damage, e, OwnerCharacter->GetController(), OwnerCharacter);

	//대미지 텍스트 설정
	ACDamageText* DamageText = nullptr;
	FTransform transform;
	transform.SetLocation(OtherActor->GetActorLocation());
	float x = UKismetMathLibrary::RandomFloatInRange(-50.0f, 50.0f);
	float y = UKismetMathLibrary::RandomFloatInRange(-50.0f, 50.0f);
	transform.AddToTranslation(FVector(x, y, 0));

	if (DamageTextClass)
	{
		DamageText = GetWorld()->SpawnActorDeferred<ACDamageText>(DamageTextClass, transform);
		DamageText->SetDamageText(Damage);
		UGameplayStatics::FinishSpawningActor(DamageText, transform);
	}

	if(!AOE)
		Destroy();
}



