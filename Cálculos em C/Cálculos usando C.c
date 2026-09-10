// Guilherme Mendes das Neves - 18129111

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    FILE *arquivo;
    char linha[100];
    float numeros[1000];
    int qtd_dados = 0;

    int dado_inicial;
    int tamanho_janela;
    int num_janelas;
    int deslocamento;

    int i, j, k;
    int inicio_janela;
    float menor_janela, maior_janela, soma_janela, media_janela;


    arquivo = fopen("serie.txt", "r");
    if (arquivo == NULL) {
        printf("ERROARQ\n");
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (linha[0] == '#') {
            break;
        }

        if (qtd_dados < 1000) {
            numeros[qtd_dados] = atof(linha);
            qtd_dados++;
        } else {
            printf("ERRODADO\n");
            fclose(arquivo);
            return 0;
        }
    }
    fclose(arquivo);

    if (scanf("%d %d %d %d", &dado_inicial, &tamanho_janela, &num_janelas, &deslocamento) != 4) {
        return 0;
    }

    for (j = 0; j < num_janelas; j++) {
        inicio_janela = dado_inicial + (j * deslocamento);
        menor_janela = numeros[inicio_janela];
        maior_janela = numeros[inicio_janela];
        soma_janela = 0.0;
        for (k = 0; k < tamanho_janela; k++) {
            float valor_atual = numeros[inicio_janela + k];

            if (valor_atual < menor_janela) {
                menor_janela = valor_atual;
            }
            if (valor_atual > maior_janela) {
                maior_janela = valor_atual;
            }
            soma_janela += valor_atual;
        }

        media_janela = soma_janela / tamanho_janela;
        printf("%.2f\n", menor_janela);
        printf("%.2f\n", maior_janela);
        printf("%.2f\n", media_janela);
    }

    return 0;
}
