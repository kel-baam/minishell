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
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
void handel_Quit(int sig)
{
		printf("\n");
        rl_on_new_line();
     //  rl_replace_line(" ", 0);
        rl_redisplay();
}


int	main(int ac, char **av, char **envs)
{
	t_list *commands;
	//char *line = NULL;
	// ignore quit
	//signal(SIGINT,handel_Quit);
	initilizer(envs);
	
	 while(1)
 {
		commands = init_commands();
	// 	//commands = parser(line);
	// 	//add_history(line);
	 	executer(commands,envs);
	 	free(commands);
		//exit(1);

	 }

	return (0);
}