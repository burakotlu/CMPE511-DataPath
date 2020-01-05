#include "cache.hpp"

extern mem_type mem[MEM_SIZE];
extern cache_mem_type cache_mem [INDEX_SIZE][OFFSET_SIZE];
tag_type t_add;
ind_type indd;
offset_type offs;

void cache_write(add_type add,add_type val){
	cache_mem_type dat=0;
	indd= (ind_type) (add >> INDEX_SHAMT) & INDEX_MASK ;
	t_add= (tag_type) (add >> TAG_SHAMT) & TAG_MASK ;
	offs= (offset_type) add & TAG_MASK ;

	for (int i=OFFSET_SIZE-1;i>=0;i--){
		dat=(cache_mem_type)val&BYTE_MASK;
		cache_mem[indd][i]=dat;
		mem[add+i]=dat;
		val=val>>8;
	}

}
