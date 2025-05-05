#include "SnappableGrabbable.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ASnappableGrabbable::ASnappableGrabbable()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create and setup mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetWorldScale3D(FVector(0.00233f, 0.1627f, 0.1128f));
	Mesh->SetSimulatePhysics(true);
	

	
	// Set cube mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
	if (CubeMeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(CubeMeshAsset.Object);
	}

	// Set mirror material
	static ConstructorHelpers::FObjectFinder<UMaterial> MirrorMaterial(TEXT("Material'/Game/Joe/SimpleLasers/Materials/M_Mirror'"));
	if (MirrorMaterial.Succeeded())
	{
		Mesh->SetMaterial(0, MirrorMaterial.Object);
	}

	// Create and setup collision box
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);

	// Initialize state
	SnapTarget = nullptr;
	OriginalYaw = 0.0f;
	bIsOverlappingSnapZone = false;
}

void ASnappableGrabbable::BeginPlay()
{
	Super::BeginPlay();

	// Bind overlap events
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASnappableGrabbable::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ASnappableGrabbable::OnOverlapEnd);
}

void ASnappableGrabbable::OnGrabReleased()
{
	if (bIsOverlappingSnapZone && SnapTarget)
	{
		// Store current yaw before snapping
		FRotator CurrentRotation = GetActorRotation();
		OriginalYaw = CurrentRotation.Yaw;

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Grab released - Snapping to target"));

		SnapToTarget();
	}
}

void ASnappableGrabbable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag(TEXT("Snap")))
	{
		SnapTarget = OtherActor;
		bIsOverlappingSnapZone = true;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Entered snap zone"));
	}
}

void ASnappableGrabbable::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag(TEXT("Snap")) && OtherActor == SnapTarget)
	{
		SnapTarget = nullptr;
		bIsOverlappingSnapZone = false;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Left snap zone"));
	}
}
void ASnappableGrabbable::SnapToTarget()
{
	if (SnapTarget)
	{
		// Get target transform
		FVector TargetLocation = SnapTarget->GetActorLocation();
		FRotator TargetRotation = SnapTarget->GetActorRotation();

		// Preserve original yaw
		TargetRotation.Yaw = OriginalYaw;

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Snapping to location: %s"), *TargetLocation.ToString()));

		// Set new transform
		SetActorLocationAndRotation(TargetLocation, TargetRotation);
	}
}
