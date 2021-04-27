#include "binary_sort_tree.h"

int main() {
    int choice=0;
    BinarySortTree bst;
    BinarySortTreePtr BST=&bst;
    BST->root=NULL;
    //��1ʹwhile��ѭ��
    while(1) {
        printf("1.��������\t\t2.��������\n");
        printf("3.ɾ������\t\t4.�ݹ�ǰ�����\n");
        printf("5.�ݹ��������\t\t6.�ݹ�������\n");
        printf("7.����ǰ�����\t\t8.�����������\n");
        printf("9.�����������\t\t10.�������\n");
        printf("11.�˳�\n");
        printf("��������\n");
        scanf("%d",&choice);
        switch(choice) {
            case 1:
                BST_insert(BST,0);
                break;
            case 2:
                BST_search(BST,0);
                break;
            case 3:
                BST_delete(BST,0);
                break;
            case 4:
                if (BST->root == NULL) {
                    printf("��Ϊ��\n");
                    break;
                } else BST_preorderR(BST->root);
                break;
            case 5:
                if (BST->root == NULL) {
                    printf("��Ϊ��\n");
                    break;
                }
                BST_inorderR(BST->root);
                break;
            case 6 :
                if (BST->root == NULL) {
                    printf("��Ϊ��\n");
                    break;
                }
                BST_postorderR(BST->root);
                break;
            case 7 :
                BST_preorderI(BST);
                break;
            case 8 :
                BST_inorderI(BST);
                break;
            case 9 :
                BST_postorderI(BST);
                break;
            case 10:
                BST_levelOrder(BST);
                break;
            case 11:
                return;
            default:
                printf("���������������\n");
                break;
        }
        sleep(1);
        system("cls");
        getchar();
    }
}
