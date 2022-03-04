#include "random.cpp"
#include <iostream>

void printNumbers(rand_gen &r, int num) {

    for (int i = 0; i < num; i++) {
        r.print_info();
        cout << "Next: " << r.next() << endl;
    }
    cout << endl;
}

int main(int argc, const char * argv[])
{
    freopen("result.txt", "w", stdout);
    rand_gen rg(3, 40, 730, 819);

    printNumbers(rg, 5);
    
    rg.set_seed(7);
    printNumbers(rg, 5);
    
    rg.set_seed(21);
    printNumbers(rg, 5);


    rand_gen rg2(69, 18, 678, 1234);
    
    printNumbers(rg2, 5);
    
    rg2.set_seed(3);
    printNumbers(rg2, 5);

    fclose(stdout);


    return 0;
}
