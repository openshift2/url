//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#ifndef BOOST_URL_RFC_IMPL_SEGMENT_IPP
#define BOOST_URL_RFC_IMPL_SEGMENT_IPP

#include <boost/url/rfc/segment.hpp>
#include <boost/url/error.hpp>
#include <boost/url/string.hpp>
#include <boost/url/bnf/algorithm.hpp>
#include <boost/url/rfc/char_sets.hpp>

namespace boost {
namespace urls {
namespace rfc {

class segment_nz_nc::pchar_nc
{
public:
    using value_type = string_view;

    value_type const&
    operator*() const noexcept
    {
        return s_;
    }

    value_type const*
    operator->() const noexcept
    {
        return &s_;
    }

    char const*
    parse(
        char const* const start,
        char const* const end,
        error_code& ec)
    {
        auto it = start;
        for(;;)
        {
            if(it == end)
            {
                ec = error::need_more;
                return start;
            }
            if(is_unreserved(*it))
            {
                ++it;
                break;
            }
            if(is_sub_delims(*it))
            {
                ++it;
                break;
            }
            if(*it == '@')
            {
                ++it;
                break;
            }
            it = bnf::consume<
                pct_encoded0>(
                    it, end, ec);
            if(ec)
                return start;
            break;
        }
        s_ = string_view(
            start, it - start);
        return it;
    }

private:
    string_view s_;
};

char const*
segment_nz_nc::
parse(
    char const* const start,
    char const* const end,
    error_code& ec)
{
    auto it = bnf::consume<
        bnf::one_or_more<pchar_nc>>(
            start, end, ec);
    if(ec)
        return start;
    s_ = string_view(
        start, it - start);
    return it;
}

} // rfc
} // urls
} // boost

#endif
