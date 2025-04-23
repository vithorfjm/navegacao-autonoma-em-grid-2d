#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LIN 100
#define COL 100
#define SORTEAR_LINHA() (int)(rand()%LIN-1)
#define SORTEAR_COLUNA() (int)(rand()%COL-1)

void gerarGrid(int porcentagemObstaculos);
void salvarGridNoTxt(char grid[LIN][COL]);
void imprimirGrid(char grid[LIN][COL]);

int main() {
    srand(time(0));
    int porcentagem;
    puts("\n - Boas vindas ao sistema de navegacao para drones autonomos.");
    printf(" - Para gerar o mapa, informe a porcentagem de obstaculos no caminho:\n");
    do {
        printf("\t > ");
        scanf("%d", &porcentagem);
    } while (porcentagem < 0 || porcentagem > 100);
    puts("Gerando o mapa...");
    // Sleep(3000);
    gerarGrid(porcentagem);
}

void gerarGrid(int porcentagemObstaculos) {
    char grid[LIN][COL] = {{' '}};
    for (int l = 0 ; l < LIN ; l++) {
      for (int c = 0 ; c < COL ; c++) {
        grid[l][c] = ' ';
      }
    }
    int qntdObstaculos = (LIN*COL) * ((float)porcentagemObstaculos / 100);
    for (qntdObstaculos ; qntdObstaculos>0 ; qntdObstaculos--) {
        int linha;
        int coluna;
        do {
            linha = SORTEAR_LINHA();
            coluna = SORTEAR_COLUNA();
        } while (grid[linha][coluna] == 'x');
        grid[linha][coluna] = 'x';
    }
    imprimirGrid(grid);
}

void salvarGridNoTxt(char grid[LIN][COL]);

void imprimirGrid(char grid[LIN][COL])
{
  for (int i = 0; i < LIN; i++)
  {
    for (int j = 0; j < COL; j++)
    {
      printf("%c", grid[i][j]);
    }
    printf("\n");
  }
}