// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GASAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class GAS_API UGASAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

    UGASAttributeSet();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
        FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UGASAttributeSet, Health);

    UFUNCTION()
        virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);




    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackPower)
        FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(UGASAttributeSet, AttackPower);

    UFUNCTION()
        virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);



    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
        FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS(UGASAttributeSet, Stamina);

    UFUNCTION()
        virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);






    //-------------------------------------------------------------------------------------------\
    // Attribute Set Overrides.
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    // Set Attributes to replicate.
    //virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // Holds the current value for Stamina.
    UPROPERTY(BlueprintReadOnly, Category = "Stamina Attribute Set", ReplicatedUsing = OnRep_CurrentStamina)
        FGameplayAttributeData CurrentStamina;
    ATTRIBUTE_ACCESSORS(UGASAttributeSet, CurrentStamina)

        // Holds the value for Maximum Stamina.
        UPROPERTY(BlueprintReadOnly, Category = "Stamina Attribute Set", ReplicatedUsing = OnRep_MaximumStamina)
        FGameplayAttributeData MaximumStamina;
    ATTRIBUTE_ACCESSORS(UGASAttributeSet, MaximumStamina)

        // Holds the current value for Stamina Regeneration.
        UPROPERTY(BlueprintReadOnly, Category = "Stamina Attribute Set", ReplicatedUsing = OnRep_StaminaRegeneration)
        FGameplayAttributeData StaminaRegeneration;
    ATTRIBUTE_ACCESSORS(UGASAttributeSet, StaminaRegeneration)



protected:

    void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const;

    UFUNCTION()
        virtual void OnRep_CurrentStamina(const FGameplayAttributeData& OldValue);

    UFUNCTION()
        virtual void OnRep_MaximumStamina(const FGameplayAttributeData& OldValue);

    UFUNCTION()
        virtual void OnRep_StaminaRegeneration(const FGameplayAttributeData& OldValue);
};
