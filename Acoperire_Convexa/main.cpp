#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
struct Punct
{
    int x, y;
};

vector<Punct> interior;

// 0 --> p, q si r sunt COLINIARE
// 1 --> In sensul acelor de ceas
// 2 --> In sensul opus acelor de ceas
int testOrientare(Punct p, Punct q, Punct r)
{
    int valoare = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); //cross product
    if (valoare == 0)
        return 0;  // coliniare
    if(valoare>0)
        return 1;
    else
        return 2;
}

// Acoperirea convexa a vectorului cu n puncte
void acoperireConvexa(Punct puncte[], int n)
{
    // caz limita
    if (n < 3) return;

    vector<Punct> margine;

    // Cautam cel mai din stanga punct
    int l = 0;
    for (int i = 1; i < n; i++)
        if (puncte[i].x < puncte[l].x)
            l = i;

    // Cel mai din stanga punct reprezinta startul.
    int p = l, q;
    do
    {
        // Cele mai din stanga puncte formeaza acoperirea convexa, deci le introducem in vector.
        margine.push_back(puncte[p]);
        /*
            In q tinem minte ultimul si cel mai din margine punct vizitat. In cazul in care gasim un punct
            mai bun il adaugam.

         */
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
            // In cazul in care i este mai in exterior decat q, q devine i;
            if (testOrientare(puncte[p], puncte[i], puncte[q]) == 2)
                q = i; // alegem cel mai la dreapta punct dintre i si q

        }
        // q a devenit urmatorul punct din mergine si trebuie adaugat in vector
        p = q;

    }
    while (p != l);    // cat timp nu am ajuns nu am ajuns in punctul de la care am inceput parcurgerea

    // Afisam acoperirea convexa obtinuta
    cout<<"Acoperirea convexa este :" << endl;
    for (int i = 0; i < margine.size(); i++)
        cout << "(" << margine[i].x << ", "<< margine[i].y << ")" << endl;


    //facem un vector separat pentru punctele care nu sunt in margine
    for(int i = 0; i < n; i++)
    {
        int k=0;
        for (int j = 0; j < margine.size(); j++)
            if(puncte[i].x == margine[j].x && puncte[i].y == margine[j].y)
                k=1;
        if(k == 0)
            interior.push_back(puncte[i]);
    }
    for(int i = 0; i < interior.size(); i++)
    {
        cout << "Punct interior: ";
        cout << interior[i].x <<" ," <<interior[i].y;
        cout << endl;
    }




    if(margine.size()==4) {
        if (testOrientare(margine[1], margine[2], margine[3]) == 0)
        {
           /*Folosim testul de orientare pentru a vedea daca punctele sunt coliniare
            * Sortam vectorul margine
            * Formam multimea I din maximul si minimul vectorului margine
            * Iar multimea J din punctele care raman intre maxim si minim
            */
            Punct p;
            p.x = 0;
            p.y = 0;
            for(int i = 0; i < margine.size() - 1; i++)
            {
                for(int j = i + 1; j < margine.size(); j++)
                {
                    if(margine[i].x + margine[i].y > margine[j].x + margine[j].y)
                    {
                        p.x = margine[j].x;
                        p.y = margine[j].y;
                        margine[j].x = margine[i].x;
                        margine[j].y = margine[i].y;
                        margine[i].x = p.x;
                        margine[i].y = p.y;
                    }

                }
            }
            cout << "Puncte coliniare: " << endl;
            cout<<" I este format din ("<<margine[0].x << ", "<< margine[0].y<<") si ("<<margine[3].x << ", "<< margine[3].y<<")" << endl;
            cout<<" J este format din ("<<margine[1].x << ", "<< margine[1].y<<") si ("<<margine[2].x << ", "<< margine[2].y<<")" << endl;

        }
        else
        {
            {
                cout << "Patrulater convex" << endl;
                cout << "\n I este format din (" << margine[0].x << ", " << margine[0].y << ") si (" << margine[2].x << ", "
                     << margine[2].y << ")";
                cout << "\n J este format din (" << margine[1].x << ", " << margine[1].y << ") si (" << margine[3].x << ", "
                     << margine[3].y << ")";
            }
        }
    }
    else if(margine.size() == 3)
    {
        cout << "Triunghi: ";
        cout<<"\n I este format din ("<<margine[0].x << ", "<< margine[0].y<<") si ("<<margine[1].x << ", "<< margine[1].y<<") si ("<<margine[2].x << ", "<< margine[2].y<<")";
        cout << "\n J este formata din ("<<interior[0].x << ", "<< interior[0].y<<")";

    }

}

int main()
{
    Punct puncte[10];
    int n;
    cout << "Numarul de puncte: ";
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cout << "Intoduceti coordonatele: " << endl;
        cin >> puncte[i].x >> puncte[i].y;
    }
    acoperireConvexa(puncte, n);

    return 0;
}
