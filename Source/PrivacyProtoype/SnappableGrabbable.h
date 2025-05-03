#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnappableGrabbable.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class PRIVACYPROTOYPE_API ASnappableGrabbable : public AActor
{
    GENERATED_BODY()

public:
    ASnappableGrabbable();

    virtual void BeginPlay() override;

    UFUNCTION()
    void OnGrabReleased();

protected:
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void SnapToTarget();

    UPROPERTY()
    UStaticMeshComponent* Mesh;

    UPROPERTY()
    UBoxComponent* CollisionBox;

    UPROPERTY()
    AActor* SnapTarget;

    float OriginalYaw;
    bool bIsOverlappingSnapZone;
};
