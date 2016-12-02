# memcached_sourcecode_analysis
=====
memcached-1.4.33-源码剖析

对源码进行分析，同时对memcached的设计进行总结。

0.memcached好多全局变量写在memcached.h中，其实单独分出一个文件public.h更好一些。

1. hash函数分析
把settings.hash_algorithm和hash.h中的hash变量声明在public.h中。

2. assoc关联数组
疑问：assoc_maintenance_thread线程是否会和assoc_delete/assoc_find操作同一个bucket，即查询或者删除的item属于当前正在迁移的bucket。
代码中不好的地方，跟前面一样，不再陈述，声明在memcached.h中，定义在thread.c中。
好的地方如下：



2.1 assoc_expand 函数中关于更新primary_hashtable部分，代码写的很巧妙和整洁。



2.2 assoc_maintenance_thread中，每次更新一个bucket时候的锁设计的很好，值得借鉴。这里把锁的粒度降低到了buckets桶的数量。


3 cache
很简单的一个object cache，采用链表型数组来保存cache对象。cache_alloc用来从cache中拿出一个object空间，以供用户使用；cache_free用于把用户使用过的object放回到cache。如果有debug，那么在object对象前后各加一个redzone_pattern。

4.daemon
设置为后台进程。
PS：不知道和redis/mcp++等等其他框架和程序有什么区别，明天看看。
看了下mcp++，实现很简单，直接调用的系统api

5.bipbuffer
----------
高效的两段式循环缓冲区参考。百度搜一下，设计很巧妙。

6. util
--------
略过
