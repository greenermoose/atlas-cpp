// This file may be redistributed and modified only under the terms of
// the GNU Lesser General Public License (See COPYING for details).
// Copyright (C) 2000 Stefanus Du Toit

// Much inspiration, the original idea and name suggestion by Mike Day.

#ifndef ATLAS_FUNKY_ENCODER_H
#define ATLAS_FUNKY_ENCODER_H

#include <string>

namespace Atlas { namespace Funky {

/** Atlas funky encoder

@see Bridge
*/

class BeginMessage {};
class EndMessage {};
class BeginMap {};
class EndMap {};
class BeginList {};
class EndList {};

template<class B> class Encoder;
template<class B, class T> class EncMap;
template<class B, class T> class EncList;
template<class B, class T> class EncMapValue;

template<class B, class T>
class EncMapValue {
public:
    EncMapValue(B& b, const string& name) : b(b), name(name) { }
    
    EncMap<B, T> operator<<(const BeginMap&)
    {
        b.MapItem(name, B::MapBegin);
        return EncMap<B, T>(b);
    }

    EncList<B, T> operator<<(const BeginList&)
    {
        b.MapItem(name, B::ListBegin);
        return EncList<B, T>(b);
    }

    T operator<<(int i)
    {
        b.MapItem(name, i);
        return T(b);
    }

    T operator<<(double d)
    {
        b.MapItem(name, d);
        return T(b);
    }

    T operator<<(const string& s)
    {
        b.MapItem(name, s);
        return T(b);
    }

protected:
    B& b;
    string name;
};

template<class B, class T>
class EncMap {
public:
    EncMap(B& b) : b(b) { }

    EncMapValue< B, EncMap<B, T> > operator<<(const string& name)
    {
        return EncMapValue< B, EncMap<B, T> >(b, name);
    }

    T operator<<(EndMap)
    {
        b.MapEnd();
        return T(b);
    }
    
protected:
    B& b;
};

template<class B, class T>
class EncList {
public:
    EncList(B& b) : b(b) { }

    EncMap<B, EncList<B, T> > operator<<(const BeginMap&)
    {
        b.ListItem(B::MapBegin);
        return EncMap<B, EncList<B, T> >(b);
    }

    EncList<B, EncList<B, T> > operator<<(const BeginList&)
    {
        b.ListItem(B::ListBegin);
        return EncList<B, EncList<B, T> >(b);
    }

    EncList<B, T> operator<<(int i)
    {
        b.ListItem(i);
        return *this;
    }

    EncList<B, T> operator<<(double d)
    {
        b.ListItem(d);
        return *this;
    }

    EncList<B, T> operator<<(const std::string& s)
    {
        b.ListItem(s);
        return *this;
    }
    
    T operator<<(EndList)
    {
        b.ListEnd();
        return T(b);
    }
    
protected:
    B& b;
};

template <class B>
class Encoder
{
public:
    Encoder(B& b) : b(b) { }
    
    EncMap<B, Encoder> operator<<(const BeginMap&) {
        b.StreamMessage(B::MapBegin);
        return EncMap<B, Encoder>(b);
    }

protected:
    B& b;
};

class Tokens {
public:

    static BeginMap begin_map;
    static EndMap end_map;
    static BeginList begin_list;
    static EndList end_list;
};


} } // Atlas::Funky namespace

#endif