/* Arquivo MAIN que usa o TAD racionais */

#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>

/* coloque seus includes aqui */

int main (){

    /* inicalizado com 0, conforme as especificacoes */
    srand(0);

    int n, max;

    do {
        printf("Digite um valor para n entre 0 e 100:\n");
        scanf("%d", &n);
    } while (n < 0 || n > 100);

    do {
        printf("Digite um valor para max entre 0 e 100:\n");
        scanf("%d", &max);
    } while (max < 0 || max > 30);

    /* imprimir as entradas do usuario*/
    printf("%d %d\n", n,max);

    for (int i = 1; i <= n; i++) {

        printf("%d:", i);

        struct racional r1 = sorteia_r(max);
        struct racional r2 = sorteia_r(max);

        imprime_r(r1);
        imprime_r(r2);

        if (!valido_r(r1) || !valido_r(r2)) {
            printf(" NUMERO INVALIDO\n");
            return 1;
        }

        struct racional sum_result;
        soma_r(r1, r2, &sum_result);

        struct racional sub_result;
        subtrai_r(r1, r2, &sub_result);

        struct racional multi_result;
        multiplica_r(r1, r2, &multi_result);

        struct racional div_result;
        divide_r(r1, r2, &div_result); 

        if (!valido_r(div_result)) {
            printf(" DIVISAO INVALIDA\n");
            return 1;
        } else {  
            imprime_r(div_result);
        }

        imprime_r(sum_result);
        imprime_r(sub_result);
        imprime_r(multi_result);

        printf("\n");
    }

    return 0;
}
