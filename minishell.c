/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:35:45 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/04 18:51:29 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
//echo \n \0

char **convert_tree_to_array()
{
	int p=0;
	char **envs=malloc(sizeof(char*)*g_data.count_envs + 1);
	char **store= store_envs(g_data.env_vars,envs,&p);

	envs[p] =NULL;

	return envs;
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

		 if(line)
		 ft_free(line);
		tcsetattr(STDIN_FILENO, TCSANOW, &(g_data.newTerm));
		line=readline( PERPOL" beautiful as a shell 😍: $ " RESET);

		if(line)
		{
			if(!ft_strlen(line) || !strcmp(line,"\n"))
				continue;
			add_history(line);
			commands = parser(line);
			executer(commands);
			add_node(&(g_data.env_vars),"?",ft_itoa(g_data.status_code),NULL);
			//printf("%d\n",g_data.status_code);

		}
		else
			exit(g_data.status_code);
		//free(commands);
	}
	return (0);
}

