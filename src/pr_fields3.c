/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_fields3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 21:23:35 by khaniche          #+#    #+#             */
/*   Updated: 2019/09/16 12:44:16 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	pr_texture(const JSON_Object *j_ob, t_objects *obj)
{
	if (!json_object_has_value_of_type(j_ob, "texture", JSONNumber))
	{
		obj->texture = -1;
		return (true);
	}
	obj->texture = json_object_get_number(j_ob, "texture");
	if (obj->texture < 0 || obj->texture > TEXTURES_COUNT)
	{
		ft_putstr("Error int count texture, ivalid count\n");
		return (false);
	}
	return (true);
}

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

bool	pr_compose(const JSON_Object *j_ob, t_objects *obj)
{
	if (!json_object_has_value_of_type(j_ob, "compose", JSONNumber))
	{
		obj->compose = 0;
		return (true);
	}
	obj->compose = json_object_get_number(j_ob, "compose");
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

bool	check_reflect__transparency(t_objects *obj)
{
	if (obj->reflection >= 0.5 && obj->transparency >= 0.5)
	{
		ft_putstr("Chandge your reflection or transparency\n");
		return (false);
	}
	return (true);
}

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
