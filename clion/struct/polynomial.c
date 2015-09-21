#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>

typedef struct PolyNode *Polynomial;
struct PolyNode {
    //系数
    int coef;
    //指数
    int expon;
    Polynomial next;
};

Polynomial readPoly();
Polynomial add(Polynomial p1, Polynomial p2);
Polynomial multi(Polynomial p1, Polynomial p2);
void printPoly(Polynomial pp, int breakLine);
void freePolynomial(Polynomial p, ...);

int main() {

    Polynomial p1, p2, pp, ps;
    p1 = readPoly();
    p2 = readPoly();
    ps = add(p1, p2);
    pp = multi(p1, p2);
    printPoly(pp, 1);
    printPoly(ps, 0);
    freePolynomial(pp, ps, p1, p2, NULL);

    return 0;
}

Polynomial readPoly() {

    int size;
    scanf("%d", &size);
    Polynomial p = calloc(1, sizeof(struct PolyNode)), pHead = p;
    while(size--){
        scanf("%d %d", &(p->coef), &(p->expon));
        if(size > 0){
            p->next = calloc(1, sizeof(struct PolyNode));
            p = p->next;
        }
    }

    return pHead;
}

Polynomial add(Polynomial p1, Polynomial p2) {

    Polynomial p = calloc(1, sizeof(struct PolyNode)), pHead = p, pTail = NULL;
    while(p1 && p2){
        if(p1->expon == p2->expon){
            p->coef = p1->coef + p2->coef;
            if(0 != p->coef){
                p->expon = p1->expon;
            }
            p1 = p1->next;
            p2 = p2->next;
        }else if(p1->expon > p2->expon){
            if(0 != p1->coef){
                p->expon = p1->expon;
                p->coef = p1->coef;
            }
            p1 = p1->next;
        }else{
            if(0 != p2->coef){
                p->expon = p2->expon;
                p->coef = p2->coef;
            }
            p2 = p2->next;
        }
        if(0 != p->coef){
            p->next = calloc(1, sizeof(struct PolyNode));
            pTail = p;
            p = p->next;
        }
    }
    if(pTail){
        free(pTail->next);
        pTail->next = NULL;
    }
    if(p1){
        if(pTail){
            free(pTail->next);
            pTail->next = p1;
        }else{
            free(pHead);
            pHead = p1;
            while(pHead && 0 == pHead->coef){
                pHead = pHead->next;
            }
            pTail = pHead;
        }
    }else if(p2){
        if(pTail){
            free(pTail->next);
            pTail->next = p2;
        }else{
            free(pHead);
            pHead = p2;
            while(pHead && 0 == pHead->coef){
                pHead = pHead->next;
            }
            pTail = pHead;
        }
    }
    if((p1 || p2) && pTail){
        while(pTail->next && 0 == pTail->next->coef){
            while(pTail->next && 0 == pTail->next->coef){
                pTail->next = pTail->next->next;
            }
            pTail = pTail->next;
        }
    }

    return pHead;
}

Polynomial multi(Polynomial p1, Polynomial p2) {

    Polynomial p, pHead, p2Head = p2, pp = NULL;
    while(p1){
        if(0 != p1->coef){
            p = calloc(1, sizeof(struct PolyNode));
            pHead = p;
            while(p2){
                p->coef = p1->coef * p2->coef;
                p->expon = p1->expon + p2->expon;
                p2 = p2->next;
                if(p2 && 0 != p2->coef){
                    p->next = calloc(1, sizeof(struct PolyNode));
                    p = p->next;
                }
            }
            pp = add(pHead, pp);
        }
        p1 = p1->next;
        p2 = p2Head;
    }

    if(!pp){
        pp = calloc(1, sizeof(struct PolyNode));
    }

    return pp;
}

void printPoly(Polynomial p, int breakLine) {

    while(p){
        if(p->next){
            printf("%d %d ", p->coef, p->expon);
        }else if(breakLine){
            printf("%d %d\n", p->coef, p->expon);
        }else{
            printf("%d %d", p->coef, p->expon);
        }
        p = p->next;
    }
}

//以NULL作为结束标识
void freePolynomial(Polynomial p, ...) {

    Polynomial temp;
    va_list arg_ptr;
    va_start(arg_ptr, p);
    while(p){
        while(p){
            temp = p;
            p = p->next;
            free(temp);
        }
        p = va_arg(arg_ptr, Polynomial);
    }
    va_end(arg_ptr);
}