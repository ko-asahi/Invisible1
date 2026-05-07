#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "KeyCardPickup.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class APawn;

UCLASS(Blueprintable)
class INVISIBLE_API AKeyCardPickup : public AActor
{
	GENERATED_BODY()

public:
	AKeyCardPickup();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> KeyCardMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> PickupSphere;

	// 拾取后写入玩家 PlayerState 的钥匙卡 Tag。
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KeyCard", meta = (Categories = "KeyCard"))
	FGameplayTag KeyCardTag;

	// 成功拾取后是否销毁 Actor。关闭时会隐藏并禁用碰撞，方便蓝图播放延迟特效。
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KeyCard")
	bool bDestroyOnPickup = true;

	UFUNCTION()
	void HandlePickupSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent, Category = "KeyCard")
	void BP_OnPickedUp(APawn* PickingPawn, FGameplayTag PickedKeyCardTag);

private:
	bool bPickedUp = false;

	bool TryGiveKeyCardToPawn(APawn* Pawn);
};
