// Josh Kay 2015

#include "BorderSecurity.h"
#include "Player/BorderSecurityPlayerState.h"
#include "MoneyWidget.h"

FText UMoneyWidget::GetMoneyText() const
{
	FText Money;

	ABorderSecurityPlayerState* PlayerState = Cast<ABorderSecurityPlayerState>(GetOwningPlayer()->PlayerState);
	if (PlayerState)
	{
		Money = FText::AsNumber(PlayerState->Money);
	}

	return Money;
}