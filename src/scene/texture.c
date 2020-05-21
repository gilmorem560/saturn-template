/*
 * texture - texture utilities
 */
#include "texture.h"

/* general texture */
texture *texture_new(size_t width, size_t height, size_t bpp)
{	
	size_t data_size = width * height * bpp;
	texture *new_texture = (texture *) MEM_Malloc(sizeof (texture));
		new_texture->data = (unsigned char *) MEM_Malloc(data_size * sizeof (char));
		new_texture->width = width;
		new_texture->height = height;
		new_texture->bpp = bpp;
	
	return new_texture;
}

void texture_free(texture *this)
{
	MEM_Free(this->data);
	MEM_Free(this);
	
	return;
}



