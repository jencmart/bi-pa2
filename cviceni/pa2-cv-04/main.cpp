#include <iostream>
#include <vector>
//TODO

class Matrix {
private:
    unsigned m_rows;
    unsigned m_cols;
    int m_biggestVal;
    std::vector<std::vector<int>> m_matrixData;

public:
    Matrix(){};
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

    void loadData(int i, int j , int value) {
        m_matrixData[i][j] = value;
    }

    friend void operator << (ofstream a ,Matrix & a) {
        for (int i = 0; i < a.m_rows; i++) {
            for (int j = 0; j < a.m_cols; j++) {
                std::cout << a.m_matrixData[i][j];
                if (j + 1 < a.m_rows)
                    std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    int getValue(int row,int col) {
        if(row >= m_rows | col >= m_cols) {
            std::cout << "Zadana pozice je mimo rozmer matice" << std::endl;
            throw;
        }
        return m_matrixData[row][col];
    }


    friend Matrix operator + (const Matrix &a, const Matrix &b) {
        if(a.m_rows != b.m_rows || a.m_cols != b.m_cols)
            throw;
        Matrix tmp(a.m_rows, a.m_cols);
        for (int i = 0; i < a.m_rows; i++) {
            for (int j = 0; j < a.m_cols; j++) {
                tmp.loadData(i,j,a.m_matrixData[i][j] + b.m_matrixData[i][j] );
            }
        }
        return tmp;
    }

    friend Matrix  operator - (const Matrix &a, const Matrix &b) {
        if(a.m_rows != b.m_rows || a.m_cols != b.m_cols)
            throw;
        Matrix tmp(a.m_rows, a.m_cols);
        for (int i = 0; i < a.m_rows; i++) {
            for (int j = 0; j < a.m_cols; j++) {
                tmp.loadData(i,j,a.m_matrixData[i][j] - b.m_matrixData[i][j] );
            }
        }
        return tmp;
    }

    void operator * () {

    }
};



int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}