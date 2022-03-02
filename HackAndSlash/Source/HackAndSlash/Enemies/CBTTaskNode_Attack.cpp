#include "CBTTaskNode_Attack.h"
#include "Global.h"
#include "Enemies/CAIController.h"
#include "Enemies/CEnemy_AI.h"
#include "Enemies/IEnemyTask.h"
#include "Components/CSkillComponent.h"
#include "Components/CStateComponent.h"

UCBTTaskNode_Attack::UCBTTaskNode_Attack()
{
	NodeName = "Attack";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* aiPawn = Cast<ACEnemy_AI>(controller->GetPawn());

	UCSkillComponent* skill = CHelpers::GetComponent<UCSkillComponent>(aiPawn);
	IIEnemyTask* check = Cast<IIEnemyTask>(aiPawn);
	if(check)
	{
		check->Attack();
	}
	TotalTime = 0.0f;
	//action->DoAction();
	CLog::Print("EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)");
	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* aiPawn = Cast<ACEnemy_AI>(controller->GetPawn());

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(aiPawn);

	TotalTime += DeltaSeconds;

	if (state->IsIdleMode() && TotalTime > Delay)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
