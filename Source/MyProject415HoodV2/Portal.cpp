// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "MyProject415HoodV2Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture");
	rootArrow = CreateDefaultSubobject<UArrowComponent>("Root Arrow");

	RootComponent = boxComp;
	mesh->SetupAttachment(boxComp);
	sceneCapture->SetupAttachment(mesh);
	rootArrow->SetupAttachment(RootComponent);

	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin); //Bind the overlap event to the OnOverlapBegin function
	mesh->SetHiddenInSceneCapture(true);


	if (mat)
	{
		mesh->SetMaterial(0, mat);
	}
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePortals();
}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyProject415HoodV2Character* playerChar = Cast<AMyProject415HoodV2Character>(OtherActor);

	if (playerChar)
	{
		if (OtherPortal)
		{
			if (!playerChar->isTeleporting)
			{
				playerChar->isTeleporting = true; // Set the flag to prevent multiple teleports
				FVector loc = OtherPortal->rootArrow->GetComponentLocation();
				playerChar->SetActorLocation(loc); // Teleport the player to the other portal's location

				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUFunction(this, "SetBool", playerChar);
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

