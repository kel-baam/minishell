/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:27:40 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/25 01:31:30 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*new_node(char *key, char *value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node)
	{
		node->key = ft_strdup(key);
		node->value = ft_strdup(value);
		node->left = NULL;
		node->right = NULL;
		node->parent = NULL;
	}
	return (node);
}

void	add_node(t_node **head, char *key, char *value, t_node *parent)
{
	t_node	*tmp;
	int		cmp;

	tmp = NULL;
	tmp = *head;
	if (tmp == NULL)
	{
		*head = new_node(key, value);
		(*head)->parent = parent;
		g_data.count_envs++;
		return ;
	}
	cmp = ft_strcmp(key, tmp->key);
	if (!cmp)
	{
		ft_free(tmp->value);
		tmp->value = ft_strdup(value);
		return ;
	}
	if (cmp > 0)
		add_node(&(tmp->right), key, value, tmp);
	else
		add_node(&(tmp->left), key, value, tmp);
}

t_node	*get_node(t_node *head, char *key)
{
	int	cmp;

	if (!head || !key)
		return (NULL);
	cmp = ft_strcmp(key, head->key);
	if (!cmp)
		return (head);
	if (cmp > 0)
		return (get_node(head->right, key));
	else
		return (get_node(head->left, key));
}

t_node	*get_most_left(t_node *node)
{
	t_node	*tmp;

	if (!node)
		return (NULL);
	tmp = node;
	while (tmp->left)
	{
		tmp = tmp->left;
	}
	return (tmp);
}

char	**convert_tree_to_array(void)
{
	int		p;
	char	**envs;
	char	**store;

	p = 0;
	envs = malloc(sizeof(char *) * (g_data.count_envs + 1));
	store = store_envs(g_data.env_vars, envs, &p);
	envs[p] = NULL;
	return (envs);
}
