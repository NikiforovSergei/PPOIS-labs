#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Matrix {
public:
    //matrix constructors
    Matrix() {

    }
    Matrix(int row_amount, int column_amount) {
        matrix.resize(row_amount);
        for (int i = 0; i < row_amount; i++) {
            matrix[i].resize(column_amount);
        }
        for (int i = 0; i < row_amount; i++) {
            for (int j = 0; j < column_amount; j++) {
                matrix[i][j] = 0;
            }
        }
    }
    Matrix(const Matrix& reference_matrix) {
        this->matrix = reference_matrix.matrix;
    }
    Matrix(std::initializer_list<std::vector<double>> _input) : matrix(_input) {};

    //matrix resize
    /// \brief Resize matrix
    /// \param row_amount New row amount
    /// \param column_amount New column amount
    void matrix_resize(int row_amount, int column_amount) {
        matrix.resize(row_amount);
        for (int i = 0; i < row_amount; i++) {
            matrix[i].resize(column_amount);
        }
    }
    ///

    //prefix operators
    /// \brief Prefix ++
    /// \param
    Matrix& operator ++() {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                ++matrix[i][j];
            }
        }
        return *this;
    }
    ///

    /// \brief Prefix --
    Matrix& operator --() {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                --matrix[i][j];
            }
        }
        return *this;
    }
    ///

    //postfix operators
    /// \brief Postfix --
    Matrix operator ++(int) {
        Matrix prev_matrix(*this);
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                ++matrix[i][j];
            }
        }
        return prev_matrix;
    }
    ///

    /// \brief Postfix --
    Matrix operator --(int) {
        Matrix prev_matrix(*this);
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                --matrix[i][j];
            }
        }
        return prev_matrix;
    }
    ///

    //comparison operators
    /// \brief Compares two matrixes by elements. Returns true if equal
    /// \param other Reference to other matrix
    bool operator==(const Matrix& other) {
        if (matrix.size() != other.matrix.size() || matrix[0].size() != other.matrix[0].size()) {
            return false;
        }
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] != other.matrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    ///

    /// \brief Compares two matrixes by elements. Returns false if equal
    /// \param other Reference to other matrix
    bool operator!=(const Matrix& other) {
        if (matrix.size() != other.matrix.size() || matrix[0].size() != other.matrix[0].size()) {
            return true;
        }
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] != other.matrix[i][j]) {
                    return true;
                }
            }
        }
        return false;
    }
    ///

    //operator ()
    /// \brief Extracts element from matrix
    /// \param row_num Row number
    /// \param col_num Column number
    double operator()(const int& row_num, const int& col_num) {
        return matrix[row_num - 1][col_num - 1];
    }
    std::vector<double> operator()(const int& row_num) {
        return matrix[row_num - 1];
    }
    ///

    //operator =
    /// \brief Provides matrix initialization using standard two-dimensional array initialization
    /// \param _input Standard two-dimensional array initializer
    Matrix& operator=(std::initializer_list<std::vector<double>>& _input) {
        matrix = std::vector<std::vector<double>>{ _input };
        return *this;
    }
    ///

    //transposition
    /// \brief Transposes matrix
    void transpose() {
        Matrix matrix_copy(*this);
        matrix.clear();
        matrix.resize(matrix_copy.matrix[0].size());
        for (int i = 0; i < matrix.size(); i++) {
            matrix[i].resize(matrix_copy.matrix.size());
        }
        for (int i = 0; i < matrix_copy.matrix[0].size(); i++) {
            for (int j = 0; j < matrix_copy.matrix.size(); j++) {
                matrix[i][j] = matrix_copy.matrix[j][i];
            }
        }
    }
    ///

    //output realization
    /// \brief << operator overload
    friend std::ostream& operator<<(std::ostream& os, Matrix& matrix) {
        std::string matrix_output = "";
        for (auto& row : matrix.matrix) {
            std::string row_output = "[";
            for (auto elem : row) {
                row_output += std::to_string(elem);
                row_output += " ";
            }
            if (row_output.size()) row_output.pop_back();
            row_output += "]";
            matrix_output += row_output;
            matrix_output += "\n";
        }
        return os << matrix_output;
    }
    ///

    //input realization
    /// \brief >> operator overloading
    friend std::istream& operator>>(std::istream& is, Matrix& matrix) {
        std::cout << "Enter your matrix\n";
        int row_amount, column_amount;
        std::cout << "Enter matrix sizes(row, column)\n";
        std::cin >> row_amount >> column_amount;
        matrix.matrix.clear();
        matrix.matrix_resize(row_amount, column_amount);
        for (int i = 0; i < row_amount; i++) {
            for (int j = 0; j < column_amount; j++) {
                std::cout << "Enter matrix[" << i + 1 << "][" << j + 1 << "]: ";
                std::cin >> matrix.matrix[i][j];
                std::cout << std::endl;
            }
        }
        return is;
    }
    ///

    //Load matrix from file
    /// \brief Load matrix from file by full path
    /// \param file_path Path to file with matrix
    void load_matrix(std::string file_path) {        
        std::ifstream input_file(file_path);
        std::string line;
        if (!input_file.is_open()) {
            std::cout << "Can't open file!\n";
            return;
        }
        matrix.clear();
        while (std::getline(input_file, line)) {
            line += "#";
            std::vector<double> temp_row;
            std::string temp_num;
            for (auto sym : line) {
                if (isdigit(sym) || sym == '.' || sym == '\n') {
                    temp_num += sym;
                }
                else {                    
                    temp_row.push_back(std::stod(temp_num));
                    temp_num = "";
                }
            }
            matrix.push_back(temp_row);
        }
        input_file.close();        
    }
    ///

    //Define matrix type
    /// \brief Defines matrix type
    /// \param
    std::string matrix_type() {        
        bool is_zero = true;
        for (auto row : matrix) {
            for (double elem : row) {
                if (elem != 0) {
                    is_zero = false;
                    break;
                }                
            }
            if (!is_zero) break;
        }
        if (is_zero) {
            return "Zero Matrix";
        }

        if (matrix.size() == matrix[0].size()) {
            bool is_identity = true;
            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < matrix[i].size(); j++) {
                    if (i == j) {
                        if (matrix[i][j] != 1) {
                            is_identity = false;
                            break;
                        }
                    }
                    else {
                        if (matrix[i][j] != 0) {
                            is_identity = false;
                            break;
                        }
                    }                    
                }
                if (!is_identity) break;
            }
            if (is_identity) return "Identity Matrix";
            bool is_diagonal = true;
            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < matrix[i].size(); j++) {
                    if (i == j) {
                        continue;
                    }
                    else {
                        if (matrix[i][j] != 0) {
                            is_diagonal = false;
                            break;
                        }
                    }
                }
                if (!is_diagonal) break;
            }
            if (is_diagonal) return "Diagonal Matrix";            
            Matrix matrix_copy = *this;
            matrix_copy.transpose();
            if (matrix_copy == *this) {
                return "Symmetrical Matrix";
            }
            bool is_lower_triangular = true;
            for (int i = 0; i < matrix.size(); i++) {
                for (int j = i+1; j < matrix.size(); j++) {
                    if (matrix[i][j] != 0) {
                        is_lower_triangular = false;
                        break;
                    }
                }
                if (!is_lower_triangular) break;
            }
            if (is_lower_triangular) return "Lower Triangular Matrix";
            bool is_upper_triangular = true;
            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < i; j++) {
                    if (matrix[i][j] != 0) {
                        is_upper_triangular = false;
                        break;
                    }
                }
                if (!is_upper_triangular) break;
            }
            if (is_upper_triangular) return "Upper Triangular Matrix";
            return "Squared Matrix";
        }        
        return "Matrix";
    }
    ///

    //submatrix
    /// \brief Extracts submatrix and returns it
    /// \param row_amount Number of rows we want to extract
    /// \param col_amount Number of columns we want to extract
    /// \param start_row Row from which we want to start extracting
    /// \param start_col Column from which we want to start extracting
    Matrix submatrix(const int& row_amount, const int& col_amount, const int& start_row = 1, const int& start_col = 1) {
        if (((start_row + row_amount - 1) > this->matrix.size()) || ((start_col + col_amount - 1) > this->matrix[0].size()) || this->matrix.empty() || this->matrix[0].empty()) {           
            return Matrix();
        }
        std::vector<std::vector<double>> matrix;
        for (int i = start_row - 1; i < row_amount + start_row - 1; i++) {
            std::vector<double> row;
            for (int j = start_col - 1; j < col_amount + start_col - 1; j++) {
                row.push_back(this->matrix[i][j]);
            }
            matrix.push_back(row);
        }
        Matrix return_matrix;
        return_matrix.matrix = matrix;        
        return return_matrix;
    }
    ///
private:
    std::vector<std::vector<double>> matrix;
};