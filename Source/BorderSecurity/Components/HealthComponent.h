// Josh Kay 2015

#pragma once

#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UENUM(BlueprintType)
enum class ERegenType : uint8
{
	RT_HealthBeforeArmor	UMETA(DisplayName = "Health Before Armor"),
	RT_ArmorBeforeHealth	UMETA(DisplayName = "Armor Before Health"),
	RT_HealthAndArmor		UMETA(DisplayName = "Health and Armor")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BORDERSECURITY_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TakeDamage(float Damage);

public:
	FORCEINLINE bool IsAlive() { return HP > 0.f; }

	FORCEINLINE bool HasArmor() { return MaxArmor > 0.f && Armor > 0.f; }

	FORCEINLINE float GetHP() { return HP; }
	FORCEINLINE float GetArmor() { return Armor; }

	FORCEINLINE float GetMaxHP() { return MaxHP; }
	FORCEINLINE float GetMaxArmor() { return MaxArmor; }

	FORCEINLINE float GetHPPercent() { return HP / MaxHP; }
	FORCEINLINE float GetArmorPercent() { return Armor / MaxArmor; }

protected:
	// Apply damage to armor, returns remaining damage that armor didn't absorb
	float ApplyDamageToArmor(float Damage);
	void ApplyDamageToHP(float Damage);

	void StartRegenTimers();
	void StartRegenArmorThenHealth();
	void StartRegenHealthThenArmor();
	void StartRegenArmorAndHealth();

	void StartArmorRegen();
	void StartHPRegen();

	void CancelRegen();

	void HPRegenerated();
	void ArmorRegenerated();

	void UpdateArmorRegen(float DeltaTime);
	void UpdateHPRegen(float DeltaTime);

protected:
	// HP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HP)
	float MaxHP;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HP)
	//float HPRegenSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HP)
	float HPRegenAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HP)
	float HPRegenTimeAfterDamage;

	float HP;
	bool bRegenHP;

	FTimerHandle HPRegenTimer;

	// Armor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
	float MaxArmor;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
	//float ArmorRegenSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
	float ArmorRegenAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor)
	float ArmorRegenTimeAfterDamage;

	float Armor;
	bool bRegenArmor;

	FTimerHandle ArmorRegenTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Regeneration)
	ERegenType RegenType;
};
