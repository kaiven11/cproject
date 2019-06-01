#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include "tran.h"

#define MAXVALUE 111103

//思路：
/*
1。打开翻译文件，加载到内存空间
2。以两行为单位进行存储

问题：1。如何开辟合适的空间大小
      2。如何在已经加载的内存空间中进行查找到内容进行输出





*/




int main(void) {

	FILE * fp = fopen("D:\\dict.txt", "rb");
	if (!fp)
	{
		return -1;
	}

	//char * buffer = (char*)malloc(sizeof(char) * 1024);//字符串数组'
	char buffer[1024];
	dic * p = (dic*)malloc(sizeof(dic*)*MAXVALUE);

	int count = 0;
	while (!feof(fp))
	{
		memset(buffer, 0, 1024);
		/*printf("%s", );*/
		//逐条开辟空间，然后放入空间内

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

	//通过键盘查找结果
	char a[1024];
	//fgets 会获取\n
	//gets 会获取空格
	//scanf 会以空格为分割符

	
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
			printf("%3s", "没有找到单词");
		}



	//释放堆空间

	for (int  i = 0; i < MAXVALUE; i++)
	{
		free(p[i].key);
		free(p[i].value);
	}
	

	free(p);

	system("pause");
	return 0;


}