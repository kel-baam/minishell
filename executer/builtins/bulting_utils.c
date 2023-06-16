/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:03:10 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/21 16:03:12 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

int	is_bultin(char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (0);
	if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (0);
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (0);
	if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (0);
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (0);
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (0);
	if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (0);
	return (1);
}
// TO DO error in len of commands
int	execute_bultin(t_command *command, int outfile)
{
	
	if (!ft_strncmp(command->cmd, "env", ft_strlen(command->cmd)))
		return (ft_env(outfile));
	else if (!ft_strncmp(command->cmd, "echo", ft_strlen(command->cmd)))
		return (ft_echo(command));
	else if (!ft_strncmp(command->cmd, "unset", ft_strlen(command->cmd)))
		return (ft_unset(command));
	else if (!ft_strncmp(command->cmd, "export", ft_strlen(command->cmd)))
		return (ft_export(command, outfile));
	else if (!ft_strncmp(command->cmd, "cd", ft_strlen(command->cmd)))
		return (ft_cd(command));
	if (!ft_strncmp(command->cmd, "pwd", ft_strlen(command->cmd)))
		return (ft_pwd(command->cmd, outfile));
	if (!ft_strncmp(command->cmd, "exit", ft_strlen(command->cmd)))
		return (ft_exit(command));
	return (0);
}

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	while ( key && key[i])
	{
		if (key[i] == '.')
			return (-1);
		i++;
	}
	printf("Ff\n");
	if (key[0] == '_')
		return (0);
	if ((key[0] >= 'a' && key[0] <= 'z') || (key[0] >= 'A' && key[0] <= 'Z'))
		return (0);
	return (-1);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (-1);
	}
	return (i);
}

