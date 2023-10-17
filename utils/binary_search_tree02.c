/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:03:44 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/25 01:11:58 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_child_to_parent(t_node *node, t_node *child_node)
{
	t_node	*node_parent;

	if (node)
	{
		node_parent = node->parent;
		if (node_parent)
		{
			if (node_parent->right == node)
				node_parent->right = child_node;
			else
				node_parent->left = child_node;
		}
	}
}

void	switch_nodes(t_node *min_node, t_node *to_delete_node)
{
	if (min_node)
	{
		add_child_to_parent(min_node, min_node->right);
		min_node->left = to_delete_node->left;
		min_node->right = to_delete_node->right;
		min_node->parent = to_delete_node->parent;
		add_child_to_parent(to_delete_node->left, min_node);
		add_child_to_parent(to_delete_node->right, min_node);
		add_child_to_parent(to_delete_node, min_node);
	}
}

t_node	*link_two_nodes(t_node **to_delete_node, t_node *child_node)
{
	t_node	*new_root;

	add_child_to_parent(*to_delete_node, child_node);
	new_root = child_node;
	return (new_root);
}

void	free_(t_node *to_delete_node)
{
	free_node(&to_delete_node);
	g_data.count_envs--;
}

void	remove_node(t_node **head, char *key)
{
	t_node	*to_delete_node;
	t_node	*new_root;
	t_node	*min_node;

	if (!head)
		return ;
	to_delete_node = get_node(*head, key);
	if (!to_delete_node || (to_delete_node->key
			&& !ft_strncmp(to_delete_node->key, "?", 1)))
		return ;
	if (to_delete_node->right == NULL && to_delete_node->left == NULL)
		new_root = link_two_nodes(&to_delete_node, NULL);
	else if (to_delete_node->right == NULL)
		new_root = link_two_nodes(&to_delete_node, to_delete_node->left);
	else if (to_delete_node->left == NULL)
		new_root = link_two_nodes(&to_delete_node, to_delete_node->right);
	else
	{
		min_node = get_most_left(to_delete_node->right);
		switch_nodes(min_node, to_delete_node);
		new_root = min_node;
	}
	if (*head == to_delete_node)
		*head = new_root;
	free_(to_delete_node);
}
