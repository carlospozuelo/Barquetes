#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 12
#define VALIDO(A) (A)>TAM-1?0:(A)<0?0:1

int toc_o_hun(char mat[TAM][TAM], int i, int j, int c){ //Función que devuelve 1 si el barco está tocado y 0 si está hundido
    if(c>1){
        if(i+1<12&&mat[i+1][j]&&mat[i+1][j]<5){ //Si hay barco en la posición i+1, j...
            if(mat[i+1][j]>0)
                return(1);  //Hay barco SIN TOCAR en la posición i+1 , j; por lo que el barco no está hundido
            else{
                if(toc_o_hun(mat,i+1,j,c-1))
                    return(1);
            } //El barco en la posición i+1, j está TOCADO. Hay que repetir el proceso en i+1, j.
        } else if(j+1<12&&mat[i][j+1]&&mat[i][j+1]<5){ //Si hay barco en la posición i, j+1...
            if(mat[i][j+1]>0)
                return(1);
            else{
                if(toc_o_hun(mat,i,j+1,c-1))
                    return(1);
            }
        } else if(i-1>0&&mat[i-1][j]&&mat[i-1][j]<5){
            if(mat[i-1][j]>0)
                return(1);
            else{
                if(toc_o_hun(mat,i-1,j,c-1))
                    return(1);
            }
        } else if(j-1>0&&mat[i][j-1]&&mat[i][j-1]<5){
            if(mat[i][j-1]>0)
                return(1);
            else{
                if(toc_o_hun(mat,i,j-1,c-1))
                    return(1);
            }
        } else
            return(0);
    }
    else
        return(0); //Condición inicial de la función recursiva
}

void mostrar_tab_jugador(char mat[TAM][TAM]){
    int i, j;

    printf("\t");

    for(i=0;i<TAM;i++)
        printf("%d\t", i);

    for(j=0;j<TAM;j++){
        for(i=0;i<TAM+1;i++){
            if(!i)
                printf("%d|\t", j);
            else if(mat[i][j]==5)
                printf("x\t"); //Si han disparado al agua, x
            else if(mat[i][j]>0)
                printf("%d\t", mat[i][j]); //Si hay un barco, n
            else if(mat[i][j]<0){
                    if(toc_o_hun(mat,i,j,5))
                        printf("x\t");
                    else
                        printf("X\t");
            }
        }
        printf("\n");
    }


}

int barc_alred(char mat[TAM][TAM], int x, int y){ //Función que devuelve 1 si hay barcos alrededor de una casilla xy, 0 sino.
    if(mat[x][y])
        return(1);
    if(mat[x+1][y])
        return(1);
    if(mat[x+1][y+1])
        return(1);
    if(mat[x][y+1])
        return(1);
    if(mat[x-1][y+1])
        return(1);
    if(mat[x-1][y])
        return(1);
    if(mat[x-1][y-1])
        return(1);
    if(mat[x][y-1])
        return(1);
    if(mat[x+1][y-1])
        return(1);
    return(0);
}

void inic_tab_jugador(char tab[TAM][TAM]){
    unsigned int x, y, c;

    char direc;

    for(c=0;c<10;c++){
        do{
            mostrar_tab_jugador(tab)
            printf("\nIntroduce la posición inicial x-y del barco de %d casillas", c>5?1:c>2?2:c?3:4);
            scanf("%u*%u", &x,&y);
        }while(!barc_alred(mat,x,y)&&VALIDO(x)&&VALIDO(y));
        do{
            mat[x][y]=c>5?1:c>2?2:c?3:4
            mostrar_tab_jugador(tab);
            printf("\nIntroduce el sentido del barco (IZQ.(I), DERE.(D), ARRIBA (A), ABAJO(B) SALIR: *");
        }
    }
}
