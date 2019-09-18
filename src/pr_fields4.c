/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_fields4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:41:47 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/09/18 10:41:53 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_light(t_lights **lg)
{
	t_lights	*lig;
	bool		ambient;

	ambient = false;
	lig = *lg;
	while (lig->next)
	{
		if (lig->type == LT_AMBIENT)
			ambient = true;
		lig = lig->next;
	}
	if (ambient == false)
	{
		lig->next = (t_lights *)malloc(sizeof(t_lights));
		lig = lig->next;
		lig->type = LT_AMBIENT;
		lig->intensity = 0.1;
		lig->next = NULL;
	}
}
