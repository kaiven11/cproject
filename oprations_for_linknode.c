#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "linknode.h"

//��ʼ����̬����

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
		//���ٶԿռ䣬�����heappoint ָ����ջ�ռ���Զ��ͷ�
		//�������ظ�����
		heappoint->value = a;
		heappoint->p = NULL;
		pRear->p = heappoint;
		pRear = heappoint;
	}

	*tmp = headnode;

}


//������̬����

void ForeachNode(struct LINKNODE* Plist) {

	//struct LINKNODE* current_node = Plist;

	while (Plist->p != NULL)
	{

		printf("ѭ����ӡ��%d\n", Plist->value);
		Plist = Plist->p;

	}



}



//��ָ������ֵ�ϲ�������

void InsertNodeByVal(struct LINKNODE* plist, int oldval, int newvalue) {

	struct LINKNODE* prenode = NULL;

	//Ϊ��ֵ ���ٶԿռ�

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



//ɾ��ָ������

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
	printf("%s\n", "û���ҵ��ýڵ㣡");
}



//����ָ�������Ƿ����

int FindNodeByVal(struct LINKNODE* plist, int value) {


	while (plist->p != NULL)
	{

		if (plist->value == value)
		{
			printf("%s\n", "�ҵ��˸ýڵ㣡");
			return 0;
		}
		plist = plist->p;
	}
	printf("%s\n", "û���ҵ��ýڵ㣡");
}



//�������

void ClearLinkNode(struct LINKNODE* plist) {

//ֻ������������ݣ�������������ṹ

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