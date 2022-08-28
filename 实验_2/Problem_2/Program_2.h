#include<iostream>
#include<vector>
#include<string>
#include <string.h>

//**stack**********************************************************************

class stack
{
public:
    stack ( std::string nums ) ;
    bool isFull ( void )      { return (top == maxSize-1) ; } ;
    bool isEmpty ( void )     { return (top == -1) ;        } ;
    void push ( char number ) { data[++top] = number ;      } ;
    char pop ( void )         { return data[top--] ;        } ;
    void burden ( void )      { delete data ;               } ;

private:
    char* data ;
    int   top ;
    int   maxSize ;
} ;
stack::stack ( std::string nums ) {
    data = new char [nums.size()] ;
    top = -1 ;
    maxSize = nums.size() ;

    for ( int i = 0 ; top < maxSize-1 ; i++ )
        data[++top] = nums[i] ;
}

//**queue**********************************************************************

class queue
{
public:
    queue ( std::string nums ) ;
    bool isFull ( void )     { return ( cnt == maxSize ) ; } ;
    bool isEmpty ( void )    { return ( cnt == 0 ) ;       } ;
    void addQ ( char number ) ;
    char delQ ( void ) ;
    void burden ( void )     { delete data ;               } ;

private:
    char* data ;
    int   front ;
    int   rear ;
    int   cnt ;
    int   maxSize ;
} ;
queue::queue ( std::string nums ) {
    data = new char [nums.size()] ;
    front = rear = cnt = 0 ;
    maxSize = nums.size() ;

    for ( int i = 0 ; rear < maxSize ; i++ ) {
        data[rear++] = nums[i] ;
        cnt++ ;
    }
}
void queue::addQ ( char number ) {
    data[rear] = number ;
    rear = (rear+1)%maxSize ;
    cnt++ ;
}
char queue::delQ ( void ) {
    char copy = data[front] ;
    front = ( front+1 ) % maxSize ;
    cnt-- ;
    return copy ;
}
