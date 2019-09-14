/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 11:58:52 by khaniche          #+#    #+#             */
/*   Updated: 2019/09/13 21:18:12 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_event_(t_sdls *app, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_w)
		app->flags.forward = true;
	if (event.key.keysym.sym == SDLK_s)
		app->flags.backward = true;
	if (event.key.keysym.sym == SDLK_d)
		app->flags.right = true;
	if (event.key.keysym.sym == SDLK_a)
		app->flags.left = true;
}

void		ft_event(t_sdls *app)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if ((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type &&
			SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
			app->flags.running = false;
		if (SDL_KEYDOWN == event.type)
		{
			if (event.key.keysym.sym == SDLK_UP)
				app->flags.rot_x = true;
			if (event.key.keysym.sym == SDLK_LEFT)
				app->flags.rot_y = true;
			if (event.key.keysym.sym == SDLK_RIGHT)
				app->flags.rot_x_min = true;
			if (event.key.keysym.sym == SDLK_DOWN)
				app->flags.rot_y_min = true;
			ft_event_(app, event);
		}
	}
}
