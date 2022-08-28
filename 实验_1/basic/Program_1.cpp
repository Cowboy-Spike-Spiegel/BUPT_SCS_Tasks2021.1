#include<iostream>
#include<windows.h>

typedef struct node
{
    int name ;
    struct node* next ;
} list , *listPtr ;

class Soldiers // 士兵连
{
public:
    Soldiers ( int n ) ; // 构造器
    bool canKill ( void ) ; // 判断是否能派遣士兵(>1)
    void kill ( int y ) ; // 往后数 y，派遣士兵
    int number ( void ) ; // 当只剩一人时返回号码
    void burden ( void ) { delete cur ; } ; // 销毁空间

private:
    listPtr head ;
    listPtr cur ;
    listPtr prev ;
    int peopleSize ;
} ;
Soldiers::Soldiers ( int n ) // 构造器
{
    head = new list ;
    head->name = 1 ;
    prev = head ;
    for ( int i = 2 ; i <= n ; i++ )
    {
        prev->next = new list ;
        prev->next->name = i ;
        prev = prev->next ;
    }
    prev->next = head ;
    cur = head ;

    peopleSize = n ;
}
bool Soldiers::canKill ( void ) // 判断是否能派遣士兵(>1)
{
    if ( peopleSize == 1 ) {
        return false ;
    }
    return true ;
}
void Soldiers::kill ( int y ) // 往后数 y，派遣士兵
{
    // 数 y次
    while ( --y )
        prev = prev->next ;
    
    // 进行删除并修正 prev,cur
    cur = prev->next ;
    prev->next = cur->next ;
    delete cur ;
    cur = prev->next ;

    peopleSize-- ;
}
int Soldiers::number ( void ) // 当只剩一人时返回号码
{
    if ( peopleSize > 1 )
        return -1 ;
    return cur->name ;
}


int main()
{
    // 输入数据规模
    int N , Y ;
    std::cout << "Please input the upper bound of n :(small than 32767)" << std::endl ;
    while ( 1 ) {
        std::cin >> N ;
        if ( N < 2 )
            std::cout << "Please try again , it's small than 2." << std::endl ;
        else
            break ;
    }
    std::cout << "Please input the upper bound of y :(small than 32767)" << std::endl ;while ( 1 ) {
        std::cin >> Y ;
        if ( Y < 1 )
            std::cout << "Please try again , it's small than 1." << std::endl ;
        else
            break ;
    }
    
    // 执行死亡计划
    for ( int n = 2 ; n <= N ; n++ ) {
        for ( int y = 1 ; y <= Y ; y++ ) {
            Soldiers Garrison(n) ;
            int num ;
            while ( Garrison.canKill() ) {
                Garrison.kill(y) ;
                num = Garrison.number() ;
            }
            Garrison.burden() ;

            // 计算答案
            if ( num != 1 )
                num = 2-num+n ;
            std::cout << "n = " << n << "  y = " << y << "  x = " << num << std::endl << std::endl ;
        }
    }

    return 0 ;
}