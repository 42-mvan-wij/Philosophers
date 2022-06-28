/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 11:21:23 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/06/28 11:21:56 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_H
# define PHIL_H

# define BUBBLE != SUCCESS ||

typedef enum e_status
{
	SUCCESS,
	ERROR,
	E_TOO_FEW_ARGS,
	E_TOO_MANY_ARGS,
	E_EXPECTED_INTEGER,
	E_MALLOC_FAIL,
	E_PHIL_TOO_LITTLE,
	E_DIE_TOO_LITTLE,
	E_EAT_TOO_LITTLE,
	E_SLEEP_TOO_LITTLE,
	E_NUM_EAT_TOO_LITTLE,

	//tmp
	tmp_status_end
}	t_status;

typedef struct s_data
{
	int	num_phil;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_eat;
}	t_data;

#endif
