#ifndef WEBTRANSLITERATEKATAKANACLASS_H
#define WEBTRANSLITERATEKATAKANACLASS_H

class WebTransliterateKatakanaClass
{
      public: 
          int posOfKatakana(unsigned char hiraganaText[], const int offset);              
          WebTransliterateKatakanaClass();
          ~WebTransliterateKatakanaClass();
           void singleWebKatakana(char Array[7][3]);
           void doubWebKatakana(unsigned char Array[15][15]);
           void tripleWebKatakana(unsigned char Array[8][30]); // added 'd' to triples; 05/23/2016
void smallWebKatakana(unsigned char Array[10][3]);
           char *pConvertToKatakanaText(char romanizedText[]);
           void pConvertToRomanText(unsigned char KatakanaText[]);
           void writeFirstBytes(char nameOfFile[]);
           void writeKANA();
           /* if 6 is returned char != VOWEL else returns position of vowel in arrays */
           unsigned short int isVowel(char); 
          
           void pause();
           void pause(char []);
           void pause(int);
};
#endif
