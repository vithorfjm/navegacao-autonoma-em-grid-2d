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
void salvarGridNoTxt(char *matriz, const char *nomeDoArquivo);
void lerGridDoTxt(char * matrix, const char *nomeDoArquivo);

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
    char matriz[LIN][COL];
    lerGridDoTxt(&matriz[0][0], "grid.txt");
    // aq vai o algoritmo de resolução
}

void gerarGrid(int porcentagemObstaculos) {
    char grid[LIN][COL] = {{' '}};

    for (int l = 0 ; l < LIN ; l++) {
        for (int c = 0 ; c < COL ; c++) {
            grid[l][c] = ' '; // preenche todos os espaços com ' '
        }
    }

    grid[SORTEAR_LINHA()][0] = 'A';       // define inicio
    grid[SORTEAR_LINHA()][COL - 1] = 'B'; // define o fim

    int qntdObstaculos = (LIN * COL) * ((float)porcentagemObstaculos / 100);
    for (qntdObstaculos; qntdObstaculos > 0; qntdObstaculos--)
    {
        int linha;
        int coluna;
        do {
            linha = SORTEAR_LINHA();
            coluna = SORTEAR_COLUNA();
        } while (grid[linha][coluna] != ' ');
        grid[linha][coluna] = 'x';
    }
    salvarGridNoTxt(&grid[0][0], "grid.txt");
}

void salvarGridNoTxt(char *grid, const char *nomeDoArquivo) {
    FILE *file = fopen(nomeDoArquivo, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    for (int l = 0; l < LIN; l++) {
        for (int c = 0; c < COL; c++) {
            fputc(*(grid + l * COL + c), file);
        }
        fputc('\n', file);
    }

    fclose(file);
}

void lerGridDoTxt(char * matrix, const char *nomeDoArquivo) {
    FILE *file = fopen(nomeDoArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    static char linha[1024];
    int l = 0;

    while (fgets(linha, sizeof(linha), file) && l < LIN) {
        int c = 0;
        char * pos = linha;
        while (*pos != '\n' && c < COL) {
            *(matrix + l*COL + c) = *pos++;
            c++;
        }
        l++;
    }

    fclose(file);
}