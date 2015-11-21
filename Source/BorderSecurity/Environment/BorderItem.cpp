// Josh Kay 2015

#include "BorderSecurity.h"
#include "BorderItem.h"

ABorderItem::ABorderItem()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->AttachTo(RootComponent);
}