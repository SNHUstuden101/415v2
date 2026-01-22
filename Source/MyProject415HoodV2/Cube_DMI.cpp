// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube_DMI.h"
#include "MyProject415HoodV2Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h" //Essential for spawning Niagara particle systems
#include "NiagaraComponent.h" //Required for UNiagaraComponent (to interact with spawned Niagara systems)

// Sets default values
ACube_DMI::ACube_DMI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box COmponent"));
	cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));

	RootComponent = boxComp;
	cubeMesh->SetupAttachment(boxComp);

}

// Called when the game starts or when spawned
void ACube_DMI::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACube_DMI::OnOverlapBegin); //Bind the overlap event to the OnOverlapBegin function

	if (baseMat) //Check to make sure the base material is assigned
	{
		dmimat = UMaterialInstanceDynamic::Create(baseMat, this); //Create the dynamic material instance from the base material
	}

	if (cubeMesh) //Check to make sure the mesh component is valid
	{
		cubeMesh->SetMaterial(0, dmimat); //Set the dynamic material instance to the cube mesh
	}
}
	

// Called every frame
void ACube_DMI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACube_DMI::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyProject415HoodV2Character* overlappedActor = Cast<AMyProject415HoodV2Character>(OtherActor);

	if (overlappedActor)
	{
		float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f); //Generate random float between 0 and 1
		float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);
		float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.0f, 1.0f);

		FLinearColor randColor = FLinearColor(ranNumX, ranNumY, ranNumZ, 1.0f); //Generate a random color
		if (dmimat) 
		{
			dmimat->SetVectorParameterValue("Color", randColor);
			dmimat->SetScalarParameterValue("Darkness", ranNumX);
			dmimat->SetScalarParameterValue("Opacity", ranNumX);

			if (colorP) //Check to make sure the Niagara system is assigned
			{
				UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, OtherComp, NAME_None, FVector(0.0f), FRotator(0.0f), EAttachLocation::KeepRelativeOffset, true); //Spawn the Niagara particle system at the location of the overlap
				particleComp->SetNiagaraVariableLinearColor(FString("Randolor"), randColor); //Set the color parameter in the Niagara system Randolor is the name of the color parameter inside the Niagara system
			}
		}
	}
}

