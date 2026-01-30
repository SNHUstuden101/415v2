// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProcPlane.generated.h"

class UProceduralMeshComponent; // Forward declaration if needed

UCLASS()
class MYPROJECT415HOODV2_API AProcPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostActorCreated() override;

	virtual void PostLoad() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) //	or UPROPERTY(VisibleAnywhere) based on your needs
		TArray<FVector> Vertices; // Array of vertex positions

	UPROPERTY(EditAnywhere) //	or UPROPERTY(VisibleAnywhere) based on your needs
		TArray<int> Triangles; // Indices for triangles

	UPROPERTY(EditAnywhere)
		TArray<FVector2D> UV0; // UV coordinates

	UPROPERTY(EditAnywhere)
		UMaterialInterface* PlaneMat; // Material for the plane

	UFUNCTION()
		void CreateMesh();// Function to create the mesh

private:
	UProceduralMeshComponent* procMesh; // Procedural Mesh Component
};
