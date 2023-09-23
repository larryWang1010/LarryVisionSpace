#include <iostream>

#include "omp.h"

int main() {
#pragma omp parallel
    std::cout << "hello, openmp! \n" << std::endl;
}
