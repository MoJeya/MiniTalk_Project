/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_side.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:35:53 by mjeyavat          #+#    #+#             */
/*   Updated: 2021/11/15 19:11:51 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minitalk.h"

/**as soon as it reaches 8 bits it will print the the char
 * the left shift is the same as 2^n
 * the kill(info-> si_pid, sigusr1) The si_pid field contains the pid of the process who's status changed,
*/

static void	ft_put_to_screen(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				bit_cnt;

	(void)context;
	if (sig == SIGUSR1)
		sig = 1;
	else if (sig == SIGUSR2)
		sig = 0;
	if (c == 0 && bit_cnt == 0)
		bit_cnt = 8;
	bit_cnt--;
	c += sig << bit_cnt;
	if (bit_cnt == 0)
	{
		if (!c)
		{
			kill(info->si_pid, SIGUSR1);
		}
		write(1, &c, 1);
		bit_cnt = 8;
		c = 0;
	}
}

/*
*	Sigaction: examine and change a signal action
	Sigempty set has to be called to initzials the struct
	1.	the struct will be set empty and than a new signlahandler will be hooked to
		the struct.
	2.	The Proccess ID will be printed to the teerminal.
	3.	The Sigaction will examine the signals SIGUSR1/2 and catch the signals if there seems to be a problem
		the programm will exit after that.
	4.	if the Signals are alright than the programm will wait for a signal

*/

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	ft_memset(&sa, '\0', sizeof(char));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ft_put_to_screen;
	sa.sa_flags = SA_SIGINFO;
	printf("Server starts...\n");
	printf("Proccess ID: %d\n", getpid());
	printf("===========================\n");
	while (1)
	{
		if (sigaction(SIGUSR1, &sa, NULL) < 0
			|| sigaction(SIGUSR2, &sa, NULL) < 0)
		{
			printf("There seems to be a problem!");
			exit(EXIT_FAILURE);
		}
		pause();
	}
	return (0);
}
