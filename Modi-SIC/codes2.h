#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

//--------------------------------------------------------------------
//--------------------------------------------------------------------
string binToHex(string x)
{
    string b;

    if(x== "0000")
        b="0";
    else if(x=="0001")
        b="1";
    else if(x=="0010")
        b="2";
    else if(x=="0011")
        b="3";
    else if(x=="0100")
        b="4";
    else if(x=="0101")
        b= "5";
    else if(x=="0110")
        b="6";
    else if(x=="0111")
        b="7";
    else if(x=="1000")
        b="8";
    else if(x=="1001")
        b="9";
    else if(x=="1010")
        b="A";
    else if(x=="1011")
        b="B";
    else if(x=="1100")
        b="C";
    else if(x=="1101")
        b="D";
    else if(x=="1110")
        b="E";
    else if(x=="1111")
        b="F";

    return b;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
string hexaToBinary(char x){
    string b="";
    int i;

    switch(x)
    {
    case '0':
        b+="0000";
        break;
    case '1':
        b+="0001";
        break;
    case '2':
        b+="0010";
        break;
    case '3':
        b+="0011";
        break;
    case '4':
        b+="0100";
        break;
    case '5':
        b+="0101";
        break;
    case '6':
        b+="0110";
        break;
    case '7':
        b+="0111";
        break;
    case '8':
        b+="1000";
        break;
    case '9':
        b+="1001";
        break;
    case 'A':
    case 'a':
        b+="1010";
        break;
    case 'B':
    case 'b':
        b+="1011";
        break;
    case 'C':
    case 'c':
        b+="1100";
        break;
    case 'D':
    case 'd':
        b+="1101";
        break;
    case 'E':
    case 'e':
        b+="1110";
        break;
    case 'F':
    case 'f':
        b+="1111";
        break;
    default:
        return "invalid";
    }

return b;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
string symbol(string label)
{
    string filename2="symbTable.txt";
    ifstream input2;
    input2.open(filename2);
    string lab,loc;
    string r;
    while(input2)
    {
        input2>>lab;
        input2>>loc;

        if(lab==label){
            r=loc;
            break;
        }
    }
    input2.close();
    return r;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
string format3(string inst,string op)
{
        string r,x,y,a;
        int d;
        char p[3];
        p[2]='\0';

        string opcode2=findOpcode(inst);
        x[0]=opcode2[1];
        string opcode=hexaToBinary(x[0]);

        //opcode2 --> AB
        //opcode  -->  B --> ----
        if(op[0]=='#')
         {
             opcode[3]='1';

                 y=binToHex(opcode);
                p[0]=opcode2[0];
                 p[1]=y[0];


             op.erase(0,1);

             r=decToHex(stoi(op));
             ostringstream o;
            o<<setw(4)<<setfill('0') << r;

             return p+o.str();
         }
        else
        {
             opcode[3]='0';

                y=binToHex(opcode);
                p[0]=opcode2[0];
                 p[1]=y[0];


        if(op[op.length()-1]=='X' ||op[op.length()-1]=='x')
        {
            for(int i=0;i<op.length()-2;i++){
                a+=op[i];
            }
            r=symbol(a);

            d=hexToDec(r)+32768; //+8000 hexa
            r=decToHex(d);

        }
        else{
            r=symbol(op);
        }
    }

        return p+r;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
string byteObj(string op)
{
    string r;
    if(op[0]=='X' ||op[0]=='x')
        {
            for(int i=2;i<op.length()-1;i++){
                r+=op[i];
            }

        }
    else if(op[0]=='C' ||op[0]=='c')
    {
        for(int i=2;i<op.length()-1;i++){
                r+=decToHex((int)(op[i]));
            }
    }
    return r;
}


//--------------------------------------------------------------------
//--------------------------------------------------------------------
void objcode()
{

    string filename="out_pass1.txt";
    ofstream MyFile("out_pass2.txt");
    ifstream input;
    input.open(filename);
    string line;
    string loc,label,instruction,operand;

  while(input)
    {
        input>>loc;
        input>>label;
        input>>instruction;
        input>>operand;


        if(findOpcode(instruction)!="-1" && instruction!="RESB" && instruction!="RESW"&& instruction!="WORD"&& instruction!="BYTE")
        {
            if(findOpcode(instruction)=="C4"||findOpcode(instruction)=="C0"||findOpcode(instruction)=="F4"||findOpcode(instruction)=="C8"|| findOpcode(instruction)=="F0"||findOpcode(instruction)=="F8")
            {
                  MyFile<< loc<<"\t"<<label<<"\t"<<instruction<<"\t"<<operand<<"\t"<<findOpcode(instruction)<<endl; //format 1
            }
            else
            {
                if(instruction=="RSUB"){
                    MyFile<< loc<<"\t"<<label<<"\t"<<instruction<<"\t"<<operand<<"\t"<<findOpcode(instruction)+"0000"<<endl;
                }

                else
                 MyFile<< loc<<"\t"<<label<<"\t"<<instruction<<"\t"<<operand<<"\t"<<setfill('0')<<setw(6)<<format3(instruction,operand)<<endl; //format 3
            }

        }
        else if(instruction=="RESB" ||instruction=="RESW" ||instruction=="START" || instruction=="END")
           {
                MyFile<< loc<<"\t"<<label<<"\t"<<instruction<<"\t"<<operand<<"\t"<<"-"<<endl;
               if(instruction=="END")
               {

                   break;
               }


           }

         else if(instruction=="WORD")
           {
               MyFile<< loc<<"\t"<<label<<"\t"<<instruction<<"\t"<<operand<<"\t"<<setfill('0')<<setw(6)<<decToHex(stoi(operand))<<endl;

           }
           else if(instruction=="BYTE")
           {
                 MyFile<< loc<<"\t"<<label<<"\t"<<instruction<<"\t"<<operand<<"\t"<<byteObj(operand)<<endl;
           }



             input.get();
        }



    input.close();
    MyFile.close();
}
