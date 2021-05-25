#include "mylibATM.h"



int main()
{
    ATM ds[MAX];
    int n;
    DocFile(ds, n);
    TienATM atm;
    menu(ds, n, atm);
    
    return 0;
}