#include "binary_sort_tree.h"

BST_status BST_init(BinarySortTreePtr BST,ElemType data) {
    Node* node=(Node*)malloc(sizeof(Node));//����һ���ڵ�
    node->value = data;
    node->left = NULL;
    node->right = NULL;
    BST->root = node;
    printf("��ʼ���Ҳ���ɹ�\n");
    return succeed;
}

BST_status BST_insert(BinarySortTreePtr BST, ElemType data) {
    printf("��������\n");
    scanf("%d",&data);
    if (BST->root == NULL)
        BST_init(BST,data);
    else {
        Node* node=(Node*)malloc(sizeof(Node));
        node->value=data;
        node->left=NULL;
        node->right=NULL;
        Node* temp = BST->root;
        while (temp != NULL) {
            if (data < temp->value) {
                if (temp->left == NULL) {
                    temp->left = node;
                    printf("����ɹ�\n");
                    return succeed;
                } else
                    temp = temp->left;
            }
            if (data > temp->value) {
                if (temp->right == NULL) {
                    temp->right = node;
                    printf("����ɹ�\n");
                    return succeed;
                } else
                    temp = temp->right;
            }
            if(data == temp->value) {
                printf("�����Ѵ���,����ʧ��\n");
                return failed;
            }
        }
    }
}

BST_status BST_search(BinarySortTreePtr BST, ElemType data) {
    if (BST->root == NULL) {
        printf("��Ϊ��\n");
        return failed;
    }
    printf("��������\n");
    scanf("%d",&data);
    Node* temp = BST->root;
    while (1) {
        if (temp->value == data) {
            printf("%d������\n",data);
            return succeed;
        }
        if (temp->value>data) {
            if(temp->left==NULL)
                break;
            temp = temp->left;
        }
        if (temp->value<data) {
            if(temp->right==NULL)
                break;
            temp = temp->right;
        }
    }
    printf("%d��������\n",data);
    return failed;
}

BST_status BST_delete(BinarySortTreePtr BST, ElemType data) {
    if (BST->root == NULL) {
        printf("��Ϊ��\n");
        return failed;
    }
    printf("��������\n");
    scanf("%d",&data);
    Node *p = BST->root;
    Node *pp = NULL;
    Node *temp=NULL;
    int flag=-1,target=0;
    while (p != NULL && p->value != data) {
        pp = p;
        if (data<p->value) {
            flag=0;
            p = p->left;
        }
        if (data>p->value) {
            flag=1;
            p = p->right;
        }
    }
    //������
    if (p == NULL) {
        printf("%d��������\n",data);
        return failed;
    }
    //ɾ�������ڸ��ڵ�
    if(p==BST->root) {
        //������һ���ӽڵ�
        if (p->left != NULL&&p->right==NULL) {
            temp=BST->root;
            BST->root=p->right;
            free(temp);
            temp=NULL;
        } else if (p->right != NULL&&p->left==NULL) {
            temp=BST->root;
            BST->root=p->right;
            free(temp);
            temp=NULL;
        }
        //��㲻�����ӽڵ�
        else if(p->right==NULL&&p->left==NULL) {
            free(BST->root);
            BST->root=NULL;
        }
        //�����������ӽڵ�
        if (p->left != NULL && p->right != NULL) {
            p=p->left;
            temp=p;
            while (p->right!=NULL) {
                target=1;
                temp=p;
                p=p->right;
            }
            BST->root->value=p->value;
            if(target==1)
                temp->right=NULL;
            if(target==0)
                temp->left=NULL;
            free(p);
            p=NULL;
        }
    }
    //ɾ�����ݲ��ڸ��ڵ�
    else if(p!=BST->root) {
        //������һ���ӽڵ�
        if (p->left != NULL&&p->right==NULL) {
            temp=p;
            p=p->left;
            free(temp);
            temp=NULL;
        } else if (p->right != NULL&&p->left==NULL) {
            temp=p;
            p=p->right;
            free(temp);
            temp=NULL;
        }
        //��㲻�����ӽڵ�
        else if(p->right==NULL&&p->left==NULL) {
            free(p);
            p=NULL;
        }
        //�����������ӽڵ�
        else if (p->left!=NULL && p->right!=NULL) {
            pp=p;
            temp=p;
            p=p->left;
            while (p->right!=NULL) {
                target=1;
                temp=p;
                p=p->right;
            }
            pp->value=p->value;
            if(target==1)
                temp->right=NULL;
            if(target==0)
                temp->left=NULL;
            free(p);
            p=NULL;
            printf("�ɹ�ɾ��%d\n",data);
            return succeed;
        }
        if(flag==0)
            pp->left=NULL;
        if(flag==1)
            pp->right=NULL;
    }
    printf("�ɹ�ɾ��%d\n",data);
    return succeed;
}

BST_status BST_preorderR(NodePtr root) {
    if(root==NULL)
        return;
    printf("%d ",root->value);
    BST_preorderR(root->left);
    BST_preorderR(root->right);
}

BST_status BST_inorderR(NodePtr root) {
    if(root==NULL)
        return;
    BST_preorderR(root->left);
    printf("%d ",root->value);
    BST_preorderR(root->right);
}

BST_status BST_postorderR(NodePtr root) {
    if(root==NULL)
        return;
    BST_preorderR(root->left);
    BST_preorderR(root->right);
    printf("%d ",root->value);
}

BST_status BST_preorderI(BinarySortTreePtr BST) {
    if (BST->root == NULL) {
        printf("��Ϊ��\n");
        return failed;
    }
    NodePtr stack[20];
    int top=-1;
    NodePtr node=BST->root;
    while(node!=NULL||top!=-1) {
        if(node!=NULL) {
            stack[++ top] = node;
            printf("%d ",node->value);
            node = node->left;
        } else {
            node = stack[top --];
            node = node->right;
        }
    }
    return succeed;
}


BST_status BST_inorderI(BinarySortTreePtr BST) {
    if (BST->root == NULL) {
        printf("��Ϊ��\n");
        return failed;
    }
    NodePtr stack[20];
    int top = -1;
    NodePtr node=BST->root;
    while(node!=NULL||top!=-1) {
        if(node!=NULL) {
            stack[++top]=node;
            node=node->left;
        } else {
            node=stack[top--];
            printf("%d ",node->value);
            node = node->right;
        }
    }
    return succeed;
}

BST_status BST_postorderI(BinarySortTreePtr BST) {
    if (BST->root == NULL) {
        printf("��Ϊ��\n");
        return failed;
    }
    NodePtr stack[20];
    int top = -1;
    int flagStack[15];
    NodePtr node=BST->root;
    while(node!=NULL||top!=-1) {
        if(node!=NULL) {
            stack[++ top] = node;
            flagStack[top] = 1;
            node = node->left;
        } else {
            if(flagStack[top] == 1) {
                node = stack[top];
                flagStack[top] = 2;
                node = node->right;
            } else {
                node = stack[top --];
                printf("%d ",node->value);
                node = NULL;
            }
        }
    }
    return succeed;
}

BST_status BST_levelOrder(BinarySortTreePtr BST) {
    if (BST->root == NULL) {
        printf("��Ϊ��\n");
        return failed;
    }
    NodePtr stack[20];
    int front=0,back=0;
    NodePtr node=BST->root;
    stack[front++]=node;
    while(front>back) {
        node=stack[back];
        if(node!=NULL) {
            printf("%d ",node->value);
            if(node->left!=NULL)
                stack[front++]=node->left;
            if(node->right!=NULL)
                stack[front++]=node->right;
        }
        back++;
    }
    return succeed;
}
