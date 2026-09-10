#include <stdio.h>

int funcaocasos(int tabuleiro[]){ 

//caso transversal (\)
    if (tabuleiro[0] == 1 && tabuleiro[4] == 1 && tabuleiro[8] == 1){
    return 1;
    }
    else if (tabuleiro[0] == 2 && tabuleiro[4] == 2 && tabuleiro[8] == 2){
    return 2; 
    }

// caso transversal (/)
    if(tabuleiro[2] == 1 && tabuleiro[4] == 1 && tabuleiro[6] == 1){
    return 1;
    }
    else if (tabuleiro[2] == 2 && tabuleiro[4] == 2 && tabuleiro[6] == 2){
    return 2; 
    }

 //caso vertical 1
    if (tabuleiro[0] == 1 && tabuleiro[3] == 1 && tabuleiro[6] == 1){
    return 1;
    }
    else if (tabuleiro[0] == 2 && tabuleiro[3] == 2 && tabuleiro[6] == 2){
    return 2;     
    }

//caso vertical 2
    if (tabuleiro[1] == 1 && tabuleiro[4] == 1 && tabuleiro[7] == 1){
    return 1;
    }
    else if (tabuleiro[1] == 2 && tabuleiro[4] == 2 && tabuleiro[7] == 2){
    return 2;     
    }

//caso vertical 3
    if (tabuleiro[2] == 1 && tabuleiro[5] == 1 && tabuleiro[8] == 1){
    return 1;
    }
    else if (tabuleiro[2] == 2 && tabuleiro[5] == 2 && tabuleiro[8] == 2){
    return 2;    
    }

 //caso horizontal 1 
    if (tabuleiro[0] == 1 && tabuleiro[1] == 1 && tabuleiro[2] == 1){
    return 1;
    }
    else if (tabuleiro[0] == 2 && tabuleiro[1] == 2 && tabuleiro[2] == 2){
    return 2;     
    }

 //caso horizontal 2 
    if (tabuleiro[3] == 1 && tabuleiro[4] == 1 && tabuleiro[5] == 1){
    return 1;
    }
    else if (tabuleiro[3] == 2 && tabuleiro[4] == 2 && tabuleiro[5] == 2){
    return 2;     
    }

//caso horizontal 3
    if (tabuleiro[6] == 1 && tabuleiro[7] == 1 && tabuleiro[8] == 1){
    return 1;
    }
    else if (tabuleiro[6] == 2 && tabuleiro[7] == 2 && tabuleiro[8] == 2){
    return 2;     
    }

    return -1;
}

void funcaofimdejogo(int vencedor){

int jogador1 = 3;
int jogador2 = 3;

switch (vencedor){
    case 0:
    printf("Empate!\n");
    break;

    case 1:
    printf("Jogada Valida %d\nJogador 1 venceu!\nTabuleiro:\n", jogador1);
    break;

    case 2:
    printf("Jogada Valida %d\nJogador 2 venceu!\nTabuleiro:\n",  jogador2);
    break;
}
}

int main(){

int jogador1 = 0;
int jogador2 = 0;
int vencedor = -1; 
int tabuleiro[9] = {0};


while ((tabuleiro[0] == 0 || tabuleiro[1] == 0 || tabuleiro[2] == 0 || tabuleiro[3] == 0 || tabuleiro[4] == 0 || tabuleiro[5] == 0 || tabuleiro[6] == 0 || tabuleiro[7] == 0 || tabuleiro[8] == 0) && vencedor == -1){

    scanf("%d", &jogador1);

    if (jogador1 == -1){
    printf("Jogada Valida -1\nFIM DE JOGO\n");
    return 0;
}

    if (jogador1 < 10 && jogador1 > 0){
        if (tabuleiro[jogador1 -1] == 0){
            tabuleiro[(jogador1 - 1)] = 1;
        }
        else {
            while (tabuleiro[jogador1 - 1] != 0){
                printf("Jogada Invalida %d\nJogador 1 joga agora!\nTabuleiro:\n%d %d %d\n%d %d %d\n%d %d %d\n", jogador1, tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);
                scanf("%d", &jogador1);
            }
            tabuleiro[(jogador1 - 1)] = 1;
        }
    }
    else {
        while (jogador1 >=10 || jogador1 <= 0){
            printf("Jogada Invalida %d\nJogador 1 joga agora!\nTabuleiro:\n%d %d %d\n%d %d %d\n%d %d %d\n", jogador1, tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);
            scanf("%d", &jogador1);
        }
        tabuleiro[(jogador1 - 1)] = 1;
    }

    vencedor = funcaocasos(tabuleiro); // ← adicionado aqui
    if (vencedor != -1){
        funcaofimdejogo(vencedor);
        printf("%d %d %d\n%d %d %d\n%d %d %d\n", tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);
        break;
    }
    if (tabuleiro[0]!=0 && tabuleiro[1]!=0 && tabuleiro[2]!=0 && tabuleiro[3]!=0 && tabuleiro[4]!=0 && tabuleiro[5]!=0 && tabuleiro[6]!=0 && tabuleiro[7]!=0 && tabuleiro[8]!=0){
        vencedor = 0;
        funcaofimdejogo(vencedor);
        printf("%d %d %d\n%d %d %d\n%d %d %d\n", tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);
        break;
}
    printf("Jogada Valida %d\nJogador 2 joga agora!\nTabuleiro:\n%d %d %d\n%d %d %d\n%d %d %d\n", jogador1, tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);

    // jogador 2 joga agora:
    scanf("%d", &jogador2);
    
    if (jogador2 == -1){
    printf("Jogada Valida -1\nFIM DE JOGO\n");
    return 0;
}

    if (jogador2 < 10 && jogador2 > 0){
        if (tabuleiro[jogador2 -1] == 0){
            tabuleiro[(jogador2 - 1)] = 2;
        }
        else {
            while (tabuleiro [jogador2 - 1] != 0){
                printf("Jogada Invalida %d\nJogador 2 joga agora!\nTabuleiro:\n%d %d %d\n%d %d %d\n%d %d %d\n", jogador2, tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);
                scanf("%d", &jogador2);
            }
            tabuleiro[(jogador2 - 1)] = 2;
        }
    }
    else {
        while (jogador2 >=10 || jogador2 <= 0){
            printf("Jogada Invalida %d\nJogador 2 joga agora!\nTabuleiro:\n%d %d %d\n%d %d %d\n%d %d %d\n", jogador2, tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);
            scanf("%d", &jogador2);
        }
        tabuleiro[(jogador2 - 1)] = 2;
    }

    vencedor = funcaocasos(tabuleiro);
    if (vencedor != -1){
        funcaofimdejogo(vencedor);
        printf("%d %d %d\n%d %d %d\n%d %d %d\n", tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);
        break;
    }
    printf("Jogada Valida %d\nJogador 1 joga agora!\nTabuleiro:\n%d %d %d\n%d %d %d\n%d %d %d\n", jogador2, tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);

}

if (vencedor == -1){
    vencedor = 0;
    funcaofimdejogo(vencedor);
    printf("%d %d %d\n%d %d %d\n%d %d %d\n", tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);
}

return 0;
}



//------------------------------------------------------------------------RASCUNHO------------------------------------------------------------------------//


/* após while ser executado:
 if (tabuleiro[0] == 1 && tabuleiro[4] == 1 && tabuleiro[8] == 1){
        vencedor = 1;
    
    }
    else if (tabuleiro[0] == 2 && tabuleiro[4] == 2 && tabuleiro[8] == 2){
    vencedor = 2; 
    }


// caso transversal (/)
    if(tabuleiro[2] == 1 && tabuleiro[4] == 1 && tabuleiro[6] == 1){
    vencedor = 1;
    }
    else if (tabuleiro[2] == 2 && tabuleiro[4] == 2 && tabuleiro[6] == 2){
    vencedor = 2; 
    }


 //caso vertical 1
    if (tabuleiro[0] == 1 && tabuleiro[3] == 1 && tabuleiro[6] == 1){
    vencedor = 1;
    
    }

    else if (tabuleiro[0] == 2 && tabuleiro[3] == 2 && tabuleiro[6] == 2){
    vencedor = 2;     
    }


//caso vertical 2
    if (tabuleiro[1] == 1 && tabuleiro[4] == 1 && tabuleiro[7] == 1){
    vencedor = 1;
    
    }

    else if (tabuleiro[1] == 2 && tabuleiro[4] == 2 && tabuleiro[7] == 2){
    vencedor = 2;     
    }


//caso vertical 3
    if (tabuleiro[2] == 1 && tabuleiro[5] == 1 && tabuleiro[8] == 1){
    vencedor = 1;
    
    }

    else if (tabuleiro[2] == 2 && tabuleiro[5] == 2 && tabuleiro[8] == 2){
    vencedor = 2;    
    }


 //caso horizontal 1 
     if (tabuleiro[0] == 1 && tabuleiro[1] == 1 && tabuleiro[2] == 1){
     vencedor = 1;
    
    }

    else if (tabuleiro[0] == 2 && tabuleiro[1] == 2 && tabuleiro[2] == 2){
    vencedor = 2;     
    }


 //caso horizontal 2 
     if (tabuleiro[3] == 1 && tabuleiro[4] == 1 && tabuleiro[5] == 1){
     vencedor = 1;
    
    }

    else if (tabuleiro[3] == 2 && tabuleiro[4] == 2 && tabuleiro[5] == 2){
    vencedor = 2;     
    }


//caso horizontal 3
     if (tabuleiro[6] == 1 && tabuleiro[7] == 1 && tabuleiro[8] == 1){
     vencedor = 1;
    
    }

    else if (tabuleiro[6] == 2 && tabuleiro[7] == 2 && tabuleiro[8] == 2){
    vencedor = 2;     
    }



criando as funções (lembrar de colocar no topo depois)
void funçãojogador1(){
    scanf("%d", &jogador1);


if (jogador1 < 10 && jogador1 > 0){
    if (tabuleiro[jogador1 -1] == 0){
    tabuleiro[(jogador1 - 1)] = 1;
    printf("Jogada Valida\nJogador 2 joga agora!\nTabuleiro:\n%d %d %d\n%d %d %d\n%d %d %d\n", tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);
}   
    else {
        while (tabuleiro [jogador1 - 1] != 0){
        printf("Jogada Invalida\nJogador 1 joga novamente!\n");
        scanf("%d", &jogador1);
    }
    tabuleiro[jogador1 - 1] = 0;
    tabuleiro[(jogador1 - 1)] = 1;
    printf("Jogada Valida\nJogador 2 joga agora!\nTabuleiro:\n%d %d %d\n%d %d %d\n%d %d %d\n", tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);

}
}
}

// função jogador 2:

void funçãojogador2(){
    scanf("%d", &jogador1);


if (jogador1 < 10 && jogador1 > 0){
    if (tabuleiro[jogador1 -1] == 0){
    tabuleiro[(jogador1 - 1)] = 1;
    printf("Jogada Valida\nJogador 2 joga agora!\nTabuleiro:\n%d %d %d\n%d %d %d\n%d %d %d\n", tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);
}   
    else {
        while (tabuleiro [jogador1 - 1] != 0){
        printf("Jogada Invalida\nJogador 1 joga novamente!\n");
        scanf("%d", &jogador1);
    }
    tabuleiro[jogador1 - 1] = 0;
    tabuleiro[(jogador1 - 1)] = 1;
    printf("Jogada Valida\nJogador 2 joga agora!\nTabuleiro:\n%d %d %d\n%d %d %d\n%d %d %d\n", tabuleiro[0], tabuleiro[1], tabuleiro[2], tabuleiro[3], tabuleiro[4], tabuleiro[5], tabuleiro[6], tabuleiro[7], tabuleiro[8]);

}
}
}

// ---------------------------------- condição de fim de jogo (tem que colocar na função depois - analizar antes de cada jogada)--------------------------// 


 // caso transversal (\)
    if (tabuleiro[0] == 1 && tabuleiro[4] == 1 && tabuleiro[8] == 1){
        vencedor = 1;
    
    }
    else if (tabuleiro[0] == 2 && tabuleiro[4] == 2 && tabuleiro[8] == 2){
    vencedor = 2; 
    }


// caso transversal (/)
    if(tabuleiro[2] == 1 && tabuleiro[4] == 1 && tabuleiro[6] == 1){
    vencedor = 1;
    }
    else if (tabuleiro[2] == 2 && tabuleiro[4] == 2 && tabuleiro[6] == 2){
    vencedor = 2; 
    }


 //caso vertical 1
    if (tabuleiro[0] == 1 && tabuleiro[3] == 1 && tabuleiro[6] == 1){
    vencedor = 1;
    
    }

    else if (tabuleiro[0] == 2 && tabuleiro[3] == 2 && tabuleiro[6] == 2){
    vencedor = 2;     
    }


//caso vertical 2
    if (tabuleiro[1] == 1 && tabuleiro[4] == 1 && tabuleiro[7] == 1){
    vencedor = 1;
    
    }

    else if (tabuleiro[1] == 2 && tabuleiro[4] == 2 && tabuleiro[7] == 2){
    vencedor = 2;     
    }


//caso vertical 3
    if (tabuleiro[2] == 1 && tabuleiro[5] == 1 && tabuleiro[8] == 1){
    vencedor = 1;
    
    }

    else if (tabuleiro[2] == 2 && tabuleiro[5] == 2 && tabuleiro[8] == 2){
    vencedor = 2;    
    }


 //caso horizontal 1 
     if (tabuleiro[0] == 1 && tabuleiro[1] == 1 && tabuleiro[2] == 1){
     vencedor = 1;
    
    }

    else if (tabuleiro[0] == 2 && tabuleiro[1] == 2 && tabuleiro[2] == 2){
    vencedor = 2;     
    }


 //caso horizontal 2 
     if (tabuleiro[3] == 1 && tabuleiro[4] == 1 && tabuleiro[5] == 1){
     vencedor = 1;
    
    }

    else if (tabuleiro[3] == 2 && tabuleiro[4] == 2 && tabuleiro[5] == 2){
    vencedor = 2;     
    }


//caso horizontal 3
     if (tabuleiro[6] == 1 && tabuleiro[7] == 1 && tabuleiro[8] == 1){
     vencedor = 1;
    
    }

    else if (tabuleiro[6] == 2 && tabuleiro[7] == 2 && tabuleiro[8] == 2){
    vencedor = 2;     
    }


if (vencedor == 1){
printf("Jogada Valida\nJogador 1 venceu!\n");
}

else if (vencedor == 2){
printf("Jogada Valida\nJogador 2 venceu!\n");
}

---------------------------------------------------------

void funcaofimdejogo( int vencedor){
if (vencedor == 1){
printf("Jogada Valida\nJogador 1 venceu!\n");
}

else if (vencedor == 2){
printf("Jogada Valida\nJogador 2 venceu!\n");
}
else if (vencedor == 0){
    printf("Empate!");
} 
*/ 