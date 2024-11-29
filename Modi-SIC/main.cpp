#include <iostream>
#include <fstream>
 #include <bits/stdc++.h>
#include "codes1.h"
#include "codes2.h"
#include "codes3.h"
using namespace std;

int main()
{

   generateIntermediateFile();
   loccount(); //pass1 location counter + symbol table
   objcode(); //objcode
   HTE();


    return 0;

}
