#ifndef STRUCTURENODEIMPL_H
#define STRUCTURENODEIMPL_H
/*
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

#include "NodeImpl.h"

namespace e57 {

class StructureNodeImpl : public NodeImpl
{
public:
    StructureNodeImpl(std::weak_ptr<ImageFileImpl> destImageFile);
    ~StructureNodeImpl()  override = default;

    NodeType    type() const override;
    bool        isTypeEquivalent(std::shared_ptr<NodeImpl> ni) override;
    bool        isDefined(const ustring& pathName) override;
    void        setAttachedRecursive() override;

    virtual int64_t     childCount() const;

    virtual std::shared_ptr<NodeImpl>  get(int64_t index);
    std::shared_ptr<NodeImpl>          get(const ustring& pathName) override;

    virtual void  set(int64_t index, std::shared_ptr<NodeImpl> ni);
    void          set(const ustring& pathName, std::shared_ptr<NodeImpl> ni, bool autoPathCreate = false) override;
    void          set(const std::vector<ustring>& fields, unsigned level, std::shared_ptr<NodeImpl> ni, bool autoPathCreate = false) override;
    virtual void  append(std::shared_ptr<NodeImpl> ni);

    void        checkLeavesInSet(const std::set<ustring>& pathNames, std::shared_ptr<NodeImpl> origin) override;

    void        writeXml(std::shared_ptr<ImageFileImpl> imf, CheckedFile& cf, int indent, const char* forcedFieldName=nullptr) override;

#ifdef E57_DEBUG
    void    dump(int indent = 0, std::ostream& os = std::cout) const override;
#endif

protected:
    friend class CompressedVectorReaderImpl;
    std::shared_ptr<NodeImpl> lookup(const ustring& pathName) override;

    std::vector<std::shared_ptr<NodeImpl> > children_;
};

}

#endif
