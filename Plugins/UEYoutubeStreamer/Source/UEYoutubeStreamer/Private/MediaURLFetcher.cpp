// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaURLFetcher.h"
#include <iostream>
#include <cstdio>
#include <memory>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

std::string execCommand(const std::string& command) {
    std::string result;
    char buffer[128];

    // Open a pipe to execute the command
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        UE_LOG(LogTemp, Error, TEXT("Failed to open pipe"));
        return "";
    }

    // Read the output
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    // Close the pipe
    pclose(pipe);

    return result;
}

// Sets default values
AMediaURLFetcher::AMediaURLFetcher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMediaURLFetcher::BeginPlay()
{
	Super::BeginPlay();
	
    std::string command = "yt-dlp -f best -g " + std::string(TCHAR_TO_UTF8(*InVideoURL));
    std::string output = execCommand(command);

    if (!output.empty())
    {
        OutVideoURL = FString(output.c_str()); // Convert std::string to FString
        UE_LOG(LogTemp, Warning, TEXT("Direct Video URL: %s"), *OutVideoURL);
        OnFetchedURL.Broadcast(OutVideoURL);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to retrieve video URL."));
    }
}

// Called every frame
void AMediaURLFetcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

