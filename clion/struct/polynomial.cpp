#include "iostream"
using namespace std;

typedef struct PolyNode *Polynomial;
struct PolyNode {
    int coef;
    int expon;
    Polynomial next;
};

Polynomial ReadPoly();

Polynomial Multi(Polynomial p1, Polynomial p2);

void PrintPoly(Polynomial p, int breakLine);

Polynomial Add(Polynomial p1, Polynomial p2);

void Attach(int c, int e, Polynomial *p);

int Compare(int i1, int i2);

int main(){

    Polynomial P1, P2, PP, PS;
    P1 = ReadPoly();
    P2 = ReadPoly();
    PP = Multi( P1, P2 );
    PrintPoly( PP , 1);
    PS = Add( P1, P2 );
    PrintPoly( PS , 0);

    return 0;
}

Polynomial Add(Polynomial p1, Polynomial p2) {

    Polynomial front, rear, temp;
    int sum;
    rear = new PolyNode;
    front = rear;
    /* 由front 记录结果多项式链表头结点 */
    while ( p1 && p2 ) /* 当两个多项式都有非零项待处理时 */
        switch ( Compare(p1->expon, p2->expon) ) {
            case 1:
                Attach( p1->coef, p1->expon, &rear);
                p1 = p1->next;
                break;
            case -1:
                Attach(p2->coef, p2->expon, &rear);
                p2 = p2->next;
                break;
            case 0:
                sum = p1->coef + p2->coef;
                if ( sum ) Attach(sum, p1->expon, &rear);
                p1 = p1->next;
                p2 = p2->next;
                break;
            default:
                break;
        }
    /* 将未处理完的另一个多项式的所有节点依次复制到结果多项式中去 */
    for ( ; p1; p1 = p1->next ) Attach(p1->coef, p1->expon, &rear);
    for ( ; p2; p2 = p2->next ) Attach(p2->coef, p2->expon, &rear);
    rear->next = nullptr;
    temp = front;
    front = front->next; /*令front指向结果多项式第一个非零项 */
    delete temp;
    /* 释放临时空表头结点 */
    return front;
}

int Compare(int i1, int i2) {
    if(i1 == i2) return 0;
    else if (i1 > i2) return 1;
    else return -1;
}

void PrintPoly(Polynomial p, int breakLine) {

    while(p){
        if(p->next){
            cout << p->coef << " " << p->expon << " ";
        }else if(breakLine){
            cout << p->coef << " " << p->expon << endl;
        }else{
            cout << p->coef << " " << p->expon;
        }
        p = p->next;
    }
}

Polynomial Multi(Polynomial p1, Polynomial p2) {

    Polynomial P, Rear, t1, t2, t;
    int c, e;
    if (!p1 || !p2) return nullptr;
    t1 = p1; t2 = p2;
    P = new PolyNode;//(Polynomial)malloc(sizeof(struct PolyNode));
    P->next = nullptr;
    Rear = P;
    while (t2) {
    /* 先用P1的第1项乘以P2,得到P */
        Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
        t2 = t2->next;
    }
    t1 = t1->next;
    while (t1) {
        t2 = p2; Rear = P;
        while (t2) {
            e = t1->expon + t2->expon;
            c = t1->coef * t2->coef;
            while (Rear->next && Rear->next->expon > e)
                Rear = Rear->next;
            if (Rear->next && Rear->next->expon == e) {
                if (Rear->next->coef + c)
                    Rear->next->coef += c;
                else {
                    t = Rear->next;
                    Rear->next = t->next;
                    delete t;
                }
            }
            else {
                t = new PolyNode;//(Polynomial)malloc(sizeof(struct PolyNode));
                t->coef = c; t->expon = e;
                t->next = Rear->next;
                Rear->next = t; Rear = Rear->next;
            }
            t2 = t2->next;
        }
        t1 = t1->next;
    }
    t2 = P;
    P = P->next;
    delete t2;
    
    return P;
}

Polynomial ReadPoly() {

    Polynomial p, rear, t;
    int c, e, n;
    cin >> n;

    p = new PolyNode;//(Polynomial)malloc(sizeof(struct PolyNode)); /* 链表头空结点 */
    p->next = nullptr;
    rear = p;
    while(n--){
        cin >> c >> e;
        Attach(c, e, &rear);
    }

    t = p;
    p = p->next;
    delete t;/* 删除临时生成的头结点 */

    return p;
}

void Attach(int c, int e, Polynomial *pRear) {

    Polynomial p = new PolyNode;//(Polynomial)malloc(sizeof(struct PolyNode));
    p->coef = c; /* 对新结点赋值 */
    p->expon = e;
    p->next = nullptr;
    (*pRear)->next = p;
    *pRear = p;/* 修改pRear值 */
}