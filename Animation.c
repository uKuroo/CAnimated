#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define COLOR_LIST \
    XColor(RESET, "White", "\x1b[0m") \
    XColor(GREEN, "Green", "\x1b[32m") \
    XColor(YELLOW, "Yellow", "\x1b[33m") \
    XColor(BLUE, "Blue", "\x1b[34m") \
    XColor(MAGENTA, "Magenta", "\x1b[35m") \
    XColor(CYAN, "Cyan", "\x1b[36m") \
    XColor(RED, "Red", "\x1b[31m") 

#define XColor(color, colorName, colorText) color,
typedef enum{
    COLOR_LIST
}Color;
#undef XColor

int indexY = 0;
int upOrDown = 0;

void clearTerminal(){
    system("clear");
}

void waitAndClear(){
    usleep(180000);
    clearTerminal();
}

void animation(int indexSentence, char sentence[], int len, int qtdLines){
    if(indexY == qtdLines - 1) upOrDown = 1;
    if(indexY == 0) upOrDown = 0;

    char empty[38] = "                                    ";
    char sentenceConcat[qtdLines][38];


    for(int i = 0; i<qtdLines; i++){
        strcpy(sentenceConcat[i], empty);
    }

    if (indexSentence + len < sizeof(sentenceConcat[0]) - 1) {
        strncpy(sentenceConcat[indexY] + indexSentence, sentence, len);
    }


    printf("|====================================|\n");
    for(int i = 0; i< qtdLines; i++){
        printf("|%s|\n", sentenceConcat[i]);
    }
    printf("|====================================|\n");
}

void startAnimation(char sentence[], int len, int qtdLines){
    for(int i = 0; i < 36 - len; i++){
        animation(i, sentence, len, qtdLines);
        waitAndClear();

        if(indexY >= 0 && indexY < qtdLines && upOrDown == 0) indexY++;
        if(indexY >= 0 && indexY < qtdLines && upOrDown == 1) indexY--;
    }
    for(int i = 36 - len; i > 0; i--){
        animation(i, sentence, len, qtdLines);
        waitAndClear();

        if(indexY >= 0 && indexY < qtdLines && upOrDown == 0) indexY++;
        if(indexY >= 0 && indexY < qtdLines && upOrDown == 1) indexY--;
    }
}

#define XColor(color, colorName, colorText) printf("%d - %s\n", color, colorName);
int menuColors(){
    int x = -1;

    while (x < 0 || x > 6)
    {
        printf("Choose one color\n");
        COLOR_LIST

        scanf("%d", &x);

        system("clear");
    } 
    
    return x;
}
#undef XColor

#define XColor(color, colorName, colorText) case color: { printf(colorText); break; }
void setTerminalColor(Color color){
    switch (color)
    {
        COLOR_LIST
    }
}
#undef XColor

int main()
{
    setTerminalColor(menuColors());

    getchar();
    
    char sentence[100];
    int qtdLines = 0;

    printf("Write the sentence to show on screen\n");
    fgets(sentence, 100, stdin);

    printf("Choose how many lines it'll have\n");
    do{
        scanf("%d", &qtdLines);
        
        if(qtdLines <= 1){
            clearTerminal();
            printf("Must be 2 or more lines!!\nChoose how many lines it'll have\n");
        }
    }while(qtdLines <= 1);

    int len;
    
    for(len = 0; sentence[len] != '\n'; len++)
        printf("%d", len);

    while(1)
        startAnimation(sentence, len, qtdLines);

    return 0;
}
