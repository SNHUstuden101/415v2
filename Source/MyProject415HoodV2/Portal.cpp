// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h" // Include the header file for the portal class to implement its functions
#include "MyProject415HoodV2Character.h" // Include the header file for the player character class to access its properties and functions
#include "Kismet/GameplayStatics.h" // Include the GameplayStatics header to access functions for getting the player's camera manager and other utility functions

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // Enable ticking for this actor
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh"); // Initialize the static mesh component
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp"); // Initialize the box component
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture"); // Initialize the scene capture component
	rootArrow = CreateDefaultSubobject<UArrowComponent>("Root Arrow");	// Initialize the arrow component

	RootComponent = boxComp; // Set the box component as the root component of the actor
	mesh->SetupAttachment(boxComp); // Attach the mesh to the box component
	sceneCapture->SetupAttachment(mesh); // Attach the scene capture to the mesh component
	rootArrow->SetupAttachment(RootComponent); // Attach the arrow to the root component

	mesh->SetCollisionResponseToAllChannels(ECR_Ignore); // Set the collision response of the mesh to ignore all channels so that it doesn't interfere with the player's movement

}

// Called when the game starts or when spawned
void APortal::BeginPlay() // Override the BeginPlay function to bind the overlap event and set the material of the portal mesh
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin); //Bind the overlap event to the OnOverlapBegin function
	mesh->SetHiddenInSceneCapture(true); // Set the mesh to be hidden in the scene capture so that it doesn't render itself in the portal view


	if (mat) // If a material is assigned to the portal, set it to the mesh
	{
		mesh->SetMaterial(0, mat); // Set the material of the mesh to the assigned material
	}
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePortals(); // Call the UpdatePortals function every frame to update the position and rotation of the scene capture component based on the player's camera and the location of the other portal
}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) // This function is called when the player enters the box component of the portal, and it teleports the player to the location of the other portal if they are not already teleporting
{
	AMyProject415HoodV2Character* playerChar = Cast<AMyProject415HoodV2Character>(OtherActor); // Cast the other actor to the player character class to check if it's the player who entered the portal

	if (playerChar) // If the cast is successful, it means the player entered the portal
	{
		if (OtherPortal) // Check if the other portal reference is valid before trying to teleport the player
		{
			if (!playerChar->isTeleporting) // Check if the player is not already teleporting to prevent multiple teleports in quick succession
			{
				playerChar->isTeleporting = true; // Set the flag to prevent multiple teleports
				FVector loc = OtherPortal->rootArrow->GetComponentLocation(); // Get the location of the other portal's arrow component to use as the teleport destination
				playerChar->SetActorLocation(loc); // Teleport the player to the other portal's location

				FTimerHandle TimerHandle; // Create a timer handle to manage the timer for resetting the teleporting flag
				FTimerDelegate TimerDelegate; //	Create a timer delegate to bind the function that will reset the teleporting flag after a short delay
				TimerDelegate.BindUFunction(this, "SetBool", playerChar); // Bind the SetBool function to the timer delegate, passing the player character as a parameter
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false); // Set a timer to reset the teleporting flag after 0.5 seconds

			}
		}
	}


}

void APortal::SetBool(AMyProject415HoodV2Character* playerChar)
{
	if (playerChar)
	{
		playerChar->isTeleporting = false; // Reset the flag to allow future teleports
	}
}

void APortal::UpdatePortals()
{
	FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation(); // Get the location of the other portal relative to this portal
	FVector camLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation(); // Get the location of the player's camera
	FRotator camRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation(); // Get the rotation of the player's camera
	FVector CombinedLocation = camLocation + Location; // Combine the location of the other portal with the camera location to get the new location for the scene capture component
}

