// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/SpawnProjectile.h"

#include "Character/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"

void USpawnProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ABaseCharacter* Player = Cast<ABaseCharacter>(MeshComp->GetOwner()))
		{
			//Character spawns
			Player->SpawnProjectile(SocketName, ProjectileClass);
			
		}
	}
}
