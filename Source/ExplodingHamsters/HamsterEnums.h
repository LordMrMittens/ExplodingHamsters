#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/UserDefinedEnum.h"

UENUM(BlueprintType)
enum class EHamsterEnums : uint8
{
    Red,
    Blue,
    Green,
    Yellow,
    EnumCount UMETA(Hidden)
};