#pragma once

#include "MassEntitySubsystem.h"
#include "MassEntityTraitBase.h"
#include "SimpleRandomMovementFragment.generated.h"

USTRUCT(BlueprintType)
struct CHAPTERONE_API FSimpleRandomMovementFragment : public FMassFragment
{
	GENERATED_BODY()

	/** Target position for the random movement */
	UPROPERTY(EditAnywhere)
	FVector Target;
};
