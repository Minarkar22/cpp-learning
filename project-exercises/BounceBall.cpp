#include <iostream>
using namespace std;

int BouncingBall (double h, double bounce, double window){
    if (h <= 0 || bounce <= 0 || bounce >= 1 || window >= h)
        return -1;
    
    int count = 1; //initial count
    double height = h * bounce;
    while (height > window){
        count += 2;
        height *= bounce;
    }

    return count;
}

int main() {
    cout << BouncingBall(10, 0.66, 1.5) << endl;  // 9
    cout << BouncingBall(3,  0.66, 1.5) << endl;  // 3
    cout << BouncingBall(10, 0.66, 10)  << endl;  // -1 (window >= h)
    cout << BouncingBall(-5, 0.66, 1.5) << endl;  // -1 (h <= 0)
    cout << BouncingBall(10, 1.0,  1.5) << endl;  // -1 (bounce >= 1)
    return 0;
}