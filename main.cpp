#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>

using namespace std;

int main(int argc, char* argv[]) {

    if(argc!=2){
        
    }

    ifstream ip_file("C:/Users/Rohith A K/Downloads/rcsb_pdb_4D2I.fasta");

    string input = "";

    bool first = false;

    string line;

    while(getline(ip_file,line)){
        if(!first)
            cout<<line<<endl;
        else 
            input+=line;
    }

    cout<<input<<endl;

    return 0;
}