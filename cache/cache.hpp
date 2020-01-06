#include <ap_int.h>
#include <stdio.h>
#include <inttypes.h>
#define MEM_SIZE 2048
#define VALID_LENGTH 1
#define OFFSET_LENGTH 2
#define OFFSET_SIZE 4
#define OFFSET_MASK 0b11
#define INDEX_SIZE 1024
#define INDEX_LENGTH 10
#define INDEX_SHAMT 2
#define INDEX_MASK 0b1111111111
#define TAG_LENGTH 20
#define TAG_SHAMT 12
#define TAG_MASK 0xFFFFF
#define ADD_LENGTH 32
#define N 1
#define Y 0
#define BYTE_MASK 0b11111111
#define CACHE_LENGTH 8
#define MEM_LENGTH 8

typedef ap_uint<ADD_LENGTH>   	add_type;
typedef ap_uint<TAG_LENGTH> 	tag_type;
typedef ap_uint<INDEX_LENGTH> 	ind_type;
typedef ap_uint<VALID_LENGTH> 	valid_type;
typedef ap_uint<OFFSET_LENGTH> 	offset_type;
typedef ap_uint<CACHE_LENGTH>	cache_mem_type;
typedef ap_uint<MEM_LENGTH>		mem_type;


void initiate_cache(void);
void fetch(tag_type tag_a,ind_type ind_a);
add_type cache (add_type address);
void write_back(tag_type tag,ind_type ind);
void cache_write(add_type add,add_type val);
