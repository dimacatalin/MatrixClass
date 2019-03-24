#ifndef MATRICE_H
#define MATRICE_H
#include <iostream>

using namespace std;

class matrice
{
    public:
        matrice();//constructorul nul//
        matrice(int,int);//constructorul cu parametrii//
        matrice(const matrice&);//construcoturl de copiere//
        ~matrice();//destructorul//
        int delta();//calcularea determinantului
        void isinv();//testarea inversabilitatii
        matrice  deleterow(int);//eliminarea unei linii//
        matrice  deletecol(int);//eliminarea unei coloane//
        matrice  deleteboth(int,int);//eliminarea unei linii si a unei coloane//
        int getrows();//returneaza numarul de linii//
        int getcols();//returneaza numarul de coloane//
        //supraincarcarea operatorilor
        matrice operator+(const matrice&);//adunarea a 2 matrice//
        matrice operator*(const matrice&);//inmultirea a 2 matrice//
        matrice operator*(int);//inmultirea unei matrice cu un scalar//
        matrice operator-(const matrice&);//scaderea a 2 matrice//
        friend istream& operator>>(istream&,const matrice&);//citirea//
        friend ostream& operator<<(ostream&,const matrice&);//afisarea//
        void operator=(const matrice&);//atribuire//
        int * operator[](int);//returnarea unei linii specifice//

    private:
        int rows;//numarul de linii
        int cols;//numarul de coloane
        int **matrix;//declar matricea ca un pointer catre un vecotor de pointeri
};

#endif // MATRICE_H
