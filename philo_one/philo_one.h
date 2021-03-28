/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:00:36 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 13:28:22 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define TRUE 1
# define FALSE 0

# define SUCCESS 1
# define ERROR 0

# define CNRM  "\x1B[0m"
# define CRED  "\x1B[31m"
# define CGRN  "\x1B[32m"
# define CYEL  "\x1B[33m"
# define CBLU  "\x1B[34m"
# define CMAG  "\x1B[35m"
# define CCYN  "\x1B[36m"
# define CWHT  "\x1B[37m"

int						g_num_philo;

typedef struct			s_table
{
	int					num_philo;
	size_t				time_life;
	size_t				time_eat;
	size_t				time_sleep;
	int					num_count_eat;
	size_t				start_table;
	int					flag_eat_required_times;
	int					count_full_philos;
	int					death;
	pthread_t			*threads;
}						t_table;

typedef struct			s_philo {
	unsigned int		id;
	size_t				last_eat;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*die_mutex;
	pthread_mutex_t		*last_eat_mutex;
	pthread_mutex_t		*print_mutex;
	t_table				*table;
	int					eating_count;
}						t_philo;

typedef struct			s_garbage {
	pthread_mutex_t		*forks;
	pthread_mutex_t		*die_mutex;
	pthread_mutex_t		*last_eat_mutex;
	pthread_mutex_t		*print_mutex;
}						t_garbage;

int						create_table_new(t_table *table);
void					*philo_life_new(void *data);
int						ft_atoi(const char *str);
size_t					time_unix_seconds(void);
void					ft_putstr_fd(const char *s, int fd);
int						sleep_in_ms(size_t time, t_philo *philo);
int						error(const char *error_str);
void					logging(t_philo *philo, const char *str);
size_t					ft_strlen(const char *s);
int						is_philo_die(t_philo *philo);
int						is_philo_has_eaten_req_times(t_philo *philo);
int						init_philos
(t_table *table, t_philo **philos, t_garbage *garbage);
int						setup_threads
(pthread_t **threads, t_philo *philos, t_table *table);

#endif
