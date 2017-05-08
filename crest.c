/* Copyright Pavel Kryukov, 2011      */
/* Sample inputs: `0 0`, `0 1`, `2 0` */ 

#include <stdio.h>

#define O signed
#define H unsigned
#define A O char
#define Q z->a[i][j]
#define T H i;for(i=0;i<3;++i){ 
#define Z T H j;for(j=0;j<3;++j){
#define B Z if(!Q){
#define E printf
#define I(t) return (t)
#define C(X1,X2,X3,X4) (z->a[X1][X2]==z->a[X3][X4])

typedef struct{A a[3][3];}D;O fi(D* z){B I(0);}}}I(1);}A f(D* z)
{T if(C(0,i,1,i)&&C(2,i,1,i)&&z->a[2][i])I(z->a[0][i]);if(C(i,0,
i,1)&&C(i,2,i,1)&&z->a[i][2])I(z->a[i][0]);}if(C(0,0,1,1)&&C(2,2
,1,1)||C(2,0,1,1)&&C(0,2,1,1))I(z->a[1][1]);I(0);}O gn(D* z,H s)
{if(f(z)==1)I(1<<(s*2));H g=0;O c=s%2?-1:1;B D t=*z;t.a[i][j]=c;
O w=f(&t);if(w)I(w>0?1<<((s-1)*2):0);g+=fi(&t)?1:gn(&t,s-1);}}}I
(g);}O dp(D* z){E("-----\n");Z E(!Q?" ":Q>0?"O":"X");}E("\n");};
I(0);}D ai(D *z,H s){O m=-1;D b;B D t=*z;t.a[i][j]=1;O ss=gn(&t,
s-1);if(ss>m)b=t,m=ss;}}}I(b);}void u(D *z){H i,j;do{scanf("%d \
%d",&j,&i);}while(j>2||i>2||Q);Q=-1;}O main(){A r;D z={0};H s=9;
while(!(fi(&z)||f(&z))){u(&z);dp(&z);--s;if(fi(&z))break;z=ai(&z
,s--);dp(&z);}r=f(&z);E(!r?"Draw\n":"O wins\n");I(0);}
