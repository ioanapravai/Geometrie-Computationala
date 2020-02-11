#include <iostream>
using namespace std;

struct Punct{
    double x, y, z;
};

Punct citire(){
    Punct A;
    cout << "Introduceti x, y, z :";
    cin >> A.x >> A.y >> A.z;
    cout << endl;
    return A;
}

int main() {
    Punct A, B, C;
    float a = 0;
    int ok = 0;
    A = citire();
    B = citire();
    C = citire();
    if(A.x == B.x && A.y == B.y && A.z == B.z){
        cout << "Sunt coliniare: A = 1 * B + 0 * C" << endl;
        ok = 1;
    }
    ///avem grija la impartirea la 0
    if(B.x - A.x != 0){
        a = (C.x - A.x)/(B.x - A.x);
    }
    if(B.y - A.y != 0){
        a = (C.y - A.y)/(B.y - A.y);
    }
    if(B.z - A.z != 0){
        a = (C.z - A.z)/(B.z - A.z);
    }
    if(a*(B.x - A.x) == (C.x - A.x) && a*(B.y - A.y) == (C.y - A.y) && a*(B.z - A.z) == (C.z - A.z) && ok == 0){
        cout << "Sunt coliniare: ";
        C.x = (1 - a) * A.x + a * B.x;
        C.y = (1 - a) * A.y + a * B.y;
        C.z = (1 - a) * A.z + a * B.z;
        cout <<1 - a << " * A + " << a << " * B ";
        ok = 1;
    }
    if(ok == 0){
        cout << "Punctele nu sunt coliniare";
    }
    return 0;
}