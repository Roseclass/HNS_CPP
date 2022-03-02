#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectileBeginOverlap, FHitResult, InHitResult);

UCLASS()
class HACKANDSLASH_API ACProjectile : public AActor
{
	GENERATED_BODY()

private:
	class ACharacter* OwnerCharacter;
	TArray<class ACharacter*> HittedCharacter;
	TSubclassOf<class ACDamageText> DamageTextClass;
	float Damage;
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* Explosion;

	UPROPERTY(EditDefaultsOnly)
		FTransform ExplosionTransform;

	UPROPERTY(EditDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Particle;

	UPROPERTY(EditDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

	UPROPERTY(EditDefaultsOnly)
		bool AOE;

public:
	ACProjectile();
	void SetDamage(float InDamage);
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(BlueprintAssignable)
		FProjectileBeginOverlap OnProjectileBeginOverlap;
};
