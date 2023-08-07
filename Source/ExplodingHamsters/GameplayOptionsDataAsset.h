
#pragma once

#include "CoreMinimal.h"
#include "GameplayOptionsDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FGameplayOptions{
 
    GENERATED_USTRUCT_BODY()
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Hamster Explosions")
    float HamsterExplosionTimer = 10.0f;
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Spawning")
    float MaxHamsterSpawnDelay = 5.0f;
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Spawning")
    float MinHamsterSpawnDelay = 0.5f;
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Scoring")
    int32 MaxHamstersInDepositBox =10;
};

/**
 * 
 */
UCLASS()
class EXPLODINGHAMSTERS_API UGameplayOptionsDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
    UPROPERTY(EditAnywhere)
    TArray<FGameplayOptions> GameplayOptionsArray;
};
