// This file may be redistributed and modified under the terms of the
// GNU Lesser General Public License (See COPYING for details).
// Copyright (C) 2000 Michael Day

#include <iostream>

#include "Utility.h"
#include "../Codec.h"

using namespace std;
using namespace Atlas;

/*

    FIXME documentation forthcoming

*/

class XMLish : public Codec
{
    public:

    XMLish(const Codec::Parameters&);

    virtual void poll(bool can_read = true);

    virtual void streamBegin();
    virtual void streamMessage(const Map&);
    virtual void streamEnd();

    virtual void mapItem(const std::string& name, const Map&);
    virtual void mapItem(const std::string& name, const List&);
    virtual void mapItem(const std::string& name, int);
    virtual void mapItem(const std::string& name, double);
    virtual void mapItem(const std::string& name, const std::string&);
    virtual void mapEnd();
    
    virtual void listItem(const Map&);
    virtual void listItem(const List&);
    virtual void listItem(int);
    virtual void listItem(double);
    virtual void listItem(const std::string&);
    virtual void listEnd();

    protected:

    iostream& socket;
    Bridge* bridge;
};

namespace
{
    /*
        We're not going to enable this sucker until it actually works.
    
    Codec<iostream>::Factory<XMLish> factory(
	"XMLish",				    // name
	Codec<iostream>::Metrics(1, 2)		    // metrics
    );

    */
}
    
XMLish::XMLish(const Codec::Parameters& p)
    : socket(p.stream), bridge(p.bridge)
{
}

void XMLish::poll(bool can_read = true)
{
    if (!can_read) return;
    do
    {
	char next = socket.get();

	// FIXME handle incoming characters
    }
    while (socket.rdbuf()->in_avail());
}

void XMLish::streamBegin()
{
    socket << "<atlas>";
}

void XMLish::streamMessage(const Map&)
{
    socket << "<map>";
}

void XMLish::streamEnd()
{
    socket << "</atlas>";
}

void XMLish::mapItem(const std::string& name, const Map&)
{
    socket << "<map name=\"" << name << "\">";
}

void XMLish::mapItem(const std::string& name, const List&)
{
    socket << "<list name=\"" << name << "\">";
}

void XMLish::mapItem(const std::string& name, int data)
{
    socket << "<int name=\"" << name << "\">" << data << "</int>";
}

void XMLish::mapItem(const std::string& name, double data)
{
    socket << "<float name=\"" << name << "\">" << data << "</float>";
}

void XMLish::mapItem(const std::string& name, const std::string& data)
{
    socket << "<string name=\"" << name << "\">" << data << "</string>";
}

void XMLish::mapEnd()
{
    socket << "</map>";
}

void XMLish::listItem(const Map&)
{
    socket << "<map>";
}

void XMLish::listItem(const List&)
{
    socket << "<list>";
}

void XMLish::listItem(int data)
{
    socket << "<int>" << data << "</int>";
}

void XMLish::listItem(double data)
{
    socket << "<float>" << data << "</float>";
}

void XMLish::listItem(const std::string& data)
{
    socket << "<string>" << data << "</string>";
}

void XMLish::listEnd()
{
    socket << "</list>";
}
