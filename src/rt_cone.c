/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 16:53:54 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/13 21:51:29 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec			rt_calc_cone_normal(t_intersect *i, t_ray ray)
{
	t_vec	normal;
	double	m;

	m = dot(ray.direction, i->closest_obj->orient) * i->dist +
		dot((ray.origin - i->closest_obj->centre), i->closest_obj->orient);
	normal = i->hit - i->closest_obj->centre - i->closest_obj->k *
		i->closest_obj->orient * m;
	return (normal / vec_length(normal));
}

static void		cut_cone(t_intersect *inter, double *data, t_objects *cone,
				t_ray ray)
{
	t_vec	oc;
	t_vec	hit;

	oc = ray.origin - cone->centre;
	if (data[2] < inter->dist)
	{
		hit = data[2] * ray.direction + oc;
		data[1] = dot(hit, cone->orient);
		if (data[1] > cone->cut[0] && data[1] < cone->cut[1])
		{
			inter->dist = data[2];
			inter->closest_obj = cone;
		}
	}
}

void			rt_intersect_ray_cone(t_ray ray, t_objects *cone,
					t_intersect *inter, double *dist_range)
{
	double	roots[2];
	t_vec	oc;
	t_vec	coeff;
	double	data[3];

	oc = ray.origin - cone->centre;
	coeff[0] = dot(ray.direction, ray.direction) - cone->k *
		pow(dot(ray.direction, cone->orient), 2);
	coeff[1] = 2 * (dot(ray.direction, oc) - cone->k *
		dot(ray.direction, cone->orient) * dot(oc, cone->orient));
	coeff[2] = dot(oc, oc) - cone->k * pow(dot(oc, cone->orient), 2);
	data[0] = coeff.y * coeff.y - 4 * coeff.x * coeff.z;
	if (data[0] >= 0)
	{
		roots[0] = (-coeff.y + sqrt(data[0])) / (2 * coeff.x);
		roots[1] = (-coeff.y - sqrt(data[0])) / (2 * coeff.x);
		data[2] = rt_select_dist(roots, dist_range);
		cut_cone(inter, data, cone, ray);
	}
}
