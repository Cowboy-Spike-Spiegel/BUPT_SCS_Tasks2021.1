#include<iostream>
#include<windows.h>

typedef struct node
{
    int name ;
    struct node* right ;
    struct node* left ;
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
    int peopleSize ;
} ;
Soldiers::Soldiers ( int n ) // 构造器
{
    head = new list ;
    head->name = 1 ;
    listPtr prev = head ;
    for ( int i = 2 ; i <= n ; i++ )
    {
        prev->right = new list ;
        prev->right->name = i ;
        prev->right->left = prev ;
        prev = prev->right ;
    }
    prev->right = head ;
    head->left = prev ;
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
    // 判断正负数个数
    int copy = y ;
    if ( copy > 0 )
        while ( --copy )
            cur = cur->right ;
    else
        while ( ++copy )
            cur = cur->left ;

    // 进行删除并修正 prev,cur
    cur->left->right = cur->right ;
    cur->right->left = cur->left ;
    if ( y > 0 ) {
        listPtr temp = cur ;
        cur = cur->right ;
        delete temp ;
    }
    else {
        listPtr temp = cur ;
        cur = cur->left ;
        delete temp ;
    }

    peopleSize-- ;
}
int Soldiers::number ( void ) // 当只剩一人时返回号码
{
    if ( peopleSize > 1 )
        return -1 ;
    return cur->name ;
}

void scan ( int &N , int &Y_lower , int &Y_upper )
{
    std::cout << "Please input the upper bound of n :(small than 32767)" << std::endl ;
    while ( 1 ) {
        std::cin >> N ;
        if ( N < 2 )
            std::cout << "Please try again , it's small than 2." << std::endl ;
        else
            break ;
    }
    std::cout << "Please input the lower bound of y :(bigger than -32768)" << std::endl ;
    while ( 1 ) {
        std::cin >> Y_lower ;
        if ( Y_lower == 0 )
            std::cout << "Please try again , it's invalid." << std::endl ;
        else
            break ;
    }
    std::cout << "Please input the upper bound of y :(small than 32767)" << std::endl ;
    while ( 1 ) {
        std::cin >> Y_upper ;
        if ( Y_upper == 0 || Y_upper < Y_lower )
            std::cout << "Please try again , it's invalid." << std::endl ;
        else
            break ;
    }
}