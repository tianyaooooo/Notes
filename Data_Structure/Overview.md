# 1	数据结构概述
## 1.1 定义
我们如何把现实中大量而复杂的问题以**特定的数据类型**（个体如何来存储）和**特定的存储结构**（个体和个体间的关系如何来存储）保存到主存储器（内存）中，
以及在此基础上为实现某个功能（比如查找某个元素，删除某个元素，对所有元素进行排序）而执行的相应操作，这个相应的操作也叫算法。  

数据结构 = 个体 + 个体间关系  

算法 = 对**存储数据**的操作   

注：  
狭义的算法是与数据的存储方式密切相关的（存储方式不同，实现同一功能所执行的操作也会不同）  
广义的算法是与数据的存储方式无关的（泛型：利用某种技术达到 不同的存储方式 执行的操作是一样的 的效果）  
例如：数组和链表的排序，具体实施步骤有差异，但排序思想相同


## 1.2 算法
即解题的方法和步骤  
衡量算法的标准：时间复杂度（程序大概要执行的次数）、空间复杂度（算法执行工程中大概所占用的最大内存）、难易程度（人人都能理解）、鲁棒性
