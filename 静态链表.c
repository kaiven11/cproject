#include <stdio.h>
#include <stdlib.h>


//链表分为静态链表和动态链表


// 链表从结构上说分为  单向链表  双向链表  单项循环链表 双向循环链表  循环链表

// 从 有无头节点  来分  有头节点 链表  无头节点链表


//下面实现 静态单项链表


struct linknode
{
	int  value;
	struct linknode* p;
};

int main01(void) {

	struct linknode  node1;
	struct linknode  node2;
	struct linknode  node3;
	struct linknode  node4;

	//init node1
	node1.value = -1;
	node1.p = &node2;

	//init node2

	node2.value = 10;
	node2.p = &node3;


	//init node3

	node3.value = 20;
	node3.p = &node4;

	//init node4


	node4.value = 30;
	node4.p = NULL;

	
	//循环链表

	//起始地址

	struct linknode* start_point = &node1;

	struct linknode* current_point = start_point;

	for (int  i = 0; i < 4; i++)
	{
		printf("%d\n",current_point->value);
		current_point = current_point->p;
	}


	return 0;
}