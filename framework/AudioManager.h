#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H
#include "AssetManager.h"

namespace EasySDL
{
	class AudioManager
	{
	public:
	
		static AudioManager* Instance();
		static void Release();
	
		void PlayMusic(std::string filename, int loops = -1);
		void PauseMusic();
		void ResumeMusic();
		bool IsMusicPaused();
	
		void PlaySFX(std::string filename, int loops = 0, int channel = 0);
	
	private:
	
		static AudioManager* sInstance;
		AssetManager* mAssetMgr;
	
		AudioManager();
		~AudioManager();
	};
}

#endif // _AUDIOMANAGER_H
