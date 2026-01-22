// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject415HoodV2Projectile.h" //Include the header file for the projectile class
#include "GameFramework/ProjectileMovementComponent.h" //Required for UProjectileMovementComponent
#include "Kismet/KismetMathLibrary.h" //Required for UKismetMathLibrary functions
#include "Components/SphereComponent.h" //Required for USphereComponent
#include "Components/DecalComponent.h" //Required for UDecalComponent
#include "Kismet/GameplayStatics.h" //Required for spawning decals
#include "NiagaraFunctionLibrary.h"//Essential for spawning Niagara particle systems
#include "NiagaraComponent.h" //Required for UNiagaraComponent (to interact with spawned Niagara systems)


AMyProject415HoodV2Projectile::AMyProject415HoodV2Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AMyProject415HoodV2Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	ballMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh")); //Create static mesh component for the projectile

	// Set as root component
	RootComponent = CollisionComp; //Set the collision component as the root component

	ballMesh->SetupAttachment(CollisionComp); //Attach the mesh to the collision component

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 2.0f;
}

void AMyProject415HoodV2Projectile::BeginPlay()
{
	Super::BeginPlay();
	randColor = FLinearColor(UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f), UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f), UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f), 1.0f);

	dmiMat = UMaterialInstanceDynamic::Create(projMat, this);//Create the dynamic material instance from the base material
	ballMesh->SetMaterial(0, dmiMat);//Set the dynamic material instance to the projectile mesh

	dmiMat->SetVectorParameterValue("ProjColor", randColor); //Set the color parameter in the projectile material
}


void AMyProject415HoodV2Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

	if (OtherActor != nullptr)
	{
		if (colorP)
		{
			UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, HitComp, NAME_None, FVector(0.0f), FRotator(0.0f), EAttachLocation::KeepRelativeOffset, true);
			particleComp->SetNiagaraVariableLinearColor(FString("Randolarr"), randColor); //Set the color parameter in the Niagara system Rabdolarr is the name of the color parameter inside the Niagara system
			ballMesh->DestroyComponent(); //Destroy the projectile mesh upon impact
			CollisionComp->BodyInstance.SetCollisionProfileName("NoCollision"); //Disable further collision to prevent multiple hits
		}
		//float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		//float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		//float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		//float frameNum = UKismetMathLibrary::RandomFloatInRange(0.0f, 3.0f);
		float frameNum = UKismetMathLibrary::RandomFloatInRange(0.0f, 3.0f); //Random frame number between 0 and 3
		//FVector4 randColor = FVector4(ranNumX, ranNumY, ranNumZ, 1.0f);

		auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), baseMat, FVector(UKismetMathLibrary::RandomFloatInRange(20.0f, 40.0f)), Hit.Location, Hit.Normal.Rotation(), 0.0f); //Spawn decal at the hit location with random size between 20 and 40 units
		auto UMaterialInstance = Decal->CreateDynamicMaterialInstance(); //Create dynamic material instance for the decal

		UMaterialInstance->SetVectorParameterValue("Color", randColor); //Set the color parameter in the decal material to the random color
		UMaterialInstance->SetScalarParameterValue("Frame", frameNum); //Set the frame parameter in the decal material to a random frame between 0 and 3

	}
}