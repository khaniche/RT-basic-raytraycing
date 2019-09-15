/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 20:16:47 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/15 13:08:56 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec			rt_calc_cylinder_normal(t_intersect *i, t_ray ray)
{
	t_vec	normal;
	double	m;

	m = dot(ray.direction, i->closest_obj->orient) * i->dist +
		dot((ray.origin - i->closest_obj->centre), i->closest_obj->orient);
	normal = i->hit - i->closest_obj->centre -
		i->closest_obj->orient * m;
	return (normal / vec_length(normal));
}

static void		cut_cylinder(t_intersect *inter, double *data, t_objects *cyl,
				t_ray ray)
{
	t_vec	oc;
	t_vec	hit;

	oc = ray.origin - cyl->centre;
	if (data[2] < inter->dist)
	{
		hit = data[2] * ray.direction + oc;
		data[1] = dot(hit, cyl->orient);
		if (data[1] > cyl->cut[0] && data[1] < cyl->cut[1])
		{
			inter->dist = data[2];
			inter->closest_obj = cyl;
		}
	}
}

void			rt_intersect_ray_cylinder(t_ray ray, t_objects *cyl,
					t_intersect *inter, double *dist_range)
{
	double	roots[2];
	t_vec	oc;
	t_vec	coeff;
	double	data[3];

	oc = ray.origin - cyl->centre;
	coeff[0] = dot(ray.direction, ray.direction) -
		pow(dot(ray.direction, cyl->orient), 2);
	coeff[1] = 2 * (dot(ray.direction, oc) -
		dot(ray.direction, cyl->orient) * dot(oc, cyl->orient));
	coeff[2] = dot(oc, oc) - pow(dot(oc, cyl->orient), 2) - cyl->radius;
	data[0] = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (data[0] >= 0)
	{
		roots[0] = (-coeff.y + sqrt(data[0])) / (2 * coeff.x);
		roots[1] = (-coeff.y - sqrt(data[0])) / (2 * coeff.x);
		data[2] = rt_select_dist(roots, dist_range);
		cut_cylinder(inter, data, cyl, ray);
	}
}
