#include "cache.hpp"

extern mem_type mem[MEM_SIZE];
extern cache_mem_type cache_mem [INDEX_SIZE][OFFSET_SIZE];
tag_type t_add;
ind_type i_add;
offset_type o_add;

void cache_write(add_type add,add_type val){
	cache_mem_type dat=0;
	i_add= (ind_type) (add >> INDEX_SHAMT) & INDEX_MASK ;
	t_add= (tag_type) (add >> TAG_SHAMT) & TAG_MASK ;
	o_add= (offset_type) add & OFFSET_MASK ;
	offset_type off=(o_add>>2)<<2; //start of the offset block
	add_type w_a= ((((add_type)t_add)<<INDEX_LENGTH)| (add_type)i_add)<<OFFSET_LENGTH;// corresponding start address of the index block
	//printf("w_a: %x\n",(uint32_t)w_a);
	for (int i=3;i>=0;i--){
		dat=(cache_mem_type)val&BYTE_MASK;
		cache_mem[i_add][i+off]=dat;
		mem[w_a+i+off]=dat;
		val=val>>8;
	}

}
