# CMPE511-DataPath

RISC5 DATAPATH IMPLEMENTATION

* 32bit instruction set (B,I,J,S formats)
* Datapath with decoder, Alu, load/store unit
* datapath connected to 16 KB cache memory (16 byte blocks)
* cache is structured in scalable form

HEADERS:

cache.hpp
datapath.hpp
DATAPATH FUNCTIONS:

datapath.cpp
decoder.cpp
alu.cpp
lsu.cpp
CACHE FUNCTIONS:

cache.cpp
fetch.cpp
cache_write.cpp
initiate_cache.cpp
write_back.cpp
