/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:35:45 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/03 18:22:22 by kjarmoum         ###   ########.fr       */
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
	int p=0;
	char **envs=malloc(sizeof(char*)*g_data.count_envs);
	char **store= store_envs(g_data.env_vars,envs,&p);
	return store;
}
int	main(int ac, char **av, char **env)
{
	t_list		*commands;
	t_command	*data;

	char *line = NULL;
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

