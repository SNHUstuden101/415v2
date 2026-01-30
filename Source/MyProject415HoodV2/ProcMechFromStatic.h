// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProcMechFromStatic.generated.h"

UCLASS()
class MYPROJECT415HOODV2_API AProcMechFromStatic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcMechFromStatic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostActorCreated() override; // called when actor is created

	virtual void PostLoad() override; // called when actor is loaded

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	TArray<FVector> Vertices; // vertex positions
	UPROPERTY()
	TArray<int> Triangles; // triangle indices
	UPROPERTY()
	TArray<FVector> Normals;
	//UPROPERTY()
	TArray<FVector2D> UV0;
	UPROPERTY()
	TArray<FLinearColor> VertexColors; // colors

	TArray<FColor> UpVertexColors;

	TArray<FProcMeshTangent> Tangents; // tangents

	UPROPERTY(EditAnywhere) // static mesh to copy from
		UStaticMeshComponent* baseMesh; // static mesh component to copy mesh data from

private:
	UProceduralMeshComponent* procMesh; // procedural mesh component to create mesh on	
	void GetMeshData(); // gather vertex, triangle, normal, uv, color data from static mesh
	void CreateMesh(); // create procedural mesh from gathered data
};
