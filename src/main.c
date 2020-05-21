/*
 * main - entrypoint
 */
#include "sgl.h"

int main(int argc, char *argv[])
{
	/* entry */
	slInitSystem(TV_320x224, NULL, 1);
	
	slPrint("Test", slLocate(9,2));
	
	while (-1) {
		slSynch();
	}
}

void __main(void)
{
}
