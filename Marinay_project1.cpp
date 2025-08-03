#include <iostream>
#include <sstream>
#include <omp.h>
#include <cstdlib>  // For srand and rand
#include <ctime>    // For time

using namespace std;

int main() {
    srand(time(NULL)); // Seed the random number generator with the current time

    #pragma omp parallel num_threads(4)
    {
        stringstream Collecting;
        int tid = omp_get_thread_num();  // Get the thread ID

        for (int i = 1; i <= 10; ++i) {
            int randomNumber;

            #pragma omp critical(rand_section)
            {
                randomNumber = rand() % 30 + 1;  // Generate a random number between 1 and 30
            }

            Collecting << "Hello world " << randomNumber << "! Thread = " << tid << endl;
        }

        #pragma omp critical(output)
        {
            cout << Collecting.str();  // Output the collected string from each thread
        }
    }

    // Wait for user input before closing
    cout << "Press Enter to exit...";
    cin.get();  // Keeps the console open until Enter is pressed

    return 0;
}
