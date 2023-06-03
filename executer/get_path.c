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

char	*get_right_path(char *cmd, t_command *data, char **envs)
{
	int		i;
	char	*absolute_path;
	char	*env;
	char	**paths;

	i = 0;
	env = get_env("PATH");
	// check _status code
	if (!env)
	{
		g_data.status_code = print_cmd_error(cmd, data->args[1],
				"No such file or directory", 127);
		exit(g_data.status_code);
	}
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
	if (!absolute_path)
		g_data.status_code = 127;
	return (absolute_path);
}

char	*get_actual_path(char *cmd, t_command *data, char **envs)
{
	int	status;

	// if (ft_strchr(cmd, '/'))
	// {
		status = 127;
		if (!access(cmd, F_OK))
		{
			if (!access(cmd, X_OK))
				return (ft_strdup(cmd));
			status = 126;
		}
		// g_data.status_code = print_cmd_error(cmd, NULL, strerror(errno),
				// status);
		// i call exit function here
		// exit(g_data.status_code);
	// }
	return (get_right_path(cmd, data, envs));
}
