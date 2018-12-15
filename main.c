#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define TAM 12

int VALIDO(int A){ // Función QUE DEVUELVE 1 SI EL NUMERO ES VALIDO, CERO SI NO.
    return(A>TAM-1?0:A<0?0:1);
}

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
    printf("\n___________________________________________________________________________________________________\n");
    for(j=0;j<TAM;j++){
        printf("%2d|\t", j);
        for(i=0;i<TAM;i++){
            if(!mat[i][j])
                printf(" \t"); // Si hay agua, espacio
            else if(mat[i][j]==5)
                printf("~\t"); //Si han disparado al agua, ~
            else if(mat[i][j]>0)
                printf("%d\t", mat[i][j]); //Si hay un barco, n (4,3,2 o 1)
            else if(mat[i][j]<0){
                    if(toc_o_hun(mat,i,j,5))
                        printf("x\t");
                    else
                        printf("X\t");
            }
        }
        printf("\n\n");
    }


}

int barc_alred(char mat[TAM][TAM], int x, int y){ //Función que devuelve 1 si hay barcos alrededor de una casilla xy, 0 si no.
    if(mat[x][y])
        return(1);
    if(mat[x+1][y]&&VALIDO(x+1))
        return(1);
    if(mat[x+1][y+1]&&VALIDO(x+1)&&VALIDO(y+1))
        return(1);
    if(mat[x][y+1]&&VALIDO(y+1))
        return(1);
    if(mat[x-1][y+1]&&VALIDO(x-1)&&VALIDO(y+1))
        return(1);
    if(mat[x-1][y]&&VALIDO(x-1))
        return(1);
    if(mat[x-1][y-1]&&VALIDO(x-1)&&VALIDO(y-1))
        return(1);
    if(mat[x][y-1]&&VALIDO(y-1))
        return(1);
    if(mat[x+1][y-1]&&VALIDO(x+1)&&VALIDO(y-1))
        return(1);
    return(0);
}

int posivalida(char mat[TAM][TAM], int x, int y, int tamabar, int posi){ //Función que devuelve 1-2-3-4 si se puede colocar una barco de 'tamabar' casillas en la posición x y, 0 si no.
    int i, conta;
    // La variable posi indica la posición en la que se desea colocar el barco. 0 implica cualquier dirección, 1 dcha, 2 arriba, 3 izda y 4 abajo.
    if(tamabar==1)
        return(1); // Si el tamaño del barco es 1, se puede colocar.

    if(!posi||posi==1){
        for(i=0, conta=0;i<tamabar;i++){ // Bucle que comprueba si se puede colocar hacia la derecha
            if(!barc_alred(mat,x+i,y)&&VALIDO(x+i))
                conta++;
        }

        if(conta==tamabar)
            return(1);
    }

    if(!posi||posi==2){
        for(i=0, conta=0;i<tamabar;i++){ // Bucle que comprueba si se puede colocar hacia abajo
            if(!barc_alred(mat,x,y+i)&&VALIDO(y+i))
                conta++;
        }

        if(conta==tamabar)
            return(2);
    }

    if(!posi||posi==3){
        for(i=0, conta=0;i<tamabar;i++){ // Bucle que comprueba si se puede colocar hacia la izquierda
            if(!barc_alred(mat,x-i,y)&&VALIDO(x-i))
                conta++;
        }

        if(conta==tamabar)
            return(3);
    }

    if(!posi||posi==4){
        for(i=0, conta=0;i<tamabar;i++){ // Bucle que comprueba si se puede colocar hacia arriba
            if(!barc_alred(mat,x,y-i)&&VALIDO(y-i))
                conta++;
        }

        if(conta==tamabar)
            return(4);
    }

    return(0);

}

void inic_tab_jugador(char tab[TAM][TAM]){
    unsigned int x, y, tamabar, i=0;
    int c;

    char direc;

    for(c=0;c<10;c++){
        tamabar=c>5?1:c>2?2:c?3:4;
        do{
            mostrar_tab_jugador(tab);
            do{
                printf("\nIntroduce la posicion inicial x para el barco de %d casillas: ", tamabar);
                scanf("%u", &x);
            }while(!VALIDO(x));
            do{
                printf("\nIntroduce la posicion inicial y para el barco de %d casillas: ", tamabar);
                scanf("%u", &y);
                fflush(stdin);
            }while(!VALIDO(y));
            if(barc_alred(tab,x,y))
                puts("POSICION INCORRECTA");
        }while(barc_alred(tab,x,y));

            i=0;
            tab[x][y]=tamabar;
            printf("\n");
            mostrar_tab_jugador(tab);
            if(tamabar>1){
                tab[x][y]=0;
                do{
                printf("\nIntroduce la direccion del barco (IZQ.(I), DERE.(D), ARRIBA (A), ABAJO(B) SALIR (* para elegir otra posicion inicial):\n");
                scanf("%c", &direc);
                fflush(stdin);
                }while(toupper(direc)!='I'&&toupper(direc)!='D'&&toupper(direc)!='A'&&toupper(direc)&&toupper(direc)!='B'&&toupper(direc)!='*');
                switch(toupper(direc)){
                case 'I':
                    if(posivalida(tab,x,y,tamabar,3)){
                        tab[x][y]=tamabar;
                        for(i=0;i<tamabar;i++)
                            tab[x-i][y]=tamabar;
                    }else{
                        puts("El barco no se puede colocar hacia la izquierda.\n");
                        c--;
                    }
                    break;
                case 'D':
                    if(posivalida(tab,x,y,tamabar,1)){
                        tab[x][y]=tamabar;
                        for(i=0;i<tamabar;i++)
                            tab[x+i][y]=tamabar;
                    }else{
                        puts("El barco no se puede colocar hacia la derecha.\n");
                        c--;
                    }
                    break;
                case 'B':
                    if(posivalida(tab,x,y,tamabar,2)){
                        tab[x][y]=tamabar;
                        for(i=0;i<tamabar;i++)
                            tab[x][y+i]=tamabar;
                    }else{
                        puts("El barco no se puede colocar hacia abajo.\n");
                        c--;
                    }
                    break;
                case 'A':
                    if(posivalida(tab,x,y,tamabar,4)){
                        tab[x][y]=tamabar;
                        for(i=0;i<tamabar;i++)
                            tab[x][y-i]=tamabar;
                    } else{
                        puts("El barco no se puede colocar hacia arriba.\n");
                        c--;
                    }
                    break;
                case '*':
                    i++;
                    c--;
                    break;
                }
            } else if (tamabar==1){
                i=1;
                tab[x][y]=tamabar;
            }

    }
}

void inic_tab_maqui(char tab[TAM][TAM]){
    unsigned int x, y, tamabar, i=0;
    int c, direc;

    for(c=0;c<10;c++){
        tamabar=c>5?1:c>2?2:c?3:4;
        do{
            x=rand()%12;
            y=rand()%12;
        }while(barc_alred(tab,x,y));
        direc=rand()%2;
        if(direc){ //Si es 1, el barco va hacia la derecha o izquierda
            if(posivalida(tab,x,y,tamabar,1)){
                for(i=0;i<tamabar;i++)
                    tab[x+i][y]=tamabar;
            } else if(posivalida(tab,x,y,tamabar,3)){
                for(i=0;i<tamabar;i++)
                    tab[x-i][y]=tamabar;
            } else
                c--;
        } else if(!direc){ //Si es 0, el barco va hacia arriba o hacia abajo
            if(posivalida(tab,x,y,tamabar,4)){
                for(i=0;i<tamabar;i++)
                    tab[x][y-i]=tamabar;
                } else if(posivalida(tab,x,y,tamabar,2)){
                    for(i=0;i<tamabar;i++)
                        tab[x][y+i]=tamabar;
                } else
                    c--;
        }
    }
}

void mostrar_tab_maquina(char mat[TAM][TAM]){

    int i, j;

    printf("\t");

    for(i=0;i<TAM;i++)
        printf("%d\t", i);
    printf("\n");
    for(j=0;j<TAM;j++){
        printf("%d\t", j);
        for(i=0;i<TAM;i++){
            if(mat[i][j]==5)
                printf("-\t"); //Si han disparado al agua, -
            else if(mat[i][j]>=0)
                printf("~\t"); //Si hay un barco o agua, ~
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

int disparo(char juga[TAM][TAM], char maqui[TAM][TAM], char bar_rest[4], int turno){ // Turno = 0 si ataca la máquina, 1 si ataca el jugador.
    int x, y, aux=0, i;

    if(turno){ // Ataque del jugador
        do{
            mostrar_tab_maquina(maqui);
            do{
                do{
                    printf("\nIntroduce la coordenada x del disparo:");
                    x=getchar();
                }while(!VALIDO(x));
                do{
                    printf("\nIntroduce la coordenada y del disparo: (* para cambiar la coord x)");
                    y=getchar();
                }while(!VALIDO(y));
                if(maqui[x][y]!=5||maqui[x][y]<0)
                    printf("\n¡Esa casilla es invalida! Selecciona otra.");
            }while(maqui[x][y]!=5||maqui[x][y]<0);
            if(maqui[x][y]==0){
                printf("\nAgua...");
                maqui[x][y]=5;
                aux=0;
            } else{
                printf("\n\t\t--- Tocado ");
                maqui[x][y]*=-1;
                aux=1;
                if (!toc_o_hun(maqui,x,y,5)){
                    printf("y hundido ---");
                    bar_rest[maqui[x][y]==-1?3:maqui[x][y]==-2?2:maqui[x][y]==-3?1:0]--; // FALTA rellenar con 5 las casillas adyacentes al barco hundido.
                }else
                    printf("---");
            }
        }while(aux);
    } else{
        do{
            aux=0;
            do{
                x=rand()%12;
                y=rand()%12;
            }while(juga[x][y]!=5||juga[x][y]<0);
            if(juga[x][y]==0){
                printf("\n(%d,%d) - Agua.", x, y);
                juga[x][y]=5;
            } else {
                printf("\n(%d,%d) - TOCADO", x,y);
                juga[x][y]*=-1;
                aux=1;
                if(!toc_o_hun(juga,x,y,5)){
                    printf(" Y HUNDIDO -");
                    bar_rest[juga[x][y]==-1?3:juga[x][y]==-2?2:juga[x][y]==-3?1:0]--; // FALTA rellenar con 5 las casillas adyacentes al barco hundido. También falta mejorar la aleatoriedad del programa.
                }
                else
                    printf(" -");
            }
        }while(aux);
    }

    for(i=0, aux=0;i<4;i++)
        aux+=bar_rest[i];

    return(aux);
    }



int main(){
    char maqui[TAM][TAM]={0}, juga[TAM][TAM]={0};
    int barjuga[4]={1,2,3,4}, barmaqui[4]={1,2,3,4};

    srand(time(NULL));

    printf("\t\t\t\t\t CARLOS POZUELO RIVAS. GM-12\n");

    inic_tab_jugador(juga);
    inic_tab_maqui(maqui);


}
