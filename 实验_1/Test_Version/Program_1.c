#include "PROGRAM_1.h"

typedef struct member
{
    struct member * next;
    struct member * prev;
    int data;
}*mem;

int main()
{
    mem head,last,cur,pre;
    int i,n,x,y,yLow,yTop;
    x=n=yLow=yTop=0;
    //生成链表
    i=1;
    while (n<2||yLow>yTop)
    {
        printf("Please input the n, the lower bound of y and the upper bound of y:\n");
        scanf("%d %d %d",&n,&yLow,&yTop);
        if (n<2||yLow>yTop)
            printf("Invalid value\n");
    }
    head=malloc(sizeof(struct member));
    head->data=0;
    cur=last=head;
    while (i<n)
    {
        cur->next=malloc(sizeof(struct member));
        cur->next->prev=cur;
        cur=cur->next;
        cur->data=i;
        last=cur;
        i=i+1;
    }
    last->next=head;
    head->prev=last;

    //开始模拟
    cur=head;
    pre=last;
    //移至X的位置
    while (x<n)
    {
        i=0;
        while (i<x)
        {
            cur=cur->next;
            pre=pre->next;
            i=i+1;
        }
        y=yLow;
        while (y<=yTop)
        {
            while (head!=last)
            {
                i=0;
                if (y>=yTop)
                {
                    break;
                }
                //当Y大于0时正向转
                if (y>=0)
                {
                    while (i<y)
                    {
                        cur=cur->next;
                        pre=pre->next;
                        i=i+1;
                    }
                    if (cur->next==cur&&cur->data==0)
                    {
                        break;
                    }
                    else if (cur->data==0)
                    {
                        break;
                    }
                    else
                    {
                        if (cur==last)
                            last=pre;
                        pre->next=cur->next;
                        cur=cur->next;
                        free(cur->prev);
                        cur->prev=pre;
                    }
                }
                //当Y小于0时逆向转
                else if (y<0)
                {
                    pre=cur->next;
                    i=-1;
                    while (i>y)
                    {
                        pre=pre->prev;
                        cur=cur->prev;
                        i=i-1;
                    }
                    if (cur->next==cur&&cur->data==0)
                    {
                        break;
                    }
                    else if (cur->data==0)
                    {
                        break;
                    }
                    else
                    {
                        if (cur==last)
                            last=cur->prev;
                        pre->prev=cur->prev;
                        cur=cur->prev;
                        free(cur->next);
                        cur->next=pre;
                    }
                }
            }
            //如果结果正确则打印
            if (cur->next==cur&&cur->data==0)
            {
                if (y>=0)
                    printf("n:%d x:%d y:%d\n",n,x+1,y+1);
                else
                    printf("n:%d x:%d y:%d\n",n,x+1,y);
            }
            //重新创建链表
            i=1;
            cur=last=head;
            while (i<n)
            {
                cur->next=malloc(sizeof(struct member));
                cur->next->prev=cur;
                cur=cur->next;
                cur->data=i;
                last=cur;
                i=i+1;
            }
            last->next=head;
            head->prev=last;
            cur=head;
            pre=last;
            y=y+1;
            //去到X的位置
            i=0;
            while (i<x)
            {
                cur=cur->next;
                pre=pre->next;
                i=i+1;
            }
        }
        x=x+1;
        cur=head;
        pre=last;
    }
    return 0;
}
