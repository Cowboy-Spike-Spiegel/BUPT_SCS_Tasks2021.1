#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//哈夫曼树的节点
typedef struct Huffman
{
    int word;
    struct Huffman* parent;
    struct Huffman* lk;//left kid
    struct Huffman* rk;//right kid
}Node;

//用于排序维护的数组节点
typedef struct countChar
{
    char word;
    int count;
    Node *cur;
    char coding[50];
}countsOfWords;


char selectMode(void);//选择模式
void encode(void);//编码
void decode(void);//解码
char* openFile(void);//打开文件
countsOfWords* countFrequency(FILE* doc,int* numsOfWord);//统计出现频率
Node* createTree(countsOfWords* words,int count);//创建哈夫曼树
int cmpfunc (const void * a, const void * b);//用于快排的比较函数
Node* createNode(void);//创建节点
char** encoding(countsOfWords* words,Node* root);//对每个字符进行编码
void dfs(char** words,Node* cur,int i,char code[]);//深搜
void outputFile(FILE* in,FILE* out,char** words, char* filePath);//输出成二进制文件
void getCode(FILE* doc,int words[]);//获取每个字符的编码
void outputDecodeFile(FILE* doc,int words[],char* fileName);//输出解压文件

char selectMode(void)
{
    char mode,c;
    mode=0;
    //输入其他字符时继续循环
    while ((mode!='1'&&mode!='2')&&mode!='3')
    {
        printf("Please enter number to select the mode:\n");
        printf("1:Encode\n");
        printf("2:Decode\n");
        printf("3:Quit\n");
        scanf("%c",&mode);
        //避免用户输入过多字符
        while ((c=getchar()!='\n'&&c!=EOF));
    }
    return mode;
}

void encode(void)
{
    FILE *doc=NULL;
    FILE *output=NULL;
    countsOfWords* words;
    int numsOfWords=0;
    Node* root;
    char** code;
    char* inputFile;
    root=NULL;
    words=NULL;
    inputFile=openFile();
    doc=fopen(inputFile,"rb+");
    //打开文件
    words=countFrequency(doc,&numsOfWords);
    //统计出现频率
    root=createTree(words,numsOfWords);
    //建哈夫曼树
    Node* tmp;
    code=encoding(words,root);
    //进行编码
    rewind(doc);
    //回到文件头
    outputFile(doc,output,code,inputFile);
    //输出二进制文件
}

char* openFile(void)
{
    int flag=0;
    int i=0;
    FILE* file;
    char* filePath;
    filePath=malloc(sizeof(char)*100);
    while (flag==0)
    {
        i=0;
        //请求用户输入
        printf("Please enter the path of the file:\n");
        while (filePath[i-1]!='\n')
        {
            scanf("%c",&filePath[i]);
            i=i+1;
        }
        //逐个字符读入，避免溢出攻击
        filePath[i-1]=0;
        file=fopen(filePath,"rb+");
        if (file==NULL)
        {
            printf("Can not open that file, please check it.\n");
        }
        else
        {
            flag=1;
        }
    }
    return filePath;
}

countsOfWords* countFrequency(FILE* doc,int* numsOfWord)
{
    int words[256]={};
    char str[500]={};
    int i,j,count;
    countsOfWords* wordsCount;
    count=fread(str,sizeof(char),256,doc);
    //count为读入的字符个数
    while (count!=0)
    {
        i=0;
        while (i<count)
        {
            if ( words[(int)str[i]+128]==0)
                //+128是为了把负数变为正数
                *numsOfWord=*numsOfWord+1;
            words[(int)str[i]+128]=words[(int)str[i]+128]+1;
            i=i+1;
        }
        count=fread(str,sizeof(char),256,doc);
    }
    wordsCount=malloc(sizeof(countsOfWords)*(*numsOfWord));
    //创建用于排序和维护的数组
    i=j=0;
    while (i<256)
    {
        if (words[i]!=0)
        {
            wordsCount[j].count=words[i];
            wordsCount[j].word=i;
            wordsCount[j].cur=malloc(sizeof(Node));
            wordsCount[j].cur->word=i;
            wordsCount[j].cur->lk=NULL;
            wordsCount[j].cur->rk=NULL;
            wordsCount[j].cur->parent=NULL;
            j=j+1;
        }
        i=i+1;
    }
    //初始化数组
    qsort(wordsCount,*numsOfWord,sizeof(countsOfWords),cmpfunc);
    return wordsCount;
}

Node* createTree(countsOfWords* words,int count)
{
    int i;
    Node *l,*r,*parent;
    l=NULL;
    r=NULL;
    parent=NULL;
    i=0;
    if (count==1)
    {
        parent=words[0].cur;
    }
    //特判只出现一个字符的情况
    else
    {
        while (i<count-1)
        {
            l=words[i].cur;
            r=words[i+1].cur;
            parent=createNode();
            parent->lk=l;
            parent->rk=r;
            parent->word=-1;
            words[i+1].count=words[i].count+words[i+1].count;
            words[i+1].cur=parent;
            words[i].count=0;
            //为当前两个最小值创建父节点，更新数组
            i=i+1;
            qsort(words,count,sizeof(countsOfWords),cmpfunc);
            //重新排序，维护数组
        }
    }
    return parent;
}

int cmpfunc (const void * a, const void * b)
{
   countsOfWords *c,*d;
   c=(countsOfWords *)a;
   d=(countsOfWords *)b;
   if (c->count>=d->count)
   {
       return 1;
   }
   else
   {
       return -1;
   }
   //从小到大排序
}

Node* createNode(void)
{
    Node* cur;
    cur=malloc(sizeof(Node));
    cur->lk=NULL;
    cur->parent=NULL;
    cur->rk=NULL;
    return cur;
}

char** encoding(countsOfWords* words,Node* root)
{
    char** coding;
    char code[100]={};
    int i,j;
    code[0]='1';
    coding=malloc(sizeof(char*)*256);
    i=0;
    //为每个字符创建一个数组，用于存编码
    while (i<256)
    {
        coding[i]=malloc(sizeof(char)*20);
        j=0;
        while (j<20)
        {
            coding[i][j]=0;
            j=j+1;
        }
        i=i+1;
    }
    dfs(coding,root,0,code);
    return coding;
}

void dfs(char** words,Node* cur,int i,char code[])
{
    if (cur->lk!=NULL)
    {
        code[i+1]='0';
        //往左走是0
        dfs(words,cur->lk,i+1,code);
    }
    if (cur->rk!=NULL)
    {
        code[i+1]='1';
        //往右走是1
        dfs(words,cur->rk,i+1,code);
    }
    if (cur->lk==NULL&&cur->rk==NULL)
    {
        code[i+1]=0;
        strcpy(words[cur->word],code);
    }
}

void outputFile(FILE* in,FILE* out,char** words, char* filePath)
{
    int count,i,tmp,j;
    char str[256];
    char buffer[200]={};
    strcat(filePath,".hfm");
    //输出格式为xxx.hfm
    out=fopen(filePath,"wb+");
    i=0;
    //先把所有字符的编码以整型输出，方便解码
    while (i<256)
    {
        j=0;
        tmp=0;
        while (j<strlen(words[i]))
        {
            tmp=tmp<<1;
            if (words[i][j]=='1')
            {
                tmp=tmp+1;
            }
            j=j+1;
        }
        fprintf(out,"%d\n",tmp);
        i=i+1;
    }
    //开始读文件
    count=fread(str,sizeof(char),256,in);
    while (count!=0)
    {
        i=0;
        //把字符对应的编码贴到缓存区
        while (i<count)
        {
            strcat(buffer,words[(int)str[i]+128]);
            //如果缓存区中的编码大于等于8的话就转换为ascii码输出
            while (strlen(buffer)>=8)
            {
                tmp=128*(buffer[0]-'0')+64*(buffer[1]-'0')+32*(buffer[2]-'0')+16*(buffer[3]-'0')+8*(buffer[4]-'0')+4*(buffer[5]-'0')+2*(buffer[6]-'0')+1*(buffer[7]-'0');
                j=8;
                int len;
                if (strlen(buffer)>16)
                {
                    len=strlen(buffer);
                }
                else
                {
                    len=16;
                }
                while (j<len)
                {
                    buffer[j-8]=buffer[j];
                    buffer[j]=0;
                    j=j+1;
                }
                fprintf(out,"%c",tmp-128);
            }
            i=i+1;
        }
        count=fread(str,sizeof(char),256,in);
    }
    //把剩余的补零输出
    if (strlen(buffer)>0)
    {
        //printf("%s\n",buffer);
        i=tmp=0;
        while (i<8)
        {
            tmp=tmp<<1;
            if (buffer[i]=='1')
                tmp=tmp+1;
            i=i+1;
        }
        fprintf(out,"%c",tmp-128);
    }
    fclose(out);
    fclose(in);
}

void decode()
{
    FILE *doc=NULL;
    FILE *output=NULL;
    int code[256];
    char* inputFile;
    inputFile=openFile();
    //打开文件
    doc=fopen(inputFile,"rb+");
    //获取编码规则
    getCode(doc,code);
    //输出解压文件
    outputDecodeFile(doc,code,inputFile);
}

void getCode(FILE* doc,int words[])
{
    int i=0;
    //获取编码规则
    while (i<256)
    {
        fscanf(doc,"%d",&words[i]);
        i=i+1;
    }
}

void outputDecodeFile(FILE* doc,int words[],char* fileName)
{
    int tmp,i,code,j,count,k,flag,size,test;
    tmp=test=0;
    char outPutFileName[100]={};//输出文件名
    char buffer1[200]={};//缓存区1，用于存放即将输出的编码
    char buffer2[100]={};//缓存区2，用于存放读入字符的编码
    char code1;//读入字符
    FILE *outPut;
    i=j=0;
    //更改输出文件名
    while (fileName[i]!='.')
    {
        outPutFileName[j]=fileName[i];
        i=i+1;
        j=j+1;
    }
    strcat(outPutFileName,"(decode).");
    j=j+9;
    i=i+1;
    while (i<strlen(fileName)-4)
    {
        outPutFileName[j]=fileName[i];
        i=i+1;
        j=j+1;
    }
    outPut=fopen(outPutFileName,"wb+");
    //读掉换行符
    fscanf(doc,"%c",&code1);
    //开始正式解压
    count=fscanf(doc,"%c",&code1);
    //当文件没读完或缓存区1内还有字符时一直运行
    while (count>=0||strlen(buffer1)!=0)
    {
        code=code1+128;
        //+128，避免负数
        if (code/128==1)
        {
            buffer2[0]='1';
            code=code%128;
        }
        else
        {
            buffer2[0]='0';
        }
        if (code/64==1)
        {
            buffer2[1]='1';
            code=code%64;
        }
        else
        {
            buffer2[1]='0';
        }
        if (code/32==1)
        {
            buffer2[2]='1';
            code=code%32;
        }
        else
        {
            buffer2[2]='0';
        }
        if (code/16==1)
        {
            buffer2[3]='1';
            code=code%16;
        }
        else
        {
            buffer2[3]='0';
        }
        if (code/8==1)
        {
            buffer2[4]='1';
            code=code%8;
        }
        else
        {
            buffer2[4]='0';
        }
        if (code/4==1)
        {
            buffer2[5]='1';
            code=code%4;
        }
        else
        {
            buffer2[5]='0';
        }
        if (code/2==1)
        {
            buffer2[6]='1';
            code=code%2;
        }
        else
        {
            buffer2[6]='0';
        }
        if (code/1==1)
        {
            buffer2[7]='1';
            code=0;
        }
        else
        {
            buffer2[7]='0';
        }
        strcat(buffer1,buffer2);
        i=tmp=0;
        //遍历缓存区1，看是否可以解码
        while (i<strlen(buffer1))
        {
            if (buffer1[i]=='1')
            {
                tmp=tmp+1;
            }
            j=0;
            while (j<256)
            {
                if (tmp==words[j]&&tmp!=0)
                {
                    test=test+1;
                    fprintf(outPut,"%c",j-128);
                    k=0;
                    size=strlen(buffer1);
                    while (k<size)
                    {
                        buffer1[k]=buffer1[i+1];
                        buffer1[i+1]=0;
                        k=k+1;
                        i=i+1;
                    }
                    i=-1;
                    tmp=0;
                    break;
                }
                j=j+1;
            }
            tmp=tmp<<1;
            i=i+1;
        }
        if (tmp==0)
        {
            buffer1[0]=0;
        }
        count=fscanf(doc,"%c",&code1);
    }
    fclose(doc);
    fclose(outPut);
}

#endif // HEAD_H_INCLUDED
