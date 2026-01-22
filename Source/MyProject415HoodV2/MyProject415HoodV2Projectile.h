// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProject415HoodV2Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem; //Forward declaration of Niagara system

UCLASS(config=Game)
class AMyProject415HoodV2Projectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
		USphereComponent* CollisionComp; //Sphere collision component

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement; //Projectile movement component

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ballMesh; //Static mesh component for the projectile

	UPROPERTY(EditAnywhere) //Base material for the projectile
		UMaterial* baseMat;

	//UPROPERTY(EditAnywhere)
	//UMaterialInstanceDynamic* splatmat;

	UPROPERTY(EditAnywhere)
		FLinearColor randColor; //Random color for the projectile

	UPROPERTY(EditAnywhere)
		UMaterialInterface* projMat; //Material for the projectile

	UPROPERTY()
		UMaterialInstanceDynamic* dmiMat; //Dynamic material instance for the projectile

	UPROPERTY(EditAnywhere) //Niagara particle system for splash effect
		UNiagaraSystem* colorP; //Niagara particle system for color splash effect

public:
	AMyProject415HoodV2Projectile();

protected:
	virtual void BeginPlay(); // Called when the game starts or when spawned

public:
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit); //Function to handle hit event

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

