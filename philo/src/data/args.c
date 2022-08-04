/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   args.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 13:33:06 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 13:33:15 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"
#include "../util/utils.h"

static t_status	check_args(int argc, t_data *data)
{
	if (data->num_phil < 1)
		return (set_err(E_PHIL_TOO_LITTLE));
	if (data->time_to_die < 0)
		return (set_err(E_DIE_TOO_LITTLE));
	if (data->time_to_eat < 0)
		return (set_err(E_EAT_TOO_LITTLE));
	if (data->time_to_sleep < 0)
		return (set_err(E_SLEEP_TOO_LITTLE));
	if (argc - 1 == 5 && data->num_eat < 1)
		return (set_err(E_NUM_EAT_TOO_LITTLE));
	return (OK);
}

t_status	parse_args(int argc, char **argv, t_data *data)
{
	bool	overflow;

	if (argc - 1 < 4)
		return (set_err(E_TOO_FEW_ARGS));
	if (argc - 1 > 5)
		return (set_err(E_TOO_MANY_ARGS));
	if (!ft_atoi_strict(argv[1], &data->num_phil, &overflow) || overflow)
		return (set_err(E_EXPECTED_INTEGER));
	if (!ft_atoi_strict(argv[2], &data->time_to_die, &overflow) || overflow)
		return (set_err(E_EXPECTED_INTEGER));
	if (!ft_atoi_strict(argv[3], &data->time_to_eat, &overflow) || overflow)
		return (set_err(E_EXPECTED_INTEGER));
	if (!ft_atoi_strict(argv[4], &data->time_to_sleep, &overflow) || overflow)
		return (set_err(E_EXPECTED_INTEGER));
	data->num_eat = -1;
	if (argc - 1 == 5 \
	&& (!ft_atoi_strict(argv[5], &data->num_eat, &overflow) || overflow))
		return (set_err(E_EXPECTED_INTEGER));
	return (check_args(argc, data));
}
