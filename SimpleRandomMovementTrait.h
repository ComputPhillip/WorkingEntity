// Copyright PkCo. All Rights Reserved.

#pragma once

#include "MassEntityTemplateRegistry.h"
#include "MassEntityTraitBase.h"
#include "CoreMinimal.h"
#include "SimpleRandomMovementFragment.h"
#include "SimpleRandomMovementTrait.generated.h"

UCLASS(meta = (DisplayName = "Simple Random Movement"))
class CHAPTERONE_API USimpleRandomMovementTrait : public UMassEntityTraitBase
{
GENERATED_BODY()
protected:
    virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override
    {
        BuildContext.AddFragment<FSimpleRandomMovementFragment>();
    }
};