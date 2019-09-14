/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:51:23 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/14 20:38:44 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_sdl_clean(t_sdls *app)
{
	t_rt rt;

	cn_destroy_canvas(&(app->canvas));
	rt_clean(&rt);
	SDL_Quit();
}
