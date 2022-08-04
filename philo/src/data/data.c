/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 13:14:59 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 13:43:21 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../structs.h"
#include "../util/utils.h"
#include "./data_int.h"

void	free_data(t_data *data)
{
	if (data->fork_mutexes != NULL)
		free_fork_mutexes(&data->fork_mutexes, data->num_phil);
	if (data->phils != NULL)
		free_phils(&data->phils, data->num_phil);
}

t_status	create_data(int argc, char **argv, t_data *data)
{
	data->fork_mutexes = NULL;
	data->phils = NULL;
	if (parse_args(argc, argv, data) != OK || create_fork_mutexes(data) != OK
		|| create_phils(data) != OK)
		return (get_err());
	return (OK);
}
