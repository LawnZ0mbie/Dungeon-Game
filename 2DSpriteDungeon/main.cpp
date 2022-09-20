#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_audio.h"
#include "GameCore.h"
//#include <windows.h>
//#include <MMSystem.h>

using namespace DungeonGame;

int main()
{
	SDL_Init(SDL_INIT_VIDEO); //Initialize video
	SDL_Init(SDL_INIT_AUDIO); //Initializes Audio
	SDL_Window* pWindow = SDL_CreateWindow("Dungeon Game", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Surface* pSurface = SDL_LoadBMP("Assets/Icon.bmp");
	SDL_SetWindowIcon(pWindow, pSurface);

	PlayerState playerState = {};
	WorldState worldState = {};

	InializeGame(pRenderer, playerState, worldState);

	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;

	SDL_LoadWAV("Assets/music.wav", &wavSpec, &wavBuffer, &wavLength);
	SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

	int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);

	int frameStartTicks, frameEndTicks = 0;
	int deltaTicks = 0;
	float deltaSeconds = 0.0f;

	while (!playerState.HasFinishedGame)
	{
		if (deltaTicks < 1)
		{
			frameStartTicks = SDL_GetTicks();
			SDL_Delay(1);
			frameEndTicks = SDL_GetTicks();
			deltaTicks = frameEndTicks - frameStartTicks;
		}

		frameStartTicks = SDL_GetTicks();

		GetInput(playerState, worldState);

		deltaSeconds = (float)deltaTicks / 1000.0f;

		UpdateGame(deltaSeconds ,playerState, worldState);

		RenderGame(pRenderer, playerState, worldState);

		frameEndTicks = SDL_GetTicks();
	}

	CleanupGame(playerState, worldState);

	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);
	SDL_Quit();

	return 0;
}