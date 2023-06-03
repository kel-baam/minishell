/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:35:45 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/31 11:22:21 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
void handel (int sig)
{
	// //printf("\33[2K");
	// printf("\n");
	// rl_on_new_line();
	// rl_replace_line("",0);
	// rl_redisplay();

}
int	main(int ac, char **av, char **envs)
{
	t_list		*commands;

	t_command	*data;
	char *line = NULL;
	//signal(SIGINT,)
	initilizer(envs);
	 // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &(g_data.newTerm));

	g_data.oldTerm = g_data.newTerm;

	signal(SIGINT,handel);
	signal(SIGQUIT,SIG_IGN);
    // Disable the printing of control characters
    g_data.newTerm.c_lflag &= ~ECHOCTL;
    // Apply the modified settings
	while (1)
	{
		if(line)
			ft_free(line);
		// tcsetattr(STDIN_FILENO, TCSANOW, &(g_data.newTerm));
		line=readline(">");
		if(line)
		{
			if(!strcmp(line,"\n"))
				continue;
			add_history(line);
			commands = init_commands();
			add_node(&(g_data.env_vars),"?",ft_itoa(g_data.status_code),NULL);
			executer(commands, envs);
			printf("%d\n",g_data.status_code);
		}
		else
			exit(g_data.status_code);
		//free(commands);

	}
	return (0);
}
<<<<<<< HEAD
>>>>>>> 66fa37c3a86b8809a3d4b3b9b1a12645b071a271
=======
>>>>>>> c498d5b4d1224187ca2019af8bdddd2060b23711
