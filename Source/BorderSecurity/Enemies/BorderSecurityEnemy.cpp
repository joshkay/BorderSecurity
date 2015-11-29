// Josh Kay 2015

#include "BorderSecurity.h"
#include "Player/BorderSecurityPlayerState.h"
#include "UI/HUD/BorderSecurityHUD.h"
#include "BorderSecurityEnemy.h"

void ABorderSecurityEnemy::BeginPlay()
{
	Super::BeginPlay();

	AHUD* HUD = GetWorld()->GetFirstPlayerController()->GetHUD();
	if (HUD)
	{
		ABorderSecurityHUD* BSHUD = Cast<ABorderSecurityHUD>(HUD);
		if (BSHUD)
		{
			BSHUD->AddHealthBar(this);
		}
	}
}

void ABorderSecurityEnemy::Killed(AController* EventInstigator, AActor* DamageCauser)
{
	Super::Killed(EventInstigator, DamageCauser);

	if (EventInstigator == GetWorld()->GetFirstPlayerController() && EventInstigator->PlayerState)
	{
		ABorderSecurityPlayerState* PlayerState = Cast<ABorderSecurityPlayerState>(EventInstigator->PlayerState);
		if (PlayerState)
		{
			PlayerState->Money += MoneyValue;
		}

		AHUD* HUD = EventInstigator->CastToPlayerController()->GetHUD();
		if (HUD)
		{
			ABorderSecurityHUD* BSHUD = Cast<ABorderSecurityHUD>(HUD);
			if (BSHUD)
			{
				BSHUD->AddMoneyNotification(this, MoneyValue);
				BSHUD->RemoveHealthBar(this);
			}
		}
	}
}