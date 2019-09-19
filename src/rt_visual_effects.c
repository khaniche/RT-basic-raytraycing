/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_visual_effects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 10:24:36 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/09/19 18:25:16 by dmolyboh         ###   ########.fr       */
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

// void				gray_rad(Uint32 *pixels, Uint32 *pixels_copy)
// {
// 	int			i;
// 	Uint32		rgb;

// 	i = -1;
// 	while (CW * CH > (++i))
// 	{
// 		rgb = 0.299 * pixels[i].r + 0.587 * pixels[i].g + 0.114 * pixels[i].b;
// 		pixels_copy[i] = rt_channel_color_to_uint((t_channel){rgb, rgb, rgb});
// 	}
// }

// void				white_rad(Uint32 *pixels, Uint32 *pixels_copy)
// {
// 	int			i;
// 	Uint32		rgb;
// 	t_channel	rez;

// 	i = -1;
// 	while (CW * CH > (++i))
// 	{
// 		rgb = 0.299 * pixels[i].r + 0.587 * pixels[i].g + 0.114 * pixels[i].b;
// 		rez.r = (((255 - rgb) < 0) ? 0 : (255 - rgb));
// 		rez.g = (((255 - rgb) < 0) ? 0 : (255 - rgb));
// 		rez.b = (((255 - rgb) < 0) ? 0 : (255 - rgb));
// 		pixels_copy[i] = rt_channel_color_to_uint(rez);
// 	}
// }

t_channel			cartoon(t_channel col)
{
	col.r = (col.r / 20) * 20;
	col.g = (col.g / 20) * 20;
	col.b = (col.b / 20) * 20;
	return (col);
}
