#include <iostream>
int main(){
    int* ptr = &1;
    int* ptr2 = &ptr;
    std::cout<<"At memory address" << ptr<< " there is value " << *ptr << std::endl;
    std::cout<<"At memory address " << ptr2 << " there is also value " << *ptr2 << std::endl;
    return 0;
}
