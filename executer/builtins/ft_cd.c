/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:04:48 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/24 15:04:53 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"
//final version
int	ft_cd(t_command *command)
{
	char		buff[1024];
	char		buff2[1024];
	struct stat	path_stat;
	if (!access(command->args[1], F_OK))
	{
		if (!stat(command->args[1], &path_stat))
		{
			if (S_ISDIR(path_stat.st_mode))
			{
				if (!access(command->args[1], X_OK))
				{
					if (!getcwd(buff, sizeof(buff)))
						return print_cmd_error(command->cmd,command->args[1], strerror(errno), 1);
					if (chdir(command->args[1]))
						return print_cmd_error(command->cmd,command->args[1], strerror(errno), 1);
					if (!getcwd(buff, sizeof(buff2)))
						return print_cmd_error(command->cmd,command->args[1], strerror(errno), 1);
					add_node(&g_data.env_vars, "OLDPWD", buff, NULL);
					add_node(&g_data.env_vars, "PWD", buff2, NULL);
				}
				else
					return print_cmd_error(command->cmd,command->args[1], strerror(errno), 1);
			}
			else
				return print_cmd_error(command->cmd,command->args[1], "Not a directory", 1);
		}
	}
	else
		return	print_cmd_error(command->cmd,command->args[1], strerror(errno), 1);
	return (g_data.status_code);
}
