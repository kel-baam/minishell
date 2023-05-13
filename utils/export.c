#include "../minishell.h"


t_tree* createnode(char* key,char *value)
{
    t_tree *tree=malloc(sizeof(t_tree));
    if(tree)
        {
            tree->key=key;
            tree->value=value;
            tree->left=NULL;
            tree->right=NULL;
        }
    return tree;
}

bool insert_num(t_tree **tree,char *key,char *value)
{
    t_tree *tmp=NULL;
    tmp =*tree;
    int cmp;
    if(tmp==NULL)
    {
        *tree=createnode(key,value);
        return true;
    }
    cmp=strcmp(tmp->key,key);
    if(!cmp)
        return false;
   if(cmp>0)
        return insert_num(&(tmp->left),key,value);
    if(cmp < 0)
        return insert_num(&(tmp->right),key,value);
    return true;
}
void inorder_traversal(t_tree *tree)
{
    if(tree==NULL)
        return;
    inorder_traversal(tree->left);
    printf("declare -x %s=%s\n", tree->key,tree->value);
    inorder_traversal(tree->right);
}
/// printf envs in alphabete order
void  ft_export()
{
    t_list *tmp;
    t_tree *tree=NULL;
    t_pair *tmp_pair=NULL;
    int i=0;
    while(i <TABLE_SIZE)
    {
        
       if (g_data.env_vars[i] == NULL)
       {
            i++;
            continue;
       }
       tmp_pair=(t_pair*)g_data.env_vars[i]->content;

        tmp=g_data.env_vars[i];
        insert_num(&tree,tmp_pair->key,tmp_pair->value);
        i++;
   }
    inorder_traversal(tree);
}
//unset 
// export 

void ft_unset (char *value)
{
    int i=0;
    t_list *tmp;
    t_pair *pair;
    while(i <TABLE_SIZE)
    {
        if(!(tmp=g_data.env_vars[i]))
            {
                i++;
                continue;
            }
           
               
        while(tmp)
        {
            pair=(t_pair*)tmp->content;
            if(!strcmp(value,pair->key))
                    {
                        free(pair->key);
                        free(pair->value);
                        pair->key=NULL;
                        pair->value=NULL;
                }
            tmp=tmp->next;
        }
        i++;
    }
}