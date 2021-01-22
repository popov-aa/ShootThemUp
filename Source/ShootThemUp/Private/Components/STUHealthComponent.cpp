// ShootThemUp Game. All rights reserved.

#include "Components/STUHealthComponent.h"

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float USTUHealthComponent::GetHealth() const
{
    return this->Health;
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	this->Health = this->MaxHealth;
}
