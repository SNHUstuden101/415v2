// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcMechFromStatic.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
AProcMechFromStatic::AProcMechFromStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Proc Mesh");// Initialize the Procedural Mesh Component
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");// Initialize the Static Mesh Component

	//procMesh->SetupAttachment(GetRootComponent()); // Attach procedural mesh to root
	RootComponent = procMesh; // Set procedural mesh as root component
	baseMesh->SetupAttachment(procMesh); // Attach static mesh to procedural mesh
}

// Called when the game starts or when spawned
void AProcMechFromStatic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProcMechFromStatic::PostActorCreated()
{
	Super::PostActorCreated();
	GetMeshData();
}

void AProcMechFromStatic::PostLoad()
{
	Super::PostLoad();
	GetMeshData();
}

void AProcMechFromStatic::GetMeshData()
{
	UStaticMesh* mesh = baseMesh->GetStaticMesh(); // get the static mesh from the static mesh component
	if (mesh) // if there is a valid static mesh
	{
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(mesh, 0, 0, Vertices, Triangles, Normals, UV0, Tangents); // gather mesh data from LOD 0, section 0
		procMesh->UpdateMeshSection(0, Vertices, Normals, UV0, UpVertexColors, Tangents); // update the procedural mesh section with gathered data
		CreateMesh(); // create the procedural mesh
	}
}

void AProcMechFromStatic::CreateMesh() // create procedural mesh from gathered data
{
	if (baseMesh) // if there is a valid static mesh component
	{
		procMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, UpVertexColors, Tangents, true);// Create the mesh section with the provided vertices and triangles true is for generating collisions
	}
}
// Called every frame
void AProcMechFromStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

