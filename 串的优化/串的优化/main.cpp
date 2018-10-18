#include <iostream>
#include <stdlib.h>
#include <mm_malloc.h>
using namespace std;
#define MaxSize 100

//顺序表的结构体
typedef struct {
    int data[MaxSize];
    int length;
}SqString;

void InitSqString(SqString *&L){
    L = (SqString *) malloc(sizeof(SqString));
    for (int i = 0;i<MaxSize;i++){
        L->data[i] = 0;
    }
    L->length;
}


//接受数组生成一个顺序表
void CreateSqString(SqString *&L,int *R,int n){
    int i=0;
    L = (SqString *) malloc(sizeof(SqString));
    for(i=0;i<n;i++){
        L->data[i] = R[i];
    }
    L->length = n;
}



bool EmptySqList(SqString *L){
    return (L->length == 0);
}


void DisplayList(SqString *L){
    int i =0;
    if(EmptySqList(L)){
        return;
    } else{
        for(i = 0;i<L->length;i++){
           cout<<L->data[i]<<endl;
        }
    }
}



void Get_first_fail(SqString *s,SqString *t,int &e,int n2,int n1) {
    int i = 0;
    int j = 0;
    int k = 0;
    for (i = 0; i < n2; i++){
        for (j = 0; j < n1; j++) {
            if (t->data[j] == s->data[i]) {
                t->data[j] = 0;
            }
        }
    }
    for( k=0;k<n1;k++){
        if(t->data[k] != 0){
            break;
        }
    }
    e = t->data[k];
    cout<<"这面这个字符串第一个没有出现在后面字符串中的字符是："<<e<<endl;
}


/*首先我们要知道怎么比较字符串的大小：
    字符串的大小比较，要先框定在同样的长度的字符串，
        所以我们取，较短的字符串的长度作为大家的公有长度
    这个时候我们再来比较大小，逐个逐个字符进行比较，如果A字符串的某一个字符率先大于了B字符的
        对应的那个字符，则退出循环，自此，结束。并认为A字符串大与B字符串，并不再继续比较
    如果出现，在公有的长度中，双方的字符串是一样的，那么我们再看字符串的长度，我们认为较长的
        字符串是较大的*/
int Strcmp(SqString *s, SqString *t){
    int i,comlen;
    if(s->length<t->length){
        comlen = s->length;
    } else{
        comlen = t->length;
    }
    for(i = 0;i<comlen;i++){
        if(s->data[i]>t->data[i]){
            return 1;
        } else if(s->data[i] < t->data[i]){
            return -1;
        }
    }
    if(s->length == t->length){
        return 0;
    } else if(s->length > t->length){
        return 1;
    } else{
        return -1;
    }
}

//用BF（brute-force）算法实现
int index_BF(SqString *s, SqString *t){  /*首先传入两个顺序表，前面的是对象，后面的是目标
                                            后面这个目标去匹配前面的字符串，如果匹配上了，
                                        就算是找到了，如果没有匹配上，就算是没有找到。*/
    int i=0,j=0;
    while(i<s->length && j<t->length){   //各自的循环过程不能超过两个顺序表各自的长度
        if(s->data[i] == t->data[j]){    //对象字符串和目标字符串都从第一个开始如果目标字符串中的
            i++;                         //第一个字符是匹配上的话，我们再看各自的下一个字符是不是匹配的
            j++;
        } else{                          //承接上面的过程，如果没有匹配成功，我们再从对象字符串的二字符开始找
            i = i-j+1;                   //但是目标字符串还是从头开始看。
            j = 0;                       //这一步是通过 i = i-j+1实现的
        }
    }
    if(j>=t->length){                    //最后while退出表示目标字符串的已经遍历完，并且已经匹配成功
        return (i - t->length);          //这个时候我们返回，匹配上的第一个字符的下标
    } else{
        return (-1);                     //走到这一步，表示j始终没有遍历完成，是i遍历完成，并且匹配失败
    }                                    //程序退出
}




//由模式t求next[j]的算法   即K值

void GetNext(SqString *t,int *next){   //定义一个数组next[]，
    int j,k;
    j = 0,k = -1;
    for(int i = 0;i<MaxSize;i++){
        next[i] = 0;
    }
    next[0] = -1;
    while(j<t->length - 1){
        if(k == -1 || t->data[j] == t->data[k]){   //确认前面有多少个相同的字符
            j++;
            k++;
            next[j] = k;
        } else{
            k = next[k];
        }
    }
}


//KMP算法的实现

/*KMP主要是消除了主串指针的回溯*/
int KMPIndex(SqString *s,SqString *t){
    int next[MaxSize],i = 0,j = 0;
    GetNext(t, next);
    while(i < s->length && j<t->length){
        if(j == -1 || s->data[i] == t->data[j]){
            i++;j++;
        } else{
            j = next[j];
        }
    }if(j >= t->length){
        return (i-t->length);
    } else{
        return (-1);
    }
}



class bunch{
public:
    bunch(SqString *&L,int *R,int n){
        InitSqString(L);
        CreateSqString(L,R,n);
    }
    void first_fail(SqString *Sq2,SqString *Sq1,int &e,int n2,int n1,int *b,int *a){
        InitSqString(Sq1);
        InitSqString(Sq2);
        CreateSqString(Sq1,a,n1);
        CreateSqString(Sq2,b,n2);
        Get_first_fail(Sq2,Sq1,e,n2,n1);
        cout<<endl;
    }
    void Compare_bunch(SqString *Sq2,SqString *Sq1,int n2,int n1,int *b,int *a){
        int m1;
        InitSqString(Sq1);
        InitSqString(Sq2);
        CreateSqString(Sq1,a,n1);
        CreateSqString(Sq2,b,n2);
        m1 = Strcmp(Sq1, Sq2);
        if(m1 == -1){
            cout<<"前面的字符串是小于后面的字符串的"<<endl;
            cout<<endl;
        }
        else if(m1 == 0){
            cout<<"前面的字符串是等于后面的字符串的"<<endl;
            cout<<endl;
        }else{
            cout<<"前面的字符串是大于后面的字符串的"<<endl;
            cout<<endl;
        }
        cout<<endl;
    }
    void BF_match(SqString *Sq4,SqString *Sq3,int n4,int n3,int *b,int *a){
        int m2;
        InitSqString(Sq3);
        InitSqString(Sq4);
        CreateSqString(Sq3,a,n3);
        CreateSqString(Sq4,b,n4);
        m2 = index_BF(Sq4,Sq3);
        if(m2 > 0){
            cout<<"BF算法匹配上的对应的下标是:"<<m2<<endl;
            cout<<endl;
        } else{
            cout<<"BF算法没有找到匹配的字符"<<endl;
            cout<<endl;
        }
    }
    void KMP_match(SqString *Sq4,SqString *Sq3,int n4,int n3,int *b,int *a){
        int m3;
        InitSqString(Sq3);
        InitSqString(Sq4);
        CreateSqString(Sq3,a,n3);
        CreateSqString(Sq4,b,n4);
        m3 = KMPIndex(Sq4,Sq3);
        if(m3>0){
            cout<<"KMP算法求解出的匹配成功的对应的下标:"<<m3<<endl;
            cout<<endl;
        }else{
            cout<<"没有匹配成功"<<endl;
            cout<<endl;
        }
    }
};



int main() {
    int n1,n2,n3,n4;//分别表示两个数组的长度
    int e,m1,m2,m3;
    SqString *Sq1,*Sq2,*Sq3,*Sq4;
    int a[] ={1,2,3,4,5,6,7,8,9};
    int b[] ={1,2,4,5,7,8,};
    int c[] ={4,5,6};
    int d[] ={1,1,1,1,1,3};
    int f[] ={1,1,1,3};
    n1 = sizeof(a)/ sizeof(int);
    n2 = sizeof(b)/ sizeof(int);
    n3 = sizeof(d)/ sizeof(int);
    n4 = sizeof(f)/ sizeof(int);

    bunch *mybunch = new bunch(Sq1,a,n1);
    mybunch->first_fail(Sq2,Sq1,e,n2,n1,b,a);
    mybunch->Compare_bunch(Sq2,Sq1,n2,n1,b,a);
    mybunch->BF_match(Sq4,Sq3,n3,n4,d,f);
    mybunch->KMP_match(Sq4,Sq3,n3,n4,d,f);
}