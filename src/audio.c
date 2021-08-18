#include "doom.h"

void	init_audio(t_audio *audio)
{
	audio->sound = NULL;
	audio->sound_trigger = 0;
	if( SDL_Init(SDL_INIT_AUDIO) < 0 )
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
	audio->sound = Mix_LoadWAV("resources/turning-pages-02.wav");

}

void audio_cleanup(t_audio *audio)
{
	Mix_FreeChunk(audio->sound);
	audio->sound = NULL;
}

void	audios(t_audio *audio)
{
	if (audio->sound_trigger == 1)
	{
		Mix_PlayChannel(-1, audio->sound, 0);
		audio->sound_trigger = 0;
	}

}

