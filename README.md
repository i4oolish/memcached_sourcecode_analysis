# memcached_sourcecode_analysis
memcached-1.4.33-源码剖析

对源码进行分析，同时对memcached的设计进行总结。

0.memcached好多全局变量写在memcached.h中，其实单独分出一个文件public.h更好一些。

1. hash函数分析
把settings.hash_algorithm和hash.h中的hash变量声明在public.h中。
