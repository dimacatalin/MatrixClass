#include <iostream>
#include <matrice.h>
using namespace std;

int main()
{
    matrice x(4,4),y(4,4);
    int *p,i;

    cin>>x;cout<<endl;
    cout<<"Matricea introdusa este de "<<x.getcols()<<" pe "<<x.getrows()<<endl;

    cout<<"Determinantul matricei intorduse este="<<x.delta()<<" si ";
    x.isinv();
    cout<<endl;

    y=x;

    cout<<"Suma"<<endl<<x+y<<endl;

    cout<<"Diferenta"<<endl<<x-y<<endl;

    cout<<"Inmultirea cu matrice"<<endl<<x*y<<endl;

    cout<<"Inmultirea cu scalarul 2"<<endl<<x*2<<endl;

    p=x[1];
    cout<<"Obtinerea liniei 1: ";
    for(i=0;i<x.getcols();i++)
        cout<<p[i]<<" ";
    cout<<endl<<endl;

    matrice z(3,4);
    z=x.deleterow(1);
    cout<<"Matricea obtinuta dupa eliminarea liniei 1: "<<endl<<z;

    matrice t(4,3);
    t=y.deletecol(1);
    cout<<"Matricea obtinuta dupa eliminarea coloanei 1: "<<endl<<t;

    matrice q(3,3);
    q=x.deleteboth(1,1);
    cout<<"Matricea obtinuta dupa eliminarea liniei 1 si coloanei 1: "<<endl<<q;



}
