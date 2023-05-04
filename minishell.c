/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:35:45 by kel-baam          #+#    #+#             */
/*   Updated: 2023/03/26 14:35:48 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(int ac, char **av, char **envs)
{
	t_list *commands;
	while(1)
	{
		//command=parser();
		commands = init_commands();
		executer(commands,envs);
		free(commands);
		exit(0);
	}
	return (0);
}