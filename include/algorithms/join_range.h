#ifndef UTILITIES_JOIN_RANGE_H
#define UTILITIES_JOIN_RANGE_H

// Boost's original join is in conflict with other libraries

#include <boost/config.hpp>
#include <boost/range/detail/join_iterator.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/iterator_range.hpp>

namespace utl
{
    namespace view {
        namespace range_detail
        {

            template<class SinglePassRange1, class SinglePassRange2>
            class joined_type
            {
                public:
                    typedef boost::iterator_range<
                        boost::range_detail::join_iterator<
                            BOOST_DEDUCED_TYPENAME boost::range_iterator<SinglePassRange1>::type,
                            BOOST_DEDUCED_TYPENAME boost::range_iterator<SinglePassRange2>::type,
                            BOOST_DEDUCED_TYPENAME boost::range_value<SinglePassRange1>::type
                    >
                    > type;
            };

        } // namespace range_detail

        namespace range
        {

            template<class SinglePassRange1, class SinglePassRange2>
            class joined_range
                    : public range_detail::joined_type<SinglePassRange1, SinglePassRange2>::type
            {
                    typedef boost::range_detail::join_iterator<
                            BOOST_DEDUCED_TYPENAME boost::range_iterator<SinglePassRange1>::type,
                            BOOST_DEDUCED_TYPENAME boost::range_iterator<SinglePassRange2>::type,
                            BOOST_DEDUCED_TYPENAME boost::range_value<SinglePassRange1>::type
                    > iterator_t;

                    typedef BOOST_DEDUCED_TYPENAME range_detail::joined_type<
                            SinglePassRange1, SinglePassRange2>::type base_t;
                public:
                    joined_range(SinglePassRange1& rng1, SinglePassRange2& rng2)
                            : base_t(
                            iterator_t(rng1, rng2, boost::range_detail::join_iterator_begin_tag()),
                            iterator_t(rng1, rng2, boost::range_detail::join_iterator_end_tag())
                    )
                    {
                    }
            };

            template<class SinglePassRange1, class SinglePassRange2>
            joined_range<const SinglePassRange1, const SinglePassRange2>
            join(const SinglePassRange1& r1, const SinglePassRange2& r2)
            {
                BOOST_RANGE_CONCEPT_ASSERT(( boost::SinglePassRangeConcept<SinglePassRange1> ));
                BOOST_RANGE_CONCEPT_ASSERT(( boost::SinglePassRangeConcept<SinglePassRange2> ));

                return joined_range<const SinglePassRange1, const SinglePassRange2>(r1, r2);
            }

            template<class SinglePassRange1, class SinglePassRange2>
            joined_range<SinglePassRange1, SinglePassRange2>
            join(SinglePassRange1& r1, SinglePassRange2& r2)
            {
                BOOST_RANGE_CONCEPT_ASSERT(( boost::SinglePassRangeConcept<SinglePassRange1> ));
                BOOST_RANGE_CONCEPT_ASSERT(( boost::SinglePassRangeConcept<SinglePassRange2> ));

                return joined_range<SinglePassRange1, SinglePassRange2>(r1, r2);
            }

        } // namespace range

        using ::utl::view::range::joined_range;
        using ::utl::view::range::join;
    }

} // namespace utl


#endif //UTILITIES_JOIN_RANGE_H
