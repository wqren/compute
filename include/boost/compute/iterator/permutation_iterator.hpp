//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_PERMUTATION_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_PERMUTATION_ITERATOR_HPP

#include <string>
#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <boost/compute/functional.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/is_buffer_iterator.hpp>
#include <boost/compute/detail/is_device_iterator.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>
#include <boost/compute/iterator/detail/get_base_iterator_buffer.hpp>

namespace boost {
namespace compute {

// forward declaration for transform_iterator
template<class ElementIterator, class IndexIterator>
class permutation_iterator;

namespace detail {

// helper class which defines the iterator_adaptor super-class
// type for permutation_iterator
template<class ElementIterator, class IndexIterator>
class permutation_iterator_base
{
public:
    typedef ::boost::iterator_adaptor<
        ::boost::compute::permutation_iterator<ElementIterator, IndexIterator>,
        ElementIterator
    > type;
};

template<class ElementIterator, class IndexIterator, class IndexExpr>
struct permutation_iterator_access_expr
{
    typedef typename std::iterator_traits<ElementIterator>::value_type result_type;

    permutation_iterator_access_expr(const ElementIterator &e,
                                     const IndexIterator &i,
                                     const IndexExpr &expr)
        : m_element_iter(e),
          m_index_iter(i),
          m_expr(expr)
    {
    }

    ElementIterator m_element_iter;
    IndexIterator m_index_iter;
    IndexExpr m_expr;
};

template<class ElementIterator, class IndexIterator, class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const permutation_iterator_access_expr<ElementIterator,
                                                                      IndexIterator,
                                                                      IndexExpr> &expr)
{
    return kernel << expr.m_element_iter[expr.m_index_iter[expr.m_expr]];
}

} // end detail namespace

template<class ElementIterator, class IndexIterator>
class permutation_iterator
    : public detail::permutation_iterator_base<ElementIterator,
                                               IndexIterator>::type
{
public:
    typedef typename
        detail::permutation_iterator_base<ElementIterator,
                                          IndexIterator>::type super_type;
    typedef typename super_type::value_type value_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::base_type base_type;
    typedef typename super_type::difference_type difference_type;
    typedef IndexIterator index_iterator;

    permutation_iterator(ElementIterator e, IndexIterator i)
        : super_type(e),
          m_map(i)
    {
    }

    permutation_iterator(const permutation_iterator<ElementIterator,
                                                    IndexIterator> &other)
        : super_type(other),
          m_map(other.m_map)
    {
    }

    permutation_iterator<ElementIterator, IndexIterator>&
    operator=(const permutation_iterator<ElementIterator,
                                         IndexIterator> &other)
    {
        if(this != &other){
            super_type::operator=(other);
            m_map = other.m_map;
        }

        return *this;
    }

    ~permutation_iterator()
    {
    }

    size_t get_index() const
    {
        return super_type::base().get_index();
    }

    const buffer& get_buffer() const
    {
        return detail::get_base_iterator_buffer(*this);
    }

    template<class IndexExpr>
    detail::permutation_iterator_access_expr<ElementIterator,
                                             IndexIterator,
                                             IndexExpr>
    operator[](const IndexExpr &expr) const
    {
        return detail::permutation_iterator_access_expr<ElementIterator,
                                                        IndexIterator,
                                                        IndexExpr>(super_type::base(),
                                                                   m_map,
                                                                   expr);
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        return reference();
    }

private:
    IndexIterator m_map;
};

template<class ElementIterator, class IndexIterator>
inline permutation_iterator<ElementIterator, IndexIterator>
make_permutation_iterator(ElementIterator e, IndexIterator i)
{
    return permutation_iterator<ElementIterator, IndexIterator>(e, i);
}

namespace detail {

// is_device_iterator specialization for permutation_iterator
template<class Iterator>
struct is_device_iterator<
    Iterator,
    typename boost::enable_if<
        boost::is_same<
            permutation_iterator<typename Iterator::base_type,
                                 typename Iterator::index_iterator>,
            typename boost::remove_const<Iterator>::type
        >
    >::type
> : public boost::true_type {};

} // end detail namespace

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_PERMUTATION_ITERATOR_HPP
