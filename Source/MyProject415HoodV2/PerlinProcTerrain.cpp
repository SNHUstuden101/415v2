// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProcTerrain.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProcTerrain::APerlinProcTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");// Initialize the Procedural Mesh Component
	ProcMesh->SetupAttachment(RootComponent);// Attach the Procedural Mesh to the Root Component

}

// Called when the game starts or when spawned
void APerlinProcTerrain::BeginPlay()
{
	Super::BeginPlay();
	
	CreateVertices();//	Create the vertices first
	CreateTriangles();//Create the triangles after the vertices have been created
	ProcMesh->CreateMeshSection(sectionID, Vertices, Triangles, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>(), true); // Create the mesh section with the provided vertices and triangles true is for generating collisions
	ProcMesh->SetMaterial(0, Mat);// Set the material of the procedural mesh

}

// Called every frame
void APerlinProcTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APerlinProcTerrain::AlterMesh(FVector impactPoint) // Function to alter the mesh at the impact point
{
	for (int i = 0; i < Vertices.Num(); i++) // Loop through all vertices
	{
		FVector tempVector = impactPoint - this->GetActorLocation(); // Convert impact point to local space

		if (FVector(Vertices[i] - tempVector).Size() < radius) // If the vertex is within the radius
		{
			Vertices[i] = Vertices[i] - Depth; // Move the vertex down by the depth vector
			ProcMesh->UpdateMeshSection(sectionID, Vertices, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>()); // Update the mesh section with the new vertices
		}
	}
}

void APerlinProcTerrain::CreateVertices()
{
	for (int X = 0; X <= XSize; X++) // Create vertices in a grid that loops
	{
		for (int Y = 0; Y <= YSize; Y++) // Create vertices in a grid that loops
		{
			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale + 0.1, Y * NoiseScale + 0.1)) * ZMultiplier; // Get the Z value from Perlin Noise
			GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Z: %f"), Z)); // Debug message to show Z value
			Vertices.Add(FVector(X * Scale, Y * Scale, Z)); // Add vertex to array
			UV0.Add(FVector2D(X * UVscale, Y * UVscale)); // Add UV coordinates
		}
	}
}

void APerlinProcTerrain::CreateTriangles()
{
	int Vertex = 0; // Initialize vertex index

	for (int X = 0; X < XSize; X++) // Loop through X size
	{
		for (int Y = 0; Y < YSize; Y++) // Loop through Y size
		{
			Triangles.Add(Vertex); // First triangle
			Triangles.Add(Vertex + 1); // Second triangle
			Triangles.Add(Vertex + YSize + 1); // Third triangle
			Triangles.Add(Vertex + 1); // First triangle
			Triangles.Add(Vertex + YSize + 2); // Second triangle
			Triangles.Add(Vertex + YSize + 1); // Third triangle
			Vertex++; // Increment vertex index
		}
		Vertex++; // Increment vertex index at the end of each row
	}
}

