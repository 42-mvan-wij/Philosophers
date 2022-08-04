/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:20:41 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 13:55:16 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../structs.h"

#include <assert.h> // FIXME: TMP

static t_status	*get_err_ptr(void)
{
	static t_status	err = OK;

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

static bool	should_print_usage_text(t_status e)
{
	if (e == E_TOO_FEW_ARGS || e == E_TOO_MANY_ARGS || e == E_EXPECTED_INTEGER)
		return (true);
	return (false);
}

void	print_err(void)
{
	static char	*err_text[] = {
	[OK] = "LOL, get prankt",
	[ERROR] = "Unknown error occurred",
	[E_TOO_FEW_ARGS] = "Error: too few arguments, expected at least 4",
	[E_TOO_MANY_ARGS] = "Error: too many arguments, expected at most 5",
	[E_EXPECTED_INTEGER] = "Error: expected integer",
	[E_MALLOC_FAIL] = "Error: Malloc failed",
	[E_WRITE_FAIL] = "Error: Write failed",
	[E_PHIL_TOO_LITTLE] = "Error: Too few philosophers, must be at least 1",
	[E_DIE_TOO_LITTLE] = "Error: Time to die cannot be negative",
	[E_EAT_TOO_LITTLE] = "Error: Time to eat cannot be negative",
	[E_SLEEP_TOO_LITTLE] = "Error: Time to sleep cannot be negative",
	[E_NUM_EAT_TOO_LITTLE] = "Error: Number of times each philosopher must eat "
		"must be at least 1",
	[E_THREAD_FAIL] = "Error: Failed to create thread",
	};
	assert(err_text[get_err()] != NULL); // FIXME: tmp
	printf("%s\n", err_text[get_err()]);
	if (should_print_usage_text(get_err()))
		printf("\tUsage: ./philo <number of philosophers> <time to die> "
			"<time to eat> <time to sleep> [amount to eat]\n");
}
