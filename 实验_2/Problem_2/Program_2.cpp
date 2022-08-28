#include"Program_2.h"

//**main***********************************************************************

int main()
{
    std::string binary ;
    std::cout << "Please input a string with chars and end with #." << std::endl ;
    while ( 1 ) {
        std::cin >> binary ;
        if ( binary[binary.size()-1] == '#' )
            break ;
        std::cout << "Invalid input, tail with no #. Please try again." << std::endl ;
    }
    binary.pop_back() ;
    
    // stack 得到反串
    stack obj_s(binary) ;
    std::vector<char> word_s ;
    while ( !obj_s.isEmpty() )
        word_s.push_back( obj_s.pop() ) ;

    // queue 得到正串
    queue obj_q(binary) ;
    std::vector<char> word_q ;
    while ( !obj_q.isEmpty() )
        word_q.push_back( obj_q.delQ() ) ;

    // 比较
    bool answer = true ;
    int i ;
    for ( i = 0 ; i < binary.size() && answer ; i++ )
        if ( word_s[i] != word_q[i] )
            answer = false ;
    if ( answer )
        std::cout << "True" ;
    else {
        std::cout << "False , there are " << i-1 << " characters are the same.\n" ;
    }
    
    return 0 ;
}