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

#include "minishell.h"

char **convert_tree_to_array()
{
	// //printf("\33[2K");
	// printf("\n");
	// rl_on_new_line();
	// rl_replace_line("",0);
	// rl_redisplay();

	int p=0;
	char **envs=malloc(sizeof(char*)*g_data.count_envs);
	char **store= store_envs(g_data.env_vars,envs,&p);
	return store;
}
//check status code
// still herdoc to insert in my part
//finall touch like leaks
//finally norm
int	main(int ac, char **av, char **env)
{
	t_list		*commands;

	t_command	*data;
	
	char *line = NULL;
	//signal(SIGINT,)
	initilizer(envs);
	 // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &(g_data.newTerm));

	g_data.oldTerm = g_data.newTerm;
	signal(SIGQUIT,SIG_IGN);
    // Disable the printing of control characters
    g_data.newTerm.c_lflag &= ~ECHOCTL;
    // Apply the modified settings
	initilizer(env);
	signals_for_parent();
	while (1)
	{
		char **tmp_envs=convert_tree_to_array();

		if(line)
			ft_free(line);
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_data.newTerm));
		line=readline(">");
		if(line)
		{
			if(!strcmp(line,"\n"))
				continue;
			add_history(line);
			commands = init_commands();
			executer(commands, env);
			add_node(&(g_data.env_vars),"?",ft_itoa(g_data.status_code),NULL);
			printf("%d\n",g_data.status_code);
		}
		else
			exit(g_data.status_code);
		//free(commands);
	}
	return (0);
}

