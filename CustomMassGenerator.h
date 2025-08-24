#pragma once

#include "CoreMinimal.h"
#include "MassEntitySpawnDataGeneratorBase.h"
#include "CustomMassGenerator.generated.h"

UCLASS(EditInlineNew, DefaultToInstanced, BlueprintType)
class CHAPTERONE_API UCustomMassGenerator : public UMassEntitySpawnDataGeneratorBase
{
	GENERATED_BODY()

public:
	// Declare ctor
	UCustomMassGenerator(const FObjectInitializer& ObjectInitializer);

	// Optional editor params (match prior response)
	UPROPERTY(EditAnywhere, Category="Layout") int32 CountX = 10;
	UPROPERTY(EditAnywhere, Category="Layout") int32 CountY = 1;
	UPROPERTY(EditAnywhere, Category="Layout", meta=(ClampMin="0.0")) float Spacing = 100.f;

	virtual void Generate(UObject& QueryOwner,
		TConstArrayView<FMassSpawnedEntityType> EntityTypes,
		int32 Count,
		FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate) const override;
};
