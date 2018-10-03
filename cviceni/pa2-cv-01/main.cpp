#include <iostream>

/**
 * author:jencmart
 * @param size
 * @param array
 */
void readArray(int * size, int ** array){

    std::cout << "Zadej nenulovou velikost pole: " << std::endl;
    std::cin >> *size;
    *array = new int[*size]; // TOHLE CHCE JESTE ZCEKOVAT...

    std::cout << "Zadej " <<*size << " prvku pole:" << std::endl;
    for(int i=0 ; i < *size ; i++) {
        std::cin >> (*array)[i] ;
    }
}

/**
 * author: jencmart
 * @param size
 * @param array
 */
void printArray(int size, int * array) {
    std::cout << '[' ;
    for(int i=0; i < size ; i++) {
        std::cout << ' ' << array[i] ;
        if( i<size-1)
            std::cout << ',';
    }
    std::cout << " ]" << std::endl;
}

/**
 * author: jencmart
 * @param size
 * @param array
 */
void bubbleSortArray(int size, int *array) {
    for(int i=0 ; i < size; i++) {
        for(int j = 0; j < size - i-1; j++) {
            if(array[j] < array[j+1]) {
                int tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
    }
}

int main() {

    int *array;
    int size;

    readArray(&size, &array);
    printArray(size, array);
    bubbleSortArray(size, array);
    printArray(size, array);

    delete []array;
    return 0;
}



