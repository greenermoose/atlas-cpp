// This file may be redistributed and modified under the terms of the
// GNU Lesser General Public License (See COPYING for details).
// Copyright (C) 2000 Michael Day

// $Log$
// Revision 1.9  2000-02-21 11:49:49  mike
// Added change log
//

#ifndef ATLAS_STREAM_ENCODER_H
#define ATLAS_STREAM_ENCODER_H

#include "Filter.h"
#include "../Object/Object.h"

namespace Atlas
{
    namespace Stream
    {
	class Encoder;
    }
}

class Atlas::Stream::Encoder
{
    public:

    virtual ~Encoder() { }

    enum Container
    {
	LIST,
	MAP,
    };
    
    virtual void Begin(Container) = 0;
    virtual void Begin(const std::string& name, Container) = 0;
    
    virtual void End() = 0;
    
    virtual void Send(int) = 0;
    virtual void Send(float) = 0;
    virtual void Send(const std::string&) = 0;
    virtual void Send(const Object&) = 0;
	
    virtual void Send(const std::string& name, int) = 0;
    virtual void Send(const std::string& name, float) = 0;
    virtual void Send(const std::string& name, const std::string&) = 0;
    virtual void Send(const std::string& name, const Object&) = 0;
};

#endif