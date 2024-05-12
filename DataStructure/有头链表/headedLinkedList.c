#include <stdio.h>
#include <stdlib.h>

// 节点结构体
typedef struct Node
{
    int data;
    struct Node *next;

} Node;

// 头插法
Node *inster(Node *head, int data)
{
    // 创建要插入的节点
    Node *node = malloc(sizeof(Node));
    if (node == NULL)
    {
        printf("Memory allocation failed.\n");
        return head; // 如果内存分配失败，则返回原头节点
    }

    node->data = data;

    // 如果没有头节点，则直接让当前节点为头节点即可
    if (head == NULL)
    {
        node->next = NULL;
        head = node;
    }
    else
    {
        // 如果头节点不为空，则插入到头部
        node->next = head;
        head = node;
    }
    // 返回插入成功的链表首地址
    return head;
}

// 遍历链表
void PrintNodeLink(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        printf("节点数据:%d\n", temp->data);
        temp = temp->next;
    }
}

int main(int argc, char const *argv[])
{
    // 定义头节点
    Node *head = NULL;

    // 创建节点并插到头部
    head = inster(head, 10);
    head = inster(head, 13);

    // 遍历链表
    PrintNodeLink(head);

    return 0;
}
