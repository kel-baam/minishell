/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:27:09 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/25 01:52:48 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_new_value(int pos, char *arg, char **value, char **key)
{
	char	*new_value;
	char	*old_value;
	char	*tmp;

	tmp = *key;
	*key = ft_substr(arg, 0, pos - 1);
	ft_free(tmp);
	old_value = get_env(*key);
	new_value = ft_substr(arg, pos + 1, ft_strlen(arg));
	if (!old_value)
		old_value = "";
	tmp = *value;
	*value = ft_strjoin(old_value, new_value);
	ft_free(new_value);
	ft_free(tmp);
}

void	check_egal_pos(char **arg, int *pos, int *flag, int i)
{
	*pos = searching_for_char(arg[i], '=');
	if (arg[i] && *pos > 0 && arg[i][*pos - 1] == '+')
		*flag = 1;
}

void	case_pos_negative(char **key, char **value, char *arg)
{
	*key = ft_strdup(arg);
	*value = ft_strdup("");
}

int	add_new_element(t_command *cmd)
{
	int		i;
	int		pos;
	char	*key;
	char	*value;
	int		flag;

	init_value(&pos, &flag, &i, &g_data.status_code);
	while (cmd->args && cmd->args[++i])
	{
		check_egal_pos(cmd->args, &pos, &flag, i);
		if (pos == -1)
			case_pos_negative(&key, &value, cmd->args[i]);
		if (!flag && pos > 0)
			key = ft_substr(cmd->args[i], 0, pos);
		else if (flag)
			key = ft_strdup(cmd->args[i]);
		if (pos >= 0)
			value = ft_substr(cmd->args[i], pos + 1, ft_strlen(cmd->args[i]));
		if (flag)
			add_new_value(pos, cmd->args[i], &value, &key);
		if (!check_err_export(cmd->args[i], key, cmd->cmd))
			add_node(&(g_data.env_vars), key, value, NULL);
		my_free(value, key);
	}
	return (g_data.status_code);
}

int	ft_export(t_command *command, int fd)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	if (command->args && command->args[i])
	{
		status = add_new_element(command);
	}
	else
		inorder_traversal(g_data.env_vars, fd);
	return (status);
}
