#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include "tran.h"

#define MAXVALUE 111103

//˼·��
/*
1���򿪷����ļ������ص��ڴ�ռ�
2��������Ϊ��λ���д洢

���⣺1����ο��ٺ��ʵĿռ��С
      2��������Ѿ����ص��ڴ�ռ��н��в��ҵ����ݽ������





*/




int main(void) {

	FILE * fp = fopen("D:\\dict.txt", "rb");
	if (!fp)
	{
		return -1;
	}

	//char * buffer = (char*)malloc(sizeof(char) * 1024);//�ַ�������'
	char buffer[1024];
	dic * p = (dic*)malloc(sizeof(dic*)*MAXVALUE);

	int count = 0;
	while (!feof(fp))
	{
		memset(buffer, 0, 1024);
		/*printf("%s", );*/
		//�������ٿռ䣬Ȼ�����ռ���

		fgets(buffer, 1024, fp);
		(p+count)->key = (char*)malloc(strlen(buffer) + 1);
		memset((p + count)->key, 0, strlen(buffer)+1);
		strcpy((p + count)->key, buffer+1);
	
		
		memset(buffer, 0, 1024);
		fgets(buffer, 1024, fp);
		(p + count)->value = (char*)malloc(strlen(buffer) + 1);
		memset((p + count)->value, 0,strlen(buffer)+1);
		strcpy((p + count)->value, buffer);

		count++;
		


	}

	fclose(fp);

	//ͨ�����̲��ҽ��
	char a[1024];
	//fgets ���ȡ\n
	//gets ���ȡ�ո�
	//scanf ���Կո�Ϊ�ָ��

	
		gets(a);

		int flag = 0;

		for (int i = 0; i < MAXVALUE; i++)
		{
			if (!strncmp(a, p[i].key, strlen(a)))
			{
				printf("%s\n", p[i].value);
				flag = 1;
				break;
			}

		}

		if (!flag)
		{
			printf("%3s", "û���ҵ�����");
		}



	//�ͷŶѿռ�

	for (int  i = 0; i < MAXVALUE; i++)
	{
		free(p[i].key);
		free(p[i].value);
	}
	

	free(p);

	system("pause");
	return 0;


}