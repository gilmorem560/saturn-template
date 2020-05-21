/*
 * main - entrypoint
 */

/* game modes */
#include "modes/modes.h"

#define INITIAL_GM	GM_ACTOR_TEST

const mode game_modes[MODE_COUNT] = {
	{actor_test_init, actor_test_render, actor_test_input, actor_test_routine, actor_test_free}
};

int main(int argc, char *argv[])
{
	/* entry */
	slInitSystem(TV_320x224, NULL, 1);
	
	MEM_Init(0x6050000, 0x10000);

	game_modes[mode_index].init();
	
	while (-1) {
		mode_index_prev = mode_index;

		/* TODO: read controllers */

		/* process movement */
		game_modes[mode_index].input();

		/* run mode routine */
		game_modes[mode_index].routine();

		/* routine may change mode */
		if (mode_index == mode_index_prev)
			/* process next frame */
			game_modes[mode_index].render();
		else {
			game_modes[mode_index_prev].free();
			game_modes[mode_index].init();
		}
	}
}

void __main(void)
{
}
