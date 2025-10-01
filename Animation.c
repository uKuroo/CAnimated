#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct Colors{
    int id;
    char colorCode[10];
}Colors;

int indexY = 0;
int upOrDown = 0;

void waitAndClear(){
    usleep(180000);
    system("clear");
}

void initializeColors(Colors colors[]){
    colors[0].id = 0;
    strcpy(colors[0].colorCode, ANSI_COLOR_RED);
    
    colors[1].id = 1;
    strcpy(colors[1].colorCode, ANSI_COLOR_GREEN);

    colors[2].id = 2;
    strcpy(colors[2].colorCode, ANSI_COLOR_YELLOW);

    colors[3].id = 3;
    strcpy(colors[3].colorCode, ANSI_COLOR_BLUE);

    colors[4].id = 4;
    strcpy(colors[4].colorCode, ANSI_COLOR_MAGENTA);

    colors[5].id = 5;
    strcpy(colors[5].colorCode, ANSI_COLOR_CYAN);

    colors[6].id = 6;
    strcpy(colors[6].colorCode, ANSI_COLOR_RESET);
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

int menuColors(){
    printf("Choose one color\n");
    printf("0 - RED\n");
    printf("1 - GREEN\n");
    printf("2 - YELLOW\n");
    printf("3 - BLUE\n");
    printf("4 - MAGENTA\n");
    printf("5 - CYAN\n");
    printf("6 - WHITE\n");

    int colorNumber;
    scanf("%d", &colorNumber);
    system("clear");
    return colorNumber;
}

int main()
{
    Colors colors[7];
    initializeColors(colors);
    
    int colorNumber = menuColors();

    getchar();
    
    printf("%s", colors[colorNumber].colorCode);
    
    char sentence[100];
    int qtdLines = 0;

    printf("Write the sentence to show on screen\n");
    fgets(sentence, 100, stdin);
    printf("Choose how many lines it'll have\n");
    scanf("%d", &qtdLines);

    int len;
    for(len = 0; sentence[len] != '\n'; len++)
        printf("%d", len);

    while(1)
        startAnimation(sentence, len, qtdLines);

    return 0;
}
