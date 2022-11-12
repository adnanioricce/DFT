#include <math.h>
#include <numbers>
#include <complex>
#include <vector>
#include <iostream>
#include <iomanip>
constexpr double pi(){
    return std::numbers::pi;
}
std::vector<std::complex<double>> dft(std::vector<std::complex<double>> X){
    // Number of samples
    int N = X.size();
    int K = N;

    // Allocate memory for internals
    std::complex<double> intSum;

    // Allocate memory for output
    std::vector<std::complex<double>> output;

    // Loop through each k
    for (size_t k = 0; k < K; k++)
    {
        // Loop through each n
        intSum = std::complex<double>(0,0);
        for (size_t n = 0; n < N; n++)
        {
            double realPart = cos( 
                ((2 * pi()) / N) * k * n
            );
            double imagPart = sin(
                ((2 * pi()) / N) * k * n
            );
            std::complex<double> w (realPart, -imagPart);
            intSum += X[n] * w;
        }
        output.push_back(intSum);
    }
    return output;
}
int main(){
    // Create a test signal.
    int N = 1000;
    std::vector<std::complex<double>> signal;
    signal.reserve(N);

    double sigK = 3.0;
    //double sigPhase = pi() / 4.0;
    double sigPhase = 0.0;
    for (size_t x = 0; x < N; x++)
    {
        auto currentSample = std::complex<double>(
            cos(
                (2 * pi() / static_cast<double>(N)) *
                    sigK * static_cast<double>(x) + sigPhase)
                ,0.0
            );       
        signal.push_back(currentSample);
    }
    std::vector<std::complex<double>> Fx = dft(signal);    
    std::cout << "Count of signals processed:" << Fx.size() << std::endl;
    // Display the first six values (real and imaginary components)
    std::cout << "****" << std::endl;    
    std::cout << "First 6 samples of the output..." << std::endl;
    std::cout << "\n" << "k\t" << std::setw(12)
        << "Real\t" << std::setw(12) 
        << "Imag" << std::endl;    
    for (size_t i = 0; i < 6; i++)
    {
        std::cout << i << "\t"
            << std::setw(12) << Fx[i].real() / static_cast<double>(N) << "\t"
            << std::setw(12) << Fx[i].imag() / static_cast<double>(N)
            << std::endl;
    }
    //expected result:
    // 0       -6.63913e-17               0
    // 1       -7.92699e-17    -3.67302e-17
    // 2        -9.4369e-17     3.80945e-17
    // 3                0.5    -1.14249e-17
    // 4        9.64784e-17     1.29077e-16
    // 5        1.09246e-16     6.29427e-17
    return 0;
}