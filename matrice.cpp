#include "matrice.h"
#include <iostream>
#include <math.h>

using namespace std;

matrice::matrice()
{
    //initializez cu 0
    rows=0;
    cols=0;
    matrix=NULL;
}

matrice::matrice(int row,int col)
{
    int i;
    //atribui nuamrul de linii si coloane
    rows=row;
    cols=col;

    matrix=new int *[rows];//aloc pointerului (numar de linii)*pointer

    for(i=0; i<rows; i++)
        matrix[i]=new int[col];//aloc fiecarui pointer din vector (numar de coloane)*int
}

matrice::matrice(const matrice &a)
{
    //copiaza datele din matricea a in matricea clasei
    rows=a.rows;
    cols=a.cols;
    matrix=a.matrix;
}

matrice::~matrice()
{
    int i;
    for(i=0; i<rows; i++)
        delete [] matrix[i];
    delete [] matrix;
}

int matrice::delta()
{
    if (cols!=rows)
        cout<<"Nu se poate calcula determinantul la o matrice care nu este patratica";
    else
    {
        if(rows==2)//daca are grad 2
            return matrix[0][0]*matrix[1][1]-matrix[1][0]*matrix[0][1];
        if(rows==3)//daca are grad 3
            return matrix[0][0]*matrix[1][1]*matrix[2][2]+matrix[1][0]*matrix[2][1]*matrix[0][2]+matrix[2][0]*matrix[0][1]*matrix[1][2]-matrix[0][2]*matrix[1][1]*matrix[2][0]-matrix[1][2]*matrix[2][1]*matrix[0][0]-matrix[2][2]*matrix[0][1]*matrix[1][0];
        else//daca este de grad mai mare
        {
            int k, subi, i, j, subj,d=0;
            matrice submatrix(rows-1,cols-1);
            //cream o submatrice,aceasta va fi reprezentata de elementele care nu se afla pe linia si coloana elementului de pe prima linie
            for(k=0;k<rows;k++)
             {//parcurgem prima linie si ii cream submatricea corespunzatoare fiecarui element de pe aceasta
                subi=0;
                for(i=1;i<rows;i++)//trecem peste prima linie deoarece nu este inclusa in submatricea noastra si ramane de pus conditie doar pentru coloane
                {
                    subj=0;
                    for(j=0;j<rows;j++)
                        if(j!=k)
                        {
                        submatrix.matrix[subi][subj] = matrix[i][j];//copiem toate elementele mai putin cele de pe coloana elementului de pe prima linie
                        subj++;
                        }
                    subi++;
                }
                d=d+(pow(-1,k)*matrix[0][k]*submatrix.delta());
            }
            return d;
        }
    }
}

matrice matrice::deleterow(int row)
{
    int i,j;
    matrice newmatrix(rows-1,cols);//declar o noua matrice si ii aloc cu o linie mai putin

    //ii copiez toate elementele in afara de linia data
    for(i=0; i<row; i++)
        for(j=0; j<cols; j++)
            newmatrix.matrix[i][j]=matrix[i][j];
    if(row!=rows)
        for(i=row; i<rows-1; i++)
            for(j=0; j<cols; j++)
                newmatrix.matrix[i][j]=matrix[i+1][j];

    return newmatrix;//returnz poiner catre noua matrice
}

matrice matrice::deletecol(int col)//identic ca la deleterow
{
    int i,j;
    matrice newmatrix(rows,cols-1);
    for(i=0; i<rows; i++)
        for(j=0; j<col; j++)
            newmatrix.matrix[i][j]=matrix[i][j];
    if(col!=cols)
        for(i=0; i<rows; i++)
            for(j=col; j<cols-1; j++)
                newmatrix.matrix[i][j]=matrix[i][j+1];

    return newmatrix;
}

matrice matrice::deleteboth(int row,int col)
{
    matrice newmatrix(rows,cols-1);
    matrice newwmatrix(rows-1,cols-1);
    newmatrix=deletecol(col);//sterg coloana data
    newwmatrix=newmatrix.deleterow(row);//sterg linia data
    return newwmatrix;
}

void matrice::isinv()
{
    if (delta()==0)//daca determinantul este 0
        cout<<"Matricea nu este inversabila"<<endl;
    else cout<<"Matricea este inversabila"<<endl;
}

int matrice::getrows()
{
    return rows;
}

int matrice::getcols()
{
    return cols;
}

matrice matrice::operator+(const matrice &a)
{
    matrice result(rows, cols);
    if(rows!=a.rows||cols!=a.cols)
        cout<<"Cele 2 matrice au nuamrul de linii sau coloane diferit"<<endl;
    else
    {
        int i,j;
        for (i=0; i<rows; i++)
            for (j=0; j<cols; j++)
                result.matrix[i][j] = matrix[i][j] + a.matrix[i][j];
    }

    return result;
}

matrice matrice::operator*(const matrice &a)
{
    matrice result(rows, cols);
    int i,j,k;
    for (i=0; i<rows; i++)
        for (j=0; j<cols; j++)
            result.matrix[i][j]=0;
    if(rows!=a.rows||cols!=a.cols)
        cout<<"Cele 2 matrice au nuamrul de linii sau coloane diferit"<<endl;
    else
    {
        for (i=0; i<rows; i++)
            for (j=0; j<cols; j++)
                for (k=0; k<rows; k++)
                    result.matrix[i][j]=result.matrix[i][j]+matrix[i][k]*a.matrix[k][j];
    }
    return result;
}

matrice matrice::operator*(int x)
{
    matrice result(rows, cols);
    int i,j;
    for (i=0; i<rows; i++)
        for (j=0; j<cols; j++)
            result.matrix[i][j] = matrix[i][j]*x;
    return result;
}

matrice matrice::operator-(const matrice &a)
{
    matrice result(rows, cols);
    if(rows!=a.rows||cols!=a.cols)
        cout<<"Cele 2 matrice au nuamrul de linii sau coloane diferit"<<endl;
    else
    {
        int i,j;
        for (i=0; i<rows; i++)
            for (j=0; j<cols; j++)
                result.matrix[i][j] = matrix[i][j] - a.matrix[i][j];
    }
    return result;
}

istream& operator>>(istream& in,const matrice &a)
{
    int i,j;
    for(i=0; i<a.rows; i++)
        for(j=0; j<a.cols; j++)
            in>>a.matrix[i][j];
    return in;
}

ostream& operator<<(ostream& out,const matrice &a)
{
    int i,j;
    for(i=0; i<a.rows; i++)
    {
        for(j=0; j<a.cols; j++)
            out<<a.matrix[i][j]<<" ";
        out<<endl;
    }
    return out;
}

void matrice::operator=(const matrice &a)
{
    if(rows!=a.rows||cols!=a.cols)
        cout<<"Cele 2 matrice au nuamrul de linii sau coloane diferit"<<endl;
    else
    {
        int i,j;
        cols=a.cols;
        rows=a.rows;
        for(i=0; i<rows; i++)
            for(j=0; j<cols; j++)
                matrix[i][j]=a.matrix[i][j];
    }

}

int * matrice::operator[](int x)
{
    return matrix[x];//returnez pointer la linia specificata ca parametru
}
