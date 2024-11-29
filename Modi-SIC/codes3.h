#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

void HTE()
{

    string filename="out_pass2.txt";
    ofstream MyFile("HTE.txt");
    ifstream input;
    input.open(filename);
    string line;
    string loc,label,instruction,operand,objcode;

    string a=decToHex(hexToDec(ending_address)-hexToDec(starting_address));
    MyFile<<"H."<<setfill('X')<<setw(6)<<program_name<<"."<<setfill('0')<<setw(6)<<starting_address<<"."<<setfill('0')<<setw(6)<<a<<endl;

        while(loc!=ending_address){
            input>>loc;
            MyFile<<"T."<<setfill('0')<<setw(6)<<loc<<".";
            for(int i=0;i<8;i++)
            {
                if(i!=0)
                    input>>loc;

            input>>label;
            input>>instruction;
            input>>operand;
            input>>objcode;
             if(loc==ending_address)
               break;

            else if(objcode!="-"){
                MyFile<<objcode<<".";
            }
            }
            MyFile<<endl;

        }
        input.get();

     MyFile<<"E."<<setfill('0')<<setw(6)<<starting_address<<endl;

    input.close();
    MyFile.close();

}
