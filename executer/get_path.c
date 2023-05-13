/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:29:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/03 10:29:29 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	*get_env(char **envs, char *var)
{
	int		i;
	char	**tmp_var;
	char	*value;

	i = 0;
	value = NULL;
	while (envs[i])
	{
		tmp_var = ft_split(envs[i], '=');
		if (tmp_var)
		{
			if (!strcmp(tmp_var[0], var))
			{
				value = ft_strdup(tmp_var[1]);
				free_double_ptr(tmp_var);
				break ;
			}
		}
		free_double_ptr(tmp_var);
		i++;
	}
	return (value);
}

char	*get_right_path(char *cmd, t_command *data,char **envs)
{
	int		i;
	char	*absolute_path;
	char	*env;
	char	**paths;

	i = 0;
	env = get_env(envs,"PATH");
	if (!env)
		print_cmd_error(cmd, "No such file or directory", 1, STDERR_FILENO);
	paths = ft_split(env, ':');
	absolute_path = NULL;
	cmd = ft_strjoin("/", cmd);
	while (paths[i])
	{
		absolute_path = ft_strjoin(paths[i], cmd);
		if (!access(absolute_path, F_OK | X_OK))
			break ;
		free(absolute_path);
		absolute_path = NULL;
		i++;
	}
	return (absolute_path);
}

char	*get_actual_path(char *cmd, t_command *data,char **envs)
{
	int	status;

	if (ft_strchr(cmd, '/'))
	{
		status = 127;
		if (!access(cmd, F_OK))
		{
			if (!access(cmd, X_OK))
				return (ft_strdup(cmd));
			status = 126;
		}
		print_cmd_error(cmd, strerror(errno), status, STDERR_FILENO);
	}
	return (get_right_path(cmd, data,envs));
}
