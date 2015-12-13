// Josh Kay 2015

#include "BorderSecurity.h"
#include "BorderSecurityPlayerController.h"
#include "UI/HUD/BorderSecurityHUD.h"
#include "GuardCharacter.h"

// Sets default values
AGuardCharacter::AGuardCharacter()
	: Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Cameraboom"));
	CameraBoom->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));
	CameraBoom->AttachTo(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(CameraBoom);
}

// Called when the game starts or when spawned
void AGuardCharacter::BeginPlay()
{
	Super::BeginPlay();

	LoadTowers();
}

// Called every frame
void AGuardCharacter::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

	UpdateRotation();
}

void AGuardCharacter::Destroyed()
{
	Super::Destroyed();

	UGameplayStatics::OpenLevel(this, TEXT("/Game/Maps/MainMenu"), false, FString());
}

// Called to bind functionality to input
void AGuardCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	//InputComponent->BindAxis(TEXT("TurnRight"), this, &ABorderSecurityCharacter::TurnRight);
	InputComponent->BindAction(TEXT("SelectWeapon1"), IE_Released, this, &AGuardCharacter::SelectWeapon1);
	InputComponent->BindAction(TEXT("SelectWeapon2"), IE_Released, this, &AGuardCharacter::SelectWeapon2);
	InputComponent->BindAction(TEXT("SelectWeapon3"), IE_Released, this, &AGuardCharacter::SelectWeapon3);
	InputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AGuardCharacter::StartFire);
	InputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AGuardCharacter::StopFire);
	InputComponent->BindAction(TEXT("MoveLeft"), IE_Released, this, &AGuardCharacter::MoveLeft);
	InputComponent->BindAction(TEXT("MoveRight"), IE_Released, this, &AGuardCharacter::MoveRight);
}

void AGuardCharacter::UpdateRotation()
{
	float RotationScale = GetRotationFromMouse();
	if (RotationScale != 0.f)
	{
		TurnRight(RotationScale);
	}

	ABorderSecurityPlayerController* PlayerController = Cast<ABorderSecurityPlayerController>(GetController());
	if (PlayerController)
	{
		FHitResult Hit;
		if (PlayerController->GetHitResultUnderCursor(ECC_Camera, false, Hit))
		{
			CurrentRotation = (Hit.ImpactPoint - GetMesh()->GetComponentLocation()).Rotation();

			FRotator Rotation = FRotator::ZeroRotator;
			Rotation.Yaw = CurrentRotation.Yaw - 90.f;
			GetMesh()->SetWorldRotation(Rotation);
		}
	}
}

void AGuardCharacter::TurnRight(float Scale)
{
	ABorderSecurityPlayerController* PlayerController = Cast<ABorderSecurityPlayerController>(GetController());
	if (PlayerController)
	{
		// Do not let actor rotate past max/min bounds
		if ((GetActorRotation().Yaw + (Scale * PlayerController->InputYawScale) + 180.f < MaxRightTurn + 180.f) && Scale > 0.f ||
			(GetActorRotation().Yaw - (Scale * PlayerController->InputYawScale) + 180.f > MaxLeftTurn + 180.f) && Scale < 0.f)
		{
			AddControllerYawInput(Scale);
			TurnSpeed = Scale;
		}
		else
		{
			TurnSpeed = 0.f;
		}
	}
}

void AGuardCharacter::StartFire()
{
	Super::StartFire();
}

void AGuardCharacter::StopFire()
{
	Super::StopFire();
}

float AGuardCharacter::GetRotationFromMouse()
{
	ABorderSecurityPlayerController* PlayerController = Cast<ABorderSecurityPlayerController>(GetController());
	if (PlayerController)
	{
		float MouseX;
		float MouseY;

		PlayerController->GetMousePosition(MouseX, MouseY);

		float TurnX = (FVector2D(MouseX, MouseY) / FVector2D(GEngine->GameViewport->Viewport->GetSizeXY())).X;

		// check if cursor is on side
		if (TurnX >= 0.f && TurnX <= ScreenTurnArea)
		{
			return (TurnX - ScreenTurnArea) / ScreenTurnArea;
		}
		else if (TurnX >= 1 - ScreenTurnArea)
		{
			return 1 - (1 - TurnX - ScreenTurnArea) / ScreenTurnArea - 1;
		}
	}

	return 0.f;
}

void AGuardCharacter::LoadTowers()
{
	for (TActorIterator<ABorderTower> BorderActorItr(GetWorld()); BorderActorItr; ++BorderActorItr)
	{
		ABorderTower* BorderItem = *BorderActorItr;
		if (BorderItem)
		{
			BorderTowers.Add(BorderItem);
		}
	}

	BorderTowers.Sort([](const ABorderTower& BorderItem1, const ABorderTower& BorderItem2) {
		return BorderItem1.GetActorLocation().X > BorderItem2.GetActorLocation().X;
	});

	TowerUsed = 2;
}

void AGuardCharacter::MoveLeft()
{
	int32 NextTower = TowerUsed - 1;
	if (BorderTowers.IsValidIndex(NextTower))
	{
		TowerUsed = NextTower;
		if (BorderTowers[NextTower]->IsValidLowLevel() && BorderTowers[NextTower]->GetHealthComponent()->IsAlive())
		{
			SetActorLocation(BorderTowers[NextTower]->GetPlayerLocation());
		}
		else
		{
			MoveLeft();
		}
	}

}

void AGuardCharacter::MoveRight()
{
	int32 NextTower = TowerUsed + 1;
	if (BorderTowers.IsValidIndex(NextTower))
	{
		TowerUsed = NextTower;
		if (BorderTowers[NextTower]->IsValidLowLevel() && BorderTowers[NextTower]->GetHealthComponent()->IsAlive())
		{
			SetActorLocation(BorderTowers[NextTower]->GetPlayerLocation());
		}
		else
		{
			MoveRight();
		}
	}
}

void AGuardCharacter::WeaponInitialized(AWeapon* Weapon)
{
	Super::WeaponInitialized(Weapon);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		ABorderSecurityHUD* HUD = Cast<ABorderSecurityHUD>(PlayerController->GetHUD());
		if (HUD)
		{
			HUD->AddWeapon(Weapon);
		}
	}
}

void AGuardCharacter::SelectWeapon1()
{
	SelectWeaponIndex(0);
}

void AGuardCharacter::SelectWeapon2()
{
	SelectWeaponIndex(1);
}

void AGuardCharacter::SelectWeapon3()
{
	SelectWeaponIndex(2);
}