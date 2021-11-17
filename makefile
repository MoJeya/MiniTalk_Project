# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 12:48:37 by mjeyavat          #+#    #+#              #
#    Updated: 2021/11/16 14:41:25 by mjeyavat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

SRC_1 = ./src/server.c

SRC_2 = ./src/client.c

DPNCY_1 = ./ft_printf/libftprintf.a

DPNCY_2 = ./ft_printf/libft/libft.a


all: server client

server: $(SRC_1) linked_objects
	gcc $(CFLAGS) -o server $(SRC_1) $(DPNCY_1) $(DPNCY_2)

client: $(SRC_2) linked_objects
	gcc $(CFLAGS) -o client $(SRC_2) $(DPNCY_1) $(DPNCY_2)

linked_objects:
	make -C ./ft_printf
	make -C ./ft_printf/libft

clean: server client
	rm -f server
	rm -f client

fclean: clean
	rm -f ./ft_printf/*.o
	rm -f ./ft_printf/*.a
	rm -f ./ft_printf/libft/*.o
	rm -f ./ft_printf/libft/*.a

re: fclean all