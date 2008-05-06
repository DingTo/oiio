/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2008 Larry Gritz
// 
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
// 
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// 
// (this is the MIT license)
/////////////////////////////////////////////////////////////////////////////


#include <cstdio>
#include <cstdlib>

#include "dassert.h"
#include "paramtype.h"
#include "strutil.h"

#define DLL_EXPORT_PUBLIC /* Because we are implementing ImageIO */
#include "imageio.h"
#undef DLL_EXPORT_PUBLIC

using namespace OpenImageIO;


void
ImageIOParameter::init (const std::string &_name, ParamBaseType _type,
                        int _nvalues, const void *_value, bool _copy)
{
    name = _name;
    type = _type;
    nvalues = _nvalues;
    copy = _copy;
    if (copy) {
        size_t size = (size_t) (nvalues * ParamBaseTypeSize (type));
        value = malloc (size);
        memcpy ((void *)value, _value, size);
    } else {
        value = _value;
    }
}



void
ImageIOParameter::clear_value ()
{
    if (copy)
        free ((void *)value);
    value = NULL;
    copy = false;
}



// FIXME - thread safety
static std::string create_error_msg;


/// Error reporting for the plugin implementation: call this with
/// printf-like arguments.
void
OpenImageIO::error (const char *message, ...)
{
    // FIXME - thread safety
    va_list ap;
    va_start (ap, message);
    create_error_msg = Strutil::format (message, ap);
    va_end (ap);
}



std::string
OpenImageIO::error_message ()
{
    // FIXME - thread safety
    return create_error_msg;
}



