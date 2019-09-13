/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 19:51:00 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/13 11:16:01 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include "rt.h"

static void		ft_update_(t_sdls *app, t_rt *rt)
{
	if (app->flags.rot_y_min)
	{
		rt->camera.orient[0] -= ROT_POWER;
		app->flags.rot_y_min = false;
		app->flags.state_changed = 1;
	}
	if (app->flags.forward)
	{
		rt->camera.origin[1] += rt->camera.orient[0];
		rt->camera.origin[0] += rt->camera.orient[1];
		rt->camera.origin[2] += 0.1;
		app->flags.forward = false;
		app->flags.state_changed = 1;
	}
	if (app->flags.backward)
	{
		rt->camera.origin[1] -= rt->camera.orient[0];
		rt->camera.origin[0] -= rt->camera.orient[1];
		rt->camera.origin[2] -= 0.1;
		app->flags.backward = false;
		app->flags.state_changed = 1;
	}
}

void			ft_update(t_sdls *app, t_rt *rt)
{
	if (app->flags.rot_x)
	{
		rt->camera.orient[0] += ROT_POWER;
		app->flags.rot_x = false;
		app->flags.state_changed = 1;
	}
	if (app->flags.rot_x_min)
	{
		rt->camera.orient[1] += ROT_POWER;
		app->flags.rot_x_min = false;
		app->flags.state_changed = 1;
	}
	if (app->flags.rot_y)
	{
		rt->camera.orient[1] -= ROT_POWER;
		app->flags.rot_y = false;
		app->flags.state_changed = 1;
	}
	ft_update_(app, rt);
	cn_update(&(app->canvas));
}

static t_vec	rt_rotate_camera_x(t_camera *camera, t_vec ray_dir)
{
	double	tmp;

	tmp = ray_dir[0];
	ray_dir[0] = tmp * cos(camera->orient[1]) + ray_dir[2]
		* sin(camera->orient[1]);
	ray_dir[2] = -tmp * sin(camera->orient[1]) + ray_dir[2]
		* cos(camera->orient[1]);
	return (ray_dir);
}

t_vec			rt_rotate_camera(t_camera *camera, t_vec ray_dir)
{
	double	tmp;

	tmp = ray_dir[1];
	ray_dir[1] = tmp * cos(camera->orient[0]) + ray_dir[2]
		* sin(camera->orient[0]);
	ray_dir[2] = -tmp * sin(camera->orient[0]) + ray_dir[2]
		* cos(camera->orient[0]);
	ray_dir = rt_rotate_camera_x(camera, ray_dir);
	return (ray_dir);
}
