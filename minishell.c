/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:35:45 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/25 23:04:15 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
<<<<<<< HEAD


// int	main(int ac, char **av, char **envs)
// {
// 	t_list *commands;
// 	while(1)
// 	{
// 		char *line=
// 		//command=parser();
// 		//commands = init_commands();
// 		executer(commands,envs);
// 		free(commands);
// 		//exit(0);
// 	}
// 	return (0);
// }
=======
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
>>>>>>> 66fa37c3a86b8809a3d4b3b9b1a12645b071a271
