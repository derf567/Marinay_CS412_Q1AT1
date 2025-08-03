#include <iostream>
#include <sstream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int i = 0;
    const int iterations = 10;

    #pragma omp parallel num_threads(6)
    {
        int tid = omp_get_thread_num();
        int localResult = 0;

        for (int loop = 0; loop < iterations; ++loop) {
            switch (tid) {
                case 0:
                    #pragma omp atomic
                    i++;
                    break;
                case 1:
                    #pragma omp atomic
                    i--;
                    break;
                case 2:
                    #pragma omp atomic
                    i *= i;
                    break;
                case 3:
                    #pragma omp atomic
                    --i;
                    break;
                case 4:
                    #pragma omp atomic
                    ++i;
                    break;
                case 5:
                    localResult = i + 1;
                    break;
                default:
                    break;
            }

            #pragma omp critical
            {
                stringstream output;
                output << "Thread " << tid << " (i = " << i << ")\n";
                cout << output.str();
            }
        }

        if (tid == 5) {
            #pragma omp critical
            {
                cout << "Final result from Thread 6 (sum of all tasks): " << localResult << endl;
            }
        }
    }

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}
