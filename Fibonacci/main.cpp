
#include <iostream>

int main() {
    int x = 0;
    int y = 1;    
    for (int i = 0; i < 10; i++) {                        
        int z = x + y;                
        x = y;        
        y = z;        

        std::cout << x << " ";
    }

    return 0;
}