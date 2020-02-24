#include "Audio.h"
#include <iostream>
Audio::~Audio()
{
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);
}

void Audio::load(const char* filename)
{
	SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);
	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

void Audio::play()
{
	if (SDL_GetQueuedAudioSize(deviceId) == 0)
	{
		SDL_QueueAudio(deviceId, wavBuffer, wavLength);
		SDL_PauseAudioDevice(deviceId, 0);
	}
}

void Audio::stop()
{
	SDL_PauseAudioDevice(deviceId, 1);
	SDL_ClearQueuedAudio(deviceId);
}
