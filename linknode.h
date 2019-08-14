#pragma once
#ifdef __cplusplus
extern "C"{
#endif // __cplusplus






	struct LINKNODE
	{
		int value;
		struct LINKNODE* p;
	};

	//初始化动态链表

	void InitLinkNode(struct LINKNODE* p);

	//遍历动态链表

	void ForeachNode(struct LINKNODE* p);



	//在指定位置插入数据

	void InsertNodeByVal(struct LINKNODE* p, int oldval, int newvalue);



	//删除指定数据

	void DeleteNodeByVal(struct LINKNODE* p, int value);



	//插入指定数据是否存在

	int FindNodeByVal(struct LINKNODE* p, int value);


	//清空数据

	void ClearLinkNode(struct LINKNDE* p);




#ifdef __cplusplus

}
#endif // __cplusplus









