/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:05:08 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/24 15:05:11 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

int	check_option(char *str)
{
	int	i;

	i = 0;
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (-1);
		i++;
	}
	return (i);
}
//problem in this function is when i have -n
int	ft_echo(t_command *command)
{
	int	i = 1;
	int	option;
	int	start;

	option = 0;
	while (command->args && check_option(command->args[i]) != -1)
	{
		option = 1;
		i++;
	}
	start = i;
	while (command->args[i])
	{
		if (i != start)
			printf(" ");
		printf("%s", command->args[i]);
		i++;
	}
	if (!option)
		printf("\n");
	return (0);
}
