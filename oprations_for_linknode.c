#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "linknode.h"

//初始化动态链表

void InitLinkNode(struct LINKNODE** p) {


	//return value 

	struct LINKNODE** tmp = p;

	//init headnode

	struct LINKNODE* headnode = malloc(sizeof(struct LINKNODE));
	headnode->value = -1;
	headnode->p = NULL;

	struct LINKNODE* pRear = headnode;
	int a = 0 ;
	while (a!=-1)
	{
		scanf("%d", &a);
		struct LINKNODE* heappoint = malloc(sizeof(struct LINKNODE));
		//开辟对空间，这里的heappoint 指针在栈空间会自动释放
		//不存在重复定义
		heappoint->value = a;
		heappoint->p = NULL;
		pRear->p = heappoint;
		pRear = heappoint;
	}

	*tmp = headnode;

}


//遍历动态链表

void ForeachNode(struct LINKNODE* Plist) {

	//struct LINKNODE* current_node = Plist;

	while (Plist->p != NULL)
	{

		printf("循环打印：%d\n", Plist->value);
		Plist = Plist->p;

	}



}



//在指定的数值上插入数据

void InsertNodeByVal(struct LINKNODE* plist, int oldval, int newvalue) {

	struct LINKNODE* prenode = NULL;

	//为新值 开辟对空间

	struct LINKNODE* newnode = malloc(sizeof(struct LINKNODE));
	newnode->p = NULL;
	newnode->value = newvalue;

	while (plist->p!=NULL)
	{
		if (oldval == plist->value)
		{
			prenode->p = newnode;
			newnode->p = plist;

		}

		prenode = plist;
		plist = plist->p;

	}



}



//删除指定数据

void DeleteNodeByVal(struct LINKNODE* plist, int value) {

	struct LINKNODE* PreNode = NULL;

	while (plist->p!=NULL)
	{   
		
		if (plist->value == value)
		{  
			PreNode->p = plist->p;
			//plist->p = NULL;
		}
		PreNode = plist;
		plist  = plist->p;
	}
	printf("%s\n", "没有找到该节点！");
}



//查找指定数据是否存在

int FindNodeByVal(struct LINKNODE* plist, int value) {


	while (plist->p != NULL)
	{

		if (plist->value == value)
		{
			printf("%s\n", "找到了该节点！");
			return 0;
		}
		plist = plist->p;
	}
	printf("%s\n", "没有找到该节点！");
}



//清空数据

void ClearLinkNode(struct LINKNODE* plist) {

//只是清空数据内容，还是留有链表结构

	while (plist->p!=NULL)
	{
		plist->value = 0;
		plist = plist->p;
	}


}




int main(void) {

	struct LINKNODE* Lhead = NULL;

	InitLinkNode(&Lhead);

	//ForeachNode(Lhead);

	//DeleteNodeByVal(Lhead, 40);

	//ForeachNode(Lhead);

	//FindNodeByVal(Lhead, 20);

	//ClearLinkNode(Lhead);

	InsertNodeByVal(Lhead, 10, 100);

	ForeachNode(Lhead);

	return 0;

}