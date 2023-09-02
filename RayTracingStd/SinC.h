#ifndef	_SINC
#define _SINC

#include <cmath>

template<typename T>
double    sinc_pi(const T x)
{
    
    using    ::std::numeric_limits;
    
    static T const    taylor_0_bound = numeric_limits<T>::epsilon();
    static T const    taylor_2_bound = sqrt(taylor_0_bound);
    static T const    taylor_n_bound = sqrt(taylor_2_bound);
    
    if    (abs(x) >= taylor_n_bound)
    {
        return(sin(x)/x);
    }
    else
    {
        // approximation by taylor series in x at 0 up to order 0
        T    result = static_cast<T>(1);
        
        if    (abs(x) >= taylor_0_bound)
        {
            T    x2 = x*x;
            
            // approximation by taylor series in x at 0 up to order 2
            result -= x2/static_cast<T>(6);
            
            if    (abs(x) >= taylor_2_bound)
            {
                // approximation by taylor series in x at 0 up to order 4
                result += (x2*x2)/static_cast<T>(120);
            }
        }
        
        return(result);
    }
}



#endif
