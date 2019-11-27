
int runserver(int a);

//创建监听描述符并返回
int createlfd(int port);

//读取一行数据
//解析头

void parsecontent(int confd,int efd);

int get_line(int sock, char *buf, int size);

//发送头
void send_response_header(char * filetype ,long content_length,int confd);


//计算字符串长度

int countlengh(char * str);


//发送文件
char * send_dir(int confd, char * Path,int flag);


void send_file(int cfd, const char* filename);
//
int get_file_size(int f);

//解码
void decode_str(char *to, char *from);

//进制转换
// int hexit(char c);

//编码

void encode_str(char* to, int tosize, const char* from);

//数字和类型映射表

struct mapping
{
    char * filetype ;
    char * contentname;
};
