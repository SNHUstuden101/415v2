// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/BoxComponent.h"
#include "MyProject415HoodV2Character.h"
#include "Components/ArrowComponent.h"
#include "Portal.generated.h"


class MyProject415HoodV2Character; // Forward declaration of the player character class

UCLASS()
class MYPROJECT415HOODV2_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

UPROPERTY(EditAnywhere) // The box component that will be used to detect when the player enters the portal
	UStaticMeshComponent* mesh;

UPROPERTY(EditAnywhere, BlueprintReadWrite) // The scene capture component that will be used to render the view from the portal
	USceneCaptureComponent2D* sceneCapture;

UPROPERTY(EditAnywhere)
UArrowComponent* rootArrow; // An arrow component to indicate the forward direction of the portal

UPROPERTY(EditAnywhere, BlueprintReadWrite) // The render target that will be used to render the view from the portal
	UTextureRenderTarget2D* renderTarget;

UPROPERTY(EditAnywhere)
	UBoxComponent* boxComp; // The box component that will be used to detect when the player enters the portal

UPROPERTY(EditAnywhere)
	APortal* OtherPortal; // A reference to the other portal that this portal is linked to

UPROPERTY(EditAnywhere)
	UMaterialInterface* mat; // The material that will be applied to the portal mesh

UFUNCTION()
void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

UFUNCTION()
void SetBool(AMyProject415HoodV2Character* playerChar); // A function to set the isTeleporting flag on the player character

UFUNCTION()
void UpdatePortals(); // A function to update the scene capture component's position and rotation to match the other portal's position and rotation, so that it renders the correct view

};
