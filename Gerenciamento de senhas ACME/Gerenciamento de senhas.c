// Aluno Guilherme Mendes das Neves - 18129111
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char login[81]; 
    char senha[31]; 
    char info[101]; 
    char atvd;     
} t_cadastro;

t_cadastro *cadastro = NULL;
int nclientes = 0;

void criptografar(char *senha, int senha_mestra){
    int i;
    int deslocamento = (senha_mestra <= 0) ? 5 : (senha_mestra % 10 + 1);
    for (i = 0; senha[i] != '\0'; i++) {
        senha[i] += deslocamento;
    }
}

void descriptografar(char *senha, int senha_mestra){
    int i;
    int deslocamento = (senha_mestra <= 0) ? 5 : (senha_mestra % 10 + 1);
    for (i = 0; senha[i] != '\0'; i++) {
        senha[i] -= deslocamento;
    }
}

int le_menu_opcao(void) {
    char digito[10];
    if (fgets(digito, sizeof(digito), stdin) == NULL) return -1;
    digito[strcspn(digito, "\r\n")] = '\0';
    return atoi(digito);
}

int le_senha_mestra(void) {
    char buffer[15];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return 0;
    buffer[strcspn(buffer, "\r\n")] = '\0';
    return atoi(buffer);
}

void salva_binario(t_cadastro *cadastro, int total_registros){
    char nome_arquivo[] = "senhas.bin"; 

    FILE *fptr = fopen(nome_arquivo, "wb");
    if(fptr == NULL){
        printf("ERRO ARQ\n");
        return; 
    }

    int ativos = 0;
    for (int i = 0; i < total_registros; i++) {
        if (cadastro[i].atvd == 'A') {
            ativos++;
        }
    }

    fwrite(&ativos, sizeof(int), 1, fptr);
 
    for (int i = 0; i < total_registros; i++) {
        if (cadastro[i].atvd == 'A') {
            fwrite(&cadastro[i], sizeof(t_cadastro), 1, fptr);
        }
    }

    fclose(fptr);
}

int carrega_binario(t_cadastro **cadastro, int *limite_maximo){
    char nome_arquivo[100] = "senhas-salvas.bin"; 
    int total_lido = 0;

    FILE *fptr = fopen(nome_arquivo, "rb");
    if (fptr == NULL) {
        printf("ERRO ARQ\n");
        return 0;
    }

    if (fread(&total_lido, sizeof(int), 1, fptr) != 1) {
        fclose(fptr);
        return 0;
    }

    if (total_lido > 0) {
        if (*cadastro != NULL) free(*cadastro);

        *limite_maximo = total_lido + 30;
        *cadastro = (t_cadastro *) malloc((*limite_maximo) * sizeof(t_cadastro));

        if (*cadastro != NULL) {
            fread(*cadastro, sizeof(t_cadastro), total_lido, fptr);

            for (int i = 0; i < total_lido; i++) {
                (*cadastro)[i].atvd = 'A';
            }
        }
    }

    fclose(fptr);
    return total_lido;
}

void exporta_texto(t_cadastro *cadastro, int total_registros, int senha_mestra) {
    char nome_arquivo[100] = "senhas-bkp.txt"; 
    int i;
    int ativos = 0;

    for (i = 0; i < total_registros; i++) {
        if (cadastro[i].atvd == 'A') {
            ativos++;
        }
    }

    FILE *fptr = fopen(nome_arquivo, "w");
    if (fptr == NULL) {
        printf("ERRO ARQ\n");
        return;
    }

    fprintf(fptr, "%d\n", ativos);

    for (i = 0; i < total_registros; i++) {
        if (cadastro[i].atvd == 'A') {
            char senha_aberta[31];
            strcpy(senha_aberta, cadastro[i].senha);
            descriptografar(senha_aberta, senha_mestra); 

            fprintf(fptr, "%s\n", cadastro[i].login);
            fprintf(fptr, "%s\n", senha_aberta);
            fprintf(fptr, "%s\n", cadastro[i].info);
        }
    }
    fclose(fptr);
}

int importa_texto(t_cadastro **cadastro, int *limite_maximo, int senha_mestra){
    char nome_arquivo[100] = "senhas-bkp.txt"; 
    char linha[100];
    int nclientes_local = 0;
    int i;

    FILE *fptr = fopen(nome_arquivo, "r");
    if (fptr == NULL){
        printf("ERRO ARQ\n");
        return 0;
    }

    if (fgets(linha, sizeof(linha), fptr) == NULL) {
        fclose(fptr);
        return 0;
    }
    linha[strcspn(linha, "\r\n")] = '\0';
    nclientes_local = atoi(linha);

    if (nclientes_local > 0) {
        if (*cadastro != NULL) {
            free(*cadastro);
        }
        *limite_maximo = nclientes_local + 30;
        *cadastro = (t_cadastro *) malloc((*limite_maximo) * sizeof(t_cadastro));
    } else {
        fclose(fptr);
        return 0;
    }

    for (i = 0; i < nclientes_local; i++){
        if (fgets((*cadastro)[i].login, sizeof((*cadastro)[i].login), fptr) == NULL) break;
        (*cadastro)[i].login[strcspn((*cadastro)[i].login, "\r\n")] = '\0';

        if (fgets((*cadastro)[i].senha, sizeof((*cadastro)[i].senha), fptr) == NULL) break;
        (*cadastro)[i].senha[strcspn((*cadastro)[i].senha, "\r\n")] = '\0';

        criptografar((*cadastro)[i].senha, senha_mestra);

        if (fgets((*cadastro)[i].info, sizeof((*cadastro)[i].info), fptr) == NULL) break;
        (*cadastro)[i].info[strcspn((*cadastro)[i].info, "\r\n")] = '\0';

        (*cadastro)[i].atvd = 'A';
    }

    fclose(fptr);
    return nclientes_local;
}
   

int dados_manual(t_cadastro *cadastro, int total_atual, int limite_maximo, int senha_mestra) {
    char linha[105]; 
    int i = total_atual;

    while (i < limite_maximo) {
        
        if (fgets(linha, sizeof(linha), stdin) == NULL) break;
        linha[strcspn(linha, "\r\n")] = '\0';

        if (linha[0] == '#' || strcmp(linha, "#") == 0) { 
            break;
        }
        strcpy(cadastro[i].login, linha);

        if (fgets(linha, sizeof(linha), stdin) == NULL) break;
        linha[strcspn(linha, "\r\n")] = '\0';
        
        criptografar(linha, senha_mestra); 
        strcpy(cadastro[i].senha, linha);

        if (fgets(linha, sizeof(linha), stdin) == NULL) break;
        linha[strcspn(linha, "\r\n")] = '\0';
        strcpy(cadastro[i].info, linha);

        cadastro[i].atvd = 'A'; 
        i++; 
    }

    return i;
}

void consulta_senha(t_cadastro *cadastro, int total_registros, int senha_mestra) {
    char procura[100];
    char procura_minusculo[100];
    int i, j;

    if (fgets(procura, sizeof(procura), stdin) == NULL) return;
    procura[strcspn(procura, "\r\n")] = '\0';

    for (i = 0; procura[i] != '\0'; i++) {
        procura_minusculo[i] = tolower((unsigned char)procura[i]);
    }
    procura_minusculo[i] = '\0';

    for (i = 0; i < total_registros; i++) {
        if (cadastro[i].atvd == 'A') {
            char login_minusculo[81];
            for (j = 0; cadastro[i].login[j] != '\0'; j++) {
                login_minusculo[j] = tolower((unsigned char)cadastro[i].login[j]);
            }
            login_minusculo[j] = '\0';

            if (strstr(login_minusculo, procura_minusculo) != NULL) {
                char senha_limpa[31];
                strcpy(senha_limpa, cadastro[i].senha);
                
                descriptografar(senha_limpa, senha_mestra);

                printf("%s\n", cadastro[i].login);
                printf("%s\n", senha_limpa);
                printf("%s\n", cadastro[i].info);
            }
        }
    }
}

void atualiza_senha(t_cadastro *cadastro, int total_registros, int senha_mestra) {
    char procura[100];
    char nova_senha[31];
    int i;
    int achou = 0;

    if (fgets(procura, sizeof(procura), stdin) == NULL) {
        return;
    }
    procura[strcspn(procura, "\r\n")] = '\0';

    if (fgets(nova_senha, sizeof(nova_senha), stdin) == NULL) return;
    nova_senha[strcspn(nova_senha, "\r\n")] = '\0';

    criptografar(nova_senha, senha_mestra);

    for (i = 0; i < total_registros; i++) {
        if (cadastro[i].atvd == 'A' && strcmp(procura, cadastro[i].login) == 0) {
            strcpy(cadastro[i].senha, nova_senha); 
            printf("EXEC NEWPWD\n");
            achou = 1;
            break;
        }
    }

    if (achou == 0) { 
        printf("EXEC FAILPWD\n");
    }
}

void consulta_texto(t_cadastro *cadastro, int total_registros, int senha_mestra) {
    char procura[100];
    char procura_minusculo[100];
    int i, j;

    if (fgets(procura, sizeof(procura), stdin) == NULL) return;
    procura[strcspn(procura, "\r\n")] = '\0';

    for (i = 0; procura[i] != '\0'; i++) {
        procura_minusculo[i] = tolower((unsigned char)procura[i]);
    }
    procura_minusculo[i] = '\0';

    for (i = 0; i < total_registros; i++) {
        if (cadastro[i].atvd == 'A') {
            char info_minusculo[101];
            for (j = 0; cadastro[i].info[j] != '\0'; j++) {
                info_minusculo[j] = tolower((unsigned char)cadastro[i].info[j]);
            }
            info_minusculo[j] = '\0';

            char login_minusculo[81];
            for (j = 0; cadastro[i].login[j] != '\0'; j++) {
                login_minusculo[j] = tolower((unsigned char)cadastro[i].login[j]);
            }
            login_minusculo[j] = '\0';

            if (strstr(info_minusculo, procura_minusculo) != NULL || 
                strstr(login_minusculo, procura_minusculo) != NULL) {
                
                char senha_limpa[31];
                strcpy(senha_limpa, cadastro[i].senha);
                descriptografar(senha_limpa, senha_mestra);

                printf("%s\n", cadastro[i].login);
                printf("%s\n", senha_limpa);
                printf("%s\n", cadastro[i].info);
            }
        }
    }
}

void remocao_logica(t_cadastro *cadastro, int total_registros) {
    char procura[100];
    int i;
    int achou = 0;

    if (fgets(procura, sizeof(procura), stdin) == NULL) return;
    procura[strcspn(procura, "\r\n")] = '\0';

    for (i = 0; i < total_registros; i++) {
        if (cadastro[i].atvd == 'A' && strcmp(procura, cadastro[i].login) == 0) {
            cadastro[i].atvd = 'I';
            printf("EXEC DEL\n");
            achou = 1;
            break;
        }
    }

    if (achou == 0) { 
        printf("EXEC ERRDEL\n");
    }
}

int main() {
    int opcao;
    int senha_mestra = 0;
    int autenticado = 0;
    int total_registros = 0;
    int limite_maximo = 30;

    printf("EXEC MAIN\n");

    while (1) {
        opcao = le_menu_opcao();

        if (opcao == -1) {
            printf("EXEC FIM\n");
            break;
        }
        
        if (!autenticado && opcao != 0) {
            printf("ZERO ERRO\n");
            printf("EXEC FIM\n");
            if (cadastro != NULL) free(cadastro);
            return 0;
        }

        switch (opcao) {
            case 0:
                printf("EXEC OPC0\n");
                senha_mestra = le_senha_mestra();
                autenticado = 1;
                break;
            
            case 1:
                printf("EXEC OPC1\n");
                total_registros = carrega_binario(&cadastro, &limite_maximo);
                break;
            
            case 2:
                printf("EXEC OPC2\n");
                if (cadastro != NULL && total_registros > 0) {
                    salva_binario(cadastro, total_registros);
                }
                break;
            
            case 3:
                printf("EXEC OPC3\n");
                if (cadastro != NULL && total_registros > 0) {
                    exporta_texto(cadastro, total_registros, senha_mestra);
                }
                break;
            
            case 4:
                printf("EXEC OPC4\n");  
                total_registros = importa_texto(&cadastro, &limite_maximo, senha_mestra);          
                break;

            case 5:
                printf("EXEC OPC5\n");
                if (cadastro == NULL) {
                    cadastro = (t_cadastro *) malloc(limite_maximo * sizeof(t_cadastro));
                }
                if (total_registros >= limite_maximo - 5) {
                    limite_maximo += 30;
                    t_cadastro *temp = (t_cadastro *) realloc(cadastro, limite_maximo * sizeof(t_cadastro));
                    if (temp != NULL) cadastro = temp;
                }
                total_registros = dados_manual(cadastro, total_registros, limite_maximo, senha_mestra);
                break;           
            
            case 6:
                printf("EXEC OPC6\n");   
                if (cadastro != NULL && total_registros > 0) {
                    consulta_senha(cadastro, total_registros, senha_mestra);
                }
                break;

            case 7:
                printf("EXEC OPC7\n");           
                if (cadastro != NULL && total_registros > 0) {
                    atualiza_senha(cadastro, total_registros, senha_mestra);
                } 
                break; 

            case 8:
                printf("EXEC OPC8\n");         
                if (cadastro != NULL && total_registros > 0) {
                    consulta_texto(cadastro, total_registros, senha_mestra);
                }
                break;

            case 9:
                printf("EXEC OPC9\n");          
                if (cadastro != NULL && total_registros > 0) {
                    remocao_logica(cadastro, total_registros);
                }
                break;

            default:
                printf("EXEC ERRO\n");
                break;
        }
    }

    if (cadastro != NULL) {
        free(cadastro);
    }

    return 0;
}