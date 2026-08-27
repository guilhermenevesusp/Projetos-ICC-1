#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    typedef struct{
        int numero;
        char nome[31];
        double saldo;
    } Conta;

    Conta *cadastro = NULL;  
    int nclientes = 0;

    int le_menu_opcao(void){
        char digito[10];
        fgets(digito, sizeof(digito), stdin);
        digito[strcspn(digito, "\r\n")] = '\0';

        int teclado;
        teclado = atoi(digito);

        return teclado; 
    }

    int le_arquivo(char *nome){
        char linha[100];
        int i;

        FILE *fptr;
        fptr = fopen(nome, "r");

        if(fptr == NULL){
            return -1;
        }

        fgets(linha, sizeof(linha), fptr);
        linha[strcspn(linha, "\r\n")] = '\0';

        nclientes = atoi(linha);
    
        cadastro = (Conta *) malloc(nclientes * sizeof(Conta));

        for (i = 0; i < nclientes; i++) {
        
          fgets(linha, sizeof(linha), fptr);
            linha[strcspn(linha, "\r\n")] = '\0';
            cadastro[i].numero = atoi(linha);;

          fgets(linha, sizeof(linha), fptr);
            linha[strcspn(linha, "\r\n")] = '\0'; 
            strcpy(cadastro[i].nome, linha);

          fgets(linha, sizeof(linha), fptr);
            linha[strcspn(linha, "\r\n")] = '\0';
            cadastro[i].saldo = atof(linha);
        }
    
     fclose(fptr);
     return nclientes;
    }

    int grava_arquivo (char *nome, int nclientes){
        FILE *fptr;
        fptr = fopen(nome, "w");

        if(fptr == NULL){
            return -1;
        }

        fprintf(fptr, "%d\n", nclientes);

        for (int i = 0; i < nclientes; i++) {
        fprintf(fptr, "%d\n", cadastro[i].numero);
        fprintf(fptr, "%s\n", cadastro[i].nome);
        fprintf(fptr, "%lf\n", cadastro[i].saldo);
        }

        fprintf(fptr, "#\n");

        fclose(fptr);
     return nclientes;
    }
    
    int procura_conta (int conta){
        int i;

            for(i = 0; i < nclientes; i++){
                
                if(cadastro[i].numero == conta){
                return i;
                }
            }
     return -1;
    }

    double deposito(int ncliente, double valor){
            cadastro[ncliente].saldo += valor;
            return cadastro[ncliente].saldo;
    }
    
    double saque(int ncliente, double valor){
        cadastro[ncliente].saldo -= valor;
        return cadastro[ncliente].saldo;
    }

    void transfere (double *saldo1, double *saldo2){
        double aux;

        aux = *saldo1;
        *saldo1 = *saldo2;
        *saldo2 = aux;
    }

    void exibe_saldo_conta(int conta){
      int temp = procura_conta(conta);
        if(temp == -1) {
        printf("ERRO CONTA\n");
        } 
        else {
            printf("%d\n", cadastro[temp].numero);
            printf("%s\n", cadastro[temp].nome);
            printf("%.2lf\n", cadastro[temp].saldo);
        }
    }

    void exibe_contas(void){
        int i;

            printf("CONTAS %d\n", nclientes);

        for(i = 0; i < nclientes; i++){
            printf("%d\n", cadastro[i].numero);
            printf("%s\n", cadastro[i].nome);
            printf("%.2lf\n", cadastro[i].saldo);
        }
    }

int main(){

    int opcao;
    char buffer[100];
    int temp;
    int temp2;
    int conta_num;
    double saldo;

    do{
        opcao = le_menu_opcao();

            switch(opcao){
                case 1: {
                    int resultado = le_arquivo("master.txt");
                    if (resultado == -1){
                        printf("ERRO ARQUIVO");
                    }
                    else{
                        printf("LIDOS %d\n", nclientes);
                    }
                 break;
                }

                case 2: {
                    double valor_deposito;
                    

                    fgets(buffer, sizeof(buffer), stdin);
                    buffer[strcspn(buffer, "\r\n")] = '\0';
                    conta_num = atoi(buffer);

                    fgets(buffer, sizeof(buffer), stdin);
                    buffer[strcspn(buffer, "\r\n")] = '\0';
                    valor_deposito = atof(buffer);

                    temp = procura_conta(conta_num);
                        if(temp == -1){
                            printf("ERRO CONTA\n");
                        }
                        else{
                            saldo = deposito(temp, valor_deposito);
                            printf("SALDO %.2lf\n", saldo);
                        }
                 break;
                }

                case 3: {
                    double valor_saque;

                    fgets(buffer, sizeof(buffer), stdin);
                    buffer[strcspn(buffer, "\r\n")] = '\0';
                    conta_num = atoi(buffer);

                    fgets(buffer, sizeof(buffer), stdin);
                    buffer[strcspn(buffer, "\r\n")] = '\0';
                    valor_saque = atof(buffer);

                    temp = procura_conta(conta_num);
                        if(temp == -1){
                            printf("ERRO CONTA\n");
                        }
                        else{
                            saldo = saque(temp, valor_saque);
                            printf("SALDO %.2lf\n", saldo);
                        }
                 break;
                }

                case 4: {
                    int conta1;
                    int conta2;
                    fgets(buffer, sizeof(buffer), stdin);
                    buffer[strcspn(buffer, "\r\n")] = '\0';
                    conta1 = atoi(buffer);

                    fgets(buffer, sizeof(buffer), stdin);
                    buffer[strcspn(buffer, "\r\n")] = '\0';
                    conta2 = atoi(buffer);

                    temp = procura_conta(conta1);
                    temp2 = procura_conta(conta2);

                    if(temp == -1){
                        printf("ERRO CONTA1\n");
                    }
                    if( temp2 == -1){
                        printf("ERRO CONTA2\n");
                    }
                    else{
                        transfere(&cadastro[temp].saldo, &cadastro[temp2].saldo);
                        printf("TRANSF OK\n");
                    }
                 break;
                }

                case 5: {

                    fgets(buffer, sizeof(buffer), stdin);
                    buffer[strcspn(buffer, "\r\n")] = '\0';
                    conta_num = atoi(buffer);

                    exibe_saldo_conta(conta_num);
                        
                 break;
                }

                case 6: 
                    exibe_contas();
                break;

                case 7: 
                
                    grava_arquivo("final.txt", nclientes);

                    if(grava_arquivo("final.txt", nclientes) == -1){
                    printf("ERRO ARQUIVO\n");
                    }
                    else{
                    printf("GRAVADOS %d\n", nclientes);

                 break;
                }

                case 0:
                    if (cadastro != NULL) {
                    free(cadastro);
                }
                break;
            }   
    }

    while(opcao != 0);

 return 0;
}