#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

//�����û��������ֵ�Զ���䵽�����У���ͷ�ڵ�  ,��̬����ֻ�ܿ��ٶѿռ䣬��ֹ��������ʱ���ͷ�
struct LINKNODE
{
	int value;
	struct LINKNODE* p;
};

int main02(void) {

	printf("%s", "������ڵ����ֵ:");
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
	  //���ٶԿռ䣬�����heappoint ָ����ջ�ռ���Զ��ͷ�
	  //�������ظ�����
	  heappoint->value = a;
	  heappoint->p = NULL;
	  current_node->p = heappoint;
	  current_node = heappoint;
	}

	current_node = start_node;
	while (current_node->p!=NULL)
	{

		printf("ѭ����ӡ��%d\n", current_node->value);
		current_node = current_node->p;

	}

	//�ͷŶԿռ�
	return 0;

}