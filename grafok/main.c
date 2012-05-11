//
//Iranyitatlan osszefuggo graf (szetszortan -szomszedossagi listaval)
//Szelessege bejaras
//
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
//-------------------------------------------------------------------------------------------
typedef struct szomszedossagiListaElem{// A szomszedossagi lista adateleme
    int kulcs;
    struct  szomszedossagiListaElem *kov;
}SzomszedossagiListaElem;

typedef struct grafListaElem{// A grafot tartalmazo lista elemei
    int kulcs;
    struct grafListaElem *kov;
    struct  szomszedossagiListaElem *szomszedok;
}GrafListaElem;

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
GrafListaElem* beRendezettGraf(GrafListaElem* fej, int kulcs, int szomszedSzam, ...);
SzomszedossagiListaElem* beRendezettLista(SzomszedossagiListaElem *fej, int kulcs);
GrafListaElem* kiGrafKulcs(GrafListaElem *fej,int kulcs);
void kiirGraf(GrafListaElem* fej, FILE *stream);
//-------------------------------------------------------------------------------------------
void szelessegiBejaras(GrafListaElem *fej);
void listaVegere(GrafListaElem **fej, GrafListaElem **vege, GrafListaElem *mit);
GrafListaElem * masol(GrafListaElem* mit);
int vanE(GrafListaElem *fej, int kulcs);
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
int main()
{   GrafListaElem *fej=NULL;

    printf("Grag felepitese...");
    fej=beRendezettGraf(fej, 10, 0);
    fej=beRendezettGraf(fej, 15, 1, 10);
    fej=beRendezettGraf(fej, 13, 1, 10);
    fej=beRendezettGraf(fej, 6, 2, 15, 13);
    fej=beRendezettGraf(fej, 20, 1, 6);
    fej=beRendezettGraf(fej, 3, 5, 10, 15, 13, 6, 20);
    printf("Kesz\n");
    printf("\nGraf kiiratasa\n");
    kiirGraf(fej,stdout);
    printf("\nSzelessegi bejaras\n");
    szelessegiBejaras(fej);
    system("pause");
    return 0;
}
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
GrafListaElem* beRendezettGraf(GrafListaElem* fej, int kulcs,  int szomszedSzam, ...){
    GrafListaElem *uj, *p,*q;
    int skulcs;
    va_list argptr;
    //Megvizsgalni hogy a kulcs letezik e mar
    if(kiGrafKulcs(fej,kulcs)){printf("HIBA---A %5d kulcs mar letezik \n\a",kulcs); return fej;}
    //Az uj grafelelem létrehozása
    uj=(GrafListaElem*)malloc(sizeof(GrafListaElem));
    uj->kulcs=kulcs;
    uj->szomszedok=NULL;
    uj->kov=NULL;
    //Szomszédok beállítása
    va_start(argptr, szomszedSzam);
    for(;szomszedSzam;szomszedSzam--){
        skulcs=va_arg(argptr, int);
        if(p=kiGrafKulcs(fej,skulcs)){
            uj->szomszedok=beRendezettLista(uj->szomszedok,skulcs);
            p->szomszedok=beRendezettLista(p->szomszedok,kulcs);
        }
        else{printf("HIBA---A %5d kulcs nem letezik (%d)\n\a",skulcs, kulcs);}
    }
    va_end(argptr);
    //Az uj elem beszurasa a grafba
    if(!fej){return uj;}
    p=q=fej;
    while(p && (p->kulcs<kulcs)){
        q=p;
        p=p->kov;
    }
    if(p==fej){uj->kov=fej; return uj;}
    q->kov=uj;
    uj->kov=p;
    return fej;
}
//-------------------------------------------------------------------------------------------
SzomszedossagiListaElem* beRendezettLista(SzomszedossagiListaElem *fej, int kulcs){
    SzomszedossagiListaElem *uj, *p, *q;
    //Az elem lefoglalása
    uj=(SzomszedossagiListaElem*)malloc(sizeof(SzomszedossagiListaElem));
    uj->kulcs=kulcs;
    uj->kov=NULL;
    //Az elem beszúrása a rendezett listába
    if(!fej){return uj;}

    p=q=fej;
    while(p && (p->kulcs<kulcs)){//Az elem helyenek megkeresese a rendezett listaba
        q=p;
        p=p->kov;
    }

    if(p==fej){
        if(p->kulcs!=kulcs){uj->kov=fej; return uj;}//Beszuras a lista elejere
        else{free(uj); return fej;}//Ez a kulcs már be volt állítva szomszédnak
    }
    if(p && (p->kulcs!=kulcs)){q->kov=uj; uj->kov=p;}//Beszuras a listaba
    else if(!p){q->kov=uj;}//Beszuras a lista vegere
    else{free(uj);}//Ez a kulcs már be volt állítva szomszédnak
    return fej;
}
//-------------------------------------------------------------------------------------------
GrafListaElem* kiGrafKulcs(GrafListaElem *fej,int kulcs){
    GrafListaElem *p;

    p=fej;
    while(p && (p->kulcs<kulcs)){p=p->kov;}

    if(!p){return NULL;}
    else if(p->kulcs==kulcs){return p;}
    return NULL;
}
//-------------------------------------------------------------------------------------------
void kiirGraf(GrafListaElem* fej, FILE *stream){
    GrafListaElem* g;
    SzomszedossagiListaElem*s;

    g=fej;
    while(g){
        fprintf(stream,"%5d   kozvetlen szomszedai:",g->kulcs);
        s=g->szomszedok;
        while(s){
            fprintf(stream,"%5d",s->kulcs);
            s=s->kov;
        }
        fprintf(stream,"\n");
        g=g->kov;
    }
}
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
void szelessegiBejaras(GrafListaElem *grafFej){
    GrafListaElem *akt, *gle, *listaVege, *listaFej;
    SzomszedossagiListaElem *sle;

    if(grafFej){
        listaVege=listaFej=NULL;
        printf("%d\n",grafFej->kulcs);//************
        listaVegere(&listaFej, &listaVege, masol(grafFej));

        akt=listaFej;
        while(akt){ //Amig el nem ertem a lista vegere
            sle=akt->szomszedok;
            while(sle){//Az osszes szomszed felhelyezese a listara (kiveve akkor ha mar rajta van)
                if(!vanE(listaFej, sle->kulcs)){
                    gle=kiGrafKulcs(grafFej, sle->kulcs);
                    printf("%d\n",gle->kulcs);//************
                    listaVegere(&listaFej, &listaVege, masol(gle));
                }
                sle=sle->kov;
            }
            akt=akt->kov;
        }
    }

    // A lista törlese
    SzomszedossagiListaElem *slet;
    akt=listaFej;
    while(akt){
        gle=akt;
        akt=akt->kov;
        sle=gle->szomszedok;
        while(sle){
            slet=sle;
            sle=sle->kov;
            free(slet);
        }
        free(gle);
    }
}
//-------------------------------------------------------------------------------------------
void listaVegere(GrafListaElem **fej, GrafListaElem **vege, GrafListaElem *mit){
    if(!(*fej)){*fej=mit; *vege=mit;}
    else{(*vege)->kov=mit; *vege=mit;}
}
//-------------------------------------------------------------------------------------------
GrafListaElem * masol(GrafListaElem* mit){
    SzomszedossagiListaElem *sle;

    GrafListaElem *uj=(GrafListaElem*)malloc(sizeof(GrafListaElem));
    uj->kulcs=mit->kulcs;
    uj->kov=NULL;
    uj->szomszedok=NULL;

    sle=mit->szomszedok;
    while(sle){

        uj->szomszedok=beRendezettLista(uj->szomszedok,sle->kulcs);
        sle=sle->kov;
    }
    return uj;
}
//-------------------------------------------------------------------------------------------
int vanE(GrafListaElem *fej, int kulcs){
    GrafListaElem *p;

    p=fej;
    while(p && (p->kulcs<kulcs)){p=p->kov;}

    if(!p){return 0;}
    else if(p->kulcs==kulcs){return 1;}
    return 0;
}
