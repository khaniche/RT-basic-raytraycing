/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:46:34 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/15 09:36:38 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	parse_array_of_scene_objects(const JSON_Array *j_arr, t_objects **objs)
{
	JSON_Object	*j_ob;
	t_objects	*obj;
	size_t		size_i[2];

	size_i[0] = json_array_get_count(j_arr);
	obj = (t_objects *)malloc(sizeof(t_objects));
	*objs = obj;
	size_i[1] = 0;
	while (size_i[1] < size_i[0])
	{
		if (size_i[1] != 0)
		{
			obj->next = (t_objects *)malloc(sizeof(t_objects));
			obj = obj->next;
		}
		j_ob = json_array_get_object(j_arr, size_i[1]++);
		if (!pr_object(j_ob, obj))
		{
			obj->next = NULL;
			rt_free_objects(objs);
			return (false);
		}
	}
	obj->next = NULL;
	if (size_i[0] <= 2)
		return (false);
	json_object_clear(j_ob);
	return (true);
}

bool	parse_array_of_lights(const JSON_Array *j_arr, t_lights **lights)
{
	JSON_Object	*j_ob;
	t_lights	*light;
	size_t		size_i[2];

	size_i[0] = json_array_get_count(j_arr);
	light = (t_lights *)malloc(sizeof(t_lights));
	*lights = light;
	size_i[1] = 0;
	while (size_i[1] < size_i[0])
	{
		if (size_i[1] != 0)
		{
			light->next = (t_lights *)malloc(sizeof(t_lights));
			light = light->next;
		}
		j_ob = json_array_get_object(j_arr, size_i[1]++);
		if (!pr_light(j_ob, light))
		{
			light->next = NULL;
			rt_free_lights(lights);
			return (false);
		}
	}
	light->next = NULL;
	if (size_i[0] <= 2)
		return (false);
	json_object_clear(j_ob);
	return (true);
}

bool	pr_camera(const JSON_Object *j_ob, t_camera *camera)
{
	JSON_Object	*j_cam;

	if ((j_cam = json_object_get_object(j_ob, "camera")) == NULL)
	{
		camera->orient = (t_vec) {0, 0, 0};
		camera->origin = (t_vec) {0, 0, 0};
	}
	else
	{
		if (!pr_vec_field(j_cam, "orient", &(camera->orient)))
			return (false);
		if (!pr_vec_field(j_cam, "origin", &(camera->origin)))
			return (false);
	}
	camera->orient[0] = DEG_TO_RAD(camera->orient[0]);
	camera->orient[1] = DEG_TO_RAD(camera->orient[1]);
	camera->orient[2] = DEG_TO_RAD(camera->orient[2]);
	json_object_clear(j_cam);
	return (true);
}

bool	rt_parse_file_(t_rt *rt, JSON_Object *json_objs)
{
	JSON_Array	*json_arr;

	if ((json_arr = json_object_get_array(json_objs, "objects")) == NULL)
		false_error("Error while getting array of scene objects");
	if (!parse_array_of_scene_objects(json_arr, &(rt->objs)))
		false_error("Error while parsing objects");
	if ((json_arr = json_object_get_array(json_objs, "lights")) == NULL)
		false_error("Error while getting array of lights");
	if (!parse_array_of_lights(json_arr, &(rt->lights)))
		false_error("Error while parsing lights");
	json_array_clear(json_arr);
	return (true);
}

bool	rt_parse_file(t_rt *rt, const char *fname)
{
	JSON_Value	*json_val;
	JSON_Object	*json_objs;

	if ((json_val = json_parse_file(fname)) == NULL)
		false_error("Error while parsing json");
	if ((json_objs = json_value_get_object(json_val)) == NULL)
		false_error("Error while getting object from value");
	if (!rt_parse_file_(rt, json_objs))
		return (false);
	if (!(pr_camera(json_objs, &(rt->camera))))
		false_error("Error while parsing camera");
	ft_putendl("All good so far");
	json_object_clear(json_objs);
	json_value_free(json_val);
	return (true);
}
