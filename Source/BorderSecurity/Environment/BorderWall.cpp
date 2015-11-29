// Josh Kay 2015

#include "BorderSecurity.h"
#include "BorderWall.h"

ABorderWall::ABorderWall(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UBoxComponent>(TEXT("ColliderComponent")))
{

}