/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:08:58 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/18 16:09:02 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	inorder_traversal(t_node *head, int fd)
{
	char	qoute;

	if (head == NULL)
		return ;
	if (!ft_strncmp(head->key, "?", ft_strlen(head->key)))
		return ;
	qoute = '"';
	inorder_traversal(head->left, fd);
	if (!head->value)
	{
		write(fd, "declare -x ", 11);
		write(fd, head->key, ft_strlen(head->key));
		write(fd, "\n", 1);
	}
	else
	{
		write(fd, "declare -x ", 11);
		write(fd, head->key, ft_strlen(head->key));
		write(fd, "=", 1);
		write(fd, &qoute, 1);
		write(fd, head->value, ft_strlen(head->value));
		write(fd, &qoute, 1);
		write(fd, "\n", 1);
	}
	inorder_traversal(head->right, fd);
}

int	check_err_export(char *arg, char *key, char *cmd)
{
	if (is_valid_key(key) == -1)
	{
		g_data.status_code = print_cmd_error(cmd, arg, "not a valid identifier",
				1);
		return (-1);
	}
	return (0);
}

void	init_value(int *pos, int *flag, int *i, int *status)
{
	*pos = 0;
	*flag = 0;
	*i = 0;
	*status = 0;
}

void	my_free(char *value, char *key)
{
	ft_free(key);
	ft_free(value);
}
