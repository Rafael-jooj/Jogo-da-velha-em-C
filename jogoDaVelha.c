#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void mostraTabuleiro(char** Tab){
    system("cls");
    printf("\t  %c  |  %c  |  %c  \n", Tab[0][0], Tab[0][1], Tab[0][2]);
    printf("\t-----------------\n");
    printf("\t  %c  |  %c  |  %c  \n", Tab[1][0], Tab[1][1], Tab[1][2]);
    printf("\t-----------------\n");
    printf("\t  %c  |  %c  |  %c  \n", Tab[2][0], Tab[2][1], Tab[2][2]);
}

void informaPosicao(int* x, int* y){
    printf("informe a linha\n");
    scanf("%i", x);
    printf("informe a coluna\n");
    scanf("%i", y);
}

bool verificaPosicao(int x, int y, char** Tab){
    if(x>2 || x<0) return 0;
    if(y>2 || y<0) return 0;
    if(Tab[x][y] == '0' || Tab[x][y] == 'X') return 0;
    else return 1;
}

bool inserirElemento(int x, int y, char** Tab, char player[2], int n){
    if(!verificaPosicao(x, y, Tab)) return 0;
    else Tab[x][y]=player[n];
    return 1;
}

void Deu_Velha(char** Tab){
    int i, j, cont=0;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(Tab[i][j] == 'X' || Tab[i][j] == '0'){
                cont++;
            }
        }
    }
    if(cont == 9){
    printf("\n---Deu Velha---\n\n");
    }
}

int analisaLinha(char** Tab, int win){
    int i;
    for (i=0; i<3; i++){
        if(Tab[i][0] == 'X' && Tab[i][1] == 'X' && Tab[i][2]=='X') return win=10;
    }
    for (i=0; i<3; i++){
        if(Tab[i][0] == '0' && Tab[i][1] == '0' && Tab[i][2]=='0') return win=11;
    }
    return win;
}

int analisaColuna(char** Tab, int win){
    int i;
    for (i=0; i<3; i++){
        if(Tab[0][i] == 'X' && Tab[1][i]=='X' && Tab[2][i]=='X') return win=12;
    }
    for (i=0; i<3; i++){
        if(Tab[0][i] == '0' && Tab[1][i]=='0' && Tab[2][i]=='0') return win=13;
    }
    return win;
}

int analisaDiagonal(char** Tab, int win){
    if (Tab[0][0]=='X' && Tab[1][1]=='X' && Tab[2][2]=='X')return win=14;
    else if (Tab[0][2]=='X' && Tab[1][1]=='X' && Tab[2][0]=='X')return win=14;

    else if (Tab[0][0]=='0' && Tab[1][1]=='0' && Tab[2][2]=='0')return win=15;
    else if (Tab[0][2]=='0' && Tab[1][1]=='0' && Tab[2][0]=='0')return win=15;
    
    return win;
}

int main(){
    int i,j, x, y, n;
    int numero_jogadas;
    char player[2]={'X', '0'}, op;

    char** tabuleiro = (char**)malloc(3*sizeof(char*));
    for(i=0; i<3; i++) tabuleiro[i] = (char*)malloc(3*sizeof(char));

        while(op != 'n' && op != 'N'){

        for (i=0; i<3; i++) for(j=0; j<3; j++) tabuleiro[i][j]= ' ';

        n=2;
        numero_jogadas = 0;

        do{

        mostraTabuleiro(tabuleiro);
        if(n%2 == 0) printf("jogador X\n");
        else printf("jogador 0\n");
        informaPosicao(&x, &y);
        verificaPosicao(x-1,y-1,tabuleiro);
        if(!verificaPosicao(x-1,y-1,tabuleiro)){
            n--;
            numero_jogadas--;
        }
        inserirElemento(x-1, y-1, tabuleiro, player, n%2);

        numero_jogadas = analisaLinha(tabuleiro, numero_jogadas);
        numero_jogadas = analisaColuna(tabuleiro, numero_jogadas);
        numero_jogadas = analisaDiagonal(tabuleiro, numero_jogadas);

        n++;
        numero_jogadas++;

        }while(numero_jogadas < 9);

        mostraTabuleiro(tabuleiro);

        Deu_Velha(tabuleiro);
        if (numero_jogadas==10+1) printf("---jogador X venceu---");
        if (numero_jogadas==11+1) printf("---jogador 0 venceu---");
        if (numero_jogadas==12+1) printf("---jogador X venceu---");
        if (numero_jogadas==13+1) printf("---jogador 0 venceu---");
        if (numero_jogadas==14+1) printf("---jogador X venceu---");
        if (numero_jogadas==15+1) printf("---jogador 0 venceu---");

        printf("\njogar novamente? (S/N)? ");
        fflush(stdin);
        scanf("%c", &op);
        }

    return 0;
}