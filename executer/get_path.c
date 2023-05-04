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

char	*get_right_path(char *cmd, t_command *data)
{
	int		i;
	char	*absolute_path;
	char *envs;
	char **paths;

	i = 0;
	envs=getenv("PATH");
	paths = ft_split(envs, ':');
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

char	*get_actual_path(char *cmd, t_command *data)
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
	
	return (get_right_path(cmd, data));
}
