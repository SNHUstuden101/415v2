// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject415HoodV2PickUpComponent.h"

UMyProject415HoodV2PickUpComponent::UMyProject415HoodV2PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UMyProject415HoodV2PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UMyProject415HoodV2PickUpComponent::OnSphereBeginOverlap);
}

void UMyProject415HoodV2PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AMyProject415HoodV2Character* Character = Cast<AMyProject415HoodV2Character>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
