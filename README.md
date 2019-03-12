# Data Structures and Algorithms

- 简介
- 目录
  - 线性容器    `yxlLinearContainer`
    | 函数      | 类型       | 功能                   |
    | --------- | ---------- | ---------------------- |
    | `empty()` | `bool`     | 判断容器是否为空       |
    | `size()`  | `unsigned` | 返回容器的内元素的个数 |
    | `clear()` | `void`     | 清空容器               |
    - 线性表    `yxlList`
    | 函数                                            | 类型   | 功能                                              |
    | ----------------------------------------------- | ------ | ------------------------------------------------- |
    | `index_of(const T& value)`                      | `int`  | 返回容器中出现`value`的第一个下表，不存在则返回-1 |
    | `erase(const unsigned& index)`                  | `void` | 删除容器中指定下标的元素                          |
    | `insert(const unsigned& index, const T& value)` | `void` | 插入元素到容器中指定的下标                        |
      - 线性数组    `yxlArray`
    | 函数         | 类型       | 功能                         |
    | ------------ | ---------- | ---------------------------- |
    | `begin()`    | `Iterator` | 返回第一个元素的迭代器       |
    | `end()`      | `Iterator` | 返回最后一个元素之后的迭代器 |
    | `operator[]` | `T&`       | 返回指定下标的元素           |
    | `operator=`  | `yxlArray` | 复制容器                     |
      - 线性链表    `yxlChain` 
    | 函数         | 类型       | 功能                         |
    | ------------ | ---------- | ---------------------------- |
    | `begin()`    | `Iterator` | 返回第一个元素的迭代器       |
    | `end()`      | `Iterator` | 返回最后一个元素之后的迭代器 |
    | `operator[]` | `T&`       | 返回指定下标的元素           |
    | `operator=`  | `yxlChain` | 复制容器                     |