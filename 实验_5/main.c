#include "head.h"

int main()
{
    char mode;
    while (mode!='3')
    {
        mode=0;
        mode=selectMode();
        //如果模式是1就编码
        if (mode=='1')
        {
            encode();
            printf("Encoded Successfully\n\n");
        }
        //如果模式是2就解码
        else if (mode=='2')
        {
            decode();
            printf("Decoded Successfully\n\n");
        }
    }

    return 0;
}


