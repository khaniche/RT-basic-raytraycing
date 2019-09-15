/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_objs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 12:02:05 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/15 18:14:51 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	pr_obj_sphere(const JSON_Object *j_ob, t_objects *sphere)
{
	if (!pr_vec_field(j_ob, "centre", &(sphere->centre)) ||
		!pr_vec_field(j_ob, "orient", &(sphere->orient)) ||
		!pr_vec_field(j_ob, "cut", &(sphere->cut)) ||
		!pr_channel_color(j_ob, sphere) ||
		!pr_specular(j_ob, sphere) ||
		!pr_compose(j_ob, sphere) ||
		!pr_radius(j_ob, sphere) ||
		!pr_reflection(j_ob, sphere) ||
		!pr_texture(j_ob, sphere) ||
		!pr_transparency(j_ob, sphere))
		return (false);
	pr_cut(sphere);
	sphere->orient /= vec_length(sphere->orient);
	return (true);
}

bool	pr_obj_plane(const JSON_Object *j_ob, t_objects *plane)
{
	if (!pr_vec_field(j_ob, "centre", &(plane->centre)) ||
		!pr_vec_field(j_ob, "orient", &(plane->orient)) ||
		!pr_vec_field(j_ob, "cut", &(plane->cut)) ||
		!pr_channel_color(j_ob, plane) ||
		!pr_specular(j_ob, plane) ||
		!pr_radius(j_ob, plane) ||
		!pr_reflection(j_ob, plane) ||
		!pr_transparency(j_ob, plane))
		return (false);
	pr_cut(plane);
	plane->orient /= vec_length(plane->orient);
	return (true);
}

bool	pr_obj_cyl(const JSON_Object *j_ob, t_objects *cyl)
{
	if (!pr_vec_field(j_ob, "centre", &(cyl->centre)) ||
		!pr_vec_field(j_ob, "orient", &(cyl->orient)) ||
		!pr_vec_field(j_ob, "cut", &(cyl->cut)) ||
		!pr_channel_color(j_ob, cyl) ||
		!pr_specular(j_ob, cyl) ||
		!pr_radius(j_ob, cyl) ||
		!pr_reflection(j_ob, cyl) ||
		!pr_transparency(j_ob, cyl))
		return (false);
	pr_cut(cyl);
	cyl->orient /= vec_length(cyl->orient);
	return (true);
}

bool	pr_obj_cone(const JSON_Object *j_ob, t_objects *cone)
{
	if (!pr_vec_field(j_ob, "centre", &(cone->centre)) ||
		!pr_vec_field(j_ob, "orient", &(cone->orient)) ||
		!pr_vec_field(j_ob, "cut", &(cone->cut)) ||
		!pr_channel_color(j_ob, cone) ||
		!pr_specular(j_ob, cone) ||
		!pr_angle(j_ob, cone) ||
		!pr_transparency(j_ob, cone) ||
		!pr_reflection(j_ob, cone))
		return (false);
	pr_cut(cone);
	cone->orient /= vec_length(cone->orient);
	cone->k = 1 + pow(tan(cone->radius / 2), 2);
	return (true);
}

bool	pr_obj_par(const JSON_Object *j_ob, t_objects *par)
{
	if (!pr_vec_field(j_ob, "centre", &(par->centre)) ||
		!pr_vec_field(j_ob, "orient", &(par->orient)) ||
		!pr_vec_field(j_ob, "cut", &(par->cut)) ||
		!pr_channel_color(j_ob, par) ||
		!pr_specular(j_ob, par) ||
		!pr_angle(j_ob, par) ||
		!pr_transparency(j_ob, par) ||
		!pr_reflection(j_ob, par))
		return (false);
	pr_cut(par);
	par->orient /= vec_length(par->orient);
	return (true);
}
