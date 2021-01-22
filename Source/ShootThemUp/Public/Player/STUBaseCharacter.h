// ShootThemUp Game. All rights reserved.

#pragma once
#include "Components/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
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
	ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="SpringArmComponent")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USTUHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UTextRenderComponent* HealthTextComponent;
    
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

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
