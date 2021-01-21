// ShootThemUp Game. All rights reserved.

#pragma once
#include "GameFramework/SpringArmComponent.h"

class UCameraComponent;

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="SpringArmComponent")
    USpringArmComponent* SpringArmComponent;
    
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category="Movement")
    bool IsRunning() const;
    
    UFUNCTION(BlueprintCallable, Category="Movement")
    float GetMovementDirection() const;
    
private:
    bool WantsToRun = false;
    bool IsMovingForward = false;
    
    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void OnStartRunning();
    void OnStopRunning();
};
