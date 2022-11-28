#include <vector>
#include <climits>

template <typename Type>
Type* TournamentSort(Type* Arr, const int N) //Tournament sort for arrays
{
    int sizeB = N, sizeM = 2 * N;
    Type* B = new Type[sizeB];
    Type* m1 = new Type[sizeM];
    int* m2 = new int[sizeM];
    int i, j, index;
    for (i = N; i <= 2 * N - 1; i++)
    {
        m1[i] = Arr[i - N];
        m2[i] = i;
    }
    for (i = N - 1; i > 0; i--)
    {
        if (m1[2 * i] <= m1[2 * i + 1])
        {
            m1[i] = m1[2 * i];  m2[i] = m2[2 * i];
        }
        else { m1[i] = m1[2 * i + 1]; m2[i] = m2[2 * i + 1]; }
    }
    for (j = 0; j < N; j++)
    {
        B[j] = m1[1];
        index = m2[1];
        m1[index] = INT_MAX;
        index = index / 2;
        while (index > 0)
        {
            if (m1[2 * index] <= m1[2 * index + 1])
            {
                m1[index] = m1[2 * index];  m2[index] = m2[2 * index];
            }
            else { m1[index] = m1[2 * index + 1]; m2[index] = m2[2 * index + 1]; }
            index = index / 2;
        }
    }
    return B;
}
template <typename T>
void TournamentSort(std::vector<T>&sortVector,int N) // Tournament sort for vectors
{
    std::vector<T>B(N);
    std::vector<T>m1(2 * N);
    std::vector<int>m2(2 * N);
    int i, j;

    for (i = N; i <= 2 * N - 1; i++)
    {
        m1[i] = sortVector[i - N];
        m2[i] = i;
    }
    for (i = N - 1; i > 0; i--)
    {
        if (m1[2 * i] <= m1[2 * i + 1])
        {
            m1[i] = m1[2 * i];  m2[i] = m2[2 * i];
        }
        else { m1[i] = m1[2 * i + 1]; m2[i] = m2[2 * i + 1]; }
    }
    for (j = 0; j < N; j++)
    {
        B[j] = m1[1]; i = m2[1]; m1[i] = INT_MAX;
        i = i / 2;
        while (i > 0)
        {
            if (m1[2 * i] <= m1[2 * i + 1])
            {
                m1[i] = m1[2 * i];  m2[i] = m2[2 * i];
            }
            else { m1[i] = m1[2 * i + 1]; m2[i] = m2[2 * i + 1]; }
            i = i / 2;
        }
    }
    sortVector = B;
}
