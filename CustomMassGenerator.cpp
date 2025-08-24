// CustomMassGenerator.cpp

#include "CustomMassGenerator.h"

#include "IDetailTreeNode.h"
#include "MassSpawnerTypes.h"                 // FMassSpawnedEntityType, FMassTransformsSpawnData
#include "MassSpawnLocationProcessor.h"       // UMassSpawnLocationProcessor
#include "GameFramework/Actor.h"              // AActor

UCustomMassGenerator::UCustomMassGenerator(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
}

void UCustomMassGenerator::Generate(
    UObject& QueryOwner,
    TConstArrayView<FMassSpawnedEntityType> EntityTypes,
    int32 Count,
    FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate
) const
{
    if (Count <= 0 || EntityTypes.IsEmpty())
    {
        FinishedGeneratingSpawnPointsDelegate.Execute(TArray<FMassEntitySpawnDataGeneratorResult>());
        return;
    }

    const AActor* OwnerActor = Cast<AActor>(&QueryOwner);
    const FTransform Origin = OwnerActor ? OwnerActor->GetActorTransform() : FTransform::Identity;

    TArray<FMassEntitySpawnDataGeneratorResult> Results;
    BuildResultsFromEntityTypes(Count, EntityTypes, Results); // fills EntityConfigIndex and NumEntities

    for (FMassEntitySpawnDataGeneratorResult& Result : Results)
    {
        Result.SpawnData.InitializeAs<FMassTransformsSpawnData>();
        FMassTransformsSpawnData& Xforms = Result.SpawnData.GetMutable<FMassTransformsSpawnData>();
        Xforms.Transforms.Reserve(Result.NumEntities);

        // Grid fill using editor-exposed CountX, CountY, Spacing
        const int32 GridX = FMath::Max(1, CountX);
        const int32 GridY = FMath::Max(1, CountY);
        const float Step = FMath::Max(0.f, Spacing);

        int32 placed = 0;
        for (int32 y = 0; y < GridY && placed < Result.NumEntities; ++y)
        {
            for (int32 x = 0; x < GridX && placed < Result.NumEntities; ++x)
            {
                FTransform T = Origin;
                T.AddToTranslation(FVector(x * Step, y * Step, 0.f));
                Xforms.Transforms.Add(T);
                ++placed;
            }
        }

        Result.SpawnDataProcessor = UMassSpawnLocationProcessor::StaticClass();
    }

    FinishedGeneratingSpawnPointsDelegate.Execute(Results);
}
