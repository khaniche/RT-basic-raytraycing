/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:52:26 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/13 21:49:42 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	rt_calc_plane_normal(t_intersect *inter, t_ray ray)
{
	double	d_dot_n;

	d_dot_n = dot(ray.direction, inter->closest_obj->orient);
	if (d_dot_n < 0)
		return (inter->closest_obj->orient);
	return (-inter->closest_obj->orient);
}

void	rt_intersect_ray_plane(t_ray ray, t_objects *plane,
					t_intersect *inter, double *dist_range)
{
	double	t;
	double	denominator;
	t_vec	oc;
	t_vec	hitpoint;

	denominator = dot(plane->orient, ray.direction);
	if (denominator != 0)
	{
		oc = ray.origin - plane->centre;
		t = -dot(oc, plane->orient) / denominator;
		if (t > dist_range[0] && t < dist_range[1] && t < inter->dist)
		{
			t = -dot(oc, plane->orient) / dot(ray.direction, plane->orient);
			hitpoint = t * ray.direction + oc;
			if (vec_length(hitpoint) < 5)
			{
				inter->dist = t;
				inter->closest_obj = plane;
			}
		}
	}
}
