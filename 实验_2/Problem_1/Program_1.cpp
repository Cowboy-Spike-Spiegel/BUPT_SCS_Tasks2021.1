#include"Program_1.h"

int main()
{
    // 录入二进制码，为反串
    stack_input binaryReverse ;
    std::cout << "Please input a string with 0 and 1.\n" ;
    
    int flag = 1 ;
    while ( flag ) {
        flag = 0 ;  // expect to break ;
        // throw 0s before the first 1
        while ( std::cin.peek() != '1' ) {
            if ( std::cin.get() != '0' ) {
                std::cin.ignore ( 0x3f3f3f , '\n' ) ;
                std::cout << "Some is neither 0 nor 1, please try again.\n" ;
                flag = 1 ;  // convert to input again
                break ;
            }
        }

        while ( !flag && std::cin.peek() != '\n' )
        {
            char ch = std::cin.get() ;
            if ( ch != '0' && ch != '1' ) {
                std::cin.ignore ( 0x3f3f3f , '\n' ) ;
                std::cout << "Some is neither 0 nor 1, please try again.\n" ;
                binaryReverse.refresh() ;  // delete input
                flag = 1 ;  // convert to input again
                break ;
            }
            binaryReverse.push ( ch ) ;
        }
    }

    // 转入八进制栈，为正串
    stack_output oct ;
    while ( binaryReverse.size() )
        oct.push( binaryReverse.pop() ) ;
    oct.print() ;

    return 0 ;
}
