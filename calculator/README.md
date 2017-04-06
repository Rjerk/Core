# 用面向对象编程实现计算器

## C1

实现一个节点类的继承体系，如下：

```
             Node
           /      \
     NumNode     BinNode
              /   /   \   \
            /    /     \    \
     AddNode MinNode MulNode DivNode
```

可以将 (1+2)*(4-1) / 3 转化如下表达式树：

```
              /
           /     \
          *       3
        /   \
       +     -
      / \   / \
     1   2 4   1
```

## C2

利用泛型编程，将上述类的继承体系简化为:

```
             Node
            /    \
       NumNode  BinNode<Op>
```

用
```
BinNode<std::plus<double>>
```
```
BinNode<std::minus<double>>
```
```
BinNode<std::multipies<double>>
```
```
BinNode<std::divides<double>>
```
来具现化BinNode<Op>类模板，通过控制模板参数的类型来实现不同运算。
