#include<iostream>
#include<vector>

//**stack_input****************************************************************

class stack_input
{
public:
    stack_input ( void )  {                      } ;
    void push ( int num ) { obj.push_back(num) ; } ;
    char pop ( void ) ;
    int size ( void )     { return obj.size() ;  } ;
    void refresh ( void ) ;

private:
    std::vector<char> obj ;
} ;
char stack_input::pop ( void ) {   
    char num = '0' ;
    int multi = 1 ;
    while ( obj.size() && multi < 8 ) {
        num += (obj[obj.size()-1]-'0')*multi ;
        obj.pop_back() ;
        multi *= 2 ;
    }

    return num ;
}
void stack_input::refresh ( void ) {
    while ( obj.size() )
        obj.pop_back() ;
}

//**stack_output***************************************************************

class stack_output
{
public:
    stack_output ( void )  {                      } ;
    void push ( char num ) { obj.push_back(num) ; } ;
    void print ( void ) ;

private:
    std::vector<char> obj ;
} ;
void stack_output::print ( void ) {
    std::cout << "0" ;
    while ( obj.size() ) {
        std::cout << obj[obj.size()-1] ;
        obj.pop_back() ;
    }
    std::cout << "\n" ;
}