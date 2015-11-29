// Josh Kay 2015

#include "BorderSecurity.h"
#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	HP = MaxHP;
	Armor = MaxArmor;
}

void UHealthComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (bRegenHP)
	{
		UpdateHPRegen(DeltaTime);
	}
	if (bRegenArmor)
	{
		UpdateArmorRegen(DeltaTime);
	}
}

void UHealthComponent::TakeDamage(float Damage)
{
	if (Armor > 0.f)
	{
		Damage = ApplyDamageToArmor(Damage);
	}

	if (HP > 0.f)
	{
		ApplyDamageToHP(Damage);
	}

	CancelRegen();
	StartRegenTimers();
}

float UHealthComponent::ApplyDamageToArmor(float Damage)
{
	float RemainingDamage = FMath::Max(Damage - Armor, 0.f);

	Armor = FMath::Max(Armor - Damage, 0.f);

	return RemainingDamage;
}

void UHealthComponent::ApplyDamageToHP(float Damage)
{
	HP = FMath::Max(HP - Damage, 0.f);
}

void UHealthComponent::StartRegenTimers()
{
	switch (RegenType)
	{
	case ERegenType::RT_ArmorBeforeHealth:
		StartRegenArmorThenHealth();
		break;
	case ERegenType::RT_HealthBeforeArmor:
		StartRegenHealthThenArmor();
		break;
	case ERegenType::RT_HealthAndArmor:
		StartRegenArmorAndHealth();
		break;
	}
}

void UHealthComponent::StartRegenArmorThenHealth()
{
	if (Armor < MaxArmor)
	{
		GetWorld()->GetTimerManager().SetTimer(ArmorRegenTimer, this, &UHealthComponent::StartArmorRegen, ArmorRegenTimeAfterDamage, false);
	}
	else if (HP < MaxHP)
	{
		GetWorld()->GetTimerManager().SetTimer(HPRegenTimer, this, &UHealthComponent::StartHPRegen, HPRegenTimeAfterDamage, false);
	}
}

void UHealthComponent::StartRegenHealthThenArmor()
{
	if (HP < MaxHP)
	{
		GetWorld()->GetTimerManager().SetTimer(HPRegenTimer, this, &UHealthComponent::StartHPRegen, HPRegenTimeAfterDamage, false);
	}
	else if (Armor < MaxArmor)
	{
		GetWorld()->GetTimerManager().SetTimer(ArmorRegenTimer, this, &UHealthComponent::StartArmorRegen, ArmorRegenTimeAfterDamage, false);
	}
}

void UHealthComponent::StartRegenArmorAndHealth()
{
	if (Armor < MaxArmor)
	{
		GetWorld()->GetTimerManager().SetTimer(ArmorRegenTimer, this, &UHealthComponent::StartArmorRegen, ArmorRegenTimeAfterDamage, false);
	}
	if (HP < MaxHP)
	{
		GetWorld()->GetTimerManager().SetTimer(HPRegenTimer, this, &UHealthComponent::StartHPRegen, HPRegenTimeAfterDamage, false);
	}
}

void UHealthComponent::StartArmorRegen()
{
	bRegenArmor = true;
}

void UHealthComponent::StartHPRegen()
{
	bRegenHP = true;
}

void UHealthComponent::CancelRegen()
{
	bRegenHP = false;
	bRegenArmor = false;
}

void UHealthComponent::HPRegenerated()
{
	bRegenArmor = false;

	if (RegenType == ERegenType::RT_HealthBeforeArmor)
	{
		StartRegenHealthThenArmor();
	}
}

void UHealthComponent::ArmorRegenerated()
{
	bRegenHP = false;

	if (RegenType == ERegenType::RT_ArmorBeforeHealth)
	{
		StartRegenArmorThenHealth();
	}
}

void UHealthComponent::UpdateArmorRegen(float DeltaTime)
{
	float RegenAmount = ArmorRegenAmount * DeltaTime;

	Armor = FMath::Min(Armor + RegenAmount, MaxArmor);

	if (Armor == MaxArmor)
	{
		ArmorRegenerated();
	}
}

void UHealthComponent::UpdateHPRegen(float DeltaTime)
{
	float RegenAmount = HPRegenAmount * DeltaTime;

	HP = FMath::Min(HP + RegenAmount, MaxHP);

	if (HP == MaxHP)
	{
		HPRegenerated();
	}
}