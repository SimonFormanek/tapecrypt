/*
crypt.cpp - reimplement crypt.sh
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char outFilNam[512], inFilNam[512], buf[1024];
int tapeInit = 0, inSize = 0, inSizeRaw = 0, i = 0;

char *in = NULL;
unsigned char* tape = NULL;

char* line = NULL;
size_t llen = 0;
ssize_t lread;

unsigned char znak[3] = {0, 0, 0};
unsigned char znaky[2][255];

//----------------------------------------------------------------------------

int findPos(unsigned char L, unsigned char H) {
    int idx = 0;
    while ((znaky[0][idx] != L) || (znaky[1][idx] != H)) if (++idx > 255) return -1;

    return idx;
}
//----------------------------------------------------------------------------

void fuj(char* mess) {

    if (in != NULL) delete[] in;
    if (tape != NULL) delete[] tape;
    perror(mess);
    exit(EXIT_FAILURE);
}
//----------------------------------------------------------------------------

int main(int argc, char* argv[]) {

    memset(&buf, 0, sizeof (buf));

    if (argc < 3) {
        sprintf(buf, "Chybi povinne parametry! KONEC!\n\0");
        fuj(buf);
    }

    sprintf(inFilNam, "%s\0", argv[1]);
    //pure:orig  sprintf(outFilNam, "%s.htmc\0", argv[1]);
    sprintf(outFilNam, "%s\0", argv[1]);

    sscanf(argv[2], "%i", &tapeInit);

    FILE *inFil = NULL;

    if (strstr(inFilNam, "-")) {
        inFil = stdin;
    } else {
//        inFil = fopen("/dev/stdin", "r");
        inFil = fopen(inFilNam, "r");
    }


    if (inFil == NULL) {
        sprintf(buf, "Nelze otevrit vstupni soubor '%s'! KONEC!\n\0", inFilNam);
        fuj(buf);
    }


    fseek(inFil, 0L, SEEK_END);
    inSizeRaw = ftell(inFil);
    fseek(inFil, 0L, SEEK_SET);


    in = new char[inSizeRaw + 1];
    fread(in, 1, inSizeRaw, inFil);
    fclose(inFil);

    //oxcavacka na delku utf8 - zjisti skut.pocet znaku textu:
    for (i = 0; i < inSizeRaw; i++) {
        inSize++;
        if ((unsigned char) in[i] > 127) i++;
    }

    //pripravit segment pasky:
    FILE* tapeFil = fopen("tape.txt", "r");
    if (tapeFil == NULL) {
        sprintf(buf, "Nelze otevrit soubor s paskou 'tape.txt'! KONEC!\n\0");
        fuj(buf);
    }

    for (i = 0; i <= tapeInit; i++) { //nalistuj 1.polozku
        if ((lread = getline(&line, &llen, tapeFil)) == -1) break;
    }

    tape = new unsigned char[inSize + 1];

    for (i = 0; i < inSize; i++) { //1.mame uz nactenou - ulozit do pameti a brat dalsi..

        sscanf(line, "%i", &tape[i]);
        if ((lread = getline(&line, &llen, tapeFil)) == -1) {
            sprintf(buf, "Dosazeno konce souboru 'tape.txt' - nelze nacist potrebnou delku klice! KONEC!\n\0");
            fuj(buf);
        }
    }

    fclose(tapeFil);


    //pripravit tabulku znaku:
    memset(&znak, 0, sizeof (znak));
    memset(&znaky, 0, sizeof (znaky));

    FILE* anFil = fopen("anumlong.txt", "r");
    if (anFil == NULL) {
        sprintf(buf, "Nelze otevrit soubor se znaky 'anumlong.txt'! KONEC!\n\0");
        fuj(buf);
    }

    i = 0;
    char* delim = NULL; //TODO tohle cele postupne asi upravit||vyhodit po dohode na definit.formatu souboru
    while ((lread = getline(&line, &llen, anFil)) != -1) {
        delim = strchr(line, ':');
        delim++;
        znaky[0][i] = *delim++;
        znaky[1][i] = (*delim != '\n') ? *delim : 0;
        i++;
    }

    int pocet = i;

    FILE *outFil = NULL;

    if (strstr(outFilNam, "-")) {
        outFil = stdout;
    } else {
        outFil = fopen(outFilNam, "r");
//        outFil = fopen("/dev/stdout", "r");
    }

    if (outFil == NULL) {
        sprintf(buf, "Nelze otevrit vystupni soubor '%s'! KONEC!\n\0", outFilNam);
        fuj(buf);
    }

    printf("%i:%i\n");
    fprintf(outFil, "%i:%i\n", inSize, tapeInit);

    int pos = 0, ri = 0;
    unsigned char idx = 0;
    for (i = 0; i < inSize; i++) {

        pos = findPos((unsigned char) in[ri], ((unsigned char) in[ri] > 127) ? in[ri + 1] : 0);

        idx = (pos != -1) ? pos : 0;
        idx += tape[i]; //vernamize_it
        printf("%u\n");
        //    fprintf(outFil, "%u\n", idx);

        if ((unsigned char) in[ri] > 127) ri++;
        ri++;
    }


    //  fclose(outFil); 

    delete[] in;
    delete[] tape;

    exit(EXIT_SUCCESS);
}

//-------------------------------END-------------------------------
