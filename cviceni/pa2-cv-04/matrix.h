//
// Created by jencmart on 3/17/17.
//

#include <vector>
#include <iostream>
#ifndef PA2_CV_04_MATRIX_H
#define PA2_CV_04_MATRIX_H



class Matrix {
private:
    unsigned m_rows;
    unsigned m_cols;
    int m_biggestVal;
    std::vector<std::vector<int>> m_matrixData;

public:
    Matrix( unsigned rows, unsigned cols) : m_rows(rows), m_cols(cols), m_matrixData(m_rows, std::vector<int>(m_cols)) {
    };

    bool loadData(){
        for(int i = 0 ; i < m_rows ; i++) {
            for(int j = 0; j< m_cols; j++) {
               std::cin >> m_matrixData[i][j];
                if(std::cin.eof())
                    return false;
            }
        }
        return true;
    }

    void operator << () {
        for (int i = 0; i < m_rows; i++) {
            for (int j = 0; j < m_cols; j++) {
                std::cout << m_matrixData[i][j];
                if (j + 1 < m_rows)
                    std::cout << " ";
            }
            std::cout << std::endl;
        }
    }
    void operator << (int row, int col) {
        if(row >= m_rows | col >= m_cols) {
            std::cout << "Zadana pozice je mimo rozmer matice" << std::endl;
            return;
        }
        std::cout << '[' << row <<  ']' << '[' << col <<  '] : '  << m_matrixData[row][col] << std::endl ;
    }

    int getValue(int row,int col) {
        if(row >= m_rows | col >= m_cols) {
            std::cout << "Zadana pozice je mimo rozmer matice" << std::endl;
            throw;
        }
        return m_matrixData[row][col];
    }
};

#endif //PA2_CV_04_MATRIX_H
