/*
 *  main.cpp- "the Client"
 *  Nana Adjekum
 *  8-Nov
 *
 *  CS 15 Proj3 ZAP!
 *
 *  main function for ZAP
 *  
 *
 *
 */

#include "HuffmanCoder.h"
using namespace std;

int main(int argc, char *argv[])
{
    string zap = "zap";
    string unzap = "unzap";

    if (argc != 4) {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile";
        cerr << endl;
        exit(1); 
    } else {
        if (argv[1] == zap) {
            HuffmanCoder encode;
            encode.encoder(argv[2], argv[3]);
        } else if (argv[1] == unzap) {
            HuffmanCoder decode;
            decode.decoder(argv[2], argv[3]);
        } else {
            cerr << "Usage: ./zap [zap | unzap] inputFile outputFile"; 
            cerr << endl;
            exit(1); 
        }
    
    }
    return 0;
}