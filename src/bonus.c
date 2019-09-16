/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 10:24:36 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/09/16 19:14:59 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			sepia_image(Uint32 *pixels, Uint32 *pixels_copy)
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

void			save_image(const char *file_name, SDL_Renderer *renderer)
{
	SDL_Surface *surface;

	surface = SDL_CreateRGBSurface(0, CW, CH, 32, 0, 0, 0, 0);
	SDL_RenderReadPixels(renderer, NULL, surface->format->format,
	surface->pixels, surface->pitch);
	IMG_SavePNG(surface, file_name);
	SDL_FreeSurface(surface);
}

void			anti_aliasing(Uint32 *pixels, int intensive)
{
	int			i;
	int			y;
	int			x;
	t_channel	rgb;
	t_channel	tmp;

	i = -1;
	while (++i <= intensive)
	{
		y = 1;
		while (++y < CH - 2)
		{
			tmp.r = (y) * CW;
			tmp.g = (y + 1) * CW;
			tmp.b = (y - 1) * CW;
			x = 0;
			while (++x < CW)
			{
				rgb.r = (((pixels[x + tmp.r + 1] >> 16) & 0xFF) + ((pixels[x
					+ tmp.r] >> 16) & 0xFF) + ((pixels[x + tmp.r - 1] >> 16) &
						0xFF) + ((pixels[x + tmp.b] >> 16) & 0xFF) +
							((pixels[x + tmp.g + 1] >> 16) & 0xFF)) / 5;
				rgb.g = (((pixels[x + tmp.r + 1] >> 8) & 0xFF) + ((pixels[x +
					tmp.r] >> 8) & 0xFF) + ((pixels[x + tmp.r - 1] >> 8) & 0xFF)
						+ ((pixels[x + tmp.b] >> 8) & 0xFF) + ((pixels[x +
							tmp.g + 1] >> 8) & 0xFF)) / 5;
				rgb.b = (((pixels[x + tmp.r + 1]) & 0xFF) + (pixels[x + tmp.r]
					& 0xFF) + (pixels[x + tmp.r - 1] & 0xFF) + (pixels[x +
						tmp.b] & 0xFF) + (pixels[x + tmp.g + 1] & 0xFF)) / 5;
				pixels[x + tmp.r] = rt_channel_color_to_uint(rgb);
			}
		}
	}
}

t_channel		noise_text(t_rt *rtv, t_vec p, t_objects *ob)
{
	t_channel	color;
	Uint32		new_pixel;
	int			u;
	int			v;

	p -= ob->centre;
	//p = normalize(p);
	u = 0;
	v = 0;
	u = (sin(p.x * 2 * M_PI * 5) + 1) * 10000000;
	u += (sin(p.x * 2 * M_PI * 5) + 1) * 10000000;
	u += (sin(p.x * 2 * M_PI * 5) + 1) * 10000000;
	u += (sin(p.x * 2 * M_PI * 5) + 1) * 10000000;
	v = (cos(p.x * 2 * M_PI * 5) + 1) * 10000000;
	v += (cos(p.x * 2 * M_PI * 5) + 1) * 10000000;
	v += (cos(p.x * 2 * M_PI * 5) + 1) * 10000000;
	v += (cos(p.x * 2 * M_PI * 5) + 1) * 10000000;
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

t_channel		wave_chechboard(t_rt *rtv, t_vec p, t_objects *ob)
{
	int			u;
	int			v;
	t_channel	color;

	p -= ob->centre;
//	p = normalize(p);
	u = 0;
	v = 0;
	u = (sin(p.x * 2 * M_PI * 5) + 1) * 10;
	u += (sin(p.x * 2 * M_PI * 5) + 1) * 10;
	u += (sin(p.x * 2 * M_PI * 5) + 1) * 10;
	u += (sin(p.x * 2 * M_PI * 5) + 1) * 10;
	v = (cos(p.y * 2 * M_PI * 5) + 1) * 10;
	v += (cos(p.y * 2 * M_PI * 5) + 1) * 10;
	v += (cos(p.y * 2 * M_PI * 5) + 1) * 10;
	v += (cos(p.y * 2 * M_PI * 5) + 1) * 10;
	if (v)
		u *= v;
	color = (t_channel){(u >> 16) & 0xFF, (u >> 8) & 0xFF, (u & 0xFF)};
	if (color.r == 0 && color.b == 0 && color.g == 0)
		color = (t_channel){0, 0, 255};
	return (color);
}

t_channel		cartoon(t_channel col)
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


// if (color.r == 255 ||  color.g == 255 || color.b == 255)
// {
// 	color.r = 0;
// 	color.g = 0;
// 	color.b = 0;
// }

//                     resultBuffer[k] = 0;
//                     resultBuffer[k + 1] = 0;
//                     resultBuffer[k + 2] = 0;
//                     resultBuffer[k + 3] = 255;
//                 }
//                 else
//                 {
//                     resultBuffer[k] = paintPixelBuffer[k];
//                     resultBuffer[k + 1] = paintPixelBuffer[k + 1];
//                     resultBuffer[k + 2] = paintPixelBuffer[k + 2];
//                     resultBuffer[k + 3] = 255;
//                 }
//             }
