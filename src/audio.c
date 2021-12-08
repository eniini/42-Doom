#include "doom.h"

void	init_audio(t_audio *audio)
{
	ft_bzero(audio, sizeof(t_audio));
	audio->sound = NULL;
	audio->boing = NULL;
	audio->money = NULL;
	audio->music = NULL;
	if( SDL_Init(SDL_INIT_AUDIO) < 0 )
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
	audio->sound = Mix_LoadWAV("resources/turning-pages-02.wav");
	audio->boing = Mix_LoadWAV("resources/boing.wav");
	audio->money = Mix_LoadWAV("resources/money.wav");
	audio->music = Mix_LoadMUS("resources/longsongnormal.wav");
}

void audio_cleanup(t_audio *audio)
{
	Mix_FreeChunk(audio->boing);
	Mix_FreeChunk(audio->money);
	Mix_FreeChunk(audio->sound);
	Mix_FreeMusic(audio->music);
	audio->boing = NULL;
	audio->money = NULL;
	audio->music = NULL;
	audio->sound = NULL;

}

void	audios(t_audio *audio)
{
	audio->music_trigger = TRUE;
	if(audio->mute_switch == TRUE)
	{
		audio->sound_trigger = FALSE;
		audio->boing_trigger = FALSE;
		audio->money_trigger = FALSE;
		audio->music_trigger = FALSE;
	//	ft_bzero(&audio->sound_trigger, sizeof(t_bool) *4);
	}
	if (audio->boing_trigger == TRUE)
	{
		Mix_PlayChannel(-1, audio->boing, 0);
		audio->boing_trigger = FALSE;
	}
	if (audio->money_trigger == TRUE)
	{
		Mix_PlayChannel(-1, audio->money, 0);
		audio->money_trigger = FALSE;
	}
	if (Mix_PlayingMusic() == 0 && audio->music_trigger == TRUE)
		Mix_PlayMusic(audio->music, -1);
	else
	{
    	if( Mix_PausedMusic() == 1 && audio->music_trigger == TRUE)
			Mix_ResumeMusic();
		else if (audio->music_trigger == FALSE)
			Mix_PauseMusic();
	}
}

