#include "CGameMode.h"
#include "Global.h"
#include "GameFramework/SpectatorPawn.h"
#include "Characters/CPlayerController.h"
#include "Characters/CPlayer.h"


ACGameMode::ACGameMode()
{
	//CHelpers::GetClass(&DefaultPawnClass, "Blueprint'/Game/Player/BP_Player_Revenant.BP_Player_Revenant_C'");
	//CHelpers::GetClass(&DefaultPawnClass, "Blueprint'/Game/Player/BP_Player_Wraith.BP_Player_Wraith_C'");
	//CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Player/BP_CRevenant.BP_CRevenant_C'");
	//CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Player/NewBlueprint1.NewBlueprint1_C'");
	ASpectatorPawn* a;
	a = NewObject<ASpectatorPawn>();
	DefaultPawnClass = a->GetClass();
	CHelpers::GetClass(&PlayerControllerClass, "Blueprint'/Game/Player/BP_CPlayerController.BP_CPlayerController_C'");
}
