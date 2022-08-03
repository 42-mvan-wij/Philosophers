/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 12:25:00 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/03 15:18:35 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include "util.h"
#include "phil.h"
#include <pthread.h>
#include <sys/time.h>

// FIXME: tmp
#include "../../libft/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

static void	ft_itob_internal(int64_t nbr, char **res, size_t *res_size)
{
	if (*res_size <= 1)
		return ;
	if (nbr / 10 != 0)
		ft_itob_internal(nbr / 10, res, res_size);
	else if (nbr < 0)
	{
		**res = '-';
		(*res)++;
		(*res_size)--;
		if (*res_size <= 1)
			return ;
	}
	if (nbr < 0)
		**res = '0' - (nbr % 10);
	else
		**res = '0' + (nbr % 10);
	(*res)++;
	(*res_size)--;
}

/**
 * Returns a pointer to after the last digit
 */
char	*ft_itob(int64_t nbr, char *res, size_t res_size)
{
	ft_itob_internal(nbr, &res, &res_size);
	if (res_size > 0)
		*res = '\0';
	return (res);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (dst == src)
		return (dst);
	while (n)
	{
		((char *)dst)[n - 1] = ((char *)src)[n - 1];
		n--;
	}
	return (dst);
}

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

// FIXME: tmp
#include <assert.h>

void	print_usage_text(void)
{
	printf("\tUsage: ./philo <number of philosophers> <time to die> <time to eat>"
		" <time to sleep> [number of times each philosopher must eat]\n");
}

bool	should_print_usage_text(t_status e)
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
	[E_THREAD_FAIL] = "Error: Failed to create thread",
	};
	assert(err_text[get_err()] != NULL); // FIXME: tmp
	printf("%s\n", err_text[get_err()]);
	if (should_print_usage_text(get_err()))
		print_usage_text();
}

void	free_fork_mutexes(pthread_mutex_t **fork_mutexes, int forks_created)
{
	if (*fork_mutexes == NULL)
		return ;
	while (forks_created > 0)
	{
		forks_created--;
		pthread_mutex_destroy(&(*fork_mutexes)[forks_created]);
	}
	free(*fork_mutexes);
	*fork_mutexes = NULL;
}

t_status	create_fork_mutexes(t_data *data)
{
	int	i;

	data->fork_mutexes = malloc(sizeof(pthread_mutex_t) * data->num_phil);
	if (data->fork_mutexes == NULL)
		return (set_err(E_MALLOC_FAIL));
	i = 0;
	while (i < data->num_phil)
	{
		if (pthread_mutex_init(&data->fork_mutexes[i], NULL) != 0)
		{
			free_fork_mutexes(&data->fork_mutexes, i - 1);
			return (set_err(E_MALLOC_FAIL));
		}
		i++;
	}
	return (OK);
}

void	free_phils(t_phil **phils, int phils_created)
{
	if (*phils == NULL)
		return ;
	while (phils_created > 0)
	{
		phils_created--;
		pthread_mutex_destroy(&(*phils)[phils_created].personal_lock);
	}
	free(*phils);
	*phils = NULL;
}

t_status	create_phils(t_data *data)
{
	int	i;

	data->phils = malloc(sizeof(t_phil) * data->num_phil);
	if (data->phils == NULL)
	{
		free_fork_mutexes(&data->fork_mutexes, data->num_phil);
		return (set_err(E_MALLOC_FAIL));
	}
	i = 0;
	while (i < data->num_phil)
	{
		data->phils[i].seat = i + 1;
		data->phils[i].times_eaten = 0;
		data->phils[i].right = &data->fork_mutexes[i];
		data->phils[i].left = &data->fork_mutexes[(i + 1) % data->num_phil];
		// data->phils[i].soul = 0;
		data->phils[i].data = data;
		data->phils[i].time_of_last_eat = 0;
		if (pthread_mutex_init(&data->phils[i].personal_lock, NULL) != 0)
		{
			free_fork_mutexes(&data->fork_mutexes, data->num_phil);
			free_phils(&data->phils, i - 1);
			return (set_err(E_MALLOC_FAIL));
		}
		i++;
	}
	return (OK);
}

struct timeval	get_time_diff(struct timeval start, struct timeval end)
{
	struct timeval	diff;

	diff.tv_usec = end.tv_usec - start.tv_usec;
	diff.tv_sec = end.tv_sec - start.tv_sec + diff.tv_sec / 1000000;
	diff.tv_usec %= 1000000;
	return (diff);
}

long	get_current_timestamp(t_data *data)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec - data->start_time.tv_sec) * 1000
		+ (tp.tv_usec - data->start_time.tv_usec) / 1000);
}

char	*append(char *src, char *dst, size_t dst_size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (src_len <= dst_size - 1)
	{
		ft_memcpy(dst, src, (src_len + 1) * sizeof(char));
		return (&dst[src_len]);
	}
	else if (dst_size != 0)
	{
		ft_memcpy(dst, src, (dst_size - 1) * sizeof(char));
		dst[dst_size - 1] = '\0';
		return (&dst[dst_size - 1]);
	}
	return (&dst[0]);
}

static void	print_msg_internal(t_phil *phil, char *msg, bool check)
{
	char		buff[128];
	const long	timestamp = get_current_timestamp(phil->data);
	// long		timestamp2;
	char		*buff_ptr;

	if (!check || !phil->data->stop)
	{
		buff_ptr = buff;
		buff_ptr = append("[", buff_ptr, 128 - (buff_ptr - buff));
		buff_ptr = ft_itob(timestamp, buff_ptr, 128 - (buff_ptr - buff));
		// buff_ptr = append(" - ", buff_ptr, 128 - (buff_ptr - buff));
	}
	if (!check || !phil->data->stop)
	{
		// timestamp2 = get_current_timestamp(phil->data);
		// buff_ptr = ft_itob(timestamp2, buff_ptr, 128 - (buff_ptr - buff));
		buff_ptr = append("]", buff_ptr, 128 - (buff_ptr - buff));
		buff_ptr = append(" ", buff_ptr, 128 - (buff_ptr - buff));
		buff_ptr = ft_itob(phil->seat, buff_ptr, 128 - (buff_ptr - buff));
		buff_ptr = append(" ", buff_ptr, 128 - (buff_ptr - buff));
		buff_ptr = append(msg, buff_ptr, 128 - (buff_ptr - buff));
		buff_ptr = append("\n", buff_ptr, 128 - (buff_ptr - buff));
	}
	pthread_mutex_lock(&phil->data->global_mutex);
	if (!check || !phil->data->stop)
		write(STDOUT_FILENO, buff, buff_ptr - buff);
	pthread_mutex_unlock(&phil->data->global_mutex);
}

void	print_msg(t_phil *phil, char *msg)
{
	print_msg_internal(phil, msg, true);
}

void	print_msg_unchecked(t_phil *phil, char *msg)
{
	print_msg_internal(phil, msg, false);
}

void	msleep(unsigned int ms)
{
	struct timeval	start;
	struct timeval	tp;

	if (ms == 0)
		return ;
	gettimeofday(&start, NULL);
	tp = start;
	// 1.999995
	// 2.000005
	// 1000 + (-999.99) = 0.01
	while ((tp.tv_sec - start.tv_sec) * 1000
		+ (tp.tv_usec - start.tv_usec) / 1000 < ms)
	{
		usleep(500);
		gettimeofday(&tp, NULL);
	}
}

void	msleep3(unsigned int ms)
{
	struct timeval	start;
	struct timeval	tp;

	if (ms == 0)
		return ;
	gettimeofday(&start, NULL);
	tp = start;
	while ((tp.tv_sec - start.tv_sec) * 1000000
		+ (tp.tv_usec - start.tv_usec) < ms * 1000)
	{
		usleep(500);
		gettimeofday(&tp, NULL);
	}
}

void	msleep2(unsigned int ms, t_data *data)
{
	long	start;
	long	tp;

	if (ms == 0)
		return ;
	start = get_current_timestamp(data);
	tp = start;
	while (tp - start < ms)
	{
		usleep(1);
		tp = get_current_timestamp(data);
	}
}

void	eat_phil(t_phil *phil)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = phil->left;
	second = phil->right;
	if (phil->seat % 2 == 0)
	{
		first = phil->right;
		second = phil->left;
	}
	pthread_mutex_lock(first);
	// if (first == phil->left)
	// 	print_msg(phil, "has taken a fork (left)");
	// else
	// 	print_msg(phil, "has taken a fork (right)");
	print_msg(phil, "has taken a fork");
	pthread_mutex_lock(second);
	// if (second == phil->left)
	// 	print_msg(phil, "has taken a fork (left)");
	// else
	// 	print_msg(phil, "has taken a fork (right)");
	print_msg(phil, "has taken a fork");
	print_msg(phil, "is eating");
	pthread_mutex_lock(&phil->personal_lock);
	phil->times_eaten++;
	phil->time_of_last_eat = get_current_timestamp(phil->data);
	pthread_mutex_unlock(&phil->personal_lock);
	msleep2(phil->data->time_to_eat, phil->data);
	// msleep3(phil->data->time_to_eat);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

void	think_phil(t_phil *phil)
{
	print_msg(phil, "is thinking");
}

void	sleep_phil(t_phil *phil)
{
	print_msg(phil, "is sleeping");
	msleep2(phil->data->time_to_sleep, phil->data);
	// msleep3(phil->data->time_to_sleep);
}

bool	should_stop(t_data *data)
{
	bool	stop;

	pthread_mutex_lock(&data->global_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->global_mutex);
	return (stop);
}

void	run_phil(t_phil *phil)
{
	if (phil->seat % 2 == 0)
		msleep2(phil->data->time_to_eat / 2, phil->data);
	while (true)
	{
		think_phil(phil);
		if (should_stop(phil->data))
			break ;
		eat_phil(phil);
		if (should_stop(phil->data))
			break ;
		sleep_phil(phil);
		if (should_stop(phil->data))
			break ;
	}
	return ;
}

void	*start_proc(void *_phil)
{
	t_phil	*phil;

	phil = _phil;
	while (true)
	{
		pthread_mutex_lock(&phil->data->global_mutex);
		if (phil->data->pthread_error)
		{
			pthread_mutex_unlock(&phil->data->global_mutex);
			return (NULL);
		}
		if (phil->data->start)
			break ;
		pthread_mutex_unlock(&phil->data->global_mutex);
	}
	pthread_mutex_unlock(&phil->data->global_mutex);
	run_phil(phil);
	return (NULL);
}

void	start_phils(t_data *data)
{
	pthread_mutex_lock(&data->global_mutex);
	gettimeofday(&data->start_time, NULL);
	data->start = true;
	pthread_mutex_unlock(&data->global_mutex);
}

t_status	join_phils(int phils_to_join, t_data *data)
{
	while (phils_to_join > 0)
	{
		phils_to_join--;
		pthread_join(data->phils[phils_to_join].soul, NULL);
	}
	if (data->pthread_error)
		return (set_err(E_THREAD_FAIL));
	return (OK);
}

void	monitor_phils(t_data *data)
{
	t_phil	*phil;
	int		i;
	bool	ok_eats;
	long	timestamp;
	t_phil	*kill;

	kill = NULL;
	while (true)
	{
		timestamp = get_current_timestamp(data);
		ok_eats = (data->num_eat > 0);
		i = 0;
		while (i < data->num_phil)
		{
			phil = &data->phils[i];
			pthread_mutex_lock(&phil->personal_lock);
			if (timestamp - phil->time_of_last_eat >= data->time_to_die)
				kill = phil;
			if (ok_eats && phil->times_eaten < data->num_eat)
				ok_eats = false;
			pthread_mutex_unlock(&phil->personal_lock);
			i++;
		}
		if (kill != NULL || ok_eats)
		{
			pthread_mutex_lock(&data->global_mutex);
			data->stop = true;
			pthread_mutex_unlock(&data->global_mutex);
			if (kill != NULL)
				print_msg_unchecked(kill, "died");
			return ;
		}
	}
}

t_status	run_all_phils(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->global_mutex, NULL) != 0)
		return (set_err(E_MALLOC_FAIL));
	data->stop = false;
	data->start = false;
	data->pthread_error = false;
	i = 0;
	while (i < data->num_phil)
	{
		if (pthread_create(&data->phils[i].soul, NULL, start_proc,
				&data->phils[i]) != 0)
		{
			pthread_mutex_lock(&data->global_mutex);
			data->pthread_error = true;
			pthread_mutex_unlock(&data->global_mutex);
			start_phils(data);
			return (join_phils(i, data));
		}
		i++;
	}
	start_phils(data);
	monitor_phils(data);
	return (join_phils(i, data));
}

void	free_data(t_data *data)
{
	if (data->fork_mutexes != NULL)
		free_fork_mutexes(&data->fork_mutexes, data->num_phil);
	if (data->phils != NULL)
		free_phils(&data->phils, data->num_phil);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.fork_mutexes = NULL;
	data.phils = NULL;
	if (parse_args(argc, argv, &data) != OK || create_fork_mutexes(&data) != OK
		|| create_phils(&data) != OK || run_all_phils(&data) != OK)
	{
		free_data(&data);
		print_err();
		return (EXIT_FAILURE);
	}
	free_data(&data);
	return (EXIT_SUCCESS);
}
