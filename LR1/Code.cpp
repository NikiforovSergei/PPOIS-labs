#include "Header.h"



Matrix::Matrix(int n)
{
    this->n = n;
    ARR = new int*[n];     		
    for(int i = 0; i < n; i++){     
		    ARR[i] = new int[n];  
    } 

    for (int i = 0; i < n; i++)
	  {
		  for (int j = 0; j < n; j++)
		  {
			  ARR[i][j] = arc4random() % 10;
		  }
	  }

}

Matrix Matrix::operator + (Matrix &D)
{

    Matrix T(n);

    for (int i = 0; i < n; i++){

      for (int j = 0; j < n; j++){

        T.ARR[i][j] = this->ARR[i][j] + D.ARR[i][j];
  
                              
      }
    }
    return T;

}
Matrix Matrix::operator + (int number)
{

    Matrix T(n);

    for (int i = 0; i < n; i++){

      for (int j = 0; j < n; j++){

        T.ARR[i][j] = this->ARR[i][j] + number;
  
                              
      }
    }
    return T;

}
Matrix Matrix::operator - (Matrix &D)
{

    Matrix T(n);

    for (int i = 0; i < n; i++){

      for (int j = 0; j < n; j++){

        T.ARR[i][j] = this->ARR[i][j] - D.ARR[i][j];
  
                              
      }
    }
    return T;

}
Matrix Matrix::operator - (int number)
{

    Matrix T(n);

    for (int i = 0; i < n; i++){

      for (int j = 0; j < n; j++){

        T.ARR[i][j] = this->ARR[i][j] - number;
  
                              
      }
    }
    return T;

}

void Matrix::print_matrix()
{
    for (int i = 0; i < this->n; i++){
      for (int j = 0; j < this->n; j++){

        cout << this->ARR[i][j] << " ";
      }
      cout <<endl;
    }

    
}
Matrix Matrix::operator * (Matrix &D)
{

    Matrix T(n);

    for (int i = 0; i < n; i++){

      for (int j = 0; j < n; j++){

        T.ARR[i][j] = this->ARR[i][j] * D.ARR[i][j];
  
                              
      }
    }
    return T;

}
Matrix Matrix::operator * (int number)
{

    Matrix T(n);

    for (int i = 0; i < n; i++){

      for (int j = 0; j < n; j++){

        T.ARR[i][j] = this->ARR[i][j] * number;
  
                              
      }
    }
    return T;

}
Matrix Matrix::operator / (int number)
{

    Matrix T(n);

    for (int i = 0; i < n; i++){

      for (int j = 0; j < n; j++){

        T.ARR[i][j] = this->ARR[i][j] / number;
  
                              
      }
    }
    return T;

}
Matrix Matrix::operator ^ (int number)
{

    Matrix T(n);

    for (int i = 0; i < n; i++){

      for (int j = 0; j < n; j++){

        T.ARR[i][j] = pow(this->ARR[i][j], number);
  
                              
      }
    }
    return T;

}

void Matrix::Minor()
{
    int minor, line_sum;

    for (int i = 0; i < n; i++){
      line_sum = 0;
      for (int j = 0; j < n; j++){
        
        line_sum+= this->ARR[i][j];

      }
      if(line_sum>minor){
        minor = line_sum;
      }
    }
    cout << minor << endl;

}

void Matrix::Determinant()
{
    int num1, num2, det = 1, index, total = 1;
    int temp[n + 1];
    for (int i = 0; i < n; i++)
    {
        index = i; // initialize the index
 
        // finding the index which has non zero value
        while (index < n && this->ARR[index][i] == 0)
        {
            index++;
        }
        if (index == n) // if there is non zero element
        {
            // the determinant of matrix as zero
            continue;
        }
        if (index != i)
        {
            // loop for swapping the diagonal element row and
            // index row
            for (int j = 0; j < n; j++)
            {
                swap(this->ARR[index][j], this->ARR[i][j]);
            }
            // determinant sign changes when we shift rows
            // go through determinant properties
            det = det * pow(-1, index - i);
        }
       
        // storing the values of diagonal row elements
        for (int j = 0; j < n; j++)
        {
            temp[j] = this->ARR[i][j];
        }
        // traversing every row below the diagonal element
        for (int j = i + 1; j < n; j++)
        {
            num1 = temp[i]; // value of diagonal element
            num2 = this->ARR[j][i]; // value of next row element
 
            // traversing every column of row
            // and multiplying to every row
            for (int k = 0; k < n; k++)
            {
                // multiplying to make the diagonal
                // element and next row element equal
                this->ARR[j][k] = (num1 * this->ARR[j][k]) - (num2 * temp[k]);
            }
            total = total * num1; // Det(kA)=kDet(A);
        }
    }
    // multiplying the diagonal elements to get determinant
    for (int i = 0; i < n; i++)
    {
        det = det * this->ARR[i][i];
    }
    cout << det / total; // Det(kA)/k=Det(A);
}


