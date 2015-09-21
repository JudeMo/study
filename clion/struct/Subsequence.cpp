#include <iostream>

using namespace std;

int main() {

    int size, n, maxSum = 0, subSum = 0, begin, end, begin_new;
    bool jump = false, init = false;
    cin >> size;
    for (int i = 0; i < size; ++i) {
        cin >> n;
        if (i == 0){
            begin_new = n;
            if (!jump)
                begin = begin_new;
        }
        subSum += n;
        if (subSum < 0) {
            subSum = 0;
            size -= i + 1;
            i = -1;
            jump = true;
        }

        if (subSum > maxSum || (0 == n && subSum == maxSum && !init)) {
            maxSum = subSum;
            end = n;
            begin = begin_new;
            init = true;
        }
    }
    if (0 == maxSum && !init)
        end = n;
    cout << maxSum << " " << begin << " " << end;
    return 0;
}

