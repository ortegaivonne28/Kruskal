/*No consegui el que estaba comentado, de todos modos aqui te mando
este para que por lo menos sepas mas o menos como es, esperaria que
porfa lo cambies,este no imprime, tienes que hacer la corrida
en kruskal, para que imprima la matriz*/

#include <stdio.h>
#include <string.h>
#define N 200
typedef struct
{
	char nom[30];
	char cod[10];
}vert;
typedef struct
{
	int conex,dis,cost;
}matriz;
void inicializar_conexas(int conex[N][N],int n)
{
	int j,i;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
			   conex[i][j]=1;
			else
			   conex[i][j]=0;
	    }
    }
}
int buscar_comp(int conexa[][N], int colun) //para el kruskal
{
    int band=0,i=0;
    while(band!=1)
    {
        if(conexa[i][colun]==1)
        {
            band=1;
        }
        i++;
    }
    return (i-1);
}
void mover_comp(int conexas[][N], int destino, int inicio, int ver)  //para el kruskal
{
     int i;
     for(i=0;i<ver;i++)
     {
         if(conexas[inicio][i]==1)
         {
             conexas[destino][i]=1;
             conexas[inicio][i]=0;
         }
     }
}
int comp_conexas(matriz mat[][N], int conex[][N], int n)
{		
	int i,j,p,nn,m;
	p=n;
	for(i=0;i<n;i++)
	{
		for(j=(i+1);j<n;j++)
		{
			if(mat[i][j].conex!=0)
			{
				nn=buscar_comp(conex,i);
				m=buscar_comp(conex,j);
				if(nn!=m)
				{
					mover_comp(conex,nn,m,n);
                    p--;
			    }
		    }
	    }
    }
	return p;
}
void kruskal(vert cuerpos[N],int arc[4][N], int tminimo[][N], int conex[N][N], int m, int n)
{
      int i,j,cont_v=0,cont_dat=0,pos1,pos2;
      while(cont_v<(n-1))
      {
          pos1=i=arc[0][cont_dat];
          pos2=j=arc[1][cont_dat];
          cont_dat++;
          i=buscar_comp(conex,i);
          j=buscar_comp(conex,j);
          if(i!=j)
          {
            mover_comp(conex,i,j,n);
            tminimo[pos1][pos2]=arc[2][(cont_dat-1)];   
			tminimo[pos2][pos1]=arc[2][(cont_dat-1)];  
            cont_v++;
          }
      } 
}
int main()
{
	int conexas[N][N];
	vert cuerpos[N],satelites[N];
	matriz ady[N][N],adys[N][N];
	int arcos[4][N];
	int i,j,n,a,longg=0,m=0;
	int temp,k,di,c,aux;
	int tminimo[N][N];
	char tempu[30],tempd[30];
	scanf("%d ",&n);
	for(i=0;i<n;i++)
	{
		scanf("%s",cuerpos[i].nom);
		scanf("%s",cuerpos[i].cod);
		if(cuerpos[i].nom[0]!='A')
		{
			strcpy(satelites[m].nom,cuerpos[i].nom);
			strcpy(satelites[m].cod,cuerpos[i].cod);
			m++;
		}
		for(j=0;j<n;j++)
		{
			ady[i][j].conex=0;
			adys[i][j].conex=0;
		}
	}
	scanf("%d ",&m); //carga de las conexiones
	longg=n;
	for(k=0;k<m;k++)
	{
		scanf("%s",tempu);
		scanf("%s",tempd);
		scanf("%d %d",&di,&c);
		temp=i=j=aux=0;
		a=0;
		while(temp<2)
		{
			if(strcmp(tempu,cuerpos[aux].cod)==0)
			{
				i=aux;
				temp++;
				if(cuerpos[aux].nom[0]=='A')
				{
					a=1;
					longg--;
				}
			}
			if(strcmp(tempd,cuerpos[aux].cod)==0)
			{				
				j=aux;
				temp++;
				if(cuerpos[aux].nom[0]=='A')
				{
					if(a==0)
						longg--;
					a=1;
				}
			}

			aux=aux+1;
		}
		ady[i][j].conex=1;
		ady[i][j].dis=di;
		ady[i][j].cost=c;
		ady[j][i].conex=1;
		ady[j][i].dis=di;
		ady[j][i].cost=c;
		if(a==0)
		{
			arcos[0][k]=i;
			arcos[1][k]=j;
			arcos[2][k]=di;
		}
	}
	inicializar_conexas(conexas,longg);
	k=comp_conexas(ady,conexas,longg);
	inicializar_conexas(conexas,longg);
	kruskal(satelites,arcos,tminimo,conexas,m,longg);
	
return 0;
}
