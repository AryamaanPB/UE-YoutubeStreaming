// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StreamingTest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnURLFetched, FString, RawVideoURL);

UCLASS()
class UEYOUTUBESTREAMER_API AStreamingTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStreamingTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, Category = "UEYoutubeStreaming")
	FString InVideoURL;

	UPROPERTY(BlueprintReadWrite, Category = "UEYoutubeStreaming")
	FString OutVideoURL;

	UPROPERTY(BlueprintAssignable, Category = "UEYoutubeStreaming")
	FOnURLFetched OnFetchedURL;
};
