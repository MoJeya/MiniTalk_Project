/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:09:03 by mjeyavat          #+#    #+#             */
/*   Updated: 2021/11/08 19:27:21 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static int	ft_error(void)
{
	ft_printf("An Error has occurred\n");
	ft_printf("Make sure the server is runing!\n");
	ft_printf("Run the client with ./client [server_pid] [String]\n");
	return (0);
}

/**
 * These two signals are used to represent the binary value's 0 and 1
 * SIGUSR1 = 1
 * SIGUSR2 = 0
 * The signals will be send in sequence coresponding to the binary
 * value of the string
 * the (0b10000000) stands for he number 8
 *
*/
static int	ft_send_message(const char *str, pid_t pid)
{
	int				i;
	unsigned char	bits;
	int				len;

	i = 0;
	if (str == NULL)
		return (-1);
	len = ft_strlen(str);
	while (i < len)
	{
		bits = 0b10000000;
		while (bits)
		{
			if (bits & (unsigned char)str[i])
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bits >>= 1;
			usleep(100);
		}
		i++;
	}
	return (0);
}

static void	ft_sighndl(int signum)
{
	(void)signum;
	ft_printf("An Error has occured!");
	exit(EXIT_SUCCESS);
}
/*
the pause() is there so it can pause after the message got encoded that
way it will send the string only one time
*/

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc != 3 && !ft_error())
		return (-1);
	else if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (pid > 1)
		{
			ft_printf("Sending data to : %d\n...\n", pid);
			while (1)
			{
				if (signal(SIGUSR1, ft_sighndl) < 0)
					exit(EXIT_FAILURE);
				ft_send_message(argv[2], pid);
				pause();
			}
		}
	}
	return (0);
}
