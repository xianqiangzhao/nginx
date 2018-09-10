
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_ARRAY_H_INCLUDED_
#define _NGX_ARRAY_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct {
    void        *elts; // 实际存储内存，在使用时要分配
    ngx_uint_t   nelts;//已经是使用的个数
    size_t       size;// array 存储每个元素的大小
    ngx_uint_t   nalloc;//分配的个数
    ngx_pool_t  *pool;//pool
} ngx_array_t;


ngx_array_t *ngx_array_create(ngx_pool_t *p, ngx_uint_t n, size_t size);
void ngx_array_destroy(ngx_array_t *a);
void *ngx_array_push(ngx_array_t *a);
void *ngx_array_push_n(ngx_array_t *a, ngx_uint_t n);


//初始化 array
// 参数n 为个数
//size 为array 中分配的多大尺寸的存储元素
static ngx_inline ngx_int_t
ngx_array_init(ngx_array_t *array, ngx_pool_t *pool, ngx_uint_t n, size_t size)
{
    /*
     * set "array->nelts" before "array->elts", otherwise MSVC thinks
     * that "array->nelts" may be used without having been initialized
     */

    array->nelts = 0;//初始为0
    array->size = size;//size
    array->nalloc = n; //个数
    array->pool = pool;

    array->elts = ngx_palloc(pool, n * size);//分配内存 大小为n*size
    if (array->elts == NULL) {
        return NGX_ERROR;
    }

    return NGX_OK;
}


#endif /* _NGX_ARRAY_H_INCLUDED_ */
