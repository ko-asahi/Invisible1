#include "UI/InvisibleWidgetHelper.h"

#include "Blueprint/UserWidget.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "Enemy/AlertnessProvider.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "UObject/UnrealType.h"

static UObject* ResolveAlertnessProviderFromObject(const UObject* Object)
{
    if (!Object)
    {
        return nullptr;
    }

    UObject* MutableObject = const_cast<UObject*>(Object);
    if (MutableObject->Implements<UAlertnessProvider>())
    {
        return MutableObject;
    }

    if (const UActorComponent* Component = Cast<UActorComponent>(Object))
    {
        return ResolveAlertnessProviderFromObject(Component->GetOwner());
    }

    if (const AController* Controller = Cast<AController>(Object))
    {
        APawn* ControlledPawn = Controller->GetPawn();
        if (ControlledPawn && ControlledPawn->Implements<UAlertnessProvider>())
        {
            return ControlledPawn;
        }
        return nullptr;
    }

    if (const APawn* Pawn = Cast<APawn>(Object))
    {
        AController* Controller = Pawn->GetController();
        if (Controller && Controller->Implements<UAlertnessProvider>())
        {
            return Controller;
        }
    }

    return nullptr;
}

static UObject* FindAlertnessProviderObjectFromWidgetProperties(const UUserWidget* Widget)
{
    if (!Widget)
    {
        return nullptr;
    }

    for (TFieldIterator<FObjectPropertyBase> It(Widget->GetClass()); It; ++It)
    {
        const FObjectPropertyBase* ObjectProperty = *It;
        if (!ObjectProperty)
        {
            continue;
        }

        if (UObject* Value = ObjectProperty->GetObjectPropertyValue_InContainer(Widget))
        {
            if (UObject* Provider = ResolveAlertnessProviderFromObject(Value))
            {
                return Provider;
            }
        }
    }

    return nullptr;
}

static const UWidgetComponent* ResolveWidgetComponentFromWidget(const UUserWidget* Widget)
{
    if (!Widget)
    {
        return nullptr;
    }

    if (const UWidgetComponent* TypedOuterComp = Widget->GetTypedOuter<UWidgetComponent>())
    {
        return TypedOuterComp;
    }

    const UObject* Outer = Widget->GetOuter();
    while (Outer)
    {
        if (const UWidgetComponent* OuterComp = Cast<UWidgetComponent>(Outer))
        {
            return OuterComp;
        }
        Outer = Outer->GetOuter();
    }

    if (UWorld* World = Widget->GetWorld())
    {
        for (TActorIterator<AActor> ActorIt(World); ActorIt; ++ActorIt)
        {
            TInlineComponentArray<UWidgetComponent*> WidgetComponents(*ActorIt);
            for (const UWidgetComponent* WidgetComp : WidgetComponents)
            {
                if (WidgetComp && WidgetComp->GetUserWidgetObject() == Widget)
                {
                    return WidgetComp;
                }
            }
        }
    }

    return nullptr;
}

static UObject* FindAlertnessProviderObjectFromWidget(const UUserWidget* Widget)
{
    const UWidgetComponent* WidgetComp = ResolveWidgetComponentFromWidget(Widget);
    if (!WidgetComp)
    {
        return nullptr;
    }

    AActor* Owner = WidgetComp->GetOwner();
    if (!Owner)
    {
        return nullptr;
    }

    return ResolveAlertnessProviderFromObject(Owner);
}

float UInvisibleWidgetHelper::GetAlertnessFromObject(const UObject* Object)
{
    if (UObject* Provider = ResolveAlertnessProviderFromObject(Object))
    {
        return IAlertnessProvider::Execute_GetAlertness(Provider);
    }

    return 0.0f;
}

float UInvisibleWidgetHelper::GetAlertnessNormalizedFromObject(const UObject* Object)
{
    if (UObject* Provider = ResolveAlertnessProviderFromObject(Object))
    {
        return IAlertnessProvider::Execute_GetAlertnessNormalized(Provider);
    }

    return 0.0f;
}

float UInvisibleWidgetHelper::GetAlertnessFromWidgetOwner(const UUserWidget* Widget)
{
    if (UObject* Provider = FindAlertnessProviderObjectFromWidget(Widget))
    {
        return IAlertnessProvider::Execute_GetAlertness(Provider);
    }

    if (UObject* Provider = FindAlertnessProviderObjectFromWidgetProperties(Widget))
    {
        return IAlertnessProvider::Execute_GetAlertness(Provider);
    }

    return 0.0f;
}

float UInvisibleWidgetHelper::GetAlertnessNormalizedFromWidgetOwner(const UUserWidget* Widget)
{
    if (UObject* Provider = FindAlertnessProviderObjectFromWidget(Widget))
    {
        return IAlertnessProvider::Execute_GetAlertnessNormalized(Provider);
    }

    if (UObject* Provider = FindAlertnessProviderObjectFromWidgetProperties(Widget))
    {
        return IAlertnessProvider::Execute_GetAlertnessNormalized(Provider);
    }

    return 0.0f;
}
