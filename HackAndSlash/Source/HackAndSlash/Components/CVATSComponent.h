#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CVATSComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HACKANDSLASH_API UCVATSComponent : public UActorComponent
{
	GENERATED_BODY()

	//property
private:
	UPROPERTY(EditAnywhere)
		class UCVATSData* VATSData;
	class ACharacter* Owner;
	class USkeletalMeshComponent* PartMesh;
	TMap<FName, FName> BoneMap;
	bool* VATS;
	class ACPlayerController* Controller;
protected:
public:

	//function
private:
	int32 GetParent(TArray<int32>& NodeList, int32 InIndex);
	void MergeParent(int32 A,int32 B);
	void ReadBoneData();
protected:
	virtual void BeginPlay() override;
public:
	UCVATSComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
	UFUNCTION(BlueprintCallable)
		void OnVATS();
	UFUNCTION(BlueprintCallable)
		void OffVATS();
	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsVATS() { return *VATS; }
	UFUNCTION(BlueprintCallable)
		FName GetBoneName();
	void ChangeMesh(FName BoneName);
};
