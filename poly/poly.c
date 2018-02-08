#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "error.h"
#include "poly.h"

typedef struct term term;


struct term {
    int expo;
    int factor;
};

struct poly_t {
    struct term terms[10];
    int size;
};



void add_to_poly(poly_t*, int, int);
int get_factor(char*);
int get_exp(char*);


void initiate_polynomial(poly_t * poly) {
    for(int i =0; i<10; i++) {
        poly->terms[i].expo = 0;
        poly->terms[i].factor = 0;
    }
    poly->size = 0;

}

poly_t* new_poly_from_string(const char* input) {
    //todo linkedlist to hol the data?
    int size = 10;
    char * tmp_string = malloc(2*strlen(input)*sizeof(char));
    char * part;
    strcpy(tmp_string, input);
    poly_t* polynom = malloc(size*sizeof(poly_t));
    initiate_polynomial(polynom);

    int sign = 1;
    // get part of string
    part = strtok(tmp_string, " ");
    //puts(part);

    while (part != NULL) {
        //printf("dadawd");

        switch (part[0]) {
            case '+':
            sign = 1;
            break;
            case '-':
            sign = -1;
            break;
        }
        if (part[0] != '+' && part[0] != '-' ) {
            //printf("part :%s\n", part);

            add_to_poly(polynom, sign*get_factor(part), get_exp(part));
        }
        // get next part of string

        part = strtok(NULL, " ");
    }
    free(tmp_string);
    free(part);
    return polynom;

}

poly_t* mul(poly_t* left, poly_t* right) {
    poly_t* result;
    result = malloc(sizeof(poly_t));
    initiate_polynomial(result);
    int factor, expo;

    for (int i = 0; i < (left->size); i++) {
        for (int k = 0; k < (right->size); k++) {
            factor = left->terms[i].factor*right->terms[k].factor;
            expo = left->terms[i].expo+right->terms[k].expo;
            add_to_poly(result, factor, expo);
        }
    }
    return result;
}

void free_poly(poly_t* poly) {
    if (poly != NULL) {
        free(poly);
    }
}
int sign(int i) {
    return (i>0) - (i<0);
}

int get_exp (char * part) {
    int i, expo;
    char * test;
    i = expo = 0;
    if ((test = strchr(part, '^')) != NULL ) {
        while (isdigit(test[i+1]) ) {
            expo = expo*10 + test[i+1] - '0';
            i++;
            }
        } else if (test == NULL && ((test = strchr(part, 'x')) != NULL)) {
            return 1;
    }
    //printf("exponent:%d\n", expo);
    return expo;
}

int get_factor(char * part) {
    int tmp = 0;
    int i = 0;
    while (isdigit(part[i])) {
        tmp = tmp*10 + part[i] - '0';
        i++;
    }

    if (tmp == 0 ) {
        tmp = 1;
    }
    //printf("factor:%d\n", tmp);
    return tmp;
}
void add_to_poly(poly_t * poly, int factor, int expo) {

    for (int i = 0; i < poly->size; i++) {
        if (expo == poly->terms[i].expo) {
            poly->terms[i].factor += factor;
            return;
        }
    }
    struct term term;
    term.expo = expo;
    term.factor = factor;
    poly->terms[poly->size] = term;
    poly->size++;
    //printf("polynomial: %dx^%d\n", (poly->terms[poly->size-1].factor), (poly->terms[poly->size-1].expo) );

}

void print_poly(poly_t* poly) {
    int factor, expo;

    for (int i = 0; i < (poly->size); i++) {
        factor = poly->terms[i].factor;
        expo = poly->terms[i].expo;

        if (sign(factor) == 1) {
            if (i > 0) {
                printf(" + ");
            }
        } else {
            printf(" - ");
            factor *= -1;
        }

        if (factor == 1 && expo > 0) {
            printf("x^%d", expo);
        } else if (expo == 0 && factor > 0) {
            printf("%d", factor);
        } else if (expo == 1 && factor > 1) {
            printf("%dx", factor);
        } else if (expo > 1 && factor > 1 ) {
            printf("%dx^%d", factor, expo);
        }
    }
    printf("\n");
}
