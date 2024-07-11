#include<iostream>

struct TreeElmt{
    void *data;
    struct TreeElmt *left;
    struct TreeElmt *right;
};

class Trees{
    private:
        int size;
        struct TreeElmt *root;
    public:
        Trees()
        {
            root=NULL;
            size=0;
        }

        void tree_destroy()
        {
            rem_left(NULL);
            // memset()
            return;
        }

        int ins_Left(struct TreeElmt *node, int _data)
        {
            struct TreeElmt *temp,**position;
            if(node==NULL)
            {
                if(size>0)
                {
                    return -1;
                }
                position=&root;
            }

            else
            {
                if(node->left!=NULL)
                {
                    return -1;
                }
                position=&node->left;
            }

            if((temp=(struct TreeElmt *)malloc(sizeof(TreeElmt)))==NULL)
            {
                return -1;
            }

            int *data=(int *)malloc(sizeof(int));
            *data=_data;
            temp->data=(void *)data;
            temp->left=NULL;
            temp->right=NULL;
            *position=temp;

            size++;
            return 0;
        }

        int ins_right(struct TreeElmt *node, int _data)
        {
            struct TreeElmt *temp,**position;

            if(node==NULL)
            {
                if(size>0)
                {
                    return -1;
                }
                position=&root;
            }

            else
            {
                if(node->right!=NULL)
                {
                    return -1;
                }
                position=&root->right;
                if((temp=(struct TreeElmt *)malloc(sizeof(struct TreeElmt)))==NULL)
                {
                    return -1;
                }

                int *data=(int *)malloc(sizeof(int));
                *data=_data;
                temp->data=(void *)data;
                temp->left=NULL;
                temp->right=NULL;
                *position=temp;

                size++;
                return 0;
            }
        }

        void rem_left(struct TreeElmt *node)
        {
            TreeElmt **position;
            if(size==0)
            {
                return;
            }

            if(node == NULL)
            {
                position=&root;
            }
            else
            {
                position=&node->left;
            }

            if(*position!=NULL)
            {
                rem_left(*position);
                rem_right(*position);

                free((*position)->data);
                free(*position);
                *position=NULL;
                size--;
            }
            return;
        }


        void rem_right(struct TreeElmt *node)
        {

        }
        TreeElmt* RetRoot()
        {
            return root;
        }
        void show()
        {
            std::cout<<*((int *)root->left->data);
        }
};

int main()
{
    Trees trees;
    trees.ins_Left(NULL,6);
    trees.ins_right(trees.RetRoot(),9);
    trees.ins_Left(trees.RetRoot(),3);
    trees.rem_left(trees.RetRoot());
    trees.show();
}