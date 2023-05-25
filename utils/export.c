#include "../minishell.h"


void	inorder_traversal(t_node *head)
{
	if (head == NULL)
		return ;
	inorder_traversal(head->left);
	///fix this
	if(!(head->value))
		printf("+++++declare -x %s\n", head->key);
	if(head->value)
    	printf("%s=\"%s\"\n", head->key, head->value);
	inorder_traversal(head->right);
}

