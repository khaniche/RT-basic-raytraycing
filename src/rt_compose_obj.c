/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:18:52 by khaniche          #+#    #+#             */
/*   Updated: 2019/09/17 11:15:04 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		copy_(t_objects *ob, t_objects *copy)
{
	static int	i;

	copy->specular = ob->specular;
	copy->color = ob->color;
	if (i == 0)
	{
		copy->centre = ob->centre;
		copy->centre.y += ob->radius * 1.2;
	}
	else
	{
		copy->centre = ob->centre;
		copy->centre.y -= ob->radius * 2;
	}
	copy->color = ob->color;
	copy->orient = ob->orient;
	if (i == 0)
		copy->radius = ob->radius - ob->radius * 0.6;
	else
		copy->radius = ob->radius + ob->radius * 0.6;
	copy->reflection = ob->reflection;
	copy->texture = ob->texture;
	copy->transparency = ob->transparency;
	i++;
}

static	void	spec(t_objects **obj, t_objects *ob, t_objects *t_ob)
{
	*obj = ob;
	ob->specular = 50;
	ob->next->specular = 0;
	t_ob->specular = 0;
}

void			compose_obj(t_objects **obj)
{
	t_objects	*ob;
	t_objects	*t_ob;
	bool		compose;

	compose = false;
	t_ob = *obj;
	while (t_ob)
	{
		if (t_ob->compose == 0 && t_ob->type == OBJ_SPHERE)
		{
			compose = true;
			break ;
		}
		t_ob = t_ob->next;
	}
	if (compose == true)
	{
		ob = (t_objects *)malloc(sizeof(t_objects));
		ob->next = (t_objects *)malloc(sizeof(t_objects));
		ob->next->next = NULL;
		copy_(t_ob, ob);
		copy_(t_ob, ob->next);
		ob->next->next = *obj;
		spec(obj, ob, t_ob);
	}
}
