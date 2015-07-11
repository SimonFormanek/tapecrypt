/*
decrypt.cpp - reimplement decrypt.sh
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char outFilNam[512], inFilNam[512], buf[1024];
int tapeInit = 0, inSize = 0, i = 0;

unsigned char* tape = NULL; 

char* line = NULL;
size_t llen = 0;
ssize_t lread;

unsigned char znak[3] = {0,0,0};
unsigned char znaky[2][255];

//----------------------------------------------------------------------------

void fuj(char* mess) {
  
  if(tape != NULL) delete[] tape;
  perror(mess); 
  exit(EXIT_FAILURE); 
}
//----------------------------------------------------------------------------

int main(int argc, char* argv[]) { 

  memset(&buf, 0, sizeof(buf));
    
  if(argc < 2) { 
    sprintf(buf, "Chybi povinne parametry! KONEC!\n\0");
    fuj(buf); 
  }
  
  sprintf(inFilNam, "%s.htmc\0", argv[1]); 
  sprintf(outFilNam, "%s.htmt\0", argv[1]);
  
  
  FILE* inFil = fopen(inFilNam, "r");
  if(inFil == NULL) {
    sprintf(buf, "Nelze otevrit vstupni soubor '%s'! KONEC!\n\0", inFilNam);
    fuj(buf); 
  }
  
  lread = getline(&line, &llen, inFil);
  char* dvojtec = strchr(line, ':'); *dvojtec = 0; dvojtec++; 
  sscanf(line, "%i", &inSize);
  sscanf(dvojtec, "%i", &tapeInit);


  //pripravit segment pasky:
  FILE* tapeFil = fopen("tape.txt", "r");
  if(tapeFil == NULL) {
    sprintf(buf, "Nelze otevrit soubor s paskou 'tape.txt'! KONEC!\n\0");
    fuj(buf); 
  }

  for(i = 0; i <= tapeInit; i++) { //nalistuj 1.polozku
    if((lread = getline(&line, &llen, tapeFil)) == -1) break; 
  }

  tape = new unsigned char[inSize+1];

  for(i = 0; i < inSize; i++) { //1.mame uz nactenou - ulozit do pameti a brat dalsi..

    sscanf(line, "%i", &tape[i]);
    lread = getline(&line, &llen, tapeFil);
  }    
  
  fclose(tapeFil);
  
  
  //pripravit tabulku znaku:
  memset(&znak, 0, sizeof(znak));
  memset(&znaky, 0, sizeof(znaky));
  
  FILE* anFil = fopen("anumlong.txt", "r");
  if(anFil == NULL) {
    sprintf(buf, "Nelze otevrit soubor se znaky 'anumlong.txt'! KONEC!\n\0");
    fuj(buf); 
  }
  
  i = 0;
  char* delim = NULL; //TODO tohle cele postupne asi upravit||vyhodit po dohode na definit.formatu souboru
  while((lread = getline(&line, &llen, anFil)) != -1) {
    delim = strchr(line, ':'); delim++;
    znaky[0][i] = *delim++;
    znaky[1][i] = (*delim != '\n') ? *delim : 0;
    i++;
  }
  
  fclose(anFil); 
  
  
  FILE* outFil = fopen(outFilNam, "w");
  if(outFil == NULL) {
    sprintf(buf, "Nelze otevrit vystupni soubor '%s'! KONEC!\n\0", outFilNam);
    fuj(buf); 
  }
  
  unsigned char rd = 0; unsigned int rdi = 0; 
  i = 0; 
  while((lread = getline(&line, &llen, inFil)) != -1) {
    sscanf(line, "%i", &rdi); 
    rd = rdi;
    rd -= tape[i]; //devernamize_it
    znak[0] = znaky[0][rd]; znak[1] = znaky[1][rd]; 

    fprintf(outFil, "%s", znak); 
    
    i++;
  }
    
 
  fclose(outFil); fclose(inFil);
  
  delete[] tape;
  
  exit(EXIT_SUCCESS);
}

//-------------------------------END-------------------------------
