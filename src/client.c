/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:23:16 by mjeyavat          #+#    #+#             */
/*   Updated: 2021/11/16 15:06:35 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

int	ft_convert_to_bin(pid_t pid, char *str)
{
	unsigned char		bits;
	size_t				i;

	i = 0;
	while (i < ft_strlen(str))
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

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_printf("Pleas enter the right Arguments:\n./client <Pid> <Message>\n");
		return (-1);
	}
	else if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (1)
		{
			ft_convert_to_bin(pid, argv[2]);
			pause();
		}
	}
	return (0);
}
