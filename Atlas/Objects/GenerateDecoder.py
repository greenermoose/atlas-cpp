#This file is distributed under the terms of 
#the GNU Lesser General Public license (See the file COPYING for details).
#Copyright (C) 2000 Aloril

#just used to partition gen_cpp.py into files, 
#not usable without GenerateCC class

from common import *

class GenerateDecoder:
    def generate_decoder(self, objects):
        self.generate_decoder_interface(objects)
        self.generate_decoder_implementation(objects)

    def generate_decoder_interface(self, objects):
        #print "Output of implementation for:",
        outfile = self.outdir + '/Decoder.h'
        #print outfile
        self.out = open(outfile + ".tmp", "w")
        header_list = ['Atlas', 'Objects', 'Decoder', 'H']
        self.header(header_list)
        self.write("""
#include <Atlas/Message/DecoderBase.h>

#include <Atlas/Objects/Root.h>

""") #"for xemacs syntax highlighting
        self.ns_open(self.base_list)
        self.write("""
/** Objects hierarchy decoder
 *
 * This decoder can be bound to a codec, will assemble incoming messages,
 * check their type, convert them into the appropriate instance in the
 * Objects hierarchy and call the relevant member functions, which
 * subclasses can conveniently override to pick up the object.
 *
 * @see Atlas::Objects::Encoder
 * @author Stefanus Du Toit <sdt@gmx.net>
 */
class ObjectsDecoder : public Atlas::Message::DecoderBase
{
public:
    /// Default destructor.
    virtual ~ObjectsDecoder();
protected:
    /// Overridden by Objects::Decoder to retrieve the object.
    virtual void messageArrived(const Atlas::Message::MapType&);

    /// An unknown object has arrived.
    virtual void unknownMessageArrived(const Atlas::Message::Element&);

    /// call right object*Arrived method
    virtual void objectArrived(const Root& obj) = 0;

""") #"for xemacs syntax highlighting
        #for (obj, namespace) in objects:
        #    id = obj.id
        #    idc = classize(id)
        #    self.write("    virtual void object%sArrived(const %s%s&) { }\n" %
        #               (classize(obj.id), namespace, classize(obj.id)))
        self.write("};\n\n")
        self.ns_close(self.base_list)
        self.footer(header_list)
        self.out.close()
        self.update_outfile(outfile)


    def generate_decoder_implementation(self, objects):
        #print "Output of implementation for:",
        outfile = self.outdir + '/Decoder.cpp'
        #print outfile
        self.out = open(outfile + ".tmp", "w")
        self.write(copyright)
        self.write('\n#include <Atlas/Objects/Decoder.h>\n')
        self.write('\n#include <Atlas/Objects/objectFactory.h>\n\n')
        self.ns_open(self.base_list)
        self.write("""
ObjectsDecoder::~ObjectsDecoder()
{
}

void ObjectsDecoder::messageArrived(const Atlas::Message::MapType& o)
{
    Root obj =  messageElement2ClassObject(o);
    objectArrived(obj);
}

void ObjectsDecoder::unknownMessageArrived(const Atlas::Message::Element&)
{
}

""") #"for xemacs syntax highlighting
        self.ns_close(self.base_list)
        self.out.close()
        self.update_outfile(outfile)
