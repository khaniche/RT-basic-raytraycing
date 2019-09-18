/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 10:24:36 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/09/18 10:40:45 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				sepia_image(Uint32 *pixels, Uint32 *pixels_copy)
{
	Uint32		i;
	Uint32		tmp;
	t_channel	rgb;

	i = -1;
	while (CW * CH > (++i))
	{
		tmp = pixels[i];
		rgb.r = (((tmp >> 16) & 0xFF) * 0.393) + ((tmp >> 8 & 0xFF) * 0.769) +
		((tmp & 0xFF) * 0.189);
		rgb.g = (((tmp >> 16) & 0xFF) * 0.349) + ((tmp >> 8 & 0xFF) * 0.686) +
		((tmp & 0xFF) * 0.168);
		rgb.b = (((tmp >> 16) & 0xFF) * 0.272) + ((tmp >> 8 & 0xFF) * 0.534) +
		((tmp & 0xFF) * 0.131);
		pixels_copy[i] = rt_channel_color_to_uint(rgb);
	}
}

void				save_image(const char *file_name, SDL_Renderer *renderer)
{
	SDL_Surface *surface;

	surface = SDL_CreateRGBSurface(0, CW, CH, 32, 0, 0, 0, 0);
	SDL_RenderReadPixels(renderer, NULL, surface->format->format,
	surface->pixels, surface->pitch);
	IMG_SavePNG(surface, file_name);
	SDL_FreeSurface(surface);
}

t_channel			noise_text(t_vec p, t_vec center)
{
	t_channel	color;
	Uint32		new_pixel;
	int			u;
	int			v;

	p -= center;
	p = normalize(p);
	u = 0;
	v = 0;
	u = ((sin(p.x * 2 * M_PI * 5) + 1) * 10000000) * 4;
	v = ((cos(p.x * 2 * M_PI * 5) + 1) * 10000000) * 4;
	if (v)
		u *= v;
	color = (t_channel){(u >> 16) & 0xFF, (u >> 8) & 0xFF, (u & 0xFF)};
	color.b = (color.r + color.g + color.b) / 3.0f;
	color.g = color.b;
	color.r = color.g;
	new_pixel = 0xFF000000 | ((Uint32)color.r << 16) |
		((Uint32)color.g << 8) | ((Uint32)color.b);
	color = (t_channel){(new_pixel >> 16) & 0xFF,
				(new_pixel >> 8) & 0xFF, (new_pixel & 0xFF)};
	return (color);
}

t_channel			wave_chechboard(t_vec p, t_vec center)
{
	int			u;
	int			v;
	t_channel	color;

	p -= center;
	p = normalize(p);
	u = 0;
	v = 0;
	u = ((sin(p.x * 2 * M_PI * 5) + 1) * 10) * 4;
	v = ((cos(p.y * 2 * M_PI * 5) + 1) * 10) * 4;
	if (v)
		u *= v;
	color = (t_channel){(u >> 16) & 0xFF, (u >> 8) & 0xFF, (u & 0xFF)};
	if (color.r == 0 && color.b == 0 && color.g == 0)
		color = (t_channel){0, 0, 255};
	return (color);
}

t_channel			cartoon(t_channel col)
{
	Uint32 rgb;

	rgb = 0.299 * col.r + 0.587 * col.g + 0.114 * col.b;
	col.r = rgb;
	col.g = rgb;
	col.b = rgb;
	col.r = (255 - rgb) < 0 ? 0 : (255 - rgb);
	col.g = (255 - rgb) < 0 ? 0 : (255 - rgb);
	col.b = (255 - rgb) < 0 ? 0 : (255 - rgb);
	return (col);
}
