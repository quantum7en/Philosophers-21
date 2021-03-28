/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelinda <pmelinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:00:36 by pmelinda          #+#    #+#             */
/*   Updated: 2021/03/13 14:34:31 by pmelinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>

# define TRUE 1
# define FALSE 0

# define SUCCESS 1
# define ERROR 0

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
	sem_t				*forks;
	sem_t				*print;
	sem_t				*last_eat_mutex;
	sem_t				*waiter;
}						t_table;

typedef struct			s_philo {
	unsigned int		id;
	int					actual_count_eat;
	size_t				last_eat;
	int					has_eaten_req_times;
	t_table				*table;
	int					eating_count;
	pthread_t			*daughter_thread;
}						t_philo;

int						create_table_new(t_table *table);
void					*philo_life_new(void *data);
int						ft_atoi(const char *str);
size_t					time_unix_seconds(void);
void					ft_putstr_fd(const char *s, int fd);
int						sleep_in_ms(size_t time);
int						error(const char *error_str);
void					logging(t_philo *philo, const char *str);
size_t					ft_strlen(const char *s);
int						is_exit(t_philo *philo);
int						is_philo_die(t_philo *philo);
int						is_philo_has_eaten_req_times(t_philo *philo);

#endif
