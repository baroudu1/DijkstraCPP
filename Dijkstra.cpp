#include <stdlib.h>
#include <stdio.h>
#define infinie 9999999999999

typedef struct Noeud
{
	int info;
	struct Noeud *suc;
} noeud;

typedef noeud *listeNoeuds;

typedef struct Arc
{
	noeud *S;
	noeud *D;
	float val;
	struct Arc *suc;
} arc;

typedef arc *listeArcs;

typedef struct Graphe
{
	listeNoeuds LN;
	listeArcs LA;
} graphe;

noeud *creerNoeud(int v)
{
	noeud *n = NULL;

	n = (noeud *)malloc(sizeof(noeud));

	n->info = v;
	n->suc = NULL;

	return n;
}

arc *creerArc(noeud *NS, noeud *ND, float v)
{
	arc *arc1 = NULL;

	arc1 = (arc *)malloc(sizeof(arc));

	arc1->D = ND;
	arc1->S = NS;
	arc1->val = v;
	arc1->suc = NULL;

	return arc1;
}

graphe creerGraphe()
{
	graphe graphe1;

	graphe1.LA = NULL;
	graphe1.LN = NULL;

	return graphe1;
}

int grapheEstVide(graphe G)
{
	if (!G.LN)
		return 1;

	return 0;
}

int aucunArc(graphe G)
{
	if (!G.LA)
		return 1;

	return 0;
}

void afficherNoeud(noeud *N)
{
	printf("%d", N->info);
}
int afficherNoeudsGraphe(graphe G)
{
	noeud *noeudTest = G.LN;

	if (!grapheEstVide(G))
	{
		while (noeudTest)
		{
			afficherNoeud(noeudTest);
			printf("\t");
			noeudTest = noeudTest->suc;
		}
		printf("\n");
		return 1;
	}
	return 0;
}

int afficherArcsGraphe(graphe G)
{
	arc *arcTest = G.LA;

	if (aucunArc(G) == 0)
	{
		printf("les arcs du graphe : \n");

		while (arcTest)
		{
			printf("( ");
			afficherNoeud(arcTest->S);
			printf(" , ");
			afficherNoeud(arcTest->D);
			printf(" , %.1f )\n", arcTest->val);
			arcTest = arcTest->suc;
		}
		return 1;
	}
	return 0;
}

noeud *insererNoeud(int Ninfo, listeNoeuds *LN)
{
	noeud *noeudNew;
	noeudNew = *LN;
	if (!noeudNew)
	{
		*LN = creerNoeud(Ninfo);
		return *LN;
	}
	while (noeudNew)
	{
		if (noeudNew->info == Ninfo)
			return noeudNew;
		if (!noeudNew->suc)
		{
			noeudNew->suc = creerNoeud(Ninfo);
			return noeudNew->suc;
		}
		noeudNew = noeudNew->suc;
	}
	return noeudNew;
}

arc *insererArc(noeud *NS, noeud *ND, float v, listeArcs *LA)
{
	arc *arcNew = *LA;
	if (!arcNew)
	{
		*LA = creerArc(NS, ND, v);
		return *LA;
	}
	while (arcNew)
	{
		if (arcNew->S->info == NS->info && arcNew->D->info == ND->info)
			return arcNew;
		if (!arcNew->suc)
		{
			arcNew->suc = creerArc(NS, ND, v);
			return arcNew->suc;
		}
		arcNew = arcNew->suc;
	}
	return arcNew;
}

noeud *insererNoeudGraphe(int v, graphe *G)
{
	return insererNoeud(v, &(G->LN));
}

arc *insererArcGraphe(int NS, int ND, float v, graphe *G)
{
	return insererArc(insererNoeud(NS, &G->LN), insererNoeud(ND, &G->LN), v, &G->LA);
}

int existNoeud(int v, graphe G)
{
	noeud *noeudNew = G.LN;

	if (grapheEstVide(G))
		return 0;
	while (noeudNew)
	{
		if (noeudNew->info == v)
			return 1;
		noeudNew = noeudNew->suc;
	}
	return 0;
}

int existArc(int Sinfo, int Dinfo, graphe G)
{
	arc *arcNew = G.LA;

	if (aucunArc(G))
		return 0;
	while (arcNew)
	{
		if (arcNew->S->info == Sinfo && arcNew->D->info == Dinfo)
			return 1;
		arcNew = arcNew->suc;
	}

	return 0;
}
int afficherNoeudsListt(Noeud *l)
{
	noeud *noeudTest = l;

	while (noeudTest)
	{
		afficherNoeud(noeudTest);
		printf("\t");
		noeudTest = noeudTest->suc;
	}
	printf("\n");
	return 0;
}
Noeud *getDinfo(int Sinfo, graphe G)
{
	Noeud *listeN = NULL;
	if (existNoeud(Sinfo, G))
	{
		while (G.LA)
		{
			if (G.LA->S->info == Sinfo)
				insererNoeud(G.LA->D->info, &listeN);
			G.LA = G.LA->suc;
		}
	}
	//afficherNoeudsListt(listeN);
	return listeN;
}

Noeud *mergeList(Noeud *l1, Noeud *l2)
{
	Noeud *listeN = l1;
	while (l2)
	{
		insererNoeud(l2->info, &listeN);
		l2 = l2->suc;
	}
	afficherNoeudsListt(listeN);
	return listeN;
}
int existNoeud_List(int v, Noeud *l)
{
	noeud *noeudNew = l;
	while (noeudNew)
	{
		if (noeudNew->info == v)
			return 1;
		noeudNew = noeudNew->suc;
	}
	return 0;
}

int existChemin1(int Sinfo, int Dinfo, graphe G)
{
	if (existNoeud(Sinfo, G) && existNoeud(Dinfo, G))
	{
		int exist = 0;
		Noeud *listeN;
		listeN = creerNoeud(Sinfo);
		while (listeN)
		{
			//printf("\n hhh\n");
			if (existNoeud_List(Dinfo, listeN))
				return 1;
			mergeList(listeN, getDinfo(listeN->info, G));
			listeN = listeN->suc;
		}
		return 0;
	}
	return 0;
}

int existChemin(int Sinfo, int Dinfo, graphe G)
{
	if (existNoeud(Sinfo, G) && existNoeud(Dinfo, G))
	{
		if (existArc(Sinfo, Dinfo, G))
			return 1;

		arc *ArcNew;
		ArcNew = G.LA;

		while (ArcNew)
		{
			if (ArcNew->S->info == Sinfo)
			{
				if (existChemin(ArcNew->D->info, Dinfo, G))
					return 1;
			}
			ArcNew = ArcNew->suc;
		}
	}
	return 0;
}

int supprimerArc(int Sinfo, int Dinfo, graphe *G)
{
	arc *arcNew = G->LA;

	if (existArc(Sinfo, Dinfo, *G))
	{
		if (arcNew->S->info == Sinfo && arcNew->D->info == Dinfo)
		{
			G->LA = arcNew->suc;
			free(arcNew);
			return 1;
		}
		while (arcNew->suc)
		{
			if (arcNew->suc->S->info == Sinfo && arcNew->suc->D->info == Dinfo)
			{
				arc *arcForFree = arcNew->suc;
				arcNew->suc = arcForFree->suc;
				free(arcForFree);
				return 1;
			}
			arcNew = arcNew->suc;
		}
	}
	return 0;
}

int supprimerNoeud(int Ninfo, graphe *G)
{
	noeud *noeudNew = G->LN;
	noeud *noeudTest = G->LN;
	if (existNoeud(Ninfo, *G))
	{
		// Supprimer tous les arcs lier a ce noeud
		noeud *noeudTest1 = G->LN;
		while (noeudTest1)
		{
			supprimerArc(Ninfo, noeudTest1->info, G);
			supprimerArc(noeudTest1->info, Ninfo, G);
			noeudTest1 = noeudTest1->suc;
		}
		if (noeudNew->info == Ninfo)
		{
			G->LN = noeudNew->suc;
			free(noeudNew);
			return 1;
		}

		while (noeudNew->suc)
		{
			if (noeudNew->suc->info == Ninfo)
			{
				noeud *noeudForFree = noeudNew->suc;
				noeudNew->suc = noeudForFree->suc;
				free(noeudForFree);
				return 1;
			}
			noeudNew = noeudNew->suc;
		}
	}
	return 0;
}

int demiDegreInterieur(int N, graphe G)
{
	arc *arcNew = G.LA;
	int count = 0;

	if (aucunArc(G))
		return count;
	while (arcNew)
	{
		if (arcNew->D->info == N)
			count++;
		arcNew = arcNew->suc;
	}
	return count;
}

int demiDegreExterieur(int N, graphe G)
{
	arc *arcNew = G.LA;
	int count = 0;

	if (aucunArc(G))
		return count;
	while (arcNew)
	{
		if (arcNew->S->info == N)
			count++;
		arcNew = arcNew->suc;
	}
	return count;
}

////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct STR_chemin
{

	noeud *Dest;
	noeud *Interm;
	float c;
	int etat;
	struct STR_chemin *suc;
} cheminDijkstra;

typedef cheminDijkstra *listeDijkstra;

void insererNoeudDijkstra(noeud *N, int infoS, graphe G, listeDijkstra *L)
{
	listeArcs Q;
	listeDijkstra P, R;
	P = (cheminDijkstra *)malloc(sizeof(cheminDijkstra));
	P->Dest = N;
	P->Interm = N;
	P->suc = NULL;
	if (N->info == infoS)
	{
		P->etat = 1;
		P->c = 0;
	}
	else
	{
		P->etat = 0;
		P->c = infinie;
	}
	Q = G.LA;

	while (Q != NULL && (Q->S->info != infoS || Q->D != N))
		Q = Q->suc;

	if (Q != NULL)
	{
		P->Interm = Q->S;
		P->c = Q->val;
	}

	if (*L == NULL)
		*L = P;
	else
	{
		R = *L;
		while (R->suc != NULL)
			R = R->suc;
		R->suc = P;
	}
}

void Dijkstra(graphe G, int infoS, listeDijkstra *L)
{
	noeud *N;
	noeud *M;
	noeud *X;
	arc *arcNew;
	listeDijkstra listeDK;
	listeDijkstra cheminN;
	int existV;

	N = G.LN;
	M = G.LN;
	X = NULL;
	while (N != NULL)
	{
		insererNoeudDijkstra(N, infoS, G, L);
		N = N->suc;
	}

	do
	{
		listeDK = *L;

		cheminN = NULL;

		arcNew = NULL;

		existV = 0;

		float V_Min = infinie;

		//Trouver W
		while (listeDK)
		{
			if (V_Min > listeDK->c && listeDK->etat == 0)
			{
				V_Min = listeDK->c;
				existV = 1;
				cheminN = listeDK;
			}
			listeDK = listeDK->suc;
		}

		// Mise A jours la liste des chemins
		if (existV)
		{
			listeDK = *L;

			while (listeDK)
			{
				if (listeDK->etat == 0)
				{
					if (listeDK->Dest->info == cheminN->Dest->info)
					{
						listeDK->etat = 1;
						insererNoeud(listeDK->Dest->info, &X);
					}
					else
					{
						arcNew = G.LA;

						while (arcNew != NULL && (arcNew->S != cheminN->Dest || arcNew->D != listeDK->Dest))
							arcNew = arcNew->suc;

						if (arcNew != NULL && (cheminN->c + arcNew->val) < listeDK->c)
						{
							listeDK->c = cheminN->c + arcNew->val;
							listeDK->Interm = cheminN->Dest;
						}
					}
				}
				listeDK = listeDK->suc;
			}
		}
	} while (existV);
}
int aa;
void afficherDijkstra(int infoS, int infoD, listeDijkstra L,FILE **fr)
{
	listeDijkstra liste = L;

	if (infoS == infoD)
	{
		while (liste)
		{
			if (liste->Dest->info == infoD && liste->c != infinie)
			{
				printf("%d", liste->Dest->info);
				fprintf(*fr, "%d", liste->Dest->info);
				return;
			}

			liste = liste->suc;
		}
		printf("il n'existe aucune chemin\n");
		fprintf(*fr, "il n'existe aucune chemin\n");
	}

	else
	{
		while (liste)
		{
			if (liste->Dest->info == infoD && liste->c != infinie)
			{
				afficherDijkstra(infoS, liste->Interm->info, L,fr);
				printf(" ---> %d", liste->Dest->info);
				fprintf(*fr, " ---> %d", liste->Dest->info);
				if (aa == liste->Dest->info){
					printf("\nLe cout de chemin :  %0.f\n", liste->c);
					fprintf(*fr, "\nLe cout de chemin :  %0.f\n\n", liste->c);
				}
				return;
			}

			liste = liste->suc;
		}
		printf("il n'existe aucune chemin\n");
		fprintf(*fr, "il n'existe aucune chemin\n");
	}
}

int lireFichier(graphe *G, FILE **fp, char *nomFichier)
{

	*fp = fopen(nomFichier, "r");
	int infoS, infoD;
	float vArc;
	int i = -1;
	if (*fp != NULL)
	{
		while (!feof(*fp))
		{
			if (i == -1)
				fscanf(*fp, "%d\n", &i);
			fscanf(*fp, "%d\t%d\t%f\n", &infoS, &infoD, &vArc);
			insererArcGraphe(infoS, infoD, vArc, G);
		}
	}
	return i;
}

int main()
{
	int a, b;
	graphe G;
	G = creerGraphe();
	listeDijkstra listeDK = NULL;
	FILE *fp;
	FILE *fr;
	char file[] = "file.txt";
	a = lireFichier(&G, &fp, file);

	printf("\n");
	
	//	insererArcGraphe(0,1,2,&G);
	//	insererArcGraphe(0,2,4,&G);
	//	insererArcGraphe(1,2,1,&G);
	//	insererArcGraphe(1,3,7,&G);
	//	insererArcGraphe(1,4,2,&G);
	//	insererArcGraphe(2,4,5,&G);
	//	insererArcGraphe(3,5,2,&G);
	//	insererArcGraphe(4,3,3,&G);
	//	insererArcGraphe(4,5,4,&G);
	afficherArcsGraphe(G);
	printf("\n\n");
	//printf("\nEnter noeud Source :\t");
	//scanf("%d", &a);
	Dijkstra(G, a, &listeDK);
	noeud *noeudTest = G.LN;
	fr = fopen("output.txt", "w+");

	if (!grapheEstVide(G))
	{
		while (noeudTest)
		{
			if (noeudTest->info != a)
			{
				aa = noeudTest->info;
				printf("Chemin entre %d et %d : ", a, aa);
				fprintf(fr, "Chemin entre %d et %d : ", a, aa);
				afficherDijkstra(a, noeudTest->info, listeDK,&fr);
				printf("\n");
			}
			noeudTest = noeudTest->suc;
		}
		fclose(fr);
	}

	/*
	afficherNoeudsGraphe(G);
	afficherArcsGraphe(G);
	printf("////////////////////////////////////////// \n");
	supprimerNoeud(1, &G);
	afficherArcsGraphe(G);
	afficherNoeudsGraphe(G);

	printf("\nexist :\t%d\n", existChemin(0, 5, G));

	//printf("\n \n %d", existNoeud(6, G));

	//printf("\n \n %d", existArc(4, 5, G));

	printf("\n \n %d", demiDegreInterieur(3, G));

	printf("\n \n %d", demiDegreExterieur(3, G));
	*/
	printf("\n\n");
	system("pause");
}