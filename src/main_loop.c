/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 17:22:55 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/17 10:14:08 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_render(t_sdls *app)
{
	cn_render(&(app->canvas));
}

void leaks_free(t_rt *rt)
{
	int   i;

	i = -1;
	while (++i < TEXTURES_COUNT)
		SDL_FreeSurface(rt->texture[i]);	
}

void	ft_mainloop(t_sdls *app)
{
	t_rt rt;

	if (rt_parse_file(&rt, "scene.json") == false)
		return ;
	if (load_textures(&rt) == false)
		return ;
	check_light(&rt.lights);
	compose_obj(&rt.objs);
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
	leaks_free(&rt);
}
