#pragma once
#ifdef __cplusplus
extern "C"{
#endif // __cplusplus






	struct LINKNODE
	{
		int value;
		struct LINKNODE* p;
	};

	//��ʼ����̬����

	void InitLinkNode(struct LINKNODE* p);

	//������̬����

	void ForeachNode(struct LINKNODE* p);



	//��ָ��λ�ò�������

	void InsertNodeByVal(struct LINKNODE* p, int oldval, int newvalue);



	//ɾ��ָ������

	void DeleteNodeByVal(struct LINKNODE* p, int value);



	//����ָ�������Ƿ����

	int FindNodeByVal(struct LINKNODE* p, int value);


	//�������

	void ClearLinkNode(struct LINKNDE* p);




#ifdef __cplusplus

}
#endif // __cplusplus









