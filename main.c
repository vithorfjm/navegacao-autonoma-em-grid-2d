#include <stdio.h>
#include <windows.h>

#define LIN 100
#define COL 100

void gerarGrid(int porcentagemObstaculos);
void salvarGridNoTxt(char grid[][]);

int main() {
    int porcentagem = 25;
    puts("Boas vindas ao sistema de navegacao para drones autonomos.");
    printf("Para gerar o mapa, informe a porcentagem de obstaculos no caminho:\n\t> ");
    scanf("%d", &porcentagem);  
    puts("Gerando o mapa...");
    sleep(2):
}

void gerarGrid(int porcentagemObstaculos) {

}

void salvarGridNoTxt(char grid[][]);