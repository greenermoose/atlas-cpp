// This file may be redistributed and modified only under the terms of
// the GNU Lesser General Public License (See COPYING for details).
// Copyright (C) 2000 Michael Day

#ifndef ATLAS_STREAM_FACTORY_H
#define ATLAS_STREAM_FACTORY_H

#include <string>
#include <list>
#include <algorithm>

namespace Atlas { namespace Stream {

/** Class factory

Factory is a template class for automatic registration, construction and
destruction of particular classes. It is used by creating a static instance
for each class that requires it. Each registered class specifies a name and
Metrics (can be any class) that is used when enumerating the classes for the
purposes of negotiation. Each class also declares a Parameters structure,
which is passed to the constructor of the class at creation time by the
factory.

Both Codec and Filter specialise Factory and use it for class registration.

@see Codec
@see Filter
@see Negotiate
*/

template <typename T>
class Factory
{
    public:

    Factory(const std::string& name, const typename T::Metrics& metrics)
     : name(name), metrics(metrics)
    {
	Factories().push_back(this);
    }
    
    virtual ~Factory()
    {
	std::list<Factory*>::iterator i;
	i = std::find(Factories().begin(), Factories().end(), this);
	Factories().erase(i);
    }
    
    virtual T* New(const typename T::Parameters&) = 0;
    virtual void Delete(T*) = 0;

    std::string GetName()
    {
	return name;
    }
    
    typename T::Metrics GetMetrics()
    {
	return metrics;
    }
   
    static std::list<Factory*>& Factories()
    {
	static std::list<Factory*> factories;
	return factories;
    }

    protected:

    std::string name;
    typename T::Metrics metrics;
};

} } // Atlas::Stream

#endif
