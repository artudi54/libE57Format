#ifndef E57FOUNDATION_H_INCLUDED
#define E57FOUNDATION_H_INCLUDED

/*
 * E57Foundation.h - public header of E57 Foundation API for reading/writing .e57 files.
 *
 * Copyright 2009 - 2010 Kevin Ackley (kackley@gwi.net)
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

//! @file  E57Foundation.h header file for the E57 Foundation API

#include <cstdint>
#include <cfloat>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


#ifndef DOXYGEN  // Doxygen is not handling namespaces well in @includelineno commands, so disable
namespace e57 {
#endif

using std::int8_t;
using std::uint8_t;
using std::int16_t;
using std::uint16_t;
using std::int32_t;
using std::uint32_t;
using std::int64_t;
using std::uint64_t;

// Shorthand for unicode string
//! @brief UTF-8 encodeded Unicode string
using ustring = std::string;

//! @brief Identifiers for types of E57 elements
enum NodeType {
    E57_STRUCTURE         = 1,  //!< StructureNode class
    E57_VECTOR            = 2,  //!< VectorNode class
    E57_COMPRESSED_VECTOR = 3,  //!< CompressedVectorNode class
    E57_INTEGER           = 4,  //!< IntegerNode class
    E57_SCALED_INTEGER    = 5,  //!< ScaledIntegerNode class
    E57_FLOAT             = 6,  //!< FloatNode class
    E57_STRING            = 7,  //!< StringNode class
    E57_BLOB              = 8   //!< BlobNode class
};

//! @brief The IEEE floating point number precisions supported
enum FloatPrecision {
    E57_SINGLE = 1,  //!< 32 bit IEEE floating point number format
    E57_DOUBLE = 2   //!< 64 bit IEEE floating point number format
};

//! @brief Identifies the representations of memory elements API can transfer data to/from
enum MemoryRepresentation {
    E57_INT8     = 1,  //!< 8 bit signed integer
    E57_UINT8    = 2,  //!< 8 bit unsigned integer
    E57_INT16    = 3,  //!< 16 bit signed integer
    E57_UINT16   = 4,  //!< 16 bit unsigned integer
    E57_INT32    = 5,  //!< 32 bit signed integer
    E57_UINT32   = 6,  //!< 32 bit unsigned integer
    E57_INT64    = 7,  //!< 64 bit signed integer
    E57_BOOL     = 8,  //!< C++ boolean type
    E57_REAL32   = 9,  //!< C++ float type
    E57_REAL64   = 10, //!< C++ double type
    E57_USTRING  = 11  //!< Unicode UTF-8 std::string
};

//! @brief Specifies the percentage of checksums which are verified when reading an ImageFile (0-100%).
using ReadChecksumPolicy = int;

const ReadChecksumPolicy CHECKSUM_POLICY_NONE = 0;    //! Do not verify the checksums. (fast)
const ReadChecksumPolicy CHECKSUM_POLICY_SPARSE = 25; //! Only verify 25% of the checksums. The last block is always verified.
const ReadChecksumPolicy CHECKSUM_POLICY_HALF = 50;   //! Only verify 50% of the checksums. The last block is always verified.
const ReadChecksumPolicy CHECKSUM_POLICY_ALL = 100;   //! Verify all checksums. This is the default. (slow)


//! @brief The major version number of the Foundation API
const int E57_FOUNDATION_API_MAJOR = 0;

//! @brief The minor version number of the Foundation API
const int E57_FOUNDATION_API_MINOR = 51;

//! @brief The URI of ASTM E57 v1.0 standard XML namespace
// Used to identify the standard field names and the grammar that relates them.
// Will typically be associated with the default namespace in an E57 file.
#define E57_V1_0_URI "http://www.astm.org/COMMIT/E57/2010-e57-v1.0"

//! @cond documentNonPublic   The following aren't documented
// Minimum and maximum values for integers
const int8_t   E57_INT8_MIN   = -128;
const int8_t   E57_INT8_MAX   = 127;
const int16_t  E57_INT16_MIN  = -32768;
const int16_t  E57_INT16_MAX  = 32767;
const int32_t  E57_INT32_MIN  = -2147483647 - 1;
const int32_t  E57_INT32_MAX  = 2147483647;
const int64_t  E57_INT64_MIN  = -9223372036854775807LL - 1;
const int64_t  E57_INT64_MAX  = 9223372036854775807LL;
const uint8_t  E57_UINT8_MIN  = 0U;
const uint8_t  E57_UINT8_MAX  = 0xffU; /* 255U */
const uint16_t E57_UINT16_MIN = 0U;
const uint16_t E57_UINT16_MAX = 0xffffU; /* 65535U */
const uint32_t E57_UINT32_MIN = 0U;
const uint32_t E57_UINT32_MAX = 0xffffffffU;  /* 4294967295U */
const uint64_t E57_UINT64_MIN = 0ULL;
const uint64_t E57_UINT64_MAX = 0xffffffffffffffffULL; /* 18446744073709551615ULL */

const float  E57_FLOAT_MIN  = -FLT_MAX;
const float  E57_FLOAT_MAX  = FLT_MAX;
const double E57_DOUBLE_MIN = -DBL_MAX;
const double E57_DOUBLE_MAX = DBL_MAX;
//! @endcond

//! @cond documentNonPublic   The following isn't part of the API, and isn't documented.
//??? Can define operator-> that will make implementation more readable
// Internal implementation files should include e57FoundationImpl.h first which defines symbol E57_INTERNAL_IMPLEMENTATION_ENABLE.
// Normal API users should not define this symbol.
// Basically the internal version allows access to the pointer to the implementation (impl_)
#ifdef E57_INTERNAL_IMPLEMENTATION_ENABLE
#  define E57_OBJECT_IMPLEMENTATION(T)                              \
public:                                                             \
    std::shared_ptr<T##Impl> impl() const {return(impl_);};       \
protected:                                                          \
    std::shared_ptr<T##Impl> impl_;
#else
#  define E57_OBJECT_IMPLEMENTATION(T)                              \
protected:                                                          \
    std::shared_ptr<T##Impl> impl_;
#endif
//! @endcond

class BlobNode;
class BlobNodeImpl;
class CompressedVectorNode;
class CompressedVectorNodeImpl;
class CompressedVectorReader;
class CompressedVectorReaderImpl;
class CompressedVectorWriter;
class CompressedVectorWriterImpl;
class FloatNode;
class FloatNodeImpl;
class ImageFile;
class ImageFileImpl;
class IntegerNode;
class IntegerNodeImpl;
class Node;
class NodeImpl;
class ScaledIntegerNode;
class ScaledIntegerNodeImpl;
class SourceDestBuffer;
class SourceDestBufferImpl;
class StringNode;
class StructureNode;
class StructureNodeImpl;
class VectorNode;
class VectorNodeImpl;

class Node {
public:
    Node() = delete;

    NodeType    type() const;
    bool        isRoot() const;
    Node        parent() const;
    ustring     pathName() const;
    ustring     elementName() const;
    ImageFile   destImageFile() const;
    bool        isAttached() const;
    void        dump(int indent = 0, std::ostream& os = std::cout) const;
    void        checkInvariant(bool doRecurse = true, bool doDowncast=true);
    bool        operator==(Node n2) const;
    bool        operator!=(Node n2) const;

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
#ifdef E57_INTERNAL_IMPLEMENTATION_ENABLE
    explicit    Node(std::shared_ptr<NodeImpl>);  // internal use only
#endif

protected:
    friend class NodeImpl;

    E57_OBJECT_IMPLEMENTATION(Node)  // Internal implementation details, not part of API, must be last in object
//! \endcond
};

class StructureNode {
public:
    StructureNode() = delete;
    StructureNode(ImageFile destImageFile);

    int64_t     childCount() const;
    bool        isDefined(const ustring& pathName) const;
    Node        get(int64_t index) const;
    Node        get(const ustring& pathName) const;
    void        set(const ustring& pathName, Node n);

    // Up/Down cast conversion
                operator Node() const;
    explicit    StructureNode(const Node& n);

    // Common generic Node functions
    bool        isRoot() const;
    Node        parent() const;
    ustring     pathName() const;
    ustring     elementName() const;
    ImageFile   destImageFile() const;
    bool        isAttached() const;

    // Diagnostic functions:
    void        dump(int indent = 0, std::ostream& os = std::cout) const;
    void        checkInvariant(bool doRecurse = true, bool doUpcast=true);

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
protected:
    friend class ImageFile;

                StructureNode(std::shared_ptr<StructureNodeImpl> ni);    // internal use only
                StructureNode(std::weak_ptr<ImageFileImpl> fileParent);  // internal use only

    E57_OBJECT_IMPLEMENTATION(StructureNode)  // Internal implementation details, not part of API, must be last in object
//! \endcond
};


class VectorNode {
public:
    VectorNode() = delete;
    explicit    VectorNode(ImageFile destImageFile, bool allowHeteroChildren = false);

    bool        allowHeteroChildren() const;

    int64_t     childCount() const;
    bool        isDefined(const ustring& pathName) const;
    Node        get(int64_t index) const;
    Node        get(const ustring& pathName) const;
    void        append(Node n);

    // Up/Down cast conversion
                operator Node() const;
    explicit    VectorNode(const Node& n);

    // Common generic Node functions
    bool        isRoot() const;
    Node        parent() const;
    ustring     pathName() const;
    ustring     elementName() const;
    ImageFile   destImageFile() const;
    bool        isAttached() const;

    // Diagnostic functions:
    void        dump(int indent = 0, std::ostream& os = std::cout) const;
    void        checkInvariant(bool doRecurse = true, bool doUpcast=true);

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
protected:
    friend class CompressedVectorNode;

                VectorNode(std::shared_ptr<VectorNodeImpl> ni);  // internal use only

    E57_OBJECT_IMPLEMENTATION(VectorNode)  // Internal implementation details, not part of API, must be last in object
//! \endcond
};

class SourceDestBuffer {
public:
    SourceDestBuffer() = delete;
    SourceDestBuffer(ImageFile destImageFile, const ustring pathName, int8_t* b,   const size_t capacity,
                     bool doConversion = false, bool doScaling = false, size_t stride = sizeof(int8_t));
    SourceDestBuffer(ImageFile destImageFile, const ustring pathName, uint8_t* b,  const size_t capacity,
                     bool doConversion = false, bool doScaling = false, size_t stride = sizeof(uint8_t));
    SourceDestBuffer(ImageFile destImageFile, const ustring pathName, int16_t* b,  const size_t capacity,
                     bool doConversion = false, bool doScaling = false, size_t stride = sizeof(int16_t));
    SourceDestBuffer(ImageFile destImageFile, const ustring pathName, uint16_t* b, const size_t capacity,
                     bool doConversion = false, bool doScaling = false, size_t stride = sizeof(uint16_t));
    SourceDestBuffer(ImageFile destImageFile, const ustring pathName, int32_t* b,  const size_t capacity,
                     bool doConversion = false, bool doScaling = false, size_t stride = sizeof(int32_t));
    SourceDestBuffer(ImageFile destImageFile, const ustring pathName, uint32_t* b, const size_t capacity,
                     bool doConversion = false, bool doScaling = false, size_t stride = sizeof(uint32_t));
    SourceDestBuffer(ImageFile destImageFile, const ustring pathName, int64_t* b,  const size_t capacity,
                     bool doConversion = false, bool doScaling = false, size_t stride = sizeof(int64_t));
    SourceDestBuffer(ImageFile destImageFile, const ustring pathName, bool* b,     const size_t capacity,
                     bool doConversion = false, bool doScaling = false, size_t stride = sizeof(bool));
    SourceDestBuffer(ImageFile destImageFile, const ustring pathName, float* b,    const size_t  capacity,
                     bool doConversion = false, bool doScaling = false, size_t stride = sizeof(float));
    SourceDestBuffer(ImageFile destImageFile, const ustring pathName, double* b,   const size_t capacity,
                     bool doConversion = false, bool doScaling = false, size_t stride = sizeof(double));
    SourceDestBuffer(ImageFile destImageFile, const ustring pathName, std::vector<ustring>* b);

    ustring         pathName() const;
    enum MemoryRepresentation  memoryRepresentation() const;
    size_t          capacity() const;
    bool            doConversion() const;
    bool            doScaling() const;
    size_t          stride() const;

    // Diagnostic functions:
    void            dump(int indent = 0, std::ostream& os = std::cout) const;
    void            checkInvariant(bool doRecurse = true);

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
protected:

    E57_OBJECT_IMPLEMENTATION(SourceDestBuffer)  // Internal implementation details, not part of API, must be last in object
//! \endcond
};

class CompressedVectorReader {
public:
    CompressedVectorReader() = delete;

    unsigned    read();
    unsigned    read(std::vector<SourceDestBuffer>& dbufs);
    void        seek(int64_t recordNumber); // !!! not implemented yet
    void        close();
    bool        isOpen();
    CompressedVectorNode compressedVectorNode() const;

    void        dump(int indent = 0, std::ostream& os = std::cout) const;
    void        checkInvariant(bool doRecurse = true);

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
protected:
    friend class CompressedVectorNode;

                CompressedVectorReader(std::shared_ptr<CompressedVectorReaderImpl> ni);

    E57_OBJECT_IMPLEMENTATION(CompressedVectorReader)  // Internal implementation details, not part of API, must be last in object
//! \endcond
};

class CompressedVectorWriter {
public:
    CompressedVectorWriter() = delete;

    void        write(const size_t requestedRecordCount);
    void        write(std::vector<SourceDestBuffer>& sbufs, const size_t requestedRecordCount);
    void        close();
    bool        isOpen();
    CompressedVectorNode compressedVectorNode() const;

    void        dump(int indent = 0, std::ostream& os = std::cout) const;
    void        checkInvariant(bool doRecurse = true);

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
protected:
    friend class CompressedVectorNode;

                CompressedVectorWriter(std::shared_ptr<CompressedVectorWriterImpl> ni);

    E57_OBJECT_IMPLEMENTATION(CompressedVectorWriter)  // Internal implementation details, not part of API, must be last in object
//! \endcond
};

class CompressedVectorNode {
public:
    CompressedVectorNode() = delete;
    explicit CompressedVectorNode(ImageFile destImageFile, Node prototype, VectorNode codecs);

    int64_t     childCount() const;
    Node        prototype() const;
    VectorNode  codecs() const;

    // Iterators
    CompressedVectorWriter writer(std::vector<SourceDestBuffer>& sbufs);
    CompressedVectorReader reader(const std::vector<SourceDestBuffer>& dbufs);

    // Up/Down cast conversion
                operator Node() const;
    explicit    CompressedVectorNode(const Node& n);

    // Common generic Node functions
    bool        isRoot() const;
    Node        parent() const;
    ustring     pathName() const;
    ustring     elementName() const;
    ImageFile   destImageFile() const;
    bool        isAttached() const;

    // Diagnostic functions:
    void        dump(int indent = 0, std::ostream& os = std::cout) const;
    void        checkInvariant(bool doRecurse = true, bool doUpcast=true);

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
protected:
    friend class CompressedVectorReader;
    friend class CompressedVectorWriter;
    friend class E57XmlParser;

                CompressedVectorNode(std::shared_ptr<CompressedVectorNodeImpl> ni);  // internal use only

    E57_OBJECT_IMPLEMENTATION(CompressedVectorNode)  // Internal implementation details, not part of API, must be last in object
//! \endcond
};

class IntegerNode {
public:
    IntegerNode() = delete;
    explicit IntegerNode(ImageFile destImageFile, int64_t value = 0, int64_t minimum = E57_INT64_MIN, int64_t maximum = E57_INT64_MAX);

    int64_t     value() const;
    int64_t     minimum() const;
    int64_t     maximum() const;

    // Up/Down cast conversion
                operator Node() const;
    explicit    IntegerNode(const Node& n);

    // Common generic Node functions
    bool        isRoot() const;
    Node        parent() const;
    ustring     pathName() const;
    ustring     elementName() const;
    ImageFile   destImageFile() const;
    bool        isAttached() const;

    // Diagnostic functions:
    void        dump(int indent = 0, std::ostream& os = std::cout) const;
    void        checkInvariant(bool doRecurse = true, bool doUpcast=true);

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
protected:

                IntegerNode(std::shared_ptr<IntegerNodeImpl> ni);  // internal use only

    E57_OBJECT_IMPLEMENTATION(IntegerNode)  // Internal implementation details, not part of API, must be last in object
//! \endcond
};

class ScaledIntegerNode {
public:
    ScaledIntegerNode() = delete;
    explicit ScaledIntegerNode(ImageFile destImageFile, int64_t value, int64_t minimum, int64_t maximum,
                               double scale = 1.0, double offset = 0.0);
    explicit ScaledIntegerNode(ImageFile destImageFile, int value, int64_t minimum, int64_t maximum,
                               double scale = 1.0, double offset = 0.0);
    explicit ScaledIntegerNode(ImageFile destImageFile, int value, int minimum, int maximum,
                               double scale = 1.0, double offset = 0.0);
    explicit ScaledIntegerNode(ImageFile destImageFile, double scaledValue, double scaledMinimum, double scaledMaximum,
                               double scale = 1.0, double offset = 0.0);

    int64_t     rawValue() const;
    double      scaledValue() const;
    int64_t     minimum() const;
    double      scaledMinimum() const;
    int64_t     maximum() const;
    double      scaledMaximum() const;
    double      scale() const;
    double      offset() const;

    // Up/Down cast conversion
                operator Node() const;
    explicit    ScaledIntegerNode(const Node& n);

    // Common generic Node functions
    bool        isRoot() const;
    Node        parent() const;
    ustring     pathName() const;
    ustring     elementName() const;
    ImageFile   destImageFile() const;
    bool        isAttached() const;

    // Diagnostic functions:
    void        dump(int indent = 0, std::ostream& os = std::cout) const;
    void        checkInvariant(bool doRecurse = true, bool doUpcast=true);

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
protected:

                ScaledIntegerNode(std::shared_ptr<ScaledIntegerNodeImpl> ni);  // internal use only

    E57_OBJECT_IMPLEMENTATION(ScaledIntegerNode)  // Internal implementation details, not part of API, must be last in object
//! \endcond
};

class FloatNode {
public:
    FloatNode() = delete;
    explicit FloatNode(ImageFile destImageFile, double value = 0.0, FloatPrecision precision = E57_DOUBLE,
                       double minimum = E57_DOUBLE_MIN, double  maximum = E57_DOUBLE_MAX);

    double      value() const;
    FloatPrecision precision() const;
    double      minimum() const;
    double      maximum() const;

    // Up/Down cast conversion
                operator Node() const;
    explicit    FloatNode(const Node& n);

    // Common generic Node functions
    bool        isRoot() const;
    Node        parent() const;
    ustring     pathName() const;
    ustring     elementName() const;
    ImageFile   destImageFile() const;
    bool        isAttached() const;

    // Diagnostic functions:
    void        dump(int indent = 0, std::ostream& os = std::cout) const;
    void        checkInvariant(bool doRecurse = true, bool doUpcast=true);

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
protected:

                FloatNode(std::shared_ptr<FloatNodeImpl> ni);  // internal use only

    E57_OBJECT_IMPLEMENTATION(FloatNode)  // Internal implementation details, not part of API, must be last in object
//! \endcond
};

class StringNodeImpl;
class StringNode {
public:
    StringNode() = delete;
    explicit StringNode(ImageFile destImageFile, const ustring value = "");

    ustring     value() const;

    // Up/Down cast conversion
                operator Node() const;
    explicit    StringNode(const Node& n);

    // Common generic Node functions
    bool        isRoot() const;
    Node        parent() const;
    ustring     pathName() const;
    ustring     elementName() const;
    ImageFile   destImageFile() const;
    bool        isAttached() const;

    // Diagnostic functions:
    void        dump(int indent = 0, std::ostream& os = std::cout) const;
    void        checkInvariant(bool doRecurse = true, bool doUpcast=true);

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
protected:
    friend class StringNodeImpl;
                StringNode(std::shared_ptr<StringNodeImpl> ni);  // internal use only

    E57_OBJECT_IMPLEMENTATION(StringNode)  // Internal implementation details, not part of API, must be last in object
//! \endcond
};

class BlobNode {
public:
    BlobNode() = delete;
    explicit BlobNode(ImageFile destImageFile, int64_t byteCount);

    int64_t     byteCount() const;
    void        read(uint8_t* buf,  int64_t start, size_t byteCount);
    void        write(uint8_t* buf, int64_t start, size_t byteCount);

    // Up/Down cast conversion
                operator Node() const;
    explicit    BlobNode(const Node& n);

    // Common generic Node functions
    bool        isRoot() const;
    Node        parent() const;
    ustring     pathName() const;
    ustring     elementName() const;
    ImageFile   destImageFile() const;
    bool        isAttached() const;

    // Diagnostic functions:
    void        dump(int indent = 0, std::ostream& os = std::cout) const;
    void        checkInvariant(bool doRecurse = true, bool doUpcast=true);

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
protected:
    friend class E57XmlParser;

                BlobNode(std::shared_ptr<BlobNodeImpl> ni);       // internal use only

                // Internal use only, create blob already in a file
                BlobNode(ImageFile destImageFile, int64_t fileOffset, int64_t length);

    E57_OBJECT_IMPLEMENTATION(BlobNode)  // Internal implementation details, not part of API, must be last in object
//! \endcond
};

class ImageFile {
public:
    ImageFile() = delete;
    ImageFile(const ustring& fname, const ustring& mode, ReadChecksumPolicy checksumPolicy = CHECKSUM_POLICY_ALL );

    StructureNode   root() const;
    void            close();
    void            cancel();
    bool            isOpen() const;
    bool            isWritable() const;
    ustring         fileName() const;
    int             writerCount() const;
    int             readerCount() const;

    // Manipulate registered extensions in the file
    void            extensionsAdd(const ustring& prefix, const ustring& uri);
    bool            extensionsLookupPrefix(const ustring& prefix, ustring& uri) const;
    bool            extensionsLookupUri(const ustring& uri, ustring& prefix) const;
    size_t          extensionsCount() const;
    ustring         extensionsPrefix(const size_t index) const;
    ustring         extensionsUri(const size_t index) const;

    // Field name functions:
    bool            isElementNameExtended(const ustring& elementName) const;
    void            elementNameParse(const ustring& elementName, ustring& prefix, ustring& localPart) const;

    // Diagnostic functions:
    void            dump(int indent = 0, std::ostream& os = std::cout) const;
    void            checkInvariant(bool doRecurse = true);
    bool            operator==(ImageFile imf2) const;
    bool            operator!=(ImageFile imf2) const;

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
private:
                    ImageFile(double);           // Give a second dummy constructor, better error msg for: ImageFile(0)
protected:
    //??? workaround?
    friend class Node;
    friend class StructureNode;
    friend class VectorNode;
    friend class CompressedVectorNode;
    friend class IntegerNode;
    friend class ScaledIntegerNode;
    friend class FloatNode;
    friend class StringNode;
    friend class BlobNode;

                    ImageFile(std::shared_ptr<ImageFileImpl> imfi);  // internal use only

    E57_OBJECT_IMPLEMENTATION(ImageFile)  // Internal implementation details, not part of API, must be last in object
//! \endcond
};

//! @brief Numeric error identifiers used in E57Exception
enum ErrorCode {
    /*
     * N.B.  *** When changing error strings here, remember to update the error strings in E57Foundation.cpp ****
     */
    E57_SUCCESS                                 = 0,  //!< operation was successful
    E57_ERROR_BAD_CV_HEADER                     = 1,  //!< a CompressedVector binary header was bad
    E57_ERROR_BAD_CV_PACKET                     = 2,  //!< a CompressedVector binary packet was bad
    E57_ERROR_CHILD_INDEX_OUT_OF_BOUNDS         = 3,  //!< a numerical index identifying a child was out of bounds
    E57_ERROR_SET_TWICE                         = 4,  //!< attempted to set an existing child element to a new value
    E57_ERROR_HOMOGENEOUS_VIOLATION             = 5,  //!< attempted to add an E57 Element that would have made the children of a homogenous Vector have different types
    E57_ERROR_VALUE_NOT_REPRESENTABLE           = 6,  //!< a value could not be represented in the requested type
    E57_ERROR_SCALED_VALUE_NOT_REPRESENTABLE    = 7,  //!< after scaling the result could not be represented in the requested type
    E57_ERROR_REAL64_TOO_LARGE                  = 8,  //!< a 64 bit IEEE float was too large to store in a 32 bit IEEE float
    E57_ERROR_EXPECTING_NUMERIC                 = 9,  //!< Expecting numeric representation in user's buffer, found ustring
    E57_ERROR_EXPECTING_USTRING                 = 10, //!< Expecting string representation in user's buffer, found numeric
    E57_ERROR_INTERNAL                          = 11, //!< An unrecoverable inconsistent internal state was detected
    E57_ERROR_BAD_XML_FORMAT                    = 12, //!< E57 primitive not encoded in XML correctly
    E57_ERROR_XML_PARSER                        = 13, //!< XML not well formed
    E57_ERROR_BAD_API_ARGUMENT                  = 14, //!< bad API function argument provided by user
    E57_ERROR_FILE_IS_READ_ONLY                 = 15, //!< can't modify read only file
    E57_ERROR_BAD_CHECKSUM                      = 16, //!< checksum mismatch, file is corrupted
    E57_ERROR_OPEN_FAILED                       = 17, //!< open() failed
    E57_ERROR_CLOSE_FAILED                      = 18, //!< close() failed
    E57_ERROR_READ_FAILED                       = 19, //!< read() failed
    E57_ERROR_WRITE_FAILED                      = 20, //!< write() failed
    E57_ERROR_LSEEK_FAILED                      = 21, //!< lseek() failed
    E57_ERROR_PATH_UNDEFINED                    = 22, //!< E57 element path well formed but not defined
    E57_ERROR_BAD_BUFFER                        = 23, //!< bad SourceDestBuffer
    E57_ERROR_NO_BUFFER_FOR_ELEMENT             = 24, //!< no buffer specified for an element in CompressedVectorNode during write
    E57_ERROR_BUFFER_SIZE_MISMATCH              = 25, //!< SourceDestBuffers not all same size
    E57_ERROR_BUFFER_DUPLICATE_PATHNAME         = 26, //!< duplicate pathname in CompressedVectorNode read/write
    E57_ERROR_BAD_FILE_SIGNATURE                = 27, //!< file signature not "ASTM-E57"
    E57_ERROR_UNKNOWN_FILE_VERSION              = 28, //!< incompatible file version
    E57_ERROR_BAD_FILE_LENGTH                   = 29, //!< size in file header not same as actual
    E57_ERROR_XML_PARSER_INIT                   = 30, //!< XML parser failed to initialize
    E57_ERROR_DUPLICATE_NAMESPACE_PREFIX        = 31, //!< namespace prefix already defined
    E57_ERROR_DUPLICATE_NAMESPACE_URI           = 32, //!< namespace URI already defined
    E57_ERROR_BAD_PROTOTYPE                     = 33, //!< bad prototype in CompressedVectorNode
    E57_ERROR_BAD_CODECS                        = 34, //!< bad codecs in CompressedVectorNode
    E57_ERROR_VALUE_OUT_OF_BOUNDS               = 35, //!< element value out of min/max bounds
    E57_ERROR_CONVERSION_REQUIRED               = 36, //!< conversion required to assign element value, but not requested
    E57_ERROR_BAD_PATH_NAME                     = 37, //!< E57 path name is not well formed
    E57_ERROR_NOT_IMPLEMENTED                   = 38, //!< functionality not implemented
    E57_ERROR_BAD_NODE_DOWNCAST                 = 39, //!< bad downcast from Node to specific node type
    E57_ERROR_WRITER_NOT_OPEN                   = 40, //!< CompressedVectorWriter is no longer open
    E57_ERROR_READER_NOT_OPEN                   = 41, //!< CompressedVectorReader is no longer open
    E57_ERROR_NODE_UNATTACHED                   = 42, //!< node is not yet attached to tree of ImageFile
    E57_ERROR_ALREADY_HAS_PARENT                = 43, //!< node already has a parent
    E57_ERROR_DIFFERENT_DEST_IMAGEFILE          = 44, //!< nodes were constructed with different destImageFiles
    E57_ERROR_IMAGEFILE_NOT_OPEN                = 45, //!< destImageFile is no longer open
    E57_ERROR_BUFFERS_NOT_COMPATIBLE            = 46, //!< SourceDestBuffers not compatible with previously given ones
    E57_ERROR_TOO_MANY_WRITERS                  = 47, //!< too many open CompressedVectorWriters of an ImageFile
    E57_ERROR_TOO_MANY_READERS                  = 48, //!< too many open CompressedVectorReaders of an ImageFile
    E57_ERROR_BAD_CONFIGURATION                 = 49, //!< bad configuration string
    E57_ERROR_INVARIANCE_VIOLATION              = 50  //!< class invariance constraint violation in debug mode
    /*
     * N.B.  *** When changing error strings here, remember to update the error strings in E57Foundation.cpp ****
     */
};

class E57Exception : public std::exception {
public:
    virtual void        report(const char* reportingFileName=nullptr, int reportingLineNumber=0, const char* reportingFunctionName=nullptr, std::ostream& os = std::cout) const;
    virtual ErrorCode   errorCode() const;
    virtual ustring     context() const;
    virtual const char* what() const noexcept;

    // For debugging purposes:
    virtual const char* sourceFileName() const;
    virtual const char* sourceFunctionName() const;
    virtual int         sourceLineNumber() const;

//! \cond documentNonPublic   The following isn't part of the API, and isn't documented.
    E57Exception() = delete;
    E57Exception(ErrorCode ecode, const ustring context,
                 const char* srcFileName = nullptr, int srcLineNumber = 0, const char* srcFunctionName = nullptr);
    ~E57Exception() noexcept {}

protected:
    ErrorCode   errorCode_;
    ustring     context_;
    const char* sourceFileName_;
    const char* sourceFunctionName_;
    int         sourceLineNumber_;
//! \endcond
};

class E57Utilities {
public:
    E57Utilities(const ustring& /*configuration*/ = "") {}

    // Get latest version of ASTM standard supported, and library id string
    void        getVersions(int& astmMajor, int& astmMinor, ustring& libraryId);

    ustring     errorCodeToString(ErrorCode ecode);

};

#ifndef DOXYGEN
}  // end namespace e57
#endif

#endif // E57FOUNDATION_H_INCLUDED
