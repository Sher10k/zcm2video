// THIS IS AN AUTOMATICALLY GENERATED FILE.
// DO NOT MODIFY BY HAND!!
//
// Generated by zcm-gen

#include <string.h>
#ifndef ZCM_EMBEDDED
#include <stdio.h>
#endif
#include "ZcmService.h"

static int __ZcmService_hash_computed = 0;
static uint64_t __ZcmService_hash;

uint64_t __ZcmService_hash_recursive(const __zcm_hash_ptr* p)
{
    const __zcm_hash_ptr* fp;
    for (fp = p; fp != NULL; fp = fp->parent)
        if (fp->v == __ZcmService_get_hash)
            return 0;

    __zcm_hash_ptr cp;
    cp.parent =  p;
    cp.v = (void*)__ZcmService_get_hash;
    (void) cp;

    uint64_t hash = (uint64_t)0xab017a94ae37fdadLL
         + __int64_t_hash_recursive(&cp)
         + __int32_t_hash_recursive(&cp)
        ;

    return (hash<<1) + ((hash>>63)&1);
}

int64_t __ZcmService_get_hash(void)
{
    if (!__ZcmService_hash_computed) {
        __ZcmService_hash = (int64_t)__ZcmService_hash_recursive(NULL);
        __ZcmService_hash_computed = 1;
    }

    return __ZcmService_hash;
}

int __ZcmService_encode_array(void* buf, uint32_t offset, uint32_t maxlen, const ZcmService* p, uint32_t elements)
{
    uint32_t pos = 0, element;
    int thislen;

    for (element = 0; element < elements; ++element) {

        thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].u_timestamp), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].processing_time), 1);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int ZcmService_encode(void* buf, uint32_t offset, uint32_t maxlen, const ZcmService* p)
{
    uint32_t pos = 0;
    int thislen;
    int64_t hash = __ZcmService_get_hash();

    thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    thislen = __ZcmService_encode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

uint32_t __ZcmService_encoded_array_size(const ZcmService* p, uint32_t elements)
{
    uint32_t size = 0, element;
    for (element = 0; element < elements; ++element) {

        size += __int64_t_encoded_array_size(&(p[element].u_timestamp), 1);

        size += __int32_t_encoded_array_size(&(p[element].processing_time), 1);

    }
    return size;
}

uint32_t ZcmService_encoded_size(const ZcmService* p)
{
    return 8 + __ZcmService_encoded_array_size(p, 1);
}

uint32_t ZcmService_struct_size(void)
{
    return sizeof(ZcmService);
}

uint32_t ZcmService_num_fields(void)
{
    return 2;
}

int ZcmService_get_field(const ZcmService* p, uint32_t i, zcm_field_t* f)
{
    if (i >= ZcmService_num_fields())
        return 1;
    
    switch (i) {
    
        case 0: {
            f->name = "u_timestamp";
            f->type = ZCM_FIELD_INT64_T;
            f->typestr = "int64_t";
            f->num_dim = 0;
            f->data = (void*) &p->u_timestamp;
            return 0;
        }
        
        case 1: {
            f->name = "processing_time";
            f->type = ZCM_FIELD_INT32_T;
            f->typestr = "int32_t";
            f->num_dim = 0;
            f->data = (void*) &p->processing_time;
            return 0;
        }
        
        default:
            return 1;
    }
}

const zcm_type_info_t* ZcmService_get_type_info(void)
{
    static int init = 0;
    static zcm_type_info_t typeinfo;
    if (!init) {
        typeinfo.encode         = (zcm_encode_t) ZcmService_encode;
        typeinfo.decode         = (zcm_decode_t) ZcmService_decode;
        typeinfo.decode_cleanup = (zcm_decode_cleanup_t) ZcmService_decode_cleanup;
        typeinfo.encoded_size   = (zcm_encoded_size_t) ZcmService_encoded_size;
        typeinfo.struct_size    = (zcm_struct_size_t)  ZcmService_struct_size;
        typeinfo.num_fields     = (zcm_num_fields_t) ZcmService_num_fields;
        typeinfo.get_field      = (zcm_get_field_t) ZcmService_get_field;
        typeinfo.get_hash       = (zcm_get_hash_t) __ZcmService_get_hash;
    }
    
    return &typeinfo;
}
int __ZcmService_decode_array(const void* buf, uint32_t offset, uint32_t maxlen, ZcmService* p, uint32_t elements)
{
    uint32_t pos = 0, element;
    int thislen;

    for (element = 0; element < elements; ++element) {

        thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].u_timestamp), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].processing_time), 1);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int __ZcmService_decode_array_cleanup(ZcmService* p, uint32_t elements)
{
    uint32_t element;
    for (element = 0; element < elements; ++element) {

        __int64_t_decode_array_cleanup(&(p[element].u_timestamp), 1);

        __int32_t_decode_array_cleanup(&(p[element].processing_time), 1);

    }
    return 0;
}

int ZcmService_decode(const void* buf, uint32_t offset, uint32_t maxlen, ZcmService* p)
{
    uint32_t pos = 0;
    int thislen;
    int64_t hash = __ZcmService_get_hash();

    int64_t this_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (this_hash != hash) return -1;

    thislen = __ZcmService_decode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int ZcmService_decode_cleanup(ZcmService* p)
{
    return __ZcmService_decode_array_cleanup(p, 1);
}

uint32_t __ZcmService_clone_array(const ZcmService* p, ZcmService* q, uint32_t elements)
{
    uint32_t n = 0, element;
    for (element = 0; element < elements; ++element) {

        n += __int64_t_clone_array(&(p[element].u_timestamp), &(q[element].u_timestamp), 1);

        n += __int32_t_clone_array(&(p[element].processing_time), &(q[element].processing_time), 1);

    }
    return n;
}

ZcmService* ZcmService_copy(const ZcmService* p)
{
    ZcmService* q = (ZcmService*) malloc(sizeof(ZcmService));
    __ZcmService_clone_array(p, q, 1);
    return q;
}

void ZcmService_destroy(ZcmService* p)
{
    __ZcmService_decode_array_cleanup(p, 1);
    free(p);
}

int ZcmService_publish(zcm_t* zcm, const char* channel, const ZcmService* p)
{
      uint32_t max_data_size = ZcmService_encoded_size (p);
      uint8_t* buf = (uint8_t*) malloc (max_data_size);
      if (!buf) return -1;
      int data_size = ZcmService_encode (buf, 0, max_data_size, p);
      if (data_size < 0) {
          free (buf);
          return data_size;
      }
      int status = zcm_publish (zcm, channel, buf, (uint32_t)data_size);
      free (buf);
      return status;
}

struct _ZcmService_subscription_t {
    ZcmService_handler_t user_handler;
    void* userdata;
    zcm_sub_t* z_sub;
};
static
void ZcmService_handler_stub (const zcm_recv_buf_t* rbuf,
                            const char* channel, void* userdata)
{
    int status;
    ZcmService p;
    memset(&p, 0, sizeof(ZcmService));
    status = ZcmService_decode (rbuf->data, 0, rbuf->data_size, &p);
    if (status < 0) {
        #ifndef ZCM_EMBEDDED
        fprintf (stderr, "error %d decoding ZcmService!!!\n", status);
        #endif
        return;
    }

    ZcmService_subscription_t* h = (ZcmService_subscription_t*) userdata;
    h->user_handler (rbuf, channel, &p, h->userdata);

    ZcmService_decode_cleanup (&p);
}

ZcmService_subscription_t* ZcmService_subscribe (zcm_t* zcm,
                    const char* channel,
                    ZcmService_handler_t f, void* userdata)
{
    ZcmService_subscription_t* n = (ZcmService_subscription_t*)
                       malloc(sizeof(ZcmService_subscription_t));
    n->user_handler = f;
    n->userdata = userdata;
    n->z_sub = zcm_subscribe (zcm, channel,
                              ZcmService_handler_stub, n);
    if (n->z_sub == NULL) {
        #ifndef ZCM_EMBEDDED
        fprintf (stderr,"couldn't reg ZcmService ZCM handler!\n");
        #endif
        free (n);
        return NULL;
    }
    return n;
}

int ZcmService_unsubscribe(zcm_t* zcm, ZcmService_subscription_t* hid)
{
    int status = zcm_unsubscribe (zcm, hid->z_sub);
    if (0 != status) {
        #ifndef ZCM_EMBEDDED
        fprintf(stderr,
           "couldn't unsubscribe ZcmService_handler %p!\n", hid);
        #endif
        return -1;
    }
    free (hid);
    return 0;
}
