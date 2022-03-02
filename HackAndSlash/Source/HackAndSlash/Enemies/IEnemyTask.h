#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IEnemyTask.generated.h"

UINTERFACE(MinimalAPI)
class UIEnemyTask : public UInterface
{
	GENERATED_BODY()
};

class HACKANDSLASH_API IIEnemyTask
{
	GENERATED_BODY()

public:
	virtual void Wait() = 0;
	virtual void Attack() = 0;
	virtual void Patrol() = 0;
	virtual void Hitted() = 0;
	virtual void Avoid() = 0;
};
