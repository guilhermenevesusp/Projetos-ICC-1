// Aluno Guilherme Mendes das Neves - 18129111
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    typedef struct{
    char nomp[10];
    int ano;
    double emissao;
    } t_emission;

    t_emission *lista = NULL;

    int def_nro_dados(char *nomarq, char *nomp, int anoi, int anof){

        int total = (anof - anoi) + 1;

        if (total <= 0){
            return -1;
        }

        return total;
        }

    int ler_arquivo(t_emission *lista, char *nomarq, char *nomp, int anoi, int anof){

        char sigla_arq[10];
        int ano_arq;
        double emissao_arq;
        int total = 0;

        FILE *fptr;
        fptr = fopen(nomarq, "r");

        if (fptr == NULL){
            return -1;
        }

        while (fscanf(fptr, "%s %d %lf", sigla_arq, &ano_arq, &emissao_arq) == 3) {

            if (strcmp(sigla_arq, "#") == 0) {
                break;
            }

            if (strcmp(nomp, sigla_arq) == 0 && ano_arq >= anoi && ano_arq <= anof) {
            strcpy(lista[total].nomp, sigla_arq);
            lista[total].ano = ano_arq;
            lista[total].emissao = emissao_arq;
            total++;
            }
        }

        fclose(fptr);
        return total;
    }

        void exibe_dados(t_emission *lista, int total){
            int i;
            for (i = 0; i < total; i++) {
            printf("%s %d %.2lf\n", lista[i].nomp, lista[i].ano, lista[i].emissao);
            }
    }


        double calcula_media_min_max(t_emission *lista, int total, double *media, double *min, double *max){
            int i;
            double soma = 0.0;

        *min = lista[0].emissao;
        *max = lista[0].emissao;

        for (i = 0; i < total; i++) {
        soma = soma + lista[i].emissao;

            if (lista[i].emissao < *min) {
                *min = lista[i].emissao;
            }
            if (lista[i].emissao > *max) {
                *max = lista[i].emissao;
            }
    }

        *media = soma / total;

        double valor_inicial = lista[0].emissao;
        double valor_final = lista[total - 1].emissao;
        double variacao = (valor_final / valor_inicial);

        return variacao;
    }

    int main(){

        char sigla_p1[10];
        int anoi_p1, anof_p1;
        t_emission *pais1 = NULL;
        int p1_qtd;
        double p1_mat;
        double p1_media, p1_min, p1_max;

        char sigla_p2[10];
        int anoi_p2, anof_p2;
        t_emission *pais2 = NULL;
        int p2_qtd;
        double p2_mat;
        double p2_media, p2_min, p2_max;

        scanf("%s %d %d", sigla_p1, &anoi_p1, &anof_p1);
        scanf("%s %d %d", sigla_p2, &anoi_p2, &anof_p2);

        p1_qtd = def_nro_dados("emissions.csv", sigla_p1, anoi_p1, anof_p1);
        p2_qtd = def_nro_dados("emissions.csv", sigla_p2, anoi_p2, anof_p2);

        if (p1_qtd == -1 || p2_qtd == -1) {
            printf("ERROARQ");
            return 1;
        }

        pais1 = (t_emission *) malloc(p1_qtd * sizeof(t_emission));
        pais2 = (t_emission *) malloc(p2_qtd * sizeof(t_emission));

        p1_qtd = ler_arquivo(pais1, "emissions.csv", sigla_p1, anoi_p1, anof_p1);
        p2_qtd = ler_arquivo(pais2, "emissions.csv", sigla_p2, anoi_p2, anof_p2);

        exibe_dados(pais1, p1_qtd);
        exibe_dados(pais2, p2_qtd);

        p1_mat = calcula_media_min_max (pais1, p1_qtd, &p1_media, &p1_min, &p1_max);
        p2_mat = calcula_media_min_max (pais2, p2_qtd, &p2_media, &p2_min, &p2_max);

        char crescimento;

        printf("%s %.2lf %.2lf %.2lf\n", sigla_p1, p1_media, p1_min, p1_max);
        printf("%s %.2lf %.2lf %.2lf\n", sigla_p2, p2_media, p2_min, p2_max);

        if (p1_mat > 1.10){
            crescimento = 'C';
            printf("%s %.2lf %c\n", sigla_p1, p1_mat, crescimento);
        }
        if (p1_mat <= 1.10 && p1_mat >= 0.9){
            crescimento = 'E';
            printf("%s %.2lf %c\n", sigla_p1, p1_mat, crescimento);
        }

        if (p1_mat < 0.90){
            crescimento = 'D';
            printf("%s %.2lf %c\n", sigla_p1, p1_mat, crescimento);
        }

        if (p2_mat > 1.10){
            crescimento = 'C';
            printf("%s %.2lf %c\n", sigla_p2, p2_mat, crescimento);
        }
        if (p2_mat <= 1.10 && p2_mat >= 0.9){
            crescimento = 'E';
            printf("%s %.2lf %c\n", sigla_p2, p2_mat, crescimento);
        }

        if (p2_mat < 0.90){
            crescimento = 'D';
            printf("%s %.2lf %c\n", sigla_p2, p2_mat, crescimento);
        }

        return 0;
    }


