/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 12:25:00 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/06/28 17:50:39 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include "util.h"
#include "phil.h"
#include <pthread.h>

// FIXME: tmp
#include "../../libft/libft.h"

static t_status	*get_err_ptr(void)
{
	static t_status	err = SUCCESS;

	return (&err);
}

t_status	set_err(t_status err)
{
	*get_err_ptr() = err;
	return (err);
}

t_status	get_err(void)
{
	return (*get_err_ptr());
}

bool	err_is_set(void)
{
	return (get_err() != SUCCESS);
}

bool	is_err(t_status err)
{
	return (err != SUCCESS);
}

void	*ph_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		set_err(E_MALLOC_FAIL);
	return (ptr);
}

ssize_t	ph_write(int fd, const void *buf, size_t nbyte)
{
	ssize_t	ret;

	ret = write(fd, buf, nbyte);
	if (ret < 0)
		set_err(E_WRITE_FAIL);
	return (ret);
}

t_status	check_args(int argc, t_data *data)
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
	return (SUCCESS);
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

#include <assert.h>

void	print_err(void)
{
	static char	*err_text[] = {
	[SUCCESS] = "LOL, get prankt",
	[ERROR] = "Unknown error occurred",
	[E_TOO_FEW_ARGS] = "Error: too few arguments supplied, expected at least 4",
	[E_TOO_MANY_ARGS] = "Error: too many arguments supplied, expected at most 5",
	[E_EXPECTED_INTEGER] = "Error: expected integer",
	[E_MALLOC_FAIL] = "Error: Malloc failed",
	[E_WRITE_FAIL] = "Error: Write failed",
	[E_PHIL_TOO_LITTLE] = "Error: Too few philosophers, must be at least 1",
	[E_DIE_TOO_LITTLE] = "Error: Time to die cannot be negative",
	[E_EAT_TOO_LITTLE] = "Error: Time to eat cannot be negative",
	[E_SLEEP_TOO_LITTLE] = "Error: Time to sleep cannot be negative",
	[E_NUM_EAT_TOO_LITTLE] = "Error: Number of times each philosopher must eat \
must be at least 1",
	};
	assert(err_text[get_err()] != NULL); // FIXME: tmp
	printf("%s\n", err_text[get_err()]);
}

void *start_proc(void *start_proc_arg)
{

}

t_status	do_phil(t_data *data)
{
	pthread_t	id;
	pthread_create(&id, NULL, start_proc, start_proc_arg);
	pthread_join(id, NULL);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(argc, argv, &data) != SUCCESS || do_phil(&data) != SUCCESS)
	{
		return (get_err());
		print_err();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
