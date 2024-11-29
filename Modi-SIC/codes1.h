#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
string starting_address;
string ending_address;
string program_name;

string findOpcode(string inst)
{
     map <string, string> opcode;
	opcode.insert(pair <string , string> ("ADD", "18"));
	opcode.insert(pair <string , string> ("AND", "40"));
	opcode.insert(pair <string , string> ("COMP", "28"));
	opcode.insert(pair <string , string> ("DIV", "24"));
	opcode.insert(pair <string , string> ("J", "3C"));
	opcode.insert(pair <string , string> ("JEQ", "30"));
	opcode.insert(pair <string , string> ("JGT", "34"));
	opcode.insert(pair <string , string> ("JLT", "38"));
	opcode.insert(pair <string , string> ("JSUB", "48"));
	opcode.insert(pair <string , string> ("LDA", "00"));
	opcode.insert(pair <string , string> ("LDCH", "50"));
	opcode.insert(pair <string , string> ("LDL", "08"));
	opcode.insert(pair <string , string> ("LDX", "04"));
	opcode.insert(pair <string , string> ("MUL", "20"));
	opcode.insert(pair <string , string> ("OR", "44"));
	opcode.insert(pair <string , string> ("RD", "D8"));
	opcode.insert(pair <string , string> ("RSUB", "4C"));
	opcode.insert(pair <string , string> ("STA", "0C"));
	opcode.insert(pair <string , string> ("STCH", "54"));
	opcode.insert(pair <string , string> ("STL", "14"));
	opcode.insert(pair <string , string> ("STSW", "E8"));
	opcode.insert(pair <string , string> ("STX", "10"));
	opcode.insert(pair <string , string> ("SUB", "1C"));
	opcode.insert(pair <string , string> ("TD", "E0"));
	opcode.insert(pair <string , string> ("TIX", "2C"));
	opcode.insert(pair <string , string> ("WD", "DC"));

    //format 1
	opcode.insert(pair <string , string> ("FIX", "C4"));
	opcode.insert(pair <string , string> ("FLOAT", "C0"));
	opcode.insert(pair <string , string> ("HIO", "F4"));
	opcode.insert(pair <string , string> ("NORM", "C8"));
	opcode.insert(pair <string , string> ("SIO", "F0"));
	opcode.insert(pair <string , string> ("TIO", "F8"));


	if(opcode.find(inst) == opcode.end())
		return "-1";

	return opcode[inst];
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------

void generateIntermediateFile()
{
    string filename="in.txt";
    ifstream input;
    ofstream MyFile("intermediate.txt");

    input.open(filename);

    while(input)
    {
        string Linenum,label,instruction,operand,comment;
        string line;

        input>>Linenum;
        input>>label;
        if(label=="."){
            getline(input,line);
        }
        else{


        if(findOpcode(label)!="-1") {

            instruction=label;
            label="-";
        }
        else if(label=="END"){
            instruction=label;
            label="-";
        }
        else
           {
               input>>instruction;
           }

        if(instruction=="RSUB" || instruction=="FIX"|| instruction=="FLOAT"|| instruction=="HIO"||instruction=="NORM"|| instruction=="SIO"||instruction=="TIO")
         {
             operand="-";
         }
        else
           {
               input>>operand;
           }
         if(instruction=="START")
         {
                 starting_address=operand;

         }

            getline(input,line);
             input.get();
            MyFile<<label<<"\t"<<instruction<<"\t"<<operand<<endl;


        }


    }
    input.close();
    MyFile.close();



}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//hexa to decimal
int hexToDec(string str)
{
    int y;
    stringstream stream;
    stream << str;
    stream >> hex >> y;
    return y;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//decimal to hexa
string decToHex(int num)
{
    stringstream stream;
    stream << hex << num;
    return stream.str();
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
 int RESB(string x)
 {
        return stoi(x);
 }
 //--------------------------------------------------------------------
//--------------------------------------------------------------------
 int RESW(string x)
 {
        int m=stoi(x);
        m*=3;
        return m;
 }
 //--------------------------------------------------------------------
//--------------------------------------------------------------------
 int WORD(string x)
 {
        return 1;
 }
 //--------------------------------------------------------------------
//--------------------------------------------------------------------
 int BYTE(string x)
 {
        if(x[0]=='C'||x[0]=='c'){
        return x.length()-3;
    }
    if(x[0]=='X'||x[0]=='x')
       {
           return (x.length()-3)/2;
       }
 }

//--------------------------------------------------------------------
//--------------------------------------------------------------------
void loccount()
{

    string filename="intermediate.txt";
    ifstream input;
    ofstream MyFile("out_pass1.txt");
    ofstream MyFile2("symbTable.txt");
    input.open(filename);
    string line;
    string label,instruction,operand;
    int starting_addressNEW;
    int starttingAddress=hexToDec(starting_address);



  while(input)
    {

        input>>label;
        input>>instruction;
        input>>operand;

        if(instruction=="START"){
            MyFile<<decToHex(starttingAddress)<<"\t"<<label<<"\t"<<instruction<<"\t"<<operand<<endl;
            program_name=label;

        }
        else if(instruction=="END")
           {

               MyFile<<decToHex(starttingAddress)<<"\t"<<label<<"\t"<<instruction<<"\t"<<operand<<endl;
               ending_address=decToHex(starttingAddress);
               break;
           }
        else{



        if(findOpcode(instruction)!="-1" && instruction!="RESB" && instruction!="RESW"&& instruction!="WORD"&& instruction!="BYTE"){
            if(findOpcode(instruction)=="C4"||findOpcode(instruction)=="C0"||findOpcode(instruction)=="F4"||findOpcode(instruction)=="C8"|| findOpcode(instruction)=="F0"||findOpcode(instruction)=="F8")
            {
                 starting_addressNEW=starttingAddress+1;
            }
            else
            {
                starting_addressNEW=starttingAddress+3;
            }

            MyFile<<decToHex(starttingAddress)<<"\t"<<label<<"\t"<<instruction<<"\t"<<operand<<endl;

        }
        else if(instruction=="RESB")
           {
               starting_addressNEW=starttingAddress+RESB(operand);
               MyFile<<decToHex(starttingAddress)<<"\t"<<label<<"\t"<<instruction<<"\t"<<operand<<endl;
           }
        else if(instruction=="RESW")
           {
               starting_addressNEW=starttingAddress+RESW(operand);
               MyFile<<decToHex(starttingAddress)<<"\t"<<label<<"\t"<<instruction<<"\t"<<operand<<endl;

           }
         else if(instruction=="WORD")
           {
                starting_addressNEW=starttingAddress+3;
               MyFile<<decToHex(starttingAddress)<<"\t"<<label<<"\t"<<instruction<<"\t"<<operand<<endl;
           }
           else if(instruction=="BYTE")
           {
                starting_addressNEW=starttingAddress+BYTE(operand);
               MyFile<<decToHex(starttingAddress)<<"\t"<<label<<"\t"<<instruction<<"\t"<<operand<<endl;
           }

            //symbol Table
            if(label !="-"){
            MyFile2<<label<<"\t"<<decToHex(starttingAddress)<<endl;
        }

        starttingAddress=starting_addressNEW;
             input.get();
        }
    }


    MyFile2.close();
    input.close();
    MyFile.close();
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------



