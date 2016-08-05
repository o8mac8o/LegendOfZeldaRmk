#include "Music.h"

Music* Music::_instance = nullptr;

Music::Music()
{
	music = Mix_LoadMUS("Ressources/Sounds/Themes/Title.wav");
}


Music::~Music()
{
	Mix_FreeMusic(music);
	music = NULL;
}
