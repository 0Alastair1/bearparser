#include "ByteBuffer.h"

ByteBuffer::ByteBuffer(bufsize_t v_size, bufsize_t v_padding)
    : content(NULL), contentSize(v_size), padding(v_padding)
{
    if (v_size == 0) throw BufferException("Zero size requested");

    this->content =  allocContent(v_size, v_padding);
    this->contentSize = v_size;
}

ByteBuffer::ByteBuffer(AbstractByteBuffer *v_parent, offset_t v_offset, bufsize_t v_size, bufsize_t v_padding)
{
    if (v_parent == NULL) throw BufferException("Cannot make subBuffer for NULL buffer!");
    if (v_size == 0) throw BufferException("Cannot make 0 size buffer!");

    bufsize_t parentSize = v_parent->getContentSize();

    bufsize_t copySize = v_size < parentSize ? v_size : parentSize;
    bufsize_t allocSize = v_size > parentSize ? v_size : parentSize;

    BYTE *bContent = v_parent->getContentAt(v_offset, copySize);
    if (bContent == NULL) throw BufferException("Cannot make Buffer for NULL content!");

    this->content =  allocContent(allocSize, v_padding);
    this->contentSize = allocSize;

    memcpy(this->content, bContent, copySize);
    TRACE();
}

BYTE* ByteBuffer::allocContent(bufsize_t v_size, bufsize_t v_padding)
{
    if (v_size == 0) throw BufferException("Zero size requested");

    BYTE* content =  (BYTE*) calloc(sizeof(BYTE), v_size + v_padding);
    if (content == NULL) throw BufferException("Cannot allocate buffer");

    return content;
}

ByteBuffer::~ByteBuffer()
{
    free(this->content);
    TRACE();
}



