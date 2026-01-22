// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Cube_DMI.generated.h"

class UNiagaraSystem; //Forward declaration of Niagara system

UCLASS()
class MYPROJECT415HOODV2_API ACube_DMI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACube_DMI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
		UBoxComponent* boxComp; //Box collision component

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* cubeMesh;//Cube mesh component

	UPROPERTY(EditAnywhere)
		UMaterialInterface* baseMat; //Base material to create dynamic instance from

	UPROPERTY(EditAnywhere)
		UMaterialInstanceDynamic* dmimat; //Dynamic material instance

	UPROPERTY(EditAnywhere) //Niagara particle system for splash effect
		UNiagaraSystem* colorP; //Niagara particle system for color splash effect

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

