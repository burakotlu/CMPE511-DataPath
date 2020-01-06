#include "cache.hpp"

extern valid_type valid[INDEX_SIZE];
void initiate_cache(void){
	//printf("initiating valid array..");
	for(int i=0; i<INDEX_SIZE;i++)
		valid[i]=N;
}
