#ifndef INCLUDED_JARED_SETUTILS_H
#define INCLUDED_JARED_SETUTILS_H

#include <vector>

template<class bseq_a, class bseq_b, class bseq_c, class ForwardIterator_a, class ForwardIterator_b>
void set_comparison(
        bseq_a& left, 
        bseq_b& right,
        bseq_c& common,
        ForwardIterator_a lhs_first, 
        ForwardIterator_a lhs_end,
        ForwardIterator_b rhs_first,
        ForwardIterator_b rhs_end
)
{
//    int a = 0, b = 0;

    ForwardIterator_a a = lhs_first;
    ForwardIterator_b b = rhs_first;
    
//    while(a < lhs.size() && b < rhs.size())
    while(a != lhs_end && b != rhs_end)
    {
//        if (lhs[a] < rhs[b])
        if (*a < *b)
        {
//            left.push_back(lhs[a]);
            left.push_back(*a);
            ++a;
        }
//        else if (lhs[a] == rhs[b])
        else if (*a == *b)
        {
//            common.push_back(lhs[a]);
            common.push_back(*a);
            ++a;
            ++b;
        }
        else // lhs[a] > rhs[b]
        {
//            right.push_back(rhs[b]);
            right.push_back(*b);
            ++b;
        }
    }

    for(; a != lhs_end;++a)
    {
        left.push_back(*a);
    }

    for(; b < rhs_end;++b)
    {
        right.push_back(*b);
    }
}

#endif // INCLUDED_JARED_SETUTILS_H
