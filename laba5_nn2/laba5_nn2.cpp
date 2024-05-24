#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> 

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    unsigned int rows, cols;

public:
    Matrix(unsigned int rows, unsigned int cols) : rows(rows), cols(cols) {
        data.resize(rows, std::vector<T>(cols));
    }

    T& operator()(unsigned int i, unsigned int j) {
        return data[i][j];
    }

    unsigned int getRows() const {
        return rows;
    }

    unsigned int getCols() const {
        return cols;
    }

    void fillRandom() {
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < cols; ++j) {
                data[i][j] = static_cast<T>(rand() % 100); // Заполнение случайными значениями
            }
        }
    }

    void print() {
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Добавим методы для сериализации/десериализации объектов Matrix
    void serialize(std::ostream& out) const {
        for (const auto& row : data) {
            for (const auto& element : row) {
                out << element << " ";
            }
            out << std::endl;
        }
    }

    void deserialize(std::istream& in) {
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < cols; ++j) {
                in >> data[i][j];
            }
        }
    }
};

int main() {
    // Создаем несколько объектов Matrix для записи
    std::vector<Matrix<int>> matrices = { Matrix<int>(3, 3), Matrix<int>(2, 2) };

    // Запись в текстовый файл
    std::ofstream textFile("matrices.txt");
    if (textFile.is_open()) {
        for (const auto& matrix : matrices) {
            matrix.serialize(textFile);
            textFile << std::endl;
        }
        textFile.close();
    }
    else {
        std::cerr << "Error opening text file for writing." << std::endl;
    }

    // Считывание из текстового файла
    std::ifstream textReadFile("matrices.txt");
    if (textReadFile.is_open()) {
        std::vector<Matrix<int>> readMatrices;
        for (const auto& matrix : matrices) {
            Matrix<int> tempMatrix(matrix.getRows(), matrix.getCols());
            tempMatrix.deserialize(textReadFile);
            readMatrices.push_back(tempMatrix);
        }
        textReadFile.close();
    }
    else {
        std::cerr << "Error opening text file for reading." << std::endl;
    }

    // Запись в бинарный файл
    std::ofstream binaryFile("matrices.bin", std::ios::binary);
    if (binaryFile.is_open()) {
        for (const auto& matrix : matrices) {
            binaryFile.write(reinterpret_cast<const char*>(&matrix), sizeof(Matrix<int>));
        }
        binaryFile.close();
    }
    else {
        std::cerr << "Error opening binary file for writing." << std::endl;
    }

    // Считывание из бинарного файла
    std::ifstream binaryReadFile("matrices.bin", std::ios::binary);
    if (binaryReadFile.is_open()) {
        std::vector<Matrix<int>> readMatricesBin;
        Matrix<int> tempMatrix(0, 0);
        while (binaryReadFile.read(reinterpret_cast<char*>(&tempMatrix), sizeof(Matrix<int>))) {
            readMatricesBin.push_back(tempMatrix);
        }
        binaryReadFile.close();
    }
    else {
        std::cerr << "Error opening binary file for reading." << std::endl;
    }

    return 0;
}