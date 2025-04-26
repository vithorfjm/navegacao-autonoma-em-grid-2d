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
void salvarGridNoTxt(char *grid, const char *nomeDoArquivo);
void lerGridDoTxt(char * grid, const char *nomeDoArquivo);
void bfs(int sx, int sy, char grid[LIN][COL]);
int dentroDoMapa(int x, int y);
int visitado[LIN][COL];
int pai[LIN][COL][2];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

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
    Sleep(2500);
    puts("Navegando...");
    Sleep(2000);
    gerarGrid(porcentagem);
    char grid[LIN][COL];
    lerGridDoTxt(&grid[0][0], "grid.txt");
    int startX = -1, startY = -1;
    for (int i = 0; i < LIN; i++) {
        for (int j = 0; j < COL; j++) {
            if (grid[i][j] == 'A') {
                startX = i;
                startY = j;
            }
        }
    }
    if (startX == -1 || startY == -1)
    {
        printf("Erro: ponto de inicio 'A' nao encontrado.\n");
        return 1;
    }
    bfs(startX, startY, grid);
    salvarGridNoTxt(&grid[0][0], "path.txt");
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

void lerGridDoTxt(char * grid, const char *nomeDoArquivo) {
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
            *(grid + l*COL + c) = *pos++;
            c++;
        }
        l++;
    }

    fclose(file);
}

void bfs(int sx, int sy, char grid[LIN][COL]) {
    int fila[LIN * COL][2];
    int frente = 0, tras = 0;

    fila[tras][0] = sx;
    fila[tras][1] = sy;
    tras++;

    visitado[sx][sy] = 1;
    pai[sx][sy][0] = -1;
    pai[sx][sy][1] = -1;

    while (frente < tras)
    {
        int x = fila[frente][0];
        int y = fila[frente][1];
        frente++;
        if (grid[x][y] == 'B')
        {
            printf("Cheguei no fim em (%d, %d)!\n", x, y);
            while (pai[x][y][0] != -1)
            {
                int px = pai[x][y][0];
                int py = pai[x][y][1];
                if (grid[px][py] != 'A')
                {
                    grid[px][py] = '*';
                }
                x = px;
                y = py;
            }
            salvarGridNoTxt(&grid[0][0], "path.txt");
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (dentroDoMapa(nx, ny) && !visitado[nx][ny] && grid[nx][ny] != 'x')
            {
                visitado[nx][ny] = 1;
                fila[tras][0] = nx;
                fila[tras][1] = ny;
                tras++;
                pai[nx][ny][0] = x;
                pai[nx][ny][1] = y;
            }
        }
    }
    

    printf("Nao foi possivel encontrar um caminho ate o 'B'.\n");
}

int dentroDoMapa(int x, int y) {
    return x >= 0 && x < LIN && y >= 0 && y < COL;
}
