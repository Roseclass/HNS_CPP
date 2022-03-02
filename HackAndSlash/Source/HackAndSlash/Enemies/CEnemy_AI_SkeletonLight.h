#pragma once

#include "CoreMinimal.h"
#include "Enemies/CEnemy_AI.h"
#include "Enemies/IEnemyTask.h"
#include "CEnemy_AI_SkeletonLight.generated.h"

UCLASS()
class HACKANDSLASH_API ACEnemy_AI_SkeletonLight : public ACEnemy_AI, public IIEnemyTask
{
	GENERATED_BODY()
	//property
private:
	UPROPERTY(EditAnywhere)
		int32 AttackIndex[2];
protected:
public:

	//function
private:
protected:
public:
	ACEnemy_AI_SkeletonLight();
	virtual void Wait() override {};
	virtual void Attack()override;
	virtual void Patrol() override {};
	virtual void Hitted() override {};
	virtual void Avoid() override {};
};
