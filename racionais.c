#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>

#define MINIMO 0
/* acrescente demais includes que voce queira ou precise */

/* Funcoes privadas restritas a este modulo.
 * Voce deve implementa-las pois serao necessarias,
 * embora elas nao precisem estar no .h */

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat (int min, int max){

    return min + rand() % (max - min + 1);
}

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
/* dica: a versao recursiva eh bem elegante! */
int mdc (int a, int b){
    if (b == 0)
        return a;
    
    return mdc(b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
int mmc (int a, int b){
    return (a * b) / mdc(a,b);
}

/* Recebe um numero racional e o retorna simplificado.
 * Por exemplo, ao receber 10/8 devera retornar 5/4.
 * Se ambos numerador e denominador forem negativos, devera retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Quem chama esta funcao deve garantir que o racional r eh valido */
void simplifica_r (struct racional *r){

    if (!r->valido)
        return;
    if (r->den == 0)
        return;

    /* calcula o mdc de ambos*/ 
    int both_den = mdc (r->num,r->den);
    r->num /= both_den;
    r->den /= both_den;

    /* garante que o denominador seja positivo */
    if (r->den < 0){
        r->num *= -1;
        r->den *= -1; 
    }
}

/* Cria um numero racional com base nas informacoes dos parametros. */
struct racional cria_r (int numerador, int denominador){
    struct racional new_rational;

    new_rational.num = numerador;
    new_rational.den = denominador;

    /*chama a funcao valido_r para testar se eh um racional valido*/
    new_rational.valido = valido_r(new_rational);

    return new_rational;
}

/* Retorna um numero racional gerado aleatoriamente. */
struct racional sorteia_r (int max){
    
    int numerador = aleat(-max,max);
    int denominador = aleat(-max,max);

    struct racional resultado = cria_r(numerador, denominador);
    simplifica_r(&resultado);

    return resultado;
}


/* Retorna o numerador do racional r */
int numerador_r (struct racional r){
    return r.num;
}

/* Retorna o denominador do racional r */
int denominador_r (struct racional r){
    return r.den;
}

/* Retorna 1 se o racional r eh valido ou 0 caso contrario. */ 
int valido_r (struct racional r){
    if (denominador_r (r) == 0)
        return 0;
    return 1;
}


/* Retorna a soma (simplificada) dos racionais r1 e r2 no parametro *r3 */
void soma_r (struct racional r1, struct racional r2, struct racional *r3){
    if (!r3)
        return;

    if (!r1.valido) {
        *r3 = r2;    
        return;
    }

    if(!r2.valido) {
        *r3 = r1;
        return;
    }

    int both_den = mmc(r1.den, r2.den);
    int numerador = r1.num * (both_den / r1.den) + r2.num * (both_den / r2.den);

    /* cria um racional com o resultado*/
    *r3 = cria_r(numerador, both_den);

    /* ja simplifica o racional, essa forma sera um padrao no codigo*/
    simplifica_r(r3);
}

/* Retorna a subtracao dos racionais r1 e r2 no parametro *r3 */ 
void subtrai_r (struct racional r1, struct racional r2, struct racional *r3) {
    if (!r3)
        return;

    if (!r1.valido) {
        *r3 = r2;    
        return;
    }

    if(!r2.valido) {
        *r3 = r1;
        return;
    }

    int both_den = mmc(r1.den, r2.den);
    int numerador = r1.num * (both_den / r1.den) - r2.num * (both_den / r2.den);

    *r3 = cria_r(numerador, both_den);

    simplifica_r(r3);
}

/* Retorna a multiplicacao dos racionais r1 e r2 no parametro *r3 */
void multiplica_r (struct racional r1, struct racional r2, struct racional *r3){

    if (!r3)
        return;
    
    /* verifica se alguns dos racionais nao eh valido */
    if (!r1.valido || !r2.valido) {
        r3->valido = 0;
        return;
    }

    int numerador = r1.num * r2.num;
    int denominador = r1.den * r2.den;

    *r3 = cria_r(numerador,denominador);

    simplifica_r(r3);
}

/* Retorna a divisao dos racionais r1 e r2 no parametro *r3 e
 * retorna 1 se *r3 for valido ou 0 caso contrario.
 * --NAO eh-- matematicamente garantido que a divisao de dois racionais validos 
 * seja valido. Se o numerador do racional r2 for 0, entao o racional 
 * resultante eh invalido. */
int divide_r (struct racional r1, struct racional r2, struct racional *r3){
    if (!r3)
        return -1;

    /* verifica se o numerador de r2 eh 0, se for 0 a divisao nao eh possivel*/
    if (r2.num == 0) {
        r3->valido = 0;
        r3->num = 0; 
        r3->den = 0;
        return 0;
    }

    /* verifica se r1 e r2 sao validos */
    if (!r1.valido || !r2.valido) {
        r3->valido = 0;
        return 0;
    }

    int numerador = r1.num * r2.den;
    int denominador = r1.den * r2.num;

    if (denominador == 0) {
        /* define o resultado como invalido */
        r3->valido = 0;
        r3->num = 0;
        r3->den = 0;
        return 0;
    }

    /* simplifica o resultado da divisao */
    int both_mdc = mdc(numerador, denominador);
    numerador /= both_mdc;
    denominador /= both_mdc; 

    /* cria o resultado da divisao e testa se eh valido */
    *r3 = cria_r(numerador, denominador);
    r3->valido = 1;

    return 1;
}
    

/* Retorna -1 se r1 < r2; 0 se r1 == r2; 1 se r1 > r2 */
int compara_r (struct racional r1, struct racional r2){
    if (!r1.valido || !r2.valido )
        return -2;

    /* calculo de produto cruzado de r1 e r2*/
    long int resultado_r1 = r1.num * r2.den;
    long int resultado_r2 = r2.num * r1.den;

    /* valores de return conforme  o especificado*/
    if (resultado_r1 < resultado_r2)
        return -1;
    if (resultado_r1 > resultado_r2)
        return 1;
    else
        return 0;
}

/* Imprime um racional r*/ 
void imprime_r (struct racional r){
    if (!r.valido){
        printf(" INVALIDO");
        return;
    }

    if (r.num == 0){ 
        printf(" 0");
        return;
    }
    
    if (r.num == r.den){ 
        printf(" 1");
        return; 
    }

    /* casos em que o denominador nao precisa aparecer */
    if (r.num % r.den == 0) { 
        printf(" %d", r.num/r.den);
        return;
    }

    printf(" %d/%d", r.num, r.den);
} 


