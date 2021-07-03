#include<bits/stdc++.h>
#define isON(x,k) (((x)>>(k))&1)
using namespace std;

int PC = 0;

map<int,  string> opcodes;  // opcode  ,  type/instruction "r" --> R , "i" --> I , "s" --> S , "b" --> B , "j" --> jalr , "f" --> fence
map<pair<int, string>, string> func3;  // <func3,  type>  ,  sub-type/instruction
map<pair<int, string>, string> func7;    //  <func7,  sub-type>  ,  instruction

// creating the maps to encode the instructions from files
void createMaps()
{
    int o;
    string c, s;

    ifstream opf;
    opf.open("opcodes.txt");
    while(!opf.eof()){
        opf>>o>>s;
        opcodes[o] = s;
    }
    opf.close();

    ifstream func3f;
    func3f.open("func3.txt");
    while(!func3f.eof()){
        func3f>>o>>c>>s;
        func3[{o,c}] = s;
    }
    func3f.close();

    ifstream func7f;
    func7f.open("func7.txt");
    while(!func7f.eof()){
        func7f>>o>>c>>s;
        func7[{o,c}] = s;
    }
    func7f.close();

    for(auto i:func7) cout<< i.first.first << " " << i.first.second << " " << i.second<<endl;
}

string getBinary(char c)
{
    string str;
    for(int i=0; i<=7; i++){
           if(isON(c,i)) str += "1";
           else str += "0";
    }
    return str;
}

// Get 32-bit instructions
void get32(string& code)
{
    int op = 0;
    for(int i=6; i>=0; i--){
        if(code[i] == '1') op |= (1<<i);
    }
    if(op == 51) printRIns(code);
    else if(op == 19) printI1Ins(code);
    else if(op == 3 || op == 103) printI2Ins(code);
    else if(op == 35) printSIns(code);
    else if(op == 111) printJIns(code);
    else if(op == 15) printFIns(code);
}



void process(string& obj)
{
    int i=0, limit;
    for(;i<obj.size();){
        string encode;
        char cur = obj[i++];
        encode += getBinary(cur);

        // check if it is compressed instruction or not
        if(encode[0] == '1' && encode[1] == '1') limit = 4;
        else limit = 2;

        // get the rest of the encode
        for(int j=1; j<limit; j++){
            cur = obj[i++];
            encode += getBinary(cur);
        }
        cout<< encode<<endl;
        if(encode[0] == '1' && encode[1] == '1') get32(encode);
        //else get16(encode);
        break;
    }
}

int main ( int argc, char *argv[] )
{
    /*
    if ( argc != 2 ) {
        cout<< "There should be 1 argument!";
        return 0;
    }

    ifstream the_file ( argv[1], ios::in | ios::binary );
    if (the_file.fail())
    {
        cout << "Could not process " << argv[1] << "!\n";
        exit(1);
    }*/
    ifstream the_file ( "div.bin", ios::in | ios::binary );
    string contents(istreambuf_iterator<char>(the_file), (istreambuf_iterator<char>()));

    if(!contents.size()) {
        cout<< "The file is empty";
        return 0;
    }

    createMaps();
    process(contents);
}