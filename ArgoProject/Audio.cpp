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

	std::cout << filename << std::endl;
	std::cout << wavBuffer << std::endl;
	std::cout << wavLength << std::endl;

	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

void Audio::play()
{
	std::cout << SDL_GetQueuedAudioSize(deviceId) << std::endl;
	if (SDL_GetQueuedAudioSize(deviceId) == 0)
	{
		SDL_QueueAudio(deviceId, wavBuffer, wavLength);
		SDL_PauseAudioDevice(deviceId, 0);
		std::cout << SDL_GetQueuedAudioSize(deviceId) << std::endl;
	}
}

void Audio::stop()
{
	SDL_PauseAudioDevice(deviceId, 1);
	SDL_ClearQueuedAudio(deviceId);
}
