/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_disruptions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:17:45 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/09/19 18:45:21 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

t_channel   wave_chechboard(t_vec p,  t_vec center)
{
 double   u,v;
 double   uv;
 t_channel color;
 (void)center;
 // t_channel color1;
 // t_channel color_Rez;

 // p -= center;
 // p = normalize(p);
 u = sin(10.0 * M_PI * p.x) + 0.5;
 v = sin(10.0 * M_PI * p.y) + 0.5;
 uv = floor(u + v / 2.0);
 color = (t_channel){255 * uv, 255 * uv, 255 * uv};
 // if (color.r <= 50 && color.b <= 50 && color.g <= 50)
 //  color = (t_channel){0, 0, 0};
 // else
 //  color = (t_channel){255, 255, 255};
 // color1 = (t_channel){(v >> 16) & 0xFF, (v >> 8), (v & 0xFF)};
 // if (color1.r <= 50 && color1.b <= 50 && color1.g <= 50)
 //  color1 = (t_channel){0, 0, 0};
 // else
 //  color1 = (t_channel){255, 255, 255};
 // if (color1.r == color.r)
 //  color_Rez =  (t_channel){0, 0, 0};
 // else
 // color_Rez = (t_channel){255, 255, 255};
 return (color);
}