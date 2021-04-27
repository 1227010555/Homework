#include "binary_sort_tree.h"

int main() {
    int choice=0;
    BinarySortTree bst;
    BinarySortTreePtr BST=&bst;
    BST->root=NULL;
    //用1使while死循环
    while(1) {
        printf("1.插入数字\t\t2.查找数字\n");
        printf("3.删除数字\t\t4.递归前序遍历\n");
        printf("5.递归中序遍历\t\t6.递归后序遍历\n");
        printf("7.迭代前序遍历\t\t8.迭代中序遍历\n");
        printf("9.迭代后序遍历\t\t10.层序遍历\n");
        printf("11.退出\n");
        printf("输入数字\n");
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
                    printf("树为空\n");
                    break;
                } else BST_preorderR(BST->root);
                break;
            case 5:
                if (BST->root == NULL) {
                    printf("树为空\n");
                    break;
                }
                BST_inorderR(BST->root);
                break;
            case 6 :
                if (BST->root == NULL) {
                    printf("树为空\n");
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
                printf("您输入的数据有误\n");
                break;
        }
        sleep(1);
        system("cls");
        getchar();
    }
}
