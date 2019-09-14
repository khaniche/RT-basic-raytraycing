/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 19:51:00 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/14 20:08:59 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ft_update__(t_sdls *app, t_rt *rt, t_vec vec_rot)
{
	if (app->flags.left)
	{
		vec_rot[0] -= 0.12;
		vec_rot = moves(vec_rot, rt->camera.orient);
		rt->camera.origin += vec_rot;
		app->flags.left = false;
	}
	if (app->flags.right)
	{
		vec_rot[0] += 0.12;
		vec_rot = moves(vec_rot, rt->camera.orient);
		rt->camera.origin += vec_rot;
		app->flags.right = false;
	}
}

static void		ft_update_(t_sdls *app, t_rt *rt)
{
	t_vec	vec_rot;

	vec_rot = (t_vec){0, 0, 0};
	if (app->flags.forward)
	{
		vec_rot[2] += 0.12;
		vec_rot = moves(vec_rot, rt->camera.orient);
		rt->camera.origin += vec_rot;
		app->flags.forward = false;
	}
	if (app->flags.backward)
	{
		vec_rot[2] -= 0.12;
		vec_rot = moves(vec_rot, rt->camera.orient);
		rt->camera.origin += vec_rot;
		app->flags.backward = false;
	}
	ft_update__(app, rt, vec_rot);
}

void			ft_update(t_sdls *app, t_rt *rt)
{
	if (app->flags.rot_x)
	{
		rt->camera.orient[0] += ROT_POWER;
		app->flags.rot_x = false;
	}
	if (app->flags.rot_x_min)
	{
		rt->camera.orient[1] += ROT_POWER;
		app->flags.rot_x_min = false;
	}
	if (app->flags.rot_y)
	{
		rt->camera.orient[1] -= ROT_POWER;
		app->flags.rot_y = false;
	}
	if (app->flags.rot_y_min)
	{
		rt->camera.orient[0] -= ROT_POWER;
		app->flags.rot_y_min = false;
	}
	app->flags.state_changed = 1;
	ft_update_(app, rt);
	cn_update(&(app->canvas));
}

static t_vec	rt_rotate_camera_x(t_camera *camera, t_vec ray_dir)
{
	double	tmp;

	tmp = ray_dir[0];
	ray_dir[0] = tmp * cos(camera->orient[1]) +
		ray_dir[2] * sin(camera->orient[1]);
	ray_dir[2] = -tmp * sin(camera->orient[1]) +
		ray_dir[2] * cos(camera->orient[1]);
	return (ray_dir);
}

t_vec			rt_rotate_camera(t_camera *camera, t_vec ray_dir)
{
	double	tmp;

	tmp = ray_dir[1];
	ray_dir[1] = tmp * cos(camera->orient[0]) +
		ray_dir[2] * sin(camera->orient[0]);
	ray_dir[2] = -tmp * sin(camera->orient[0]) +
		ray_dir[2] * cos(camera->orient[0]);
	ray_dir = rt_rotate_camera_x(camera, ray_dir);
	return (ray_dir);
}
