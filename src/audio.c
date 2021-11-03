#include "doom.h"


//THIS IS TEST EDIT FOR GIT TESTIN PURPOSES!!
//

void	init_audio(t_audio *audio)
{
	ft_bzero(audio, sizeof(t_audio));
	audio->sound = NULL;
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
	if (audio->sound_trigger == TRUE)
	{
		Mix_PlayChannel(-1, audio->sound, 0);
		audio->sound_trigger = FALSE;
	}

}

