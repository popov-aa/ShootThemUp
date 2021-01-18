// ShootThemUp Game. All rights reserved.


#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"

ASTUGameModeBase::ASTUGameModeBase()
{
    this->DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    this->PlayerControllerClass = ASTUPlayerController::StaticClass();
}
