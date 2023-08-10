
#pragma once

#include "CoreMinimal.h"
#include "GameplayOptionsDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FGameplayOptions{
 
    GENERATED_USTRUCT_BODY()
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Hamster Explosions")
    float HamsterExplosionTimer = 15.0f;
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Spawning")
    float MaxHamsterSpawnDelay = 3.0f;
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Spawning")
    float MinHamsterSpawnDelay = 1.0f;
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Scoring")
    int32 MaxHamstersInDepositBox =10;
};

/**
 * 
 */
UCLASS()
class EXPLODINGHAMSTERS_API UGameplayOptionsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
	public: 
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayOptions GameplayOptions;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FGameplayOptions DefaultGameplayOptions;

	UGameplayOptionsDataAsset();
};
