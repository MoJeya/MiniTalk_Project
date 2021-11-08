/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:18:35 by mjeyavat          #+#    #+#             */
/*   Updated: 2021/11/08 17:37:26 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	server_start(void)
{
	ft_printf("The Server is Starting\n");
	ft_printf("========================\n");
	ft_printf("Process ID: %d\n", getpid());
}

static void	ft_print_message(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static size_t			s;

	(void)context;
	if (sig == SIGUSR2)
		sig = 0;
	else if (sig == SIGUSR1)
		sig = 1;
	if (c == 0 && s == 0)
		s = 8;
	s--;
	c += (sig & 1) << s;
	if (s == 0)
	{
		if (!c)
		{
			ft_printf("\n");
			kill(info->si_pid, SIGUSR1);
		}
		ft_printf("%c", c);
		s = 8;
		c = 0;
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	server_start();
	ft_memset(&sa, '\0', sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = ft_print_message;
	sa.sa_flags = SA_SIGINFO;
	while (1)
	{
		if (sigaction(SIGUSR1, &sa, NULL) < 0
			|| sigaction(SIGUSR2, &sa, NULL) < 0)
		{
			ft_printf("there seems to be a Problem");
			exit(EXIT_FAILURE);
		}
		pause();
	}
	return (0);
}
