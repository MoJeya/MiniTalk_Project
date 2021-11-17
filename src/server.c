/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:18:21 by mjeyavat          #+#    #+#             */
/*   Updated: 2021/11/16 15:15:07 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static void	ft_put_to_screen(int sig, siginfo_t *info)
{
	static unsigned char	c;
	static int				bit_cnt;

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

int	main(void)
{
	struct sigaction	sa;

	ft_memset(&sa, '\0', sizeof(char));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = (void *)ft_put_to_screen;
	sa.sa_flags = SA_SIGINFO;
	ft_printf("Server starts...\n");
	ft_printf("Proccess ID: %d\n", getpid());
	ft_printf("===========================\n");
	while (1)
	{
		if (sigaction(SIGUSR1, &sa, NULL) < 0
			|| sigaction(SIGUSR2, &sa, NULL) < 0)
		{
			ft_printf("There seems to be a problem!");
			exit(EXIT_FAILURE);
		}
		pause();
	}
	return (0);
}
