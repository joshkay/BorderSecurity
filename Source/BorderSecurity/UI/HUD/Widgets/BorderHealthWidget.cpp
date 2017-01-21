// Josh Kay 2015

#include "BorderSecurity.h"
#include "Environment/BorderItem.h"
#include "BorderHealthWidget.h"

void UBorderHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<ABorderItem*> BorderItems;
	for (TActorIterator<ABorderItem> BorderActorItr(GetWorld()); BorderActorItr; ++BorderActorItr)
	{
		ABorderItem* BorderItem = *BorderActorItr;
		if (BorderItem)
		{
			BorderItems.Add(BorderItem);
		}
	}

	BorderItems.Sort([](const ABorderItem& BorderItem1, const ABorderItem& BorderItem2) {
		return BorderItem1.GetActorLocation().X > BorderItem2.GetActorLocation().X;
	});

	for (ABorderItem* BorderItem : BorderItems)
	{
		UBorderItemWidget* BorderItemWidget = NewObject<UBorderItemWidget>(this, BorderItemClass);
		BorderItemWidget->SetOwner(BorderItem);

		UHorizontalBoxSlot* HorizontalSlot = Cast<UHorizontalBoxSlot>(GetHorizontalBox()->AddChild(BorderItemWidget));
		HorizontalSlot->SetHorizontalAlignment(HAlign_Fill);
		HorizontalSlot->SetVerticalAlignment(VAlign_Bottom);
	}
}