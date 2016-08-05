#pragma once
#include "Engine.h"

class Music
{
public:
	static Music* getInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new Music();
		}
		
		return _instance;
	}

	void Play() { Mix_PlayMusic(music, 1); }
	void Stop() { Mix_HaltMusic(); }
	void ChangeMusic(const char* path) { music = Mix_LoadMUS(path); }

private:
	Music();
	~Music();

	static Music* _instance;
	
	Mix_Music *music = NULL;
};

