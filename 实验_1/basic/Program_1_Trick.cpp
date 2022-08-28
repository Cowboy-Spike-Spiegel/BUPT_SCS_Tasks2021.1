#include<iostream>
#include<windows.h>
#include<string>

//**struct*********************************************************************

typedef struct node
{
    int name ;
    struct node* next ;
} list , *listPtr ;

//**class**********************************************************************

class Str
{
public :
    Str ( std::string line ) { Line = line ; } ;
    void convertPrint ( std::string line ) ;
    void print ( void ) ;

private:
    std::string Line ;
} ;
void Str::print ( void )
{
    for ( int i = 0 ; i < Line.length() ; i++ ) {
        std::cout << Line[i] ;
        Sleep(60) ;
    }
}
void Str::convertPrint ( std::string line )
{
    Line = line ;
    for ( int i = 0 ; i < Line.length() ; i++ ) {
        std::cout << Line[i] ;
        Sleep(60) ;
    }
}

class Soldiers // 士兵连
{
public:
    Soldiers ( int n ) ;
    bool canKill ( void ) ;
    void kill ( int y ) ;
    int number ( void ) ;
    void burden ( void ) { delete cur ; } ;

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
        Str line("Just one people left. And his number is " + std::to_string(cur->name) + ".\n") ;
        line.print() ;
        return false ;
    }
    return true ;
}
void Soldiers::kill ( int y ) // 往后数 y，派遣士兵
{
    // 数 y次
    while ( --y )
        prev = prev->next ;
    cur = prev->next ;

    Str Line(std::to_string(cur->name) + " is dead.\n") ;
    Line.print() ;
    Sleep(500) ;
    
    // 进行删除并修正 prev,cur
    prev->next = cur->next ;
    delete cur ;
    cur = prev->next ;
    peopleSize-- ;

    // 输出剩余人数
    if ( peopleSize > 1 )
        Line.convertPrint("There are " + std::to_string(peopleSize) + " people left , they are :\n") ;
    else
        Line.convertPrint("There is " + std::to_string(peopleSize) + " people left , they are :\n") ;

    Sleep(500) ;
    for ( int i = 0 ; i < peopleSize ; i++ ) {
        std::cout << cur->name << " " ;
        cur = cur->next ;
        Sleep(500) ;
    }
    std::cout << std::endl << std::endl ;
    Sleep(1000) ;
}
int Soldiers::number ( void ) // 当只剩一人时返回号码
{
    if ( peopleSize > 1 )
        return -1 ;
    return cur->name ;
}

//**main***********************************************************************

int main()
{
    // 输入数据规模
    int n , x , y ;
    Str Line("\nYou , Garrison , please input three integers with an enter.\n\n") ;
    Line.print() ;
    Sleep(1000) ;

    while ( 1 ) {
        Line.convertPrint("Please input n : (The size of your soldiers with >= 2)\n") ;
        std::cin >> n ;
        if ( n < 2 )
            Line.convertPrint("The input is invalid , please input again.\n") ;
        else
            break ;
    }
    Sleep(500) ;
    while ( 1 ) {
        Line.convertPrint("Please input x : (Guess your number)\n") ;
        std::cin >> x ;
        if ( x < 1 )
            Line.convertPrint("The input is invalid , please input again.\n") ;
        else
            break ;
    }
    Sleep(500) ;
    while ( 1 ) {
        Line.convertPrint("Please input y : (The size once you count with >= 1)\n") ;
        std::cin >> y ;
        if ( y < 1 )
            Line.convertPrint("The input is invalid , please input again.\n") ;
        else
            break ;
    }
    Sleep(500) ;
    Line.convertPrint("\nLet's go to die one by one.\n") ;
    Line.convertPrint("And start from number 1.\n\n") ;

    // 执行死亡计划
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
    
    Line.convertPrint("Because start from 1 , so the answer should be " + std::to_string(num) + "\n") ;
    Line.convertPrint("Your guess is " + std::to_string(x) + ".\n") ;
    
    if ( num == x )
        Line.convertPrint("You are correct , but no one witness your death! What a pity for a soldier!\n") ;
    else {
        Line.convertPrint("You are wrong , you are not the last one to die.\n") ;
        Sleep(1000) ;
        Line.convertPrint("Everyone is equal , no one wants to die.\n") ;
        Sleep(1000) ;
        system("cls") ;
        Sleep(1000) ;
        Line.convertPrint("So , NO WARS , NO PAINS.\n\n") ;
        Sleep(5*1000) ;
    }

    return 0 ;
}