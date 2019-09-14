/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:51:23 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/14 13:18:13 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_sdl_clean(t_sdls *app)
{
	t_rt rt;

	cn_destroy_canvas(&(app->canvas));
	rt_clean(&rt);
	system("leaks -q RTv1");
	SDL_Quit();
}
