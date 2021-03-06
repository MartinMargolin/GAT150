#pragma once

#include <fmod.hpp>

namespace smile
{
	class AudioChannel
	{
	public:
		AudioChannel() {}
		AudioChannel(FMOD::Channel* channel) : channel{ channel } {}

		bool isPlaying();
		void Stop();

		void SetPitch(float pitch);
		float GetPitch();

		void SetVolume(float volume);
		float GetVolume();
	private: 
		FMOD::Channel* channel{ nullptr };
	};
}