#include <iterator>
#include <algorithm>

/**
 * @brief quicksort
 *
 * @tparam ForwardIt iter of sequence
 * @param first iter to begin of sequence
 * @param last iter to end of sequence
 */
template <class ForwardIterator>
void quickSort(ForwardIterator first, ForwardIterator last)
{
    if (first == last)
        return;

    auto nextElement = *std::next(first, std::distance(first, last) / 2);
    auto middle1 = std::partition(first, last, [nextElement](const auto &em)
                                  { return em > nextElement; });
    auto middle2 = std::partition(first, last, [nextElement](const auto &em)
                                  { return em >= nextElement; });

    quickSort(first, middle1);
    quickSort(middle2, last);
}

/**
 * @brief bubble sort algorithm
 *
 * @tparam ForwardIterator
 * @param first iter to first element in sequence
 * @param last iter to last element in sequence
 */
template <typename ForwardIterator>
void bubbleSort(ForwardIterator first, ForwardIterator last)
{
    for (auto sorted = first; first != last; last = sorted)
    {
        sorted = first;
        for (auto current = first, prev = first; ++current != last; ++prev)
        {
            if (*current < *prev)
            {
                std::iter_swap(current, prev);
                sorted = current;
            }
        }
    }
}

/**
 * @brief sorting networks implementation with bubble sort
 * 
 * @tparam ForwardIterator 
 * @param first iter to first element of sequence
 * @param last iter to last element of sequence
 */
template <typename ForwardIterator>
void _sortingNetwork(ForwardIterator first, ForwardIterator last)
{
    for (auto i = first; i != last; i++)
        for (auto j = first; j < i; j++)
            if (*i < *j)
                std::iter_swap(i, j);
}
