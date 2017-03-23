#ifndef TREE_H
#define TREE_H

//ADT Tree

typedef int addr;
typedef struct{
	addr bapak;
	int visited;
    int jumlah_anak;
	int anakke;
	int alamat;
	addr anak1;
	addr anak2;
	addr anak3;
}ElTree;

typedef struct{
	ElTree Elm[101];
}Tree;
//info
#define Alamat(E) (E).alamat
#define Visited(E) (E).visited
#define AnakKe(E) (E).anakke
#define JmlAnak(E) (E).jumlah_anak
//pointer ke anak
#define Anak1(E) (E).anak1
#define Anak2(E) (E).anak2
#define Anak3(E) (E).anak3
//pointer ke bapak
#define Bapak(E) (E).bapak

//Constructor
void CreateTree (Tree *T);
void AlokNode (ElTree *X);
void DealokNode (ElTree *X);
//pindah" node
void MoveToParent (Tree T, ElTree *anak);
void GoToChild(Tree T, ElTree *N, int anakke);
//ElTree GetTreeEl(Tree T, int idx);
void SetTreeEl(Tree *T, ElTree E, int idx);
void SetTreeEl2(Tree *T, addr Bpk, addr anak1, addr anak2, addr anak3, int anakke, int jmlanak, int idx);
void AddAnak(Tree *T, ElTree *ElBapak, int anakke);

//Constructor
void CreateTree (Tree *T){
	int i;
	ElTree E;
	
	for(i=1;i<101;i++){
		AlokNode(&E);
		SetTreeEl(T,E,i);
	}
	SetTreeEl2(T,0,0,0,0,1,0,1);
}

void AlokNode(ElTree *X){
	
	//alokasi berhasil
	Bapak(*X)= 0 ;
	Visited(*X)=0;
	JmlAnak(*X)=0;
	Anak1(*X)=0;
	Anak2(*X)=0;
	Anak3(*X)=0;

}

void DealokNode (ElTree *X){
	Bapak(*X)= 0 ;
	Visited(*X)=0;
	JmlAnak(*X)=0;
	Anak1(*X)=0;
	Anak2(*X)=0;
	Anak3(*X)=0;
}

//pindah" node
void MoveToParent (Tree T, ElTree *anak){
	*anak = T.Elm[Bapak(*anak)];	
}

void GoToChild(Tree T, ElTree *N, int anakke){
	if(anakke==1){
		*N = T.Elm[Anak1(*N)];
	}else if(anakke==2){
		*N = T.Elm[Anak2(*N)];
	}else{//anakke == 3
		*N = T.Elm[Anak3(*N)];
	}
}
/*
ElTree GetTreeEl(Tree T, int idx){
	return T.Elm[idx];
}
*/
void SetTreeEl(Tree *T, ElTree E, int idx){
	(*T).Elm[idx] = E;
	Alamat((*T).Elm[idx]) = idx;
}

void SetTreeEl2(Tree *T, addr Bpk, addr anak1, addr anak2, addr anak3, int anakke, int jmlanak, int idx){
	Bapak((*T).Elm[idx]) = Bpk;
	Anak1((*T).Elm[idx]) = anak1;
	Anak2((*T).Elm[idx]) = anak2;
	Anak3((*T).Elm[idx]) = anak3;
	AnakKe((*T).Elm[idx]) = anakke;
	JmlAnak((*T).Elm[idx]) = jmlanak;
	Alamat((*T).Elm[idx]) = idx;
}

void AddAnak(Tree *T, ElTree *ElBapak, int anakke){
	int i=1;
	while((AnakKe((*T).Elm[i]) != 0)&&(i<101)){//elemen belum pernah jadi anak
		i++;
	}
	if(i<101){
		SetTreeEl2(T,Bapak(*ElBapak),0,0,0,anakke,0,i);
		if(anakke==1){
			Anak1(*ElBapak) = i;
		}else if(anakke==2){
			Anak2(*ElBapak) = i;
		}else{//anakke == 3
			Anak3(*ElBapak) = i;
		}
	}
}
#endif