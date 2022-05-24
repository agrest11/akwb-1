#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct mojaLista
{
    int numer_wierzcholka;
    mojaLista *nastepny;
};
mojaLista **lista_sasiedztwa;
mojaLista *nowa, *pomocnicza, *pomocnicza2, *pomocnicza3, *pomocnicza4;

struct mojaLista2
{
    int numer;
    mojaLista2 *nowy_nastepny;
};
mojaLista2 **lista2;
mojaLista2 *pom, *pom2;

struct nowaLista
{
    int number;
    nowaLista *next;
};
nowaLista **nowa_lista;
nowaLista *p1, *p2;

struct oryginalna
{
    int nr;
    oryginalna *n;
};
oryginalna **org;
oryginalna *o1, *o2;

int multigraf(int liczba_wierzcholkow)
{
    int j,wyjscie=1;
    for(j=0;j<liczba_wierzcholkow;j++)
    {
        pomocnicza=lista_sasiedztwa[j];
        while(pomocnicza)
        {
            pomocnicza2=pomocnicza->nastepny;
            while(pomocnicza2)
            {
                if(pomocnicza->numer_wierzcholka==pomocnicza2->numer_wierzcholka)
                {
                    wyjscie=0;
                    return wyjscie;
                }
                pomocnicza2=pomocnicza2->nastepny;
            }
            pomocnicza=pomocnicza->nastepny;
        }
    }
    return wyjscie;
}

int sprzezony(int tablica[], int liczba_wierzcholkow)
{
    int i,j,nast,wyjscie=1;
    for(i=0;i<liczba_wierzcholkow;i++)
    {
        pomocnicza=lista_sasiedztwa[i];
        for(j=0;j<liczba_wierzcholkow;j++)
        {
            nast=0;
            while(pomocnicza)
            {
                pomocnicza2=lista_sasiedztwa[j];
                while(pomocnicza2)
                {
                    if(pomocnicza->numer_wierzcholka==pomocnicza2->numer_wierzcholka)
                        nast++;
                    pomocnicza2=pomocnicza2->nastepny;
                }
                pomocnicza=pomocnicza->nastepny;
            }
            if(tablica[i]!=tablica[j] && nast>0)
            {
                wyjscie=0;
                return wyjscie;
            }
            else if(tablica[i]==tablica[j] && nast>0 && nast<tablica[i])
            {
                wyjscie=0;
                return wyjscie;
            }
        }
    }
    return wyjscie;
}

int liniowy1(int tablica[], int liczba_wierzcholkow)
{
    int i,wyjscie=1;
    for(i=0;i<liczba_wierzcholkow;i++)
    {
        if(tablica[i]>1)
        {
            nowa=lista_sasiedztwa[i];
            while(nowa->nastepny)
            {
                pomocnicza=nowa->nastepny;
                while(pomocnicza)
                {
                    pomocnicza2=lista_sasiedztwa[nowa->numer_wierzcholka];
                    while(pomocnicza2)
                    {
                        pomocnicza3=lista_sasiedztwa[pomocnicza->numer_wierzcholka];
                        while(pomocnicza3)
                        {
                            if(pomocnicza3->numer_wierzcholka==pomocnicza2->numer_wierzcholka)
                            {
                                wyjscie=0;
                                return wyjscie;
                            }
                            pomocnicza3=pomocnicza3->nastepny;
                        }
                        pomocnicza2=pomocnicza2->nastepny;
                    }
                    pomocnicza=pomocnicza->nastepny;
                }
                nowa=nowa->nastepny;
            }
        }
    }
    return wyjscie;
}

int liniowy2(int tablica[], int liczba_wierzcholkow)
{
    int i,wyjscie=1;
    for(i=0;i<liczba_wierzcholkow;i++)
    {
        if(tablica[i]>1)
        {
            pomocnicza=lista_sasiedztwa[i];
            while(pomocnicza)
            {
                pomocnicza2=pomocnicza->nastepny;
                while(pomocnicza2)
                {
                    pomocnicza3=lista_sasiedztwa[pomocnicza->numer_wierzcholka];
                    while(pomocnicza3)
                    {
                        pomocnicza4=lista_sasiedztwa[pomocnicza2->numer_wierzcholka];
                        while(pomocnicza4)
                        {
                            if(pomocnicza3->numer_wierzcholka==i && pomocnicza4->numer_wierzcholka==i)
                            {
                                wyjscie=0;
                                return wyjscie;
                            }
                            pomocnicza4=pomocnicza4->nastepny;
                        }
                        pomocnicza3=pomocnicza3->nastepny;
                    }
                    pomocnicza2=pomocnicza2->nastepny;
                }
                pomocnicza=pomocnicza->nastepny;
            }
        }
    }
    return wyjscie;
}

int liniowy3(int licznik_petli, int tab[])
{
    int i,j,wyjscie=1;
    for(i=0;i<licznik_petli;i++)
    {
        pomocnicza=lista_sasiedztwa[tab[i]];
        while(pomocnicza)
        {
            for(j=0;j<licznik_petli;j++)
            {
                if(j!=i)
                {
                    pomocnicza2=lista_sasiedztwa[tab[j]];
                    while(pomocnicza2)
                    {
                        if(pomocnicza2->numer_wierzcholka==tab[i] && pomocnicza->numer_wierzcholka==tab[j])
                        {
                            wyjscie=0;
                            return wyjscie;
                        }
                        pomocnicza2=pomocnicza2->nastepny;
                    }
                }
            }
            pomocnicza=pomocnicza->nastepny;
        }
    }
    return wyjscie;
}

int main()
{
    int liczba_wierzcholkow,liczba_lukow,v1,v2,v3,i,j,licznik;
    liczba_lukow=0;
    liczba_wierzcholkow=0;

    //zlicza luki
    ifstream mojGraf("pierwszy.txt");
    if(mojGraf.is_open())
    {
        while(mojGraf>>v1>>v2)
        {
            if(v2>0)
                liczba_lukow++;
        }
    }
    else
        cout<<"Blad"<<endl;
    mojGraf.close();

    //zlicza wierzcholki
    int minimalny=liczba_lukow;
    ifstream mojGraf2("pierwszy.txt");
    if(mojGraf2.is_open())
    {
        while(mojGraf2>>v1>>v2)
        {
            if(v1>liczba_wierzcholkow)
                liczba_wierzcholkow=v1;
            if(v1<minimalny)
                minimalny=v1;
        }
    }
    else
        cout<<"Blad2"<<endl;
    mojGraf2.close();
    cout<<liczba_wierzcholkow<<endl;

    //tworzy liste sasiedztwa
    lista_sasiedztwa=new mojaLista *[liczba_wierzcholkow];
    for(i=0;i<liczba_wierzcholkow;i++)
        lista_sasiedztwa[i]=NULL;

    ifstream mojGraf3("pierwszy.txt");
    if(mojGraf3.is_open())
    {
        //for(i=0;i<liczba_lukow;i++)
        //{
            while(mojGraf3>>v1>>v2)
            {
                nowa=new mojaLista;
                nowa->numer_wierzcholka=v2-1;
                nowa->nastepny=lista_sasiedztwa[v1-1];
                lista_sasiedztwa[v1-1]=nowa;
            }
        //}
    }
    else
        cout<<"Blad3"<<endl;
    mojGraf3.close();

    //sprawdza, czy graf jest 1-grafem
    int mult=multigraf(liczba_wierzcholkow);
    if(mult==0)
    {
        cout<<"Graf jest multigrafem"<<endl;
        exit(0);
    }

    //zlicza nastepniki wierzcholkow
    int tablica[liczba_wierzcholkow];
    for(i=0;i<liczba_wierzcholkow;i++)
    {
        licznik=0;
        pomocnicza=lista_sasiedztwa[i];
        while(pomocnicza)
        {
            licznik++;
            pomocnicza=pomocnicza->nastepny;
        }
        tablica[i]=licznik;
    }

    //sprawdza czy graf jest sprzezony
    int sprz=sprzezony(tablica,liczba_wierzcholkow);
    if(sprz==0)
    {
        cout<<"Graf nie jest sprzezony"<<endl;
        exit(0);
    }

    //struktura pierwsza
    int lin1=liniowy1(tablica,liczba_wierzcholkow);
    if(lin1==0)
        cout<<"Graf nie jest liniowy"<<endl;

    //struktura druga
    int lin2=liniowy2(tablica,liczba_wierzcholkow);
    if(lin2==0)
        cout<<"Graf nie jest liniowy"<<endl;

    //liczy ile jest petli wlasnych
    int licznik_petli=0;
    int tab[liczba_wierzcholkow];
    for(i=0;i<liczba_wierzcholkow;i++)
    {
        pomocnicza=lista_sasiedztwa[i];
        while(pomocnicza)
        {
            if(pomocnicza->numer_wierzcholka==i)
            {
                licznik_petli++;
                tab[licznik_petli-1]=i;
            }
            pomocnicza=pomocnicza->nastepny;
        }
    }

    //struktura trzecia
    int lin3=liniowy3(licznik_petli,tab);
    if(lin3==0)
        cout<<"Graf nie jest liniowy"<<endl;

    //transformacja
    lista2=new mojaLista2 *[liczba_lukow*2];
    for(i=0;i<liczba_lukow*2;i=i+2)
        lista2[i]=NULL;

    for(i=0;i<liczba_lukow*2;i=i+2)
    {
        pom=new mojaLista2;
        pom->numer=i+1;
        pom->nowy_nastepny=lista2[i];
        lista2[i]=pom;
    }

    for(i = 0; i < liczba_lukow*2; i=i+2)
    {
        cout << "A[" << i << "] =";
        pom = lista2[i];
        while(pom)
        {
            cout << pom->numer<<" ";
            pom= pom->nowy_nastepny;
        }
        cout << endl;
    }

    nowa_lista=new nowaLista *[liczba_wierzcholkow];
    for(i=0;i<liczba_wierzcholkow;i++)
        nowa_lista[i]=NULL;

    //(3) podpisuje wartosci z (1) przyporzadkowane nastepnikom z grafu wejsciowego
    for(i=0,j=0;i<liczba_lukow*2,j<liczba_wierzcholkow;j++)
    {
        pomocnicza=lista_sasiedztwa[j];
        while(pomocnicza)
        {
            pom2=lista2[i];
            while(pom2)
            {
                v1=pomocnicza->numer_wierzcholka;
                v2=pom2->numer;
                p1=new nowaLista;
                p1->number=v2;
                p1->next=nowa_lista[j];
                nowa_lista[j]=p1;
                i=i+2;
                pom2=pom2->nowy_nastepny;
            }
            pomocnicza=pomocnicza->nastepny;
        }
    }

    for(i = 0; i < liczba_wierzcholkow; i++)
    {
        cout << "A[" << i << "] =";
        p1 = nowa_lista[i];
        while(p1)
        {
            cout << p1->number<<" ";
            p1= p1->next;
        }
        cout << endl;
    }

    //bierze najmniejsza wartosc z listy
    int najmniejszy[liczba_wierzcholkow];
    int minimum;
    for(i=0;i<liczba_wierzcholkow;i++)
    {
        p1=nowa_lista[i];
        while(p1)
        {
            minimum=p1->number;
            p1=p1->next;
        }
        najmniejszy[i]=minimum;
    }

    org=new oryginalna *[liczba_wierzcholkow];
    for(i=0;i<liczba_wierzcholkow;i++)
        org[i]=NULL;

    for(i=0;i<liczba_wierzcholkow;i++)
    {
        pomocnicza=lista_sasiedztwa[i];
        while(pomocnicza)
        {
            v1=najmniejszy[i];
            o1=new oryginalna;
            o1->nr=v1;
            o1->n=org[i];
            org[i]=o1;
            pomocnicza=pomocnicza->nastepny;
        }
    }

    for(i = 0; i < liczba_wierzcholkow; i++)
    {
        cout << "org[" << i << "] =";
        o1 = org[i];
        while(o1)
        {
            cout << o1->nr<< " ";
            o1= o1->n;
        }
        cout << endl;
    }

    int wierzcholki[liczba_wierzcholkow];
    for(i=0;i<liczba_wierzcholkow;i++)
        wierzcholki[i]=0;

    for(i=0;i<liczba_wierzcholkow;i++)
    {
        pomocnicza=lista_sasiedztwa[i];
        o1=org[i];
        while(pomocnicza && o1)
        {
            v1=pomocnicza->numer_wierzcholka;
            v2=o1->nr;
            wierzcholki[v1]=v2;
            o1=o1->n;
            pomocnicza=pomocnicza->nastepny;
        }
    }
    for(i=0;i<liczba_wierzcholkow;i++)
        cout<<i<<" "<<wierzcholki[i]<<endl;
    cout<<endl;
    int wierzcholki2[liczba_wierzcholkow];
    for(i=0;i<liczba_wierzcholkow;i++)
        wierzcholki2[i]=i+2;
    for(i=0;i<liczba_wierzcholkow;i++)
    {
        if(wierzcholki[i]==wierzcholki[i+1])
            wierzcholki2[i+1]=wierzcholki2[i];
    }

    //zapis do pliku
    ofstream zapis("oryginalny.txt");
    for(i=0;i<liczba_wierzcholkow;i++)
    {
        pomocnicza=lista_sasiedztwa[i];
        while(pomocnicza)
        {
            v1=pomocnicza->numer_wierzcholka;
            v2=wierzcholki2[i];
            v3=wierzcholki2[v1];
            pomocnicza=pomocnicza->nastepny;
        }
        if(i>=minimalny-1)
            zapis<<v2<<" "<<v3<<"\n";
        cout<<"zapisano"<<endl;
    }
    zapis.close();

    //usuwanie list
    for(i=0;i<liczba_wierzcholkow;i++)
    {
        pomocnicza=lista_sasiedztwa[i];
        while(pomocnicza)
        {
            nowa=pomocnicza;
            pomocnicza=pomocnicza->nastepny;
            delete nowa;
        }
    }
    delete [ ] lista_sasiedztwa;

    for(i=0;i<liczba_lukow*2;i=i+2)
    {
        pom=lista2[i];
        while(pom)
        {
            pom2=pom;
            pom=pom->nowy_nastepny;
            delete pom2;
        }
    }
    delete [ ] lista2;

    for(i=0;i<liczba_wierzcholkow;i++)
    {
        p1=nowa_lista[i];
        while(p1)
        {
            p2=p1;
            p1=p1->next;
            delete p2;
        }
    }
    delete [ ] nowa_lista;

    for(i=0;i<liczba_wierzcholkow;i++)
    {
        o1=org[i];
        while(o1)
        {
            o2=o1;
            o1=o1->n;
            delete o2;
        }
    }
    delete [ ] org;

    return 0;
}
