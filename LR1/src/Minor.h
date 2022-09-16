#include <map>
using namespace std;

inline double Minor(map<int, map<int, double>> matrix, int N, int k) {
	
	double det = 0;

	//if (cache[deep][k][] != 0) return cache[deep][k][];

	if (N == 2) return det = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];

	map<int, map<int, double>> Tmatrix;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {

			Tmatrix[i][j] = matrix[i][j];

		}
	}

	//PrintMat(Tmatrix, N);
	//printf("\n");

	for (int k = 1; k <= N; k++) {

		for (int i = 1; i < N; i++) {
			for (int j = 1; j < N; j++) {

				(j >= k) ? matrix[i][j] = matrix[i + 1][j + 1] : matrix[i][j] = matrix[i + 1][j];

			}
		}

		//PrintMat(matrix, N);
		//printf("--------------------------------------\n");

		Tmatrix[1][k] *= (k % 2 == 0) ? -1 : 1;
		det += Tmatrix[1][k] * Minor(matrix, N - 1, k);

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {

				matrix[i][j] = Tmatrix[i][j];

			}
		}
	}

	//cache[deep][k][] = det;

	return det;
}