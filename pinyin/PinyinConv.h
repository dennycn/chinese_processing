#ifndef _PINYIN_H
#define _PINYIN_H

#include <stdio.h>   // called printf()
#include <iostream>
#include <string>
#include <map>

using std::string;
using std::map;
using namespace std;

#define ALPHABETNUM 26
#define PINYINNUM 396


namespace Pinyin
{

class PinyinConv
{
public:
        PinyinConv();
        static PinyinConv *get_instance();
        string getFirstSpell(const char* src);
        string getFullSpell(const char* src);
        
private:
        inline bool isGBCode(const char* src);
        inline int getGBValue(const char* src, int type=1);
        char getGBJP(int iAscii);

private:
        static PinyinConv *_instance;        
        static int pyvalue[PINYINNUM];
        static string pystr[PINYINNUM];
        static string stockGBList[];
        static string stockGBpyList[];

typedef map<int, string> pyMap;
        pyMap _m_pyMap;

};

extern "C" {
    string getFirstSpell(const char* src);
    string getFullSpell(const char* src);
}

} // end namespace

#endif
