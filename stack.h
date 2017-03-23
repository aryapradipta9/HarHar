#ifndef STACK_H
#define STACK_H

#define Nil 0;
//ADT Stack
typedef struct{
	int el[100];
	int TOP;
	int curr_elidx;//elemen yang
}Stack;
#define Top(S) (S).TOP
#define InfoTop(S) (S).el[(S).TOP]
#define Curr(S) (S).curr_elidx

void CreateEmpty(Stack *S);
bool IsEmpty(Stack S);
bool IsFull(Stack S);
void Push(Stack *S, int X);
void Pop(Stack *S, int *X);
void SetCurrElement(Stack *S, int X);

//Stack
void CreateEmpty(Stack *S){
	Top(*S) = Nil;
}
bool IsEmpty(Stack S){
	return Top(S)==Nil;
}
bool IsFull(Stack S){
	return (Top(S)==100);
}
void Push(Stack *S, int X){
	Top(*S)++;
	InfoTop(*S)=X;
}
void Pop(Stack *S, int *X){
	*X=InfoTop(*S);
	Top(*S)--;
}
void SetCurrElement(Stack *S,int X){
  Curr(*S) = X;
}

#endif