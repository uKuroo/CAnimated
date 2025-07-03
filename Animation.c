#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int indexY = 0;
int upOrDown = 0;

void waitAndClear(){
    usleep(180000);
    system("clear");
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

int main()
{
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
