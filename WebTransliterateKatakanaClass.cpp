#include "WebTransliterateKatakanaClass.h"
#include <iostream>
#include <fstream>

/*
 Fixed transToHiragana( dyo,dyu,dya ): added 'd' to triples; modded transToTRiples memberFunc() to reflect. and all using triples(); 05/23/2016
 Added Logic Line 686: new IF conditional ( =='tt' ) {replace with small 'tsu' char; } 02/13/2016 
 Added Line 1302: transformation needed, no 'j' in doubles; if( triples[firstChar] == 'j' ) { romanizedText[counter]= 'z'; } // transformation needed; 
 Fixed Line: 552:46 Logic error: indexVal Off-by-one 7 changed to 6; Line: 570:35 indexVal Off-by-one 7 changed to 6;  
 Fixed ending in little tsu; 05/09/2015 
 
 
cout <<"Programmer: Joseph Stone\n"
     << "E-mail:    josephStoneBusiness@gmail.com
<< "Quote: \t\t\t\n\t\t\t\"Your strength is equal \n\t\t\tto that of your will to win\"\n\n"
<< "Complied: " <<__DATE__ __TIME__<<endl;
/ *cout<< "\nRead from input.txt.\n\n"; * /

*/

using namespace std;

/* TransliterateHiraganaClass Constructor */
WebTransliterateKatakanaClass::WebTransliterateKatakanaClass()
{
}

/* destructor */
WebTransliterateKatakanaClass::~WebTransliterateKatakanaClass()
{
}

int WebTransliterateKatakanaClass::posOfKatakana(unsigned char KatakanaText[], const int offset=0) {
    
    int foundPos;
     char pArrayOfSingleKatakana[7][3];
     unsigned char pArrayOfDoubKatakana[15][15];
     unsigned char pArrayOfTripKatakana[8][30];
unsigned char pArrayOfSmallKatakana[10][3];

     singleWebKatakana(pArrayOfSingleKatakana);
     doubWebKatakana(pArrayOfDoubKatakana);
    
     smallWebKatakana(pArrayOfSmallKatakana);

     tripleWebKatakana(pArrayOfTripKatakana); /* [6][29] */

      bool kanaReplaced=false;
      int numCharsOmitted=0;
      
      int numCharsInLine=0;
           doubWebKatakana(pArrayOfDoubKatakana);
      for( ; KatakanaText[numCharsInLine] !='\0'; numCharsInLine++) { }

      const int BYTE_LENGTH=3;
      const int DOUBLES_COLUMN=14; // [14]'s entries are NULL vals;
      const int DOUBLES_ROWS=15;
      const int SINGLES_COLUMN=7;
      const int SINGLES_ROWS=3;
      const int TRIPLES_COLUMN=7;
      const int TRIPLES_ROWS=30;
      const int TRIPLES_BYTE_LENGTH=6;
      const int SMALLS_COLUMN=10;
      const int SMALLS_ROWS=3;
      for( int i=offset; i+BYTE_LENGTH <= numCharsInLine && !foundPos; i++) { 
           
               // Doubles!
           for(int j=0; j< DOUBLES_COLUMN && !foundPos; j++) { 
               for(int k=0; k+BYTE_LENGTH <= DOUBLES_ROWS && !foundPos; k+=BYTE_LENGTH) {
                   if( KatakanaText[i+0] == pArrayOfDoubKatakana[j][k] &&
                       KatakanaText[i+1] == pArrayOfDoubKatakana[j][k+1] &&
                       KatakanaText[i+2] == pArrayOfDoubKatakana[j][k+2] 
                     ) {
                          foundPos = i;
                          break;
                     }
               } 
           }
       
           
           // SINGLES!
           for(int j=0; j< SINGLES_COLUMN && !foundPos; j++) { 
               for(int k=0; k+BYTE_LENGTH <= SINGLES_ROWS && !foundPos; k+=BYTE_LENGTH) {
                   if( KatakanaText[i+0] == pArrayOfSingleKatakana[j][k] &&
                       KatakanaText[i+1] == pArrayOfSingleKatakana[j][k+1] &&
                       KatakanaText[i+2] == pArrayOfSingleKatakana[j][k+2] 
                     ) {
                          foundPos = i;
                          break;
                     }
               } 
           }
           
           // Triples!
           // Need to check bounds on this one; 3more bytes are checked here;
           for(int j=0; j+TRIPLES_BYTE_LENGTH <= TRIPLES_COLUMN && !foundPos; j++) { 
               for(int k=0; k+TRIPLES_BYTE_LENGTH <= TRIPLES_ROWS && !foundPos; k+=TRIPLES_BYTE_LENGTH) {
                   if( KatakanaText[i+0] == pArrayOfDoubKatakana[j][k] &&
                       KatakanaText[i+1] == pArrayOfDoubKatakana[j][k+1] &&
                       KatakanaText[i+2] == pArrayOfDoubKatakana[j][k+2] &&
                       KatakanaText[i+3] == pArrayOfDoubKatakana[j][k+3] &&
                       KatakanaText[i+4] == pArrayOfDoubKatakana[j][k+4] &&
                       KatakanaText[i+5] == pArrayOfDoubKatakana[j][k+5] 
                     ) {
                          foundPos = i;
                          break;
                     }
               } 
           }
           
           // Singles-SMALLS!
           for(int j=0; j< SMALLS_COLUMN && !foundPos; j++) { 
               for(int k=0; k+BYTE_LENGTH <= SMALLS_ROWS && !foundPos; k+=BYTE_LENGTH) {
                   if( KatakanaText[i+0] == pArrayOfSmallKatakana[j][k] &&
                       KatakanaText[i+1] == pArrayOfSmallKatakana[j][k+1] &&
                       KatakanaText[i+2] == pArrayOfSmallKatakana[j][k+2] 
                     ) {
                          foundPos = i;
                          break;
                     }
               } 
           }
       
      }
      
      return foundPos;
} 

void WebTransliterateKatakanaClass::pConvertToRomanText(unsigned char hiraganaText[]) { 
     char pArrayOfSingleKatakana[7][3];
     unsigned char pArrayOfDoubKatakana[15][15];
     unsigned char pArrayOfTripKatakana[8][30];
unsigned char pArrayOfSmallKatakana[10][3];

     singleWebKatakana(pArrayOfSingleKatakana);
     doubWebKatakana(pArrayOfDoubKatakana);

     smallWebKatakana(pArrayOfSmallKatakana);

     tripleWebKatakana(pArrayOfTripKatakana); /* [6][29] */
      char singles[]="AIUEON";
      char doubles[]="KSTNHMYRWGZDBP";     /* ka~sa~ta~na~ha~my~ra~wa~ga~za~da~ba~pa */    
      char triples[]="SCKNHMR"; /*sha~cha~kya~nya~hya~mya~rya~"; */ 

      
      bool kanaReplaced=false;
      int numCharsOmitted=0;
      
      int numCharsInLine=0;
      for( ; hiraganaText[numCharsInLine] !='\0'; numCharsInLine++) { }
      
          doubWebKatakana(pArrayOfDoubKatakana);
      /////
      // Checks for matches and replaced kana kana by kana. 
      /////
      for(int a=0, index=0; index < numCharsInLine; ) {
          // a==TempVar mostly used in multiDementioned arrays as Column.
          // index==Position loop is looking at to convert kana.
          kanaReplaced=false;  // Used to shortcut out of comparisons.
          
          // triples[].
          if( hiraganaText[index+1] && hiraganaText[index+2] &&
           hiraganaText[index+4] && hiraganaText[index+5]
          &&  hiraganaText[index+6] ) {
              // Safe to proceed ( bounds checking... )
              for(a=0; triples[a] != '\0' && kanaReplaced==false; a++) {
                  for(int i=0; i < 30 && kanaReplaced==false; i+=6) { // numRows == 30
                      if( hiraganaText[index+0] == pArrayOfTripKatakana[a][i] 
                      &&  hiraganaText[index+1] == pArrayOfTripKatakana[a][i+1] 
                      &&  hiraganaText[index+2] == pArrayOfTripKatakana[a][i+2] 
                      &&  hiraganaText[index+3] == pArrayOfTripKatakana[a][i+3] 
                      &&  hiraganaText[index+4] == pArrayOfTripKatakana[a][i+4] 
                      &&  hiraganaText[index+5] == pArrayOfTripKatakana[a][i+5] ) {
                          hiraganaText[index-numCharsOmitted] = triples[a];
                          if( triples[a]=='S' || triples[a]=='C' ) {
                              hiraganaText[index-numCharsOmitted+1] = doubles[4]; // 'h'
                          } else {
                              hiraganaText[index-numCharsOmitted+1] = doubles[6];  // 'y'
                          }
                          hiraganaText[index-numCharsOmitted+2] = singles[i/6];
                          numCharsOmitted+=3;
                          index+=6;
                          kanaReplaced = true;
                      }
                  }
              }
          } // Bounds Check on If.
          // End of triples.
        if( hiraganaText[index+1] && hiraganaText[index+2] ) {
          // Doubles[] doubWebKatakana
          if( !kanaReplaced ) { 
              // safe to proceed, bounds checking already executed.
              for(a=0; doubles[a] != '\0' && kanaReplaced==false; a++) {//doubles[]="kstnhmyrwgzdbp";
                  for(int i=0; i < 15 && kanaReplaced==false; i+=3) { // numRows == 15
                      if( hiraganaText[index+0] == pArrayOfDoubKatakana[a][i] 
                      &&  hiraganaText[index+1] == pArrayOfDoubKatakana[a][i+1] 
                      &&  hiraganaText[index+2] == pArrayOfDoubKatakana[a][i+2] ) {
                          // MATCH!
                          if( doubles[a] == doubles[2] ) {       // 't'
                              if(singles[i/3] == singles[1] ) { // 'i'
                                  hiraganaText[index-numCharsOmitted] = 'C';
                              }
                              else { // tsu , chi different lenght of chars.
                                  hiraganaText[index-numCharsOmitted] = doubles[a]; 
                              }
                          } else 
                          if ( doubles[a] == doubles[4] && singles[i/3] == singles[2] ) 
                          {   // 'h' change to 'f' if singles[i/3]=='u'
                              hiraganaText[index-numCharsOmitted] = 'F';
                          } else
                          if( doubles[a] == doubles[10] && singles[i/3] == singles[1] ) { 
                              hiraganaText[index-numCharsOmitted] = 'J';
                          } else {
                              hiraganaText[index-numCharsOmitted] = doubles[a];
                          }
//singles[]="aiueo";
                          hiraganaText[index-numCharsOmitted+1] = singles[i/3];
                          
                          // No chars need omitted if 'tsu' or 'chi' is replacing kana char. (3 for 3)
                          if( singles[i/3] == singles[1]&& doubles[a]==doubles[2] ) { // 'chi'
                              hiraganaText[index-numCharsOmitted+1] = doubles[4];
                              hiraganaText[index-numCharsOmitted+2] = singles[1]; 
                              numCharsOmitted--;
                          } 
                          if( singles[i/3] == singles[2]&& doubles[a]== doubles[2] ) { // 'tsu'
                              hiraganaText[index-numCharsOmitted+1] = doubles[1];
                              hiraganaText[index-numCharsOmitted+2] = singles[2];
                              numCharsOmitted--;  
                          }
                          if( singles[i/3] == singles[1]&& doubles[a]== doubles[1] ) { // 'shi'
                              hiraganaText[index-numCharsOmitted+1] = doubles[4];
                              hiraganaText[index-numCharsOmitted+2] = singles[1];
                              numCharsOmitted--;  
                          }
                          
                          numCharsOmitted+=1;
                          index+=3;
                          kanaReplaced = true;                      
                      }
                  }
              }
          }

          // singles[] doubWebKatakana
          if( !kanaReplaced ) { 
              // safe to proceed, bounds checking already executed.
              for(a=0; //singles[a] != '\0' 
                       a< 8 && kanaReplaced==false; a++) {//singles[]="aiueo";
              unsigned char usTemp[3];
                  if ( a < 6 ) { // all singles :aiueon.
                      usTemp[0] = pArrayOfSingleKatakana[a][0];
                      usTemp[1] = pArrayOfSingleKatakana[a][1];
                      usTemp[2] = pArrayOfSingleKatakana[a][2];   
                      for(int i=0; i < 3 && kanaReplaced==false; i+=3) { // numRows == 15
                          if( hiraganaText[index+0] == usTemp[0]//pArrayOfSingleKatakana[a][i] 
                          &&  hiraganaText[index+1] == usTemp[1]//pArrayOfSingleKatakana[a][i+1] 
                          &&  hiraganaText[index+2] == usTemp[2] ) {//pArrayOfSingleKatakana[a][i+2] ) {
                              // MATCH!
                              hiraganaText[index-numCharsOmitted] = singles[a];
                              numCharsOmitted+=2;
                              index+=3;
                              kanaReplaced = true;                          
                          }
                      } 
                  }

                  //10[3] Checks the smalls 
                  if( hiraganaText[index+0] == pArrayOfSmallKatakana[a][0] && !kanaReplaced 
                  &&  hiraganaText[index+1] == pArrayOfSmallKatakana[a][1] 
                  &&  hiraganaText[index+2] == pArrayOfSmallKatakana[a][2] ) {
                      // MATCH!
                      if ( a < 5 ) { // all singles :aiueon.
                          hiraganaText[index-numCharsOmitted] = singles[a];
                      } else {
                          // +1 is to make a triple: jiya jiyo -> jyo jya
                          numCharsOmitted++;
                          if( hiraganaText[index-numCharsOmitted+1] == doubles[10] ) {
                              hiraganaText[index-numCharsOmitted+1] = 'J';
                          }
                          hiraganaText[index-numCharsOmitted] = doubles[6];// 'y'
                          hiraganaText[index+1-numCharsOmitted] = singles[(a-5) *2]; // 'a u o'
                          numCharsOmitted--; // used two chars
                      }
                      numCharsOmitted+=2;
                      index+=3;
                      kanaReplaced = true;                          
                  }
              }
          }
          
          // Lastly find if small tsu is present.
          if( !kanaReplaced ) {
              if( hiraganaText[index+0] == 0xE3 
              &&  hiraganaText[index+1] == 0x83
              &&  hiraganaText[index+2] == 0x83 ) {
                  // MATCH!
                  hiraganaText[index-numCharsOmitted] = 0x06; // placeholder
                                                             // change after out of this loop(double consonant )
                  numCharsOmitted+=2;
                  index+=3;
                  kanaReplaced = true;
              }
          }
        } // End bounds checking..
        
          if ( !kanaReplaced ) { 
              if( index-numCharsOmitted >0 && hiraganaText[index-numCharsOmitted-1] == 0x06 ) { hiraganaText[index-numCharsOmitted]='T'; numCharsOmitted--; } 
              hiraganaText[index-numCharsOmitted] = hiraganaText[index];
              index++;
          }
      }       
      // Place nullterminator.
      hiraganaText[numCharsInLine - numCharsOmitted] = '\0';
    
    // Search all arrays until matches are converted...
    // Now find all x06 s and replace with a doubleConsonant. 
    
    for(int i=0; hiraganaText[i+1] !='\0'; i++) { 
        if( hiraganaText[i]== 0x06) { 
           hiraganaText[i]= hiraganaText[i+1]; 
        }
    }
    // Done.
    
     
    
}

void WebTransliterateKatakanaClass::writeKANA()
{
     char pArrayOfSingleKatakana[7][3];
     unsigned char pArrayOfDoubKatakana[15][15];
     unsigned char pArrayOfTripKatakana[8][30];
         
     singleWebKatakana(pArrayOfSingleKatakana);
     doubWebKatakana(pArrayOfDoubKatakana);
     tripleWebKatakana(pArrayOfTripKatakana); /* [6][29] */
     
     writeFirstBytes("ALLKANA.txt");
     
     ofstream out1;
     unsigned char e[2]={0x0D,0x0A};
     unsigned char space[1];
     space[0]=0x20;
     doubWebKatakana(pArrayOfDoubKatakana);
     out1.open("ALLKANA.txt", ios::app |ios::binary);
          for(int i=0;i<7;i++)
     {
             for(int j=0;j<3;j++)
             {
             out1 << pArrayOfSingleKatakana[i][j];
         //    for(int z=0;z<6;z++)
          //       out1 << space[0];
             }
             out1 << e[0];
             out1 << e[1];
             }
             
                  for(int i=0;i<15;i++)
     {
             for(int j=0;j<15;j++)
             {
             out1 << pArrayOfDoubKatakana[i][j];
       //                   for(int z=0;z<6;z++)
            //     out1 << space[0];
             }
             out1 << e[0];
             out1 << e[1];             }
             
                  for(int i=0;i<6;i++)
     {
             for(int j=0;j<30;j++)
             {
             out1 << pArrayOfTripKatakana[i][j];
           //               for(int z=0;z<6;z++)
           //      out1 << space[0];
             }
             out1 << e[0];
             out1 << e[1];             }
             
             unsigned char missing[]= {0xE3,0x83,0xA7};
             for(int i=0;i<3;i++)
                 out1 << missing[i];
         out1.close();    
}
void WebTransliterateKatakanaClass::writeFirstBytes(char nameOfFile[])
{
    ofstream out;
    const char header[3]= {0xEF, 0xBB, 0xBF};
/*    header[0]=0xEF;
    header[1]=0xBB;
    header[2]=0xBF;
    header[3]='\0'; */
    
    out.open(nameOfFile, ios::binary);
    out.write(header, 3);
    out.close();
}
char * WebTransliterateKatakanaClass::pConvertToKatakanaText(char romanizedText0[])
{
     // Replace all "ji" with "zi" for Kana replacement; 
     char romanizedText[strlen(romanizedText0)+1];
     romanizedText[0]=romanizedText0[0]; 
     if(romanizedText[0]) { romanizedText[1]= romanizedText0[1]; }
     for(int i=1; romanizedText0[i]; i++) {
         if( romanizedText0[i-1] == 'j' && romanizedText0[i]=='i') { 
             romanizedText[i-1]= 'z'; 
         }
         if( romanizedText0[i-1] == 'f' && romanizedText0[i]=='u') { 
             romanizedText[i-1]= 'h'; 
         }
         romanizedText[i+1]= romanizedText0[i+1];
     }
          
     char blahpArrayOfSingleKatakana[7][3];
     unsigned char pArrayOfDoubKatakana[15][15];
     unsigned char pArrayOfTripKatakana[8][30];
     
     
     /* holds katakana representation of romanized text 
           If max lenght is reached in below for-loop then
           the extra space is for the null terminator
     */
     unsigned char holdKana[512]; 
     singleWebKatakana(blahpArrayOfSingleKatakana);
     unsigned char pArrayOfSingleKatakana[7][3];
     for(int a=0; a<7; a++) {
         for(int i=0; i<3; i++) {
             pArrayOfSingleKatakana[a][i] = blahpArrayOfSingleKatakana[a][i];
         }
     }
     
     doubWebKatakana(pArrayOfDoubKatakana);
     tripleWebKatakana(pArrayOfTripKatakana); /* [6][29] */
     
      /* Matches up with singleWebKatakana for easy extraction of like chars */
      char singles[]="aiueo";
      char doubles[]="kstnhmyrwgzdbp";     /* ka~sa~ta~na~ha~my~ra~wa~ga~za~da~ba~pa */    
      char triples[]="scknhmrjgbpd"; /*sha~cha~kya~nya~hya~mya~rya~"; */ 
      
      
      int numCharsHoldKana=0;
      unsigned short int moreTest=0; /* used to store num till end if end is near */
      unsigned short int prevVowel=6; /* needed to add a - character if double vowels */
      unsigned short int prevCons=14; /* 14 == no consonant */
      bool cutLoop=false;
      doubWebKatakana(pArrayOfDoubKatakana);
      for(int counter=0;counter<256&&romanizedText[counter]!='\0';counter++)
      { 
/* SINGLES */
           cutLoop=false;
           if(romanizedText[counter]==' ')
           {
               holdKana[numCharsHoldKana]=' ';
               numCharsHoldKana+=1;
               prevVowel=6;
               prevCons=14;
               cutLoop=true;
           }
          for(int i=0;i<5&& !cutLoop;i++)
          {                  
              if(romanizedText[counter]==singles[i])
              {
                  if( 1==2 && prevVowel==i) /* then add a long mark */
                  {
                      holdKana[numCharsHoldKana]=0xE3;
                      holdKana[numCharsHoldKana+1]=0x83;
                      holdKana[numCharsHoldKana+2]=0xBC;
                      numCharsHoldKana+=3;
                      prevVowel=6;                      
                      cutLoop=true;
                  }
                  else
                  {
                      for(int yuffie=0;yuffie<3;yuffie++)
                          holdKana[numCharsHoldKana+yuffie]=pArrayOfSingleKatakana[i][yuffie];
                          /* counter increases at FOR LOOP  */
                          numCharsHoldKana+=3; 
                          prevVowel=i;  
                          prevCons=14;                   
                          cutLoop=true;
                  }
              }
          }         
          moreTest=0;
          if(romanizedText[counter+1]!='\0'&& counter+1!=256)
              moreTest=1;   /* 1 chars left to test for till end '\0'*/         
          if(moreTest && romanizedText[counter+2]!='\0'&& counter+2!=256)
              moreTest=2; /* at least 2 chars left to test for */
              
          if(moreTest==2) /* if at least 2+counter characters are left then test for triples */
          {  /* IF */
              unsigned short int firstChar;
              firstChar=13; /* 13 is value when none is found */
              for(int yuffie=0;yuffie<12;yuffie++)
              {
                  if(romanizedText[counter]==triples[yuffie])
                  {
                      firstChar=yuffie;
                  }
              }     
/* TRIPLES Checks for 3char cha's || sha's */         
              if(firstChar<2&&!cutLoop) /* if firstChar==c||s */
              {
                  /* if condition 2nd char == 'h' else 3rd char=='y' && 3rd==VOWEL*/
                  if(romanizedText[counter+1]=='h')
                  {    /* if 3rd==VOWEL proceed */
                   /* starting pos of kana character Index COLUMN*6 */
                       unsigned short int vowel=6;
                       vowel=isVowel(romanizedText[counter+2]);
                       if(vowel!=6) /* if six then not a vowel */
                       {   
                           prevVowel=vowel;
                           vowel*=6; /* Starting index val of Columns */
                           if( firstChar < 8 && pArrayOfTripKatakana[firstChar][vowel]!='\0')
                           {
                              if( triples[firstChar]==doubles[prevCons] )
                              { /* double CONSONANT -> overrides prev alpha for tsu kana */
                                  // ///////////////////////
                                  holdKana[numCharsHoldKana-1]=0xE3;//pArrayOfDoubKatakana[2][6];
                                  holdKana[numCharsHoldKana]=0x83;//pArrayOfDoubKatakana[2][7];
                                  holdKana[numCharsHoldKana+1]=0x83;//pArrayOfDoubKatakana[2][8];
                                  numCharsHoldKana+=2;
                                  prevCons=14;
                              }                                                                           
                              else
                              { /* else sets prevCons for next round */
                                  prevCons=14;
                              }

                              for(int yuffie=0;yuffie<6;yuffie++)
                                  holdKana[numCharsHoldKana+yuffie]=pArrayOfTripKatakana[firstChar][vowel+yuffie];

                              counter+=2; /* plus 2 After break will increment the third time */
                              if(holdKana[numCharsHoldKana+3]=='\0')
                                  numCharsHoldKana+=3;
                              else
                                  numCharsHoldKana+=6;                             
                              cutLoop=true;  /* if some chars were written then break */                         
                           }
                        }                    
                   }
              }  /* Checks for 3char kya's and other ya's */
              else if(firstChar!=13&&!cutLoop) /* between num 2-6 */
              {
                  if(romanizedText[counter+1]=='y')
                  {
                   /* starting pos of kana character Index COLUMN*6 */
                       unsigned short int vowel=6;
                       vowel=isVowel(romanizedText[counter+2]);
                       if(vowel!=6) /* if six then not a vowel */
                       {   
                           prevVowel=vowel;
                           vowel*=6; /* Starting index val of Columns */
                           if( firstChar > 6 || pArrayOfTripKatakana[firstChar][vowel]!='\0') // hope to short-circuit for no out-bounds;
                           { /* TRUE == found triple char ya */
                              if( triples[firstChar]==doubles[prevCons] )
                              { /* double CONSONANT -> overrides prev alpha for tsu kana */
                                  ////////////////////////////////////////////////////////
                                  holdKana[numCharsHoldKana-1]=0xE3;//pArrayOfDoubKatakana[2][6];
                                  holdKana[numCharsHoldKana]=0x83;//pArrayOfDoubKatakana[2][7];
                                  holdKana[numCharsHoldKana+1]=0x83;//pArrayOfDoubKatakana[2][8];
                                  numCharsHoldKana+=2;
                                  prevCons=14;
                              }                                                                           
                              else
                              { /* else sets prevCons for next round */
                              prevCons=14;
                              }

                              int holdVowel= vowel;
                              int yuffie=0;
                              if( firstChar > 6 ) {
                                if( triples[firstChar] == 'j' ) { romanizedText[counter]= 'z'; } // transformation needed; 
                                firstChar= 0;
                                for(int j=0;j<14;j++) /* number in doubles */
                                {
                                  vowel=1*3; /* ==i Starting index val of Columns */
                                  if(romanizedText[counter]==doubles[j] )
                                  {
                                    // all nessasary info to add to holdKana.
                                    for(yuffie=0;yuffie<3;yuffie++)
                                      holdKana[numCharsHoldKana+yuffie]=pArrayOfDoubKatakana[j][vowel+yuffie];
                                  }
                                }
                              }                                             
                              vowel= holdVowel;                                          
                                             
                              for( ;yuffie<6;yuffie++)
                                  holdKana[numCharsHoldKana+yuffie]=pArrayOfTripKatakana[firstChar][vowel+yuffie];
                              counter+=2;  /* plus 2 After break will increment the third time */
                              if(holdKana[numCharsHoldKana+3]=='\0')
                                  numCharsHoldKana+=3;
                              else
                                  numCharsHoldKana+=6; 
                              cutLoop=true;  /* if some chars were written then break */
                           }
                       }
                  }
              } 
          } /* END IF */
          if(moreTest>0&&!cutLoop) /* if at least two chars to test */
          { /* if */
/* DOUBLES */
             for(int j=0;j<14;j++) /* number in doubles */
             {
                  if(romanizedText[counter]==doubles[j])
                  {
                       unsigned short int vowel=6;
                       vowel=isVowel(romanizedText[counter+1]);
                       /////////////// SPECIAL TSU ADDED
                       if(vowel==6)
                       {
                           if(romanizedText[counter+1]==doubles[1])
                           {
                            // if more to test && next2 chars are 'su'
                               if(moreTest==2 && 
                                  romanizedText[counter+2]==singles[2] &&
                                  doubles[j]==doubles[2])
                               {
                                   vowel=2; // 'u'                             
                               }
                           }
                       }

                       if(vowel!=6) /* if six then not a vowel */
                       {   
                          prevVowel=vowel;                          
                          vowel*=3; /* Starting index val of Columns */
                          /* checks for '0' specific identifier signifies NONE FOUND IN THAT INDEX */
                          if(pArrayOfDoubKatakana[j][vowel]!='0')
                          {
                              if( romanizedText[counter]==doubles[prevCons] )
                              { /* double CONSONANT -> overrides prev alpha for tsu kana */
                                  ////////////////////////////////////////////////////////
                                  holdKana[numCharsHoldKana-1]=0xE3;//pArrayOfDoubKatakana[2][6];
                                  holdKana[numCharsHoldKana]=0x83;//pArrayOfDoubKatakana[2][7];
                                  holdKana[numCharsHoldKana+1]=0x83;//pArrayOfDoubKatakana[2][8];
                                  numCharsHoldKana+=2;
                                  prevCons=14;
                              }                                                                           
                              else
                              { /* else sets prevCons for next round */
                                  prevCons=14;
                              }
                          
                              for(int yuffie=0;yuffie<3;yuffie++)
                                  holdKana[numCharsHoldKana+yuffie]=pArrayOfDoubKatakana[j][vowel+yuffie];
                              numCharsHoldKana+=3;
                              // MORE FOR TSU ADDITION. if =='s' 
                              // ONLY possible to be here if tsu.
                              if(romanizedText[counter+1]==doubles[1])
                                  counter+=2; // 3 chars transcribed to kana.
                              else
                                  counter+=1; /* one added now, after break another makes two added */
                              cutLoop=true;
                          }
                       }
                       j=13; /* end For loop */
                 }
              }
          } /* end if AGAIN */
          if(romanizedText[counter]=='n'&& !cutLoop)
          {
          /* adds the 'n' katakana char to holdKana  */

              for(int yuffie=0;yuffie<3;yuffie++)
                  holdKana[numCharsHoldKana+yuffie]=pArrayOfSingleKatakana[5][yuffie];
              numCharsHoldKana+=3;              
              cutLoop=true;
              prevVowel=6; 
              prevCons=14; /* can't override 'n' with tsu */           
          }
          /* writes last chars if NO mathces were found */
          if(!cutLoop)
          {
              prevCons=14; /* not a match */                      
              for( int yuffie=0; yuffie<14; yuffie++) /* 14 is numChars in doubles */
              {
                  if( doubles[yuffie]==romanizedText[counter] )
                  {
                      prevCons=yuffie;
                      yuffie=14;
                  }
              }
              // Logic for double 'tt' being little 'tsu' char; 
              if( counter > 0 && romanizedText[counter-1] == romanizedText[counter]&& romanizedText[counter]=='t' ) { 
                  holdKana[numCharsHoldKana-1]=0xE3; // little tsu char; 
                  holdKana[numCharsHoldKana+0]=0x83; 
                  holdKana[numCharsHoldKana+1]=0x83;
                  numCharsHoldKana+=2;
                  prevCons=14; // no match found; dont look next consonant; 
                  cutLoop=true; 
              } else {     
                  holdKana[numCharsHoldKana]=romanizedText[counter];
                  numCharsHoldKana+=1;
                  prevVowel=6;
              }
          }
      }
      
      /*

      */
      char *pKatakana = new char[numCharsHoldKana+1];
    for(int i=0;i<numCharsHoldKana;i++)
        pKatakana[i]=holdKana[i];
    pKatakana[numCharsHoldKana]='\0';
    
    return pKatakana;
}
void WebTransliterateKatakanaClass::singleWebKatakana(char Array[7][3])
{
  		 //Normal Vowel order: {a, i, u, e, o}
    Array[0][0]=0xE3;             /* a */
    Array[0][1]=0x82;
    Array[0][2]=0xA2;
        Array[1][0]=0xE3;             /* i */
        Array[1][1]=0x82;
        Array[1][2]=0xA4;
    Array[2][0]=0xE3;             /* u */
    Array[2][1]=0x82;
    Array[2][2]=0xA6;
        Array[3][0]=0xE3;             /* e */
        Array[3][1]=0x82;
        Array[3][2]=0xA8;
    Array[4][0]=0xE3;           /* o */
    Array[4][1]=0x82;
    Array[4][2]=0xAA;     
        Array[5][0]=0xE3;             /* N */
        Array[5][1]=0x83;  /* 82 83 */
        Array[5][2]=0xB3;
    Array[6][0]='\0';
    Array[6][1]='\0';
    Array[6][2]='\0';
}

/* array x by 9 made for speed; every character set {k,s,z,d,b ... etc}
       are on separate columns and match the alpha representation with the
       exception of the columns (becuase the hex codes are larger than 
       the alpha values. Fixed by taking second index, column, and 
       multiply x3, this gives the starting point of the hiragana values
*/
/* !!DOES NOT have null terminators!! 
       use functions to search through arrays 
*/
void WebTransliterateKatakanaClass::doubWebKatakana(unsigned char Array[15][15])
{
  		 //Normal Vowel order: {a, i, u, e, o}
    Array[0][0]=0xE3;            /* KA */
    Array[0][1]=0x82;
    Array[0][2]=0xAB;
        Array[0][3]=0xE3;            /* KI */
        Array[0][4]=0x82;
        Array[0][5]=0xAD;
            Array[0][6]=0xE3;            /* KU */
            Array[0][7]=0x82;
            Array[0][8]=0xAF;
                Array[0][9]=0xE3;            /* KE */ 
                Array[0][10]=0x82;
                Array[0][11]=0xB1;
                    Array[0][12]=0xE3;            /* KO */
                    Array[0][13]=0x82;
                    Array[0][14]=0xB3;
    Array[1][0]=0xE3;            /* SA */
    Array[1][1]=0x82;
    Array[1][2]=0xB5;
        Array[1][3]=0xE3;            /* SHI */
        Array[1][4]=0x82;
        Array[1][5]=0xB7;
            Array[1][6]=0xE3;            /* SU */
            Array[1][7]=0x82;
            Array[1][8]=0xB9;
                Array[1][9]=0xE3;            /* SE */
                Array[1][10]=0x82;
                Array[1][11]=0xBB;
                    Array[1][12]=0xE3;            /* SO */
                    Array[1][13]=0x82;
                    Array[1][14]=0xBD;
    Array[2][0]=0xE3;            /* TA */
    Array[2][1]=0x82;
    Array[2][2]=0xBF;
        Array[2][3]=0xE3;            /* CHI */
        Array[2][4]=0x83;
        Array[2][5]=0x81;
            Array[2][6]=0xE3;            /* TSU */
            Array[2][7]=0x83;
            Array[2][8]=0x84;
                Array[2][9]=0xE3;            /* TE */
                Array[2][10]=0x83;
                Array[2][11]=0x86;
                    Array[2][12]=0xE3;           /* TO */
                    Array[2][13]=0x83;
                    Array[2][14]=0x88;
    Array[3][0]=0xE3;            /* NA */
    Array[3][1]=0x83; 
    Array[3][2]=0x8A;
        Array[3][3]=0xE3;                  /* NI */
        Array[3][4]=0x83;
        Array[3][5]=0x8B;
            Array[3][6]=0xE3;               /* NU */
            Array[3][7]=0x83;
            Array[3][8]=0x8C;
                Array[3][9]=0xE3;               /* NE */
                Array[3][10]=0x83;
                Array[3][11]=0x8D;
                    Array[3][12]=0xE3;               /* NO */
                    Array[3][13]=0x83;
                    Array[3][14]=0x8E;
    Array[4][0]=0xE3;               /* HA */
    Array[4][1]=0x83;
    Array[4][2]=0x8F;
        Array[4][3]=0xE3;
        Array[4][4]=0x83;
        Array[4][5]=0x92;
            Array[4][6]=0xE3;               /* FU */
            Array[4][7]=0x83;
            Array[4][8]=0x95;
                Array[4][9]=0xE3;
                Array[4][10]=0x83;
                Array[4][11]=0x98;
                    Array[4][12]=0xE3;
                    Array[4][13]=0x83;
                    Array[4][14]=0x9B;
    Array[5][0]=0xE3;               /* MA */
    Array[5][1]=0x83;
    Array[5][2]=0x9E; 
        Array[5][3]=0xE3;
        Array[5][4]=0x83;
        Array[5][5]=0x9F;
            Array[5][6]=0xE3;
            Array[5][7]=0x83;
            Array[5][8]=0xA0;
                Array[5][9]=0xE3;
                Array[5][10]=0x83;
                Array[5][11]=0xA1;
                    Array[5][12]=0xE3;
                    Array[5][13]=0x83;
                    Array[5][14]=0xA2;    
            
    Array[6][0]=0xE3;               /* YA */
    Array[6][1]=0x83;
    Array[6][2]=0xA4;
        Array[6][3]='0';               /* yi 0 */
        Array[6][4]='0';
        Array[6][5]='0';
            Array[6][6]=0xE3;              /* YU */
            Array[6][7]=0x83;
            Array[6][8]=0xA6; 
                Array[6][9]='0';               /* ye 0 */
                Array[6][10]='0';
                Array[6][11]='0';
                    Array[6][12]=0xE3;
                    Array[6][13]=0x83;
                    Array[6][14]=0xA8;
    Array[7][0]=0xE3;                /* RA */
    Array[7][1]=0x83;
    Array[7][2]=0xA9;
        Array[7][3]=0xE3;
        Array[7][4]=0x83;
        Array[7][5]=0xAA;
            Array[7][6]=0xE3;
            Array[7][7]=0x83;
            Array[7][8]=0xAB;
                Array[7][9]=0xE3;
                Array[7][10]=0x83;
                Array[7][11]=0xAC;    
                    Array[7][12]=0xE3;
                    Array[7][13]=0x83;
                    Array[7][14]=0xAD;    
    Array[8][0]=0xE3;                 /* WA */
    Array[8][1]=0x83;
    Array[8][2]=0xAF;
        Array[8][3]='0';               /* wi 0 */
        Array[8][4]='0';
        Array[8][5]='0';
            Array[8][6]='0';               /* wu 0 */
            Array[8][7]='0';
            Array[8][8]='0';
                Array[8][9]='0';               /* we 0 */
                Array[8][10]='0';
                Array[8][11]='0';
                    Array[8][12]=0xE3;              /* WO */
                    Array[8][13]=0x83;
                    Array[8][14]=0xB2;  
    Array[9][0]=0xE3;              /* GA */
    Array[9][1]=0x82;
    Array[9][2]=0xAC;
        Array[9][3]=0xE3;
        Array[9][4]=0x82;
        Array[9][5]=0xAE;
            Array[9][6]=0xE3;
            Array[9][7]=0x82;
            Array[9][8]=0xB0;
                Array[9][9]=0xE3;
                Array[9][10]=0x82;
                Array[9][11]=0xB2;
                    Array[9][12]=0xE3;
                    Array[9][13]=0x82;
                    Array[9][14]=0xB4;
    Array[10][0]=0xE3;              /* ZA */
    Array[10][1]=0x82;
    Array[10][2]=0xB6;
        Array[10][3]=0xE3;              /* JI ** */
        Array[10][4]=0x82;
        Array[10][5]=0xB8;
            Array[10][6]=0xE3;            /* ZU */
            Array[10][7]=0x82;
            Array[10][8]=0xBA;    
                Array[10][9]=0xE3;
                Array[10][10]=0x82;
                Array[10][11]=0xBC;    
                    Array[10][12]=0xE3;
                    Array[10][13]=0x82;
                    Array[10][14]=0xBE;        
    Array[11][0]=0xE3;                 /* DA */
    Array[11][1]=0x83;
    Array[11][2]=0x80;
        Array[11][3]=0xE3;
        Array[11][4]=0x83;
        Array[11][5]=0x82;
            Array[11][6]=0xE3;
            Array[11][7]=0x83;
            Array[11][8]=0x85;
                Array[11][9]=0xE3;
                Array[11][10]=0x83;
                Array[11][11]=0x87; 
                    Array[11][12]=0xE3;
                    Array[11][13]=0x83;
                    Array[11][14]=0x89;
    Array[12][0]=0xE3;                 /* BA */
    Array[12][1]=0x83;
    Array[12][2]=0x90;
        Array[12][3]=0xE3;
        Array[12][4]=0x83;
        Array[12][5]=0x93;
            Array[12][6]=0xE3;
            Array[12][7]=0x83;
            Array[12][8]=0x96;
                Array[12][9]=0xE3;
                Array[12][10]=0x83;
                Array[12][11]=0x99;
                    Array[12][12]=0xE3;
                    Array[12][13]=0x83;
                    Array[12][14]=0x9C;
    Array[13][0]=0xE3;         /* PA */
    Array[13][1]=0x83;
    Array[13][2]=0x91;
        Array[13][3]=0xE3;
        Array[13][4]=0x83;
        Array[13][5]=0x94;
            Array[13][6]=0xE3;
            Array[13][7]=0x83;
            Array[13][8]=0x97;
                Array[13][9]=0xE3;
                Array[13][10]=0x83;
                Array[13][11]=0x9A;
                    Array[13][12]=0xE3;
                    Array[13][13]=0x83;
                    Array[13][14]=0x9D;
    Array[14][0]='\0';
    Array[14][1]='\0';
    Array[14][2]='\0';
    Array[14][3]='\0';
    Array[14][4]='\0';
    Array[14][5]='\0';
    Array[14][6]='\0';
    Array[14][7]='\0';
    Array[14][8]='\0';
    Array[14][9]='\0';
    Array[14][0]='\0';
    Array[14][11]='\0';
    Array[14][12]='\0';
    Array[14][13]='\0';
    Array[14][14]='\0';
}


void WebTransliterateKatakanaClass::tripleWebKatakana(unsigned char Array[8][30])
{  		 //Normal Vowel order: {a, i, u, e, o}

    Array[0][0]=0xE3;            /* SHA first [0-2]==shi [3-5]==ya (small)  */
    Array[0][1]=0x82;
    Array[0][2]=0xB7;
        Array[0][3]=0xE3;            /* ya (small) */
        Array[0][4]=0x83;
        Array[0][5]=0xA3;
            Array[0][6]=0xE3;            /* SHI  */
            Array[0][7]=0x82;
            Array[0][8]=0xB7;
                Array[0][9]='\0';            /* N/A (small) */
                Array[0][10]='\0';
                Array[0][11]='\0';
                    Array[0][12]=0xE3;            /* shu */ 
                    Array[0][13]=0x82;
                    Array[0][14]=0xB7;
                        Array[0][15]=0xE3;            /* yu (small) */
                        Array[0][16]=0x83;
                        Array[0][17]=0xA5;
                            Array[0][18]=0xE3;            /* she  */
                            Array[0][19]=0x82;
                            Array[0][20]=0xB7;
                                Array[0][21]=0xE3;            /* e (small) */
                                Array[0][22]=0x82;
                                Array[0][23]=0xA8;                        
                                    Array[0][24]=0xE3;            /* sho */ 
                                    Array[0][25]=0x82;
                                    Array[0][26]=0xB7;
                                        Array[0][27]=0xE3;            /* yo (small) */
                                        Array[0][28]=0x83;
                                        Array[0][29]=0xA7;
    Array[1][0]=0xE3;            /* CHA first [0-2]==shi [3-5]==ya (small)  */
    Array[1][1]=0x83;
    Array[1][2]=0x81;
        Array[1][3]=0xE3;            /* ya (small) */
        Array[1][4]=0x83;
        Array[1][5]=0xA3;
            Array[1][6]=0xE3;            /* CHI  */
            Array[1][7]=0x83;
            Array[1][8]=0x81;
                Array[1][9]='\0';            /* N/A (small) */
                Array[1][10]='\0';
                Array[1][11]='\0';
                    Array[1][12]=0xE3;            /* CHU */ 
                    Array[1][13]=0x83;
                    Array[1][14]=0x81;
                        Array[1][15]=0xE3;            /* yu (small) */
                        Array[1][16]=0x83;
                        Array[1][17]=0xA5;
                            Array[1][18]=0xE3;            /* she  */
                            Array[1][19]=0x83;
                            Array[1][20]=0x81;
                                Array[1][21]=0xE3;            /* e (small) */
                                Array[1][22]=0x82;
                                Array[1][23]=0xA8;                        
                                    Array[1][24]=0xE3;            /* sho */ 
                                    Array[1][25]=0x83;
                                    Array[1][26]=0x81;
                                        Array[1][27]=0xE3;            /* yo (small) */
                                        Array[1][28]=0x83;
                                        Array[1][29]=0xA7;
    Array[2][0]=0xE3;            /* Kya first [0-2]==ki [3-5]==ya (small)  */
    Array[2][1]=0x82;
    Array[2][2]=0xAD;
        Array[2][3]=0xE3;            /* ya (small) */
        Array[2][4]=0x83;
        Array[2][5]=0xA3;
            Array[2][6]='\0';            /* i N/A  */
            Array[2][7]='\0';
            Array[2][8]='\0';
                Array[2][9]='\0';            /* N/A */
                Array[2][10]='\0';
                Array[2][11]='\0';                        
                    Array[2][12]=0xE3;            /* kyu  */
                    Array[2][13]=0x82;
                    Array[2][14]=0xAD;
                        Array[2][15]=0xE3;            /* yu (small) */
                        Array[2][16]=0x83;
                        Array[2][17]=0xA5;
                            Array[2][18]='\0';            /* e N/A  */
                            Array[2][19]='\0';
                            Array[2][20]='\0';
                                Array[2][21]='\0';            
                                Array[2][22]='\0';
                                Array[2][23]='\0';                        
                                    Array[2][24]=0xE3;            /* kyo */ 
                                    Array[2][25]=0x82;
                                    Array[2][26]=0xAD;
                                        Array[2][27]=0xE3;            /* yo (small) */
                                        Array[2][28]=0x83;
                                        Array[2][29]=0xA7;
    Array[3][0]=0xE3;            /* NYA first [0-2]==NI [3-5]==ya (small)  */
    Array[3][1]=0x83;
    Array[3][2]=0x8B;
        Array[3][3]=0xE3;            /* ya (small) */
        Array[3][4]=0x83;
        Array[3][5]=0xA3;
            Array[3][6]='\0';            /* i N/A  */
            Array[3][7]='\0';
            Array[3][8]='\0';
                Array[3][9]='\0';            /* N/A */
                Array[3][10]='\0';
                Array[3][11]='\0';                        
                    Array[3][12]=0xE3;            /* Nyu  */
                    Array[3][13]=0x83;
                    Array[3][14]=0x8B;
                        Array[3][15]=0xE3;            /* yu (small) */
                        Array[3][16]=0x83;
                        Array[3][17]=0xA5;
                            Array[3][18]='\0';            /* e N/A  */
                            Array[3][19]='\0';
                            Array[3][20]='\0';
                                Array[3][21]='\0';            
                                Array[3][22]='\0';
                                Array[3][23]='\0';                        
                                    Array[3][24]=0xE3;            /* kyo */ 
                                    Array[3][25]=0x83;
                                    Array[3][26]=0x8B;
                                        Array[3][27]=0xE3;            /* yo (small) */
                                        Array[3][28]=0x83;
                                        Array[3][29]=0xA7;
    Array[4][0]=0xE3;            /* Hya first [0-2]==Hi [3-5]==ya (small)  */
    Array[4][1]=0x83;
    Array[4][2]=0x92;
        Array[4][3]=0xE3;            /* ya (small) */
        Array[4][4]=0x83;
        Array[4][5]=0xA3;
            Array[4][6]='\0';            /* i N/A  */
            Array[4][7]='\0';
            Array[4][8]='\0';
                Array[4][9]='\0';            /* N/A */
                Array[4][10]='\0';
                Array[4][11]='\0';                        
                    Array[4][12]=0xE3;            /* Hyu  */
                    Array[4][13]=0x83;
                    Array[4][14]=0x92;
                        Array[4][15]=0xE3;            /* yu (small) */
                        Array[4][16]=0x83;
                        Array[4][17]=0xA5;
                            Array[4][18]='\0';            /* e N/A  */
                            Array[4][19]='\0';
                            Array[4][20]='\0';
                                Array[4][21]='\0';            
                                Array[4][22]='\0';
                                Array[4][23]='\0';                        
                                    Array[4][24]=0xE3;            /* Hyo */ 
                                    Array[4][25]=0x83;
                                    Array[4][26]=0x92;
                                        Array[4][27]=0xE3;            /* yo (small) */
                                        Array[4][28]=0x83;
                                        Array[4][29]=0xA7;
    Array[5][0]=0xE3;            /* Mya first [0-2]==Mi [3-5]==ya (small)  */
    Array[5][1]=0x83;
    Array[5][2]=0x9F;
        Array[5][3]=0xE3;            /* ya (small) */
        Array[5][4]=0x83;
        Array[5][5]=0xA3;
            Array[5][6]='\0';            /* i N/A  */
            Array[5][7]='\0';
            Array[5][8]='\0';
                Array[5][9]='\0';            /* N/A */
                Array[5][10]='\0';
                Array[5][11]='\0';                        
                    Array[5][12]=0xE3;            /* Myu  */
                    Array[5][13]=0x83;
                    Array[5][14]=0x9F;
                        Array[5][15]=0xE3;            /* yu (small) */
                        Array[5][16]=0x83;
                        Array[5][17]=0xA5;
                            Array[5][18]='\0';            /* e N/A  */
                            Array[5][19]='\0';
                            Array[5][20]='\0';
                                Array[5][21]='\0';            
                                Array[5][22]='\0';
                                Array[5][23]='\0';                        
                                    Array[5][24]=0xE3;            /* Myo */ 
                                    Array[5][25]=0x83;
                                    Array[5][26]=0x9F;
                                        Array[5][27]=0xE3;            /* yo (small) */
                                        Array[5][28]=0x83;
                                        Array[5][29]=0xA7;
    Array[6][0]=0xE3;            /* Rya first [0-2]==Ri [3-5]==ya (small)  */
    Array[6][1]=0x83;
    Array[6][2]=0xAA;
        Array[6][3]=0xE3;            /* ya (small) */
        Array[6][4]=0x83;
        Array[6][5]=0xA3;
            Array[6][6]='\0';            /* i N/A  */
            Array[6][7]='\0';
            Array[6][8]='\0';
                Array[6][9]='\0';            /* N/A */
                Array[6][10]='\0';
                Array[6][11]='\0';                        
                    Array[6][12]=0xE3;            /* Ryu  */
                    Array[6][13]=0x83;
                    Array[6][14]=0xAA;
                        Array[6][15]=0xE3;            /* yu (small) */
                        Array[6][16]=0x83;
                        Array[6][17]=0xA5;
                            Array[6][18]='\0';            /* e N/A  */
                            Array[6][19]='\0';
                            Array[6][20]='\0';
                                Array[6][21]='\0';            
                                Array[6][22]='\0';
                                Array[6][23]='\0';                        
                                    Array[6][24]=0xE3;            /* Ryo */ 
                                    Array[6][25]=0x83;
                                    Array[6][26]=0xAA;
                                        Array[6][27]=0xE3;            /* yo (small) */
                                        Array[6][28]=0x83;
                                        Array[6][29]=0xA7;
    Array[7][0]=0xE3;            /* Jya first [0-2]==Ri [3-5]==ya (small)  */
    Array[7][1]=0x82;
    Array[7][2]=0xB8;
        Array[7][3]=0xE3;            /* ya (small) */
        Array[7][4]=0x83;
        Array[7][5]=0xA3;
            Array[7][6]='\0';            /* i N/A  */
            Array[7][7]='\0';
            Array[7][8]='\0';
                Array[7][9]='\0';            /* N/A */
                Array[7][10]='\0';
                Array[7][11]='\0';                        
                    Array[7][12]=0xE3;            /* Jyu  */
                    Array[7][13]=0x82;
                    Array[7][14]=0xB8;
                        Array[7][15]=0xE3;            /* yu (small) */
                        Array[7][16]=0x83;
                        Array[7][17]=0xA5;
                            Array[7][18]='\0';            /* e N/A  */
                            Array[7][19]='\0';
                            Array[7][20]='\0';
                                Array[7][21]='\0';            
                                Array[7][22]='\0';
                                Array[7][23]='\0';                        
                                    Array[7][24]=0xE3;            /* Jyo */ 
                                    Array[7][25]=0x82;
                                    Array[7][26]=0xB8;
                                        Array[7][27]=0xE3;            /* yo (small) */
                                        Array[7][28]=0x83;
                                        Array[7][29]=0xA7;

    Array[8][0]=0xE3;            /* Jya first [0-2]==Ri [3-5]==ya (small)  */
    Array[8][1]=0x83;
    Array[8][2]=0x82;
        Array[8][3]=0xE3;            /* ya (small) */
        Array[8][4]=0x83;
        Array[8][5]=0xA3;
            Array[8][6]='\0';            /* i N/A  */
            Array[8][7]='\0';
            Array[8][8]='\0';
                Array[8][9]='\0';            /* N/A */
                Array[8][10]='\0';
                Array[8][11]='\0';                        
                    Array[8][12]=0xE3;            /* Jyu  */
                    Array[8][13]=0x83;
                    Array[8][14]=0x82;
                        Array[8][15]=0xE3;            /* yu (small) */
                        Array[8][16]=0x83;
                        Array[8][17]=0xA5;
                            Array[8][18]='\0';            /* e N/A  */
                            Array[8][19]='\0';
                            Array[8][20]='\0';
                                Array[8][21]='\0';            
                                Array[8][22]='\0';
                                Array[8][23]='\0';                        
                                    Array[8][24]=0xE3;            /* Jyo */ 
                                    Array[8][25]=0x83;
                                    Array[8][26]=0x82;
                                        Array[8][27]=0xE3;            /* yo (small) */
                                        Array[8][28]=0x83;
                                        Array[8][29]=0xA7;
}

void WebTransliterateKatakanaClass::smallWebKatakana(unsigned char Array[10][3])
{  		 //Normal Vowel order: { a, i, u, e, o, ya, yu, yo, tsu [small] )
      //{a, i, u, e, o}
    Array[0][0]=0xE3;             /* a */
    Array[0][1]=0x82;
    Array[0][2]=0xA1;
        Array[1][0]=0xE3;             /* i */
        Array[1][1]=0x82;
        Array[1][2]=0xA3;
            Array[2][0]=0xE3;             /* u */
            Array[2][1]=0x82;
            Array[2][2]=0xA5;
                Array[3][0]=0xE3;             /* e */
                Array[3][1]=0x82;
                Array[3][2]=0xA7;
                    Array[4][0]=0xE3;           /* o */
                    Array[4][1]=0x82;
                    Array[4][2]=0xA9;     
                        Array[5][0]=0xE3;            /* ya (small)  */
                        Array[5][1]=0x83;
                        Array[5][2]=0xA3;
                            Array[6][0]=0xE3;            /* yu (small) */
                            Array[6][1]=0x83;
                            Array[6][2]=0xA5;
                                Array[7][0]=0xE3;            /* yo (small) */
                                Array[7][1]=0x83;
                                Array[7][2]=0xA7;
                                    Array[8][0]='\0';
                                    Array[8][1]='\0';
                                    Array[8][2]='\0';
                                        Array[9][0]='\0';
                                        Array[9][1]='\0';
                                        Array[9][2]='\0';
}

unsigned short int WebTransliterateKatakanaClass::isVowel(char character)
{//Normal Vowel order: {a, i, u, e, o}
    unsigned short int vowel=6;
    char charVowels[]="aiueo";
    for(int i=0;i<5;i++)
    {
        if(charVowels[i]==character)
            vowel=i;
    }
    return vowel;
     
}
void WebTransliterateKatakanaClass::pause()
{
			char i;
            char *z = new char;
			cout << "\ntype a character and press Enter...\n";
            cin >> i;
			z[0]=i;
            //z = NULL;
            // Just added!!
                 delete z;
				 z=0;
            cin.ignore();
}
void WebTransliterateKatakanaClass::pause(char STRING[])
{
     			char i;
            char *z = new char;
			cout << STRING << endl;
            cin >> i;
			z[0]=i;
            //z = NULL;
            // Just added!!
                 delete z;
				 z=0;
            cin.ignore();

}
void WebTransliterateKatakanaClass::pause(int STRING)
{
     			char i;
            char *z = new char;
			cout << STRING << endl;
            cin >> i;
			z[0]=i;
            //z = NULL;
            // Just added!!
                 delete z;
				 z=0;
            cin.ignore();

}
