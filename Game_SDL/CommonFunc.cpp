#include "CommonFunc.h"
void CommonFunction::loadAudio(std::string path)
{
	Mix_Chunk* sound_ = Mix_LoadWAV(path.c_str());
	if (sound_ != NULL)
		Mix_PlayChannel(-1, sound_, 0);
	else
		cout << "load audio error!";
}