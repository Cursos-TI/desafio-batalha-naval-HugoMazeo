#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void Atualizar_Tela(int campo[10][10])
{

    int letra = 0;
    int contagem = 0;
    int cont_linha = 10;
        //limpar tela
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux/macOS
    #endif
    //finalizar limpar tela

    //atualizar campo
    printf("0 1 2 3 4 5 6 7 8 9 \n");
    for (int i = 0; i < 10; i++) 
    {
        for (int j =0; j < 10; j++)
        {
            printf("%d ", campo[i][j]);
            contagem ++;

            if (contagem >= cont_linha)
            {
                printf("%d",letra);
                cont_linha += 10; 
                letra ++;
                printf ("\n");
            }
        }
    }
    //finalizar atualizar campo
}
void PosicionarNavio(char resposta,int campo[10][10],int p1turn)
{
    int piece;
    if(p1turn == 1)
    {
        piece = 3;
    }
    else
    {
        piece = 5;
    }
    while(1)
    {
        int line;
        int column; 
        printf("Declare a posição dessa maneira: (linha, coluna) 0 0 ou 0 1 ou 4 8\n");
        scanf("%d %d", &line,&column);
        if(resposta == 'A')
        {
            if(column <= 0 || column >=9)
            {
                printf("Seu navio sairia para fora da tela, coordenada inválida\n");

            }
            else
            {
                campo[line][column] = piece;
                campo[line][column+1] = piece;
                campo[line][column-1] = piece;
                Atualizar_Tela(campo);
                break;
            }
        }
        else if (resposta == 'B')
        {
            if(line <= 0 || line >= 9)
            {
                printf("Seu navio sairia para fora da tela, coordenada inválida\n");
            }
            else
            {
                campo[line][column] = piece;
                campo[line+1][column] = piece;
                campo[line-1][column] = piece;
                Atualizar_Tela(campo);
                break;
            }
        }
        else if (resposta == 'C')
        {
            if((line <= 0 || line >= 9) || (column <=0 || column >=9))
            {
                printf("Seu navio sairia para fora da tela, coordenada inválida\n");
            }
            else
            {
                printf("Vamos posicionar de maneira crescente ou decrescente?\n");
                printf("A - Crescente\n");
                printf("B - Decrescente\n");
                char answer;
                scanf(" %c",&answer);
                answer = toupper(answer);
                if(answer == 'A')
                {
                    campo[line][column] = piece;
                    campo[line+1][column-1] = piece;
                    campo[line-1][column+1] = piece;
                    Atualizar_Tela(campo);
                    break;
                }
                else if (answer == 'B')
                {
                    campo[line][column] = piece;
                    campo[line-1][column-1] = piece;
                    campo[line+1][column+1] = piece;
                    Atualizar_Tela(campo);
                    break;
                }
                else
                {
                    printf("Alternativa inválida\n");
                }
            }
        }    
        else
        {
            printf("Alternativa inválida\n");
        }
    }
}

void Aplicar_Habilidade(int campo[10][10], int habilidade[5][5], int line_, int column_) 
{
    // Varre a matriz da habilidade (5x5)
    for (int i = 0; i < 5; i++) 
    {
        for (int j = 0; j < 5; j++) 
        {
            if (habilidade[i][j] == 1) 
            { // Se a posição na habilidade é válida
                int x = line_ + (i - 2); // Centraliza a máscara na linha
                int y = column_ + (j - 2); // Centraliza a máscara na coluna

                // Verifica se a posição está dentro dos limites da matriz
                if (x >= 0 && x < 10 && y >= 0 && y < 10) 
                {
                    // Apenas modifica se o valor for 0, 3 ou 5
                    if (campo[x][y] == 0 || campo[x][y] == 3 || campo[x][y] == 5) 
                    {
                        campo[x][y] = 1;
                    }
                }
            }
        }
    }
}
int main() 
{

int cone[5][5] = 
{
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
    {1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0}
};

int octaedro[5][5] = 
{
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
    {1, 1, 1, 1, 1},
    {0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0}
};

int cruz[5][5] = 
{
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0}
};


char player1[20];
char player2[20];
int mapeamento = 0;
int qual_linha = 1;
int p1turn = 1;


int campo [10][10] = 
{
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
};
printf("Esse é um jogo de batalha naval!\n");
printf("Vamos começar com o Jogador número 1, qual seu nome?\n");
scanf("%s",player1);
printf("Muito bem %s, agora é a vez do Jogador número 2, qual seu nome?\n",player1);
scanf("%s",player2);
printf("Muito bem Player 1 %s jogará contra o Player 2 %s\n",player1,player2);

Atualizar_Tela(campo);
printf("Esse é o campo:\n");
printf("Agora, é a vez de %s jogar, deseja colocar seu navio horizontalmente ou verticalmente?\n",player1);
p1turn = 1;
printf("A - Horizontalmente\n");
printf("B - Verticalmente\n");
printf("C - Diagonalmente\n");
char resposta;
scanf(" %c",&resposta);
resposta = toupper(resposta);
Atualizar_Tela(campo);
printf("Seu navio tem 3 peças, declare a peça do meio para posicionarmos o navio\n");
PosicionarNavio(resposta,campo,p1turn);
printf("Hora de colocar seu segundo navio!\n");
printf("A - Horizontalmente\n");
printf("B - Verticalmente\n");
printf("C - Diagonalmente\n");
scanf(" %c",&resposta);
resposta = toupper(resposta);
Atualizar_Tela(campo);
printf("Seu navio tem 3 peças, declare a peça do meio para posicionarmos o navio\n");
PosicionarNavio(resposta,campo,p1turn);
printf("Agora, é a vez de %s jogar, deseja colocar seu navio horizontalmente ou verticalmente?\n",player2);
p1turn = 0;
printf("A - Horizontalmente\n");
printf("B - Verticalmente\n");
printf("C - Diagonalmente\n");
resposta;
scanf(" %c",&resposta);
resposta = toupper(resposta);
Atualizar_Tela(campo);
printf("Seu navio tem 3 peças, declare a peça do meio para posicionarmos o navio\n");
PosicionarNavio(resposta,campo,p1turn);
printf("Hora de colocar seu segundo navio!\n");
printf("A - Horizontalmente\n");
printf("B - Verticalmente\n");
printf("C - Diagonalmente\n");
scanf(" %c",&resposta);
resposta = toupper(resposta);
Atualizar_Tela(campo);
printf("Seu navio tem 3 peças, declare a peça do meio para posicionarmos o navio\n");
PosicionarNavio(resposta,campo,p1turn);
printf("Agora vamos aplicar uma habilidade para explodir os navios\n");
printf("Escolha qual habilidade usar\n");
printf("A - Cone\nB - Octaedro\nC - Cruz\n");
scanf(" %c",&resposta);
resposta = toupper(resposta);
Atualizar_Tela(campo);
printf("Onde vamos aplicar a habilidade? Digite linha e coluna, exeplo:\n0 3 ou 5 8 ou 4 3\n");
int linha;
int coluna;
scanf("%d %d", &linha, &coluna);
switch(resposta)
{
    case 'A':
        Aplicar_Habilidade(campo,cone,linha,coluna);
        break;
    case 'B':
        Aplicar_Habilidade(campo,octaedro,linha,coluna);
        break;
    case 'C':
        Aplicar_Habilidade(campo,cruz,linha,coluna);
        break;
    default:
        printf("Habilidade invalida!\n");
        return 1;
}
    Atualizar_Tela(campo);

    return 0;
}
