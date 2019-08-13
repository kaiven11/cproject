#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

//根据用户输入的数值自动填充到链表中，有头节点  ,动态数组只能开辟堆空间，防止函数结束时被释放
struct LINKNODE
{
	int value;
	struct LINKNODE* p;
};

int main02(void) {

	printf("%s", "请输入节点的数值:");
	//init headnode
	struct LINKNODE headnode;
	headnode.value = -1;
	headnode.p = NULL;
	struct LINKNODE* start_node = &headnode;
	struct LINKNODE* current_node = start_node;

	int a = 0;
	while (a!=-1)
	{
	  scanf("%d", &a);
	  struct LINKNODE* heappoint = malloc(sizeof(struct LINKNODE));
	  //开辟对空间，这里的heappoint 指针在栈空间会自动释放
	  //不存在重复定义
	  heappoint->value = a;
	  heappoint->p = NULL;
	  current_node->p = heappoint;
	  current_node = heappoint;
	}

	current_node = start_node;
	while (current_node->p!=NULL)
	{

		printf("循环打印：%d\n", current_node->value);
		current_node = current_node->p;

	}

	//释放对空间
	return 0;

}