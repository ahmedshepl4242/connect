#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//returns 1 if XML file is valid and 0 otherwise
_Bool checkValidity (char filePath[1000]) {
    FILE *fpointer = fopen(filePath,"r+");
    if (!fpointer) {
        fclose(fpointer);
        return 0;
    }
    char input;
    _Bool doTheCeck (_Bool isGlobal) {
    char tagInput[100] = {0};
    while (!(feof(fpointer))) {
        input = fgetc(fpointer);
        if(!(isspace(input)) && input != '<' && input != EOF)
        {
            return 0;
        }
        if (input=='<'){
            int i=0;
            while(1){
                input = fgetc(fpointer);
                if (input == '/') {
                    if (isGlobal) {
                        return 0;
                    }
                    else {
                        return 1;
                    }
                }
                else if (isspace(input)) {
                    return 0;
                }
                tagInput[i] = input;
                i++;
                if (input=='>') break;
            }
            while((input = fgetc(fpointer))!='<') {
                if (input == EOF) {
                    return 0;
                }
            }
            if (fgetc(fpointer)!='/') {
                fseek(fpointer,-2,SEEK_CUR);
                int num = doTheCeck(0);
                if (!num) {
                    return 0;
                }
            }
            for(int j = 0; j<i; j++) {
                if (fgetc(fpointer)!=tagInput[j]){
                    return 0;
                }
            }
        }
    }
    return 1;
    }
    int checkResult = doTheCeck(1);
    fclose(fpointer);
    return checkResult;
}
//return -1 if not found
int getWidth (char filePath[1000]) {
    FILE *fpointer = fopen(filePath,"r");
    char configTag[15] = "configurations";
    char widthTag[6] = "width";
    char input ;
    while (!feof(fpointer)) {
        input = fgetc(fpointer);
        //check if <configurations> exists and return -1 if it does not exist
        if(input=='<') {
            _Bool isConfigTag = 1;
            for (int i=0; i<14; i++) {
                if (fgetc(fpointer)!=configTag[i]) {
                    isConfigTag = 0;
                    break;
                }
            }
            getc(fpointer);
            if (!isConfigTag) continue;
            while (1) {
                while (isspace(fgetc(fpointer)));
                input = fgetc(fpointer);
                if (input == '/') {
                    _Bool terminal = 1;
                    for (int i=0; i<14; i++) {
                        if (fgetc(fpointer)!=configTag[i]) {
                            terminal=0;
                            break;
                        }
                    }
                    if (terminal) {
                        fclose(fpointer);
                        return -1;
                    }
                }
                else {
                    _Bool tagfound = 1;
                    fseek(fpointer,-1,SEEK_CUR);
                    for (int i=0; i<5; i++) {
                        if (fgetc(fpointer)!=widthTag[i]) {
                            tagfound = 0;
                            break;
                        }
                    }
                    if (tagfound) {
                        getc(fpointer);
                        char integerChars[10];
                        int i =0;
                        while (i<9) {
                            input = fgetc(fpointer);
                            if (isspace(input)) continue;
                            if (isdigit(input)){
                                integerChars[i] = input;
                                i++;
                            }
                            else if (input == '<') {
                                break;
                            }
                            else if (input != '<') {
                                fclose(fpointer);
                                return -1;
                            }
                        }
                        integerChars[i] = '\0';
                        fclose(fpointer);
                        return atoi(integerChars);
                    }
                }
            }
        }
    }
    fclose(fpointer);
    return - 1;
}

int getHeight (char filePath[1000]) {
    FILE *fpointer = fopen(filePath,"r");
    char configTag[15] = "configurations";
    char heightTag[7] = "height";
    char input ;
    while (!feof(fpointer)) {
        input = fgetc(fpointer);
        //check if <configurations> exists and return -1 if it does not exist
        if(input=='<') {
            _Bool isConfigTag = 1;
            for (int i=0; i<14; i++) {
                if (fgetc(fpointer)!=configTag[i]) {
                    isConfigTag = 0;
                    break;
                }
            }
            getc(fpointer);
            if (!isConfigTag) continue;
            while (1) {
                while (isspace(fgetc(fpointer)));
                input = fgetc(fpointer);
                if (input == '/') {
                    _Bool terminal = 1;
                    for (int i=0; i<14; i++) {
                        if (fgetc(fpointer)!=configTag[i]) {
                            terminal=0;
                            break;
                        }
                    }
                    if (terminal) {
                        fclose(fpointer);
                        return -1;
                    }
                }
                else {
                    _Bool tagfound = 1;
                    fseek(fpointer,-1,SEEK_CUR);
                    for (int i=0; i<6; i++) {
                        if (fgetc(fpointer)!=heightTag[i]) {
                            tagfound = 0;
                            break;
                        }
                    }
                    if (tagfound) {
                        getc(fpointer);
                        char integerChars[10];
                        int i =0;
                        while (i<9) {
                            input = fgetc(fpointer);
                            if (isspace(input)) continue;
                            if (isdigit(input)){
                                integerChars[i] = input;
                                i++;
                            }
                            else if (input == '<') {
                                break;
                            }
                            else if (input != '<') {
                                fclose(fpointer);
                                return -1;
                            }
                        }
                        integerChars[i] = '\0';
                        fclose(fpointer);
                        return atoi(integerChars);
                    }
                }
            }
        }
    }
    fclose(fpointer);
    return - 1;
}

int getHighScores (char filePath[1000]) {
    FILE *fpointer = fopen(filePath,"r");
    char configTag[15] = "configurations";
    char highScoresTag[11] = "highscores";
    char input ;
    while (!feof(fpointer)) {
        input = fgetc(fpointer);
        //check if <configurations> exists and return -1 if it does not exist
        if(input=='<') {
            _Bool isConfigTag = 1;
            for (int i=0; i<14; i++) {
                if (fgetc(fpointer)!=configTag[i]) {
                    isConfigTag = 0;
                    break;
                }
            }
            getc(fpointer);
            if (!isConfigTag) continue;
            while (1) {
                while (isspace(fgetc(fpointer)));
                input = fgetc(fpointer);
                if (input == '/') {
                    _Bool terminal = 1;
                    for (int i=0; i<14; i++) {
                        if (fgetc(fpointer)!=configTag[i]) {
                            terminal=0;
                            break;
                        }
                    }
                    if (terminal) {
                        fclose(fpointer);
                        return -1;
                    }
                }
                else {
                    _Bool tagfound = 1;
                    fseek(fpointer,-1,SEEK_CUR);
                    for (int i=0; i<10; i++) {
                        if (fgetc(fpointer)!=highScoresTag[i]) {
                            tagfound = 0;
                            break;
                        }
                    }
                    if (tagfound) {
                        getc(fpointer);
                        char integerChars[20];
                        int i =0;
                        while (i<19) {
                            input = fgetc(fpointer);
                            if (isspace(input)) continue;
                            if (isdigit(input)){
                                integerChars[i] = input;
                                i++;
                            }
                            else if (input == '<') {
                                break;
                            }
                            else if (input != '<') {
                                fclose(fpointer);
                                return -1;
                            }
                        }
                        integerChars[i] = '\0';
                        fclose(fpointer);
                        return atoi(integerChars);
                    }
                }
            }
        }
    }
    fclose(fpointer);
    return - 1;
}

_Bool readParametars (int *width, int *hight, int *highScores,char path[1000]) {
    _Bool isValidFile = checkValidity(path);
    if (isValidFile==0) {
        return 0;
    }
    int wdth = getWidth(path);
    int ht = getHeight(path);
    int hScrs = getHighScores(path);
    if ((wdth == -1 )|| (ht == -1) || (hScrs == -1)) isValidFile = 0;
    if (isValidFile) {
        *width = wdth;
        *hight = ht;
        *highScores = hScrs;
        return 1;
    }
    else return 0;
}

