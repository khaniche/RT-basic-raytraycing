/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 17:36:52 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/15 09:23:07 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(void)
{
	t_sdls		app;

	ft_sdl_init(&app);
	ft_mainloop(&app);
	ft_sdl_clean(&app);
	system("leaks -q RTv1");
	return (0);
}
