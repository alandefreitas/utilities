#ifndef UTILITIES_RANGE_CXX11_ALGORITHMS_RANGE_H
#define UTILITIES_RANGE_CXX11_ALGORITHMS_RANGE_H

// These algorithms from the boost library are in conflict with ::std and ::range
// because they define the original function (most of them are in ::std now)
// and the range function (many of them are already in ::range)

// This header implements only the algorithms that are not in the STL
// It also implements all range versions because many of them are not in ::range
// The ones that are in ::range are individually imported in algorithm_utils.h

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace utl {
    template<typename Range, typename Predicate>
    bool all_of ( const Range &r, Predicate p )
    {
        return std::all_of ( boost::begin (r), boost::end (r), p );
    }

    template<typename InputIterator, typename T>
    bool all_of_equal ( InputIterator first, InputIterator last, const T &val )
    {
        for ( ; first != last; ++first )
            if ( val != *first )
                return false;
        return true;
    }

    template<typename Range, typename T>
    bool all_of_equal ( const Range &r, const T &val )
    {
        return utl::all_of_equal ( boost::begin (r), boost::end (r), val );
    }

    template<typename Range, typename Predicate>
    bool any_of ( const Range &r, Predicate p )
    {
        return std::any_of (boost::begin (r), boost::end (r), p);
    }

    template<typename InputIterator, typename V>
    bool any_of_equal ( InputIterator first, InputIterator last, const V &val )
    {
        for ( ; first != last; ++first )
            if ( val == *first )
                return true;
        return false;
    }

    template<typename Range, typename V>
    bool any_of_equal ( const Range &r, const V &val )
    {
        return utl::any_of_equal (boost::begin (r), boost::end (r), val);
    }

    template<typename Range, typename OutputIterator, typename Predicate>
    OutputIterator copy_if ( const Range &r, OutputIterator result, Predicate p )
    {
        return std::copy_if (boost::begin (r), boost::end(r), result, p);
    }

    template<typename InputIterator, typename OutputIterator, typename Predicate>
    std::pair<InputIterator, OutputIterator>
    copy_while ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
    {
        for ( ; first != last && p(*first); ++first )
            *result++ = *first;
        return std::make_pair(first, result);
    }

    template<typename Range, typename OutputIterator, typename Predicate>
    std::pair<typename boost::range_iterator<const Range>::type, OutputIterator>
    copy_while ( const Range &r, OutputIterator result, Predicate p )
    {
        return utl::copy_while (boost::begin (r), boost::end(r), result, p);
    }

    template<typename InputIterator, typename OutputIterator, typename Predicate>
    std::pair<InputIterator, OutputIterator>
    copy_until ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
    {
        for ( ; first != last && !p(*first); ++first )
            *result++ = *first;
        return std::make_pair(first, result);
    }

    template<typename Range, typename OutputIterator, typename Predicate>
    std::pair<typename boost::range_iterator<const Range>::type, OutputIterator>
    copy_until ( const Range &r, OutputIterator result, Predicate p )
    {
        return utl::copy_until (boost::begin (r), boost::end(r), result, p);
    }

    template<typename Range, typename Predicate>
    typename boost::range_iterator<const Range>::type find_if_not ( const Range &r, Predicate p )
    {
        return std::find_if_not (boost::begin (r), boost::end(r), p);
    }

    //template <typename ForwardIterator, typename T>
    //void iota ( ForwardIterator first, ForwardIterator last, T value )
    //{
    //    for ( ; first != last; ++first, ++value )
    //        *first = value;
    //}

    template <typename Range, typename UnaryPredicate>
    bool is_partitioned ( const Range &r, UnaryPredicate p )
    {
        return std::is_partitioned (boost::begin(r), boost::end(r), p);
    }

    template <typename Range, typename ForwardIterator>
    bool is_permutation ( const Range &r, ForwardIterator first2 )
    {
        return std::is_permutation (boost::begin (r), boost::end (r), first2 );
    }

    template <typename R, typename Pred>
    typename boost::lazy_disable_if_c<
            boost::is_same<R, Pred>::value,
            typename boost::range_iterator<const R>
    >::type is_sorted_until ( const R &range, Pred p )
    {
        return std::is_sorted_until ( boost::begin ( range ), boost::end ( range ), p );
    }

    template <typename R>
    typename boost::range_iterator<const R>::type is_sorted_until ( const R &range )
    {
        return std::is_sorted_until ( boost::begin ( range ), boost::end ( range ));
    }

    template <typename R, typename Pred>
    typename boost::lazy_disable_if_c< boost::is_same<R, Pred>::value, boost::mpl::identity<bool> >::type
    is_sorted ( const R &range, Pred p )
    {
        return std::is_sorted ( boost::begin ( range ), boost::end ( range ), p );
    }

    template <typename R>
    bool is_sorted ( const R &range )
    {
        return std::is_sorted ( boost::begin ( range ), boost::end ( range ));
    }

    template <typename ForwardIterator>
    bool is_increasing ( ForwardIterator first, ForwardIterator last )
    {
        typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
        return std::is_sorted (first, last, std::less<value_type>());
    }

    template <typename R>
    bool is_increasing ( const R &range )
    {
        return is_increasing ( boost::begin ( range ), boost::end ( range ));
    }


    template <typename ForwardIterator>
    bool is_decreasing ( ForwardIterator first, ForwardIterator last )
    {
        typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
        return std::is_sorted (first, last, std::greater<value_type>());
    }

    template <typename R>
    bool is_decreasing ( const R &range )
    {
        return is_decreasing ( boost::begin ( range ), boost::end ( range ));
    }

    template <typename ForwardIterator>
    bool is_strictly_increasing ( ForwardIterator first, ForwardIterator last )
    {
        typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
        return std::is_sorted (first, last, std::less_equal<value_type>());
    }

    template <typename R>
    bool is_strictly_increasing ( const R &range )
    {
        return is_strictly_increasing ( boost::begin ( range ), boost::end ( range ));
    }

    template <typename ForwardIterator>
    bool is_strictly_decreasing ( ForwardIterator first, ForwardIterator last )
    {
        typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
        return std::is_sorted (first, last, std::greater_equal<value_type>());
    }

    template <typename R>
    bool is_strictly_decreasing ( const R &range )
    {
        return is_strictly_decreasing ( boost::begin ( range ), boost::end ( range ));
    }

    template<typename Range, typename Predicate>
    bool none_of ( const Range &r, Predicate p )
    {
        return std::none_of (boost::begin (r), boost::end (r), p );
    }

    template<typename InputIterator, typename V>
    bool none_of_equal ( InputIterator first, InputIterator last, const V &val )
    {
        for ( ; first != last; ++first )
            if ( val == *first )
                return false;
        return true;
    }

    template<typename Range, typename V>
    bool none_of_equal ( const Range &r, const V & val )
    {
        return utl::none_of_equal (boost::begin (r), boost::end (r), val);
    }

    template <typename Range, typename OutputIterator1, typename OutputIterator2,
            typename UnaryPredicate>
    std::pair<OutputIterator1, OutputIterator2>
    partition_copy ( const Range &r, OutputIterator1 out_true, OutputIterator2 out_false,
                     UnaryPredicate p )
    {
        return std::partition_copy
                (boost::begin(r), boost::end(r), out_true, out_false, p );
    }

    template <typename Range, typename Predicate>
    typename boost::range_iterator<Range>::type partition_point ( Range &r, Predicate p )
    {
        return std::partition_point (boost::begin(r), boost::end(r), p);
    }

}


#endif //UTILITIES_RANGE_CXX11_ALGORITHMS_RANGE_H
