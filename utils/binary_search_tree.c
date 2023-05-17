
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

//it return 0 if a new ket added & 1 if we overwite the key
void	add_node(t_node **head, char *key, char *value, t_node *parent)
{
	t_node	*tmp;
	int		cmp;

	tmp = NULL;
	tmp = *head;
	//if(key && value=='\0')
	//value=NULL;
	if (tmp == NULL)
	{
		*head = new_node(key, value);
		(*head)->parent = parent;
		return ;
	}
	cmp = strcmp(key, tmp->key);
	if (!cmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
		return ;
	}
	if (cmp > 0)
		add_node(&(tmp->right), key, value, tmp);
	else
		add_node(&(tmp->left), key, value, tmp);
	// return (0);
}

t_node	*get_node(t_node *head, char *key)
{
	int	cmp;

	if (!head || !key)
		return (NULL);
	cmp = strcmp(key, head->key);
	if (!cmp)
		return (head);
	if (cmp > 0)
		return (get_node(head->right, key));
	else
		return (get_node(head->left, key));
}
//TODO remove node
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
void add_child_to_parent(t_node *node,t_node *child_node)
{
	t_node *node_parent=node->parent;
		if (node_parent)
		{
			// check if the node is on the right of it's parent
			if (node_parent->right == node)
					node_parent->right =child_node;
			else
				node_parent->left = child_node;
		}
}
void switch_nodes(t_node *node_1,t_node *node_2)
{
		add_child_to_parent(node_1,NULL);
		node_1->parent=node_2->parent;
		node_1->left=node_2->left;
		node_1->right=node_2->right;
		//MADE A LINK WHIT THE PARENT 
		add_child_to_parent(node_2,node_1);
}
void remove_node(t_node **head, char *key)
{
	if(!head)
		return ;
	t_node *to_delete_node = get_node(*head, key);
	if (!to_delete_node)
		return;
	t_node *new_root;
	if (to_delete_node->right == NULL && to_delete_node->left == NULL)
	{// 	// check if the to_delete_node is on the right of it's parent or left 
		add_child_to_parent(to_delete_node,NULL);
		new_root=NULL;
	}
	else if (to_delete_node->right == NULL)
	{ //left child
		add_child_to_parent(to_delete_node,to_delete_node->left);
		new_root=to_delete_node->left;
	}
	else if (to_delete_node->left == NULL)
	{
		add_child_to_parent(to_delete_node,to_delete_node->right);
		new_root=to_delete_node->right;
	}
	else
	{
		t_node *min_node = get_most_left(to_delete_node->right);
		switch_nodes(min_node,to_delete_node);
		new_root=min_node;
	}
	if(*head==to_delete_node)
		*head=new_root;
	free_node(&to_delete_node);
}