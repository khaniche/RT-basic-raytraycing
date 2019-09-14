/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_fields3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaniche <khaniche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 21:23:35 by khaniche          #+#    #+#             */
/*   Updated: 2019/09/14 14:33:59 by khaniche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	pr_transparency(const JSON_Object *j_ob, t_objects *obj)
{
	if (!json_object_has_value_of_type(j_ob, "transparency", JSONNumber))
	{
		obj->transparency = -1;
		return (true);
	}
	obj->transparency = json_object_get_number(j_ob, "transparency");
	if (obj->transparency > 1)
		return (false);
	return (true);
}

void	pr_cut(t_objects *obj)
{
	obj->cut[2] = 0;
	if ((obj->cut[1] == 0 && obj->cut[0] == 0)
		|| (obj->cut[0] > obj->cut[1]) || obj->cut[1] == obj->cut[0])
	{
		obj->cut[0] = -2147483648;
		obj->cut[1] = 2147483647;
	}
}
