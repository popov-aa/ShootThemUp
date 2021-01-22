// ShootThemUp Game. All rights reserved.

#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/STUCharacterMovementComponent.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    this->SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    this->SpringArmComponent->SetupAttachment(this->GetRootComponent());
    this->SpringArmComponent->bUsePawnControlRotation = true;
    
    this->CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    this->CameraComponent->SetupAttachment(this->SpringArmComponent);

    this->HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

    this->HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    this->HealthTextComponent->SetupAttachment(this->GetRootComponent());
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(this->HealthComponent);
    check(this->HealthTextComponent);
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    this->HealthTextComponent->SetText(FText::FromString(FString::SanitizeFloat(this->HealthComponent->GetHealth()))); 
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (PlayerInputComponent)
    {
        PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
        PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
        PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
        PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);
        PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
        PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::OnStartRunning);
        PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::OnStopRunning);
    }
}

bool ASTUBaseCharacter::IsRunning() const
{
    return this->WantsToRun && this->IsMovingForward && !this->GetVelocity().IsZero();
}

float ASTUBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
    {
        return 0;
    }
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween); 
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTUBaseCharacter::MoveForward(float Amount)
{
    this->IsMovingForward = Amount > 0.0f;
    if (Amount != 0.0f)
    {
        this->AddMovementInput(this->GetActorForwardVector(), Amount);        
    }
}

void ASTUBaseCharacter::MoveRight(float Amount)
{
    if (Amount != 0.0f)
    {
        this->AddMovementInput(this->GetActorRightVector(), Amount);        
    }
}

void ASTUBaseCharacter::OnStartRunning()
{
    WantsToRun = true;
}

void ASTUBaseCharacter::OnStopRunning()
{
    WantsToRun = false;
}
