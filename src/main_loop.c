/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 17:22:55 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/15 16:50:06 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_render(t_sdls *app)
{
	cn_render(&(app->canvas));
}

void	ft_mainloop(t_sdls *app)
{
	t_rt rt;

	if (rt_parse_file(&rt, "scene.json") == false)
		return ;
	check_light(&rt.lights);
	rt.pixels = app->canvas.pixels;
	while (app->flags.running)
	{
		ft_event(app);
		ft_update(app, &rt);
		if (app->flags.state_changed)
		{
			rt_thread_tracer(&rt);
			app->canvas.pixels = rt.pixels;
			app->flags.state_changed = 0;
		}
		ft_render(app);
	}
}
