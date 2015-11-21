// Josh Kay 2015

#include "BorderSecurity.h"
#include "MinionAIController.h"
#include "MinionCharacter.h"

AMinionCharacter::AMinionCharacter()
{
	AIControllerClass = AMinionAIController::StaticClass();
}