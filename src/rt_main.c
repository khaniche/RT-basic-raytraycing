/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:24:31 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/19 18:35:48 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_channel	find_color_texture(t_rt *rt, t_intersect inter, double i)
{
	t_channel		tex_color;

	if (inter.closest_obj->texture > -1 &&
	inter.closest_obj->texture < TEXTURES_COUNT)
	{
		tex_color = texture_mapping(rt, inter.hit, inter.closest_obj);
		tex_color = rt_enlightenment(tex_color, i);
	}
	else if (inter.closest_obj->texture > -1 &&
		inter.closest_obj->texture < (TEXTURES_COUNT + 2))
	{
		if (inter.closest_obj->texture == (TEXTURES_COUNT + 1))
		{
			tex_color = noise_text(inter.hit, inter.closest_obj->centre);
		}
		else
		{
			tex_color = wave_chechboard(inter.hit, inter.closest_obj->centre);
		}
	}
	else
		tex_color = rt_enlightenment(inter.closest_obj->color, i);
	return (tex_color);
}

void		init_color_trcae(t_color_trace *color)
{
	color->transparency_color = (t_channel){0, 0, 0};
	color->reflected_color = (t_channel){0, 0, 0};
}

t_channel	rt_trace_ray(t_ray ray, t_rt *rt,
double *dist_range, int depth)
{
	t_color_trace	color;
	t_intersect		inter;
	double			i;

	if (!rt_find_closest_obj(ray, rt->objs, &inter, dist_range))
		return ((t_channel) {0, 0, 0});
	init_color_trcae(&color);
	inter.hit = ray.origin + inter.dist * ray.direction;
	inter.normal = rt_calc_normal(&inter, ray);
	i = rt_compute_lighting(rt->objs, rt->lights, ray, &inter);
	color.local_color = find_color_texture(rt, inter, i);
	if (depth <= 0 || (inter.closest_obj->reflection <= 0
	&& inter.closest_obj->transparency <= 0))
		return (color.local_color);
	ray.origin = inter.hit;
	if (inter.closest_obj->transparency > 0)
		color.transparency_color = rt_trace_ray(ray, rt,
			(double[2]) {0.001, DBL_MAX}, depth - 1);
	ray.direction = rt_reflect_ray(inter.normal, -ray.direction);
	if (inter.closest_obj->reflection > 0)
		color.reflected_color = rt_trace_ray(ray, rt,
			(double[2]) {0.001, DBL_MAX}, depth - 1);
	return (rt_calc_ref_tran_color(color, inter.closest_obj->reflection,
			inter.closest_obj->transparency));
}

void		*rt_threaded_loop(void *r)
{
	t_rt			*rt;
	t_ray			ray;
	t_channel		color;
	int				y;
	double			dist_range[2];

	rt = (t_rt *)r;
	dist_range[0] = 1;
	dist_range[1] = DBL_MAX;
	ray.origin = rt->camera.origin;
	rt->x_start--;
	while (++rt->x_start <= CW / 2)
	{
		y = -CH / 2 - 1;
		while (++y <= CH / 2)
		{
			ray.direction = rt_canvas_to_viewport(rt->x_start, y);
			ray.direction = rt_rotate_camera(&(rt->camera), ray.direction);
			color = rt_trace_ray(ray, rt, dist_range, RECURTION_DEPTH);
			// color = cartoon(color);
			ft_pp_img(rt->pixels, rt->x_start + CW / 2, CH / 2 - y,
				rt_channel_color_to_uint(color));
		}
	}
	return (r);
}
