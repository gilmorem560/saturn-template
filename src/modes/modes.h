/*
 * modes - configurable list of game modes
 */

#ifndef __MODES_H__
#define __MODES_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
	
/* Saturn graphics library */
#include <sgl.h>
/* basic objects */
#include "../graphics/primitives/prim.h"
/* vector calculations */
#include "../graphics/primitives/vect.h"
/* scene graphing */
#include "../scene/scene.h"
/* game mode primitive */
#include "../scene/mode.h"
/* useful macros */
#include "../util/macros.h"

/* defined game modes */
#include "actor_test.h"
#define	GM_ACTOR_TEST	0
#define	MODE_COUNT		1

extern mode *current_mode;
extern unsigned int mode_index;
extern unsigned int mode_index_prev;
extern double current_ratio;
	
#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __MODES_H__ */
