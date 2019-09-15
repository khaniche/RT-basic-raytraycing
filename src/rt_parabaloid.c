/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parabaloid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:07:21 by khaniche          #+#    #+#             */
/*   Updated: 2019/09/15 15:23:37 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec			rt_calc_par_normal(t_intersect *i, t_ray ray)
{
	t_vec	normal;
	double	m;

	m = dot(ray.direction, i->closest_obj->orient) * i->dist +
		dot((ray.origin - i->closest_obj->centre), i->closest_obj->orient);
	normal = i->hit - i->closest_obj->centre - i->closest_obj->k -
		(i->closest_obj->orient * m);
	return (normal / vec_length(normal));
}

static void		cut_par(t_intersect *inter, double *data, t_objects *par,
				t_ray ray)
{
	t_vec	oc;
	t_vec	hit;

	oc = ray.origin - par->centre;
	if (data[2] < inter->dist)
	{
		hit = data[2] * ray.direction + oc;
		data[1] = dot(hit, par->orient);
		if (data[1] > 0 && data[1] < 10)
		{
			inter->dist = data[2];
			inter->closest_obj = par;
		}
	}
}

void			rt_intersect_ray_par(t_ray ray, t_objects *par,
					t_intersect *inter, double *dist_range)
{
	double	roots[2];
	double	data[5];
	t_vec	oc;
	t_vec	coeff;

	oc = ray.origin - par->centre;
	data[3] = dot(ray.direction, par->orient);
	data[4] = dot(oc, par->orient);
	coeff[0] = 2.0 * (dot(ray.direction, ray.direction) - data[3] * data[3]);
	coeff[1] = 2 * (dot(ray.direction, oc) - data[3] *
		(data[4] + 2.0 * par->radius));
	coeff[2] = dot(oc, oc) - data[4] * (data[4] + 4.0 * par->radius);
	data[0] = coeff.y * coeff.y - 2 * coeff.x * coeff.z;
	if (data[0] >= 0)
	{
		roots[0] = (-coeff.y + sqrt(data[0])) / (coeff.x);
		roots[1] = (-coeff.y - sqrt(data[0])) / (coeff.x);
		data[2] = rt_select_dist(roots, dist_range);
		cut_par(inter, data, par, ray);
	}
}
