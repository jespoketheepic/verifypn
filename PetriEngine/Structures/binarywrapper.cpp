/* 
 * File:   binarywrapper.cpp
 * Author: Peter G. Jensen
 *
 * Created on 10 June 2015, 19:20
 */

#include <sstream>

#include "binarywrapper.h"
namespace ptrie
{
    
    const uchar binarywrapper_t::_masks[8] = {
        static_cast <uchar>(0x80),
        static_cast <uchar>(0x40),
        static_cast <uchar>(0x20),
        static_cast <uchar>(0x10),
        static_cast <uchar>(0x08),
        static_cast <uchar>(0x04),
        static_cast <uchar>(0x02),
        static_cast <uchar>(0x01)
    };
            
    size_t binarywrapper_t::overhead(uint size)
    {
        size = size % 8;
        if (size == 0)
            return 0;
        else
            return 8 - size; 
    }
    
    
    size_t binarywrapper_t::bytes(uint size)
    {
        return (size + overhead(size))/8;
    }
    
    
    binarywrapper_t::binarywrapper_t(uint size)
    {
        _nbytes = (size + overhead(size)) / 8;
        _blob = zallocate(_nbytes);
    }
    
    
    binarywrapper_t::binarywrapper_t(const binarywrapper_t& other, uint offset)
    {
         offset = offset / 8;

        _nbytes = other._nbytes/*.load()*/;
        if (_nbytes > offset)
            _nbytes -= offset;
        else {
            _nbytes = 0;
        }

        _blob = allocate(_nbytes);
        memcpy(raw(), &(other.const_raw()[offset]), _nbytes);
        assert(raw()[0] == other.const_raw()[offset]);
    }
    
    binarywrapper_t::binarywrapper_t
        (uchar* raw, uint size, uint offset, uint encodingsize)
    {
        if(size == 0 || offset >= encodingsize)
        {
            _nbytes = 0;
            _blob = NULL;            
            return;
        }
        
        uint so = size + offset;
        offset = ((so - 1) / 8) - ((size - 1) / 8);

        _nbytes = ((encodingsize + this->overhead(encodingsize)) / 8);
        if (_nbytes > offset)
            _nbytes -= offset;
        else {
            _nbytes = 0;
            _blob = NULL;
            return;
        }

        uchar* tmp = &(raw[offset]);
        if(_nbytes <= __BW_BSIZE__)
        {
            memcpy(const_raw(), tmp, _nbytes);            
        }
        else
        {
            _blob = tmp;
        }
        assert(raw[offset] == const_raw()[0]);

    }
    
    
    binarywrapper_t::binarywrapper_t(uchar* raw, uint size)
    {
        _nbytes = size / 8 + (size % 8 ? 1 : 0);     
        _blob = raw;
        
        if(_nbytes <= __BW_BSIZE__)
            memcpy(const_raw(), raw, _nbytes);
        
//        assert(raw[0] == const_raw()[0]);
    }
    
    
    void binarywrapper_t::copy(const binarywrapper_t& other, uint offset)
    {
        memcpy(&(raw()[offset / 8]), other.const_raw(), other._nbytes);
        assert(other.const_raw()[0] == raw()[0]);
    }
    
    
    void binarywrapper_t::copy(const uchar* data, uint size)
    {
        if(size > 0)
        {
            assert(false);
            _blob = allocate(size);
            memcpy(raw(), data, size);
            assert(data[0] == raw()[0]);
        }
    }
        
    // accessors
    
    void binarywrapper_t::print(size_t length) const
    {
        std::stringstream ss;
        for (size_t i = 0; i < _nbytes * 8 && i < length; i++)
        {
            if(i % 8 == 0 && i != 0) ss << "-";
            ss << this->at(i);
        }
        ss << std::endl;
        std::cerr << ss.str();
    }
}
