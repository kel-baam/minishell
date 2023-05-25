#include "../minishell.h"


void	preorder_traversal(t_node *head)
{
	if (head == NULL)
		return ;
	if(head->left)
   		printf("%s=%s\n", head->key, head->value);
	preorder_traversal(head->left);
	preorder_traversal(head->right);
}

void ft_env()
{
    preorder_traversal(g_data.env_vars);
}

