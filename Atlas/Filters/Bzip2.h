// This file may be redistributed and modified only under the terms of
// the GNU Lesser General Public License (See COPYING for details).
// Copyright (C) 2000 Stefanus Du Toit, Dmitry Derevyanko

#ifndef ATLAS_FILTERS_BZIP2_H
#define ATLAS_FILTERS_BZIP2_H

#if defined(HAVE_BZLIB_H) && defined(HAVE_LIBBZ2)

#include <Atlas/Filter.h>

#include <cstdio>

// my version of bzlib.h does not have extern "C" in the header file,
// like it should
// dmitryd 05/08/200
extern "C" {
#include <bzlib.h>
}

namespace Atlas { namespace Filters {

class Bzip2 : public Filter
{
    bz_stream incoming;
    bz_stream outgoing;
    char buf[4096];

    public:

    virtual void begin();
    virtual void end();
    
    virtual std::string encode(const std::string&);
    virtual std::string decode(const std::string&);
};

} } // namespace Atlas::Filters

#endif // HAVE_BZLIB_H && HAVE_LIBBZ2

#endif // ATLAS_FILTERS_BZIP2_H
