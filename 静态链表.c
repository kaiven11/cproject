#include <stdio.h>
#include <stdlib.h>


//�����Ϊ��̬����Ͷ�̬����


// ����ӽṹ��˵��Ϊ  ��������  ˫������  ����ѭ������ ˫��ѭ������  ѭ������

// �� ����ͷ�ڵ�  ����  ��ͷ�ڵ� ����  ��ͷ�ڵ�����


//����ʵ�� ��̬��������


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

	
	//ѭ������

	//��ʼ��ַ

	struct linknode* start_point = &node1;

	struct linknode* current_point = start_point;

	for (int  i = 0; i < 4; i++)
	{
		printf("%d\n",current_point->value);
		current_point = current_point->p;
	}


	return 0;
}