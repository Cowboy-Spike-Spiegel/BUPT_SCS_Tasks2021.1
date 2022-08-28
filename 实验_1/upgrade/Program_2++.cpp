#include"Program_2++.h"

int main()
{
    int N , Y_lower , Y_upper ;  // 输入数据
    scan ( N , Y_lower , Y_upper ) ;

    for ( int n = 2 ; n <= N ; n++ ) {
        for ( int y = Y_lower ; y <= Y_upper ; y++ ) {
            if ( y == 0 ) {
                std::cout << "0 can't be the value of y , let's skip." << std::endl ;
                continue ;
            }

            Soldiers Garrison(n) ;  // 执行死亡计划
            while ( Garrison.canKill() ) {
                Garrison.kill(y) ;
            }
            int num = Garrison.number() ;
            Garrison.burden() ;

            if ( num != 1 )  // 输出答案
                num = 2-num+n ;
            std::cout << "n = " << n << "  y = " << y << "  x = " << num << std::endl ;
        }
        std::cout << std::endl ;
    }

    system("pause") ;
    return 0 ;
}
