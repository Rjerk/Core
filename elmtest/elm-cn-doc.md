# elm-lang 的中文手册 

翻译自  

http://elm-lang.org/

https://github.com/elm-lang/elm-compiler

#前言介绍

函数式编程 (Functional Programming)像是： Haskell, Scala, Closure 等等被开发出来在各式各样的专桉中使用。
但是，这些语言很少被拿来当成开发前端的工具。而Elm就是为前端人所设计的函数式编程语言

Elm 是一个强型别的函数式编程语言。最终会将它编译成 JavaScript 以便于在浏览器上使用。

* 不会有执行阶段错误 (Runtime Error)

* Render 的速度快

* 语法简洁，易于测试

* 完整的错误讯息

* 良好的设计架构 (Elm-Architecture)

它与 React 一样使用了 Virtual DOM 的技术来提高效能并号称比 React 快

官方的[Learn By example](http://elm-lang.org/examples)

# 目录

1.[安装](#安装)

2.[elm工具介绍](#elm-工具)

3.[设定你的Editor的syntax](#编译器的-elm-syntax)

4.[开始学习Elm](#开始学习elm)

5.[语言核心](#语言核心)

6.[Model in elm](#model-in-elm)

7.[elm的核心架构](#the-elm-architecture)

8.[Signals](#signals)

9.[Interop](#interop)

# 安装

1.如果您使用Mac 或 Windows 可以直接点选以下连结进行安装

http://elm-lang.org/install


2.如果您是使用linux OS 可以使用 npm installer 进行安装
```
npm install -g elm
```

3.如果以上对您都不适用，您也可以选择从source去安装，可参考以下连结

https://github.com/elm-lang/elm-platform#get-haskell-working



----

# elm 工具

接着会开始引导您使用Elm 与 Elm 之一系列工具.

我们假设您已安装好Elm

#### 工具

Elm有一系列的工具可帮助您开发Elm程式，在您安装好Elm时，他们会跟着安装在您电脑上:

* [Elm](http://elm-lang.org/get-started#elm)

* [elm-package](http://elm-lang.org/get-started#elm-package)

* [elm-make](http://elm-lang.org/get-started#elm-make)

* [elm-repl](http://elm-lang.org/get-started#elm-repl)
 

以下分别介绍，他们的功能

#### elm

elm 为启动其他工具的方式. 试着打开 terminal 并输入`elm`试试.

如果没出现任何讯息，请先将以下路径，加入环境变数

```
C:\Program Files (x86)\Elm Platform\0.16\bin
```

#### elm-package

elm-package 是一个套件管理工具, 让你可以简单的发佈即安装套件到Elm Package Catalog.

当你要开始一个新的Elm程式时, 执行:
```
elm package install
```

这将会安装` elm-core package` 以即将会创造一个 Elm project的档桉: `elm-package.json`

 `elm-package.json` 用来写一些关于套件相关的讯息，类似一个描述档

以下为一些常用的 commands:

```
install: 安装在 elm-package.json 所描述的套件
publish: 将你的 library 发佈到  Elm Package Catalog
bump: 根据 API changes 改变你的版本号码
diff: 查看两个 API 的差异
```


#### elm-make

elm-make 是在命令列中执行，用来将elm程式编译为HTML与Javascript. 一般都以此种方式来编译elm的程式

当我们在编译时(例如将: Main.elm)编译为  HTML 档桉 (index.html), 你将会写出以下指令:

```
elm make Main.elm --output=index.html
```

可用的附加 flags:
```
--warn: Prints warnings to improve code quality
```

#### elm-repl

REPL 意思为 `read-eval-print-loop` 让你可以执行一些简单的 Elm 语句.  你可以从你的project引入一些程式码到elm-repl进行测试 ， elm-repl 最终将会转为javascript程式码,所以在这之前你需要安装好 node.js . 需要注意的是 elm-rep只提供 command line interface, browser 相关的 函式 将无法作用.

常用的 commands:

:help: 将会印出提示讯息
:exit: 离开REPL

#### elm-reactor

elm-reactor 为Elm的互动式开发工具. 使用 elm-reactor 你可以不用先编译程式就可以执行 Elm programs，
elm-reactor 还提供了 hot swapping 与 time travel debugging.(类似于redux开发时的功能)

执行 elm reactor时 将会执行一个 web server 于 `0.0.0.0:8000` 你可以开启你的 browser 选择你想要执行的程式去执行，
如果你想使用 elm-reactor 更进阶的功能, 点击左侧在档桉名称旁的 wrench ， 之后将会开启档桉，并且在右方显示一些功能栏位.

常用的 flags:

-a=<ADDRESS>: 改变 elm-reactor 执行时的ip位置

由于预设的位置 0.0.0.0 不是所有浏览器都支援，但我们建议使用` -a=localhost`


-p=<PORT>: 改变 elm-reactor执行时所监听的PORT

以下为执行的例子
```
elm reactor -a=localhost
打开浏览器，输入 localhost:8000.
```


以上即为elm tools的相关介绍，可以前往https://github.com/elm-lang查看

----

# 编译器的 elm syntax


[Atom](https://atom.io/packages/language-elm)

[Brackets](https://github.com/lepinay/elm-brackets)

[Emacs](https://github.com/jcollard/elm-mode)

[Light Table](https://github.com/rundis/elm-light)

[Sublime Text](https://github.com/deadfoxygrandpa/Elm.tmLanguage)

[Vim](https://github.com/lambdatoast/elm.vim)

[VS Code](https://github.com/sbrink/vscode-elm)

----

# 开始学习Elm

## 第一个Elm程式

最简单学习Elm的方式，可从这个连结进入 [范例](http://elm-lang.org/examples). 或是可以试试Elm的[线上编辑器](http://elm-lang.org/try)
或是先前提到的[elm-reactor](https://github.com/elm-lang/elm-reactor)

## 进阶学习

在官网的 [documentation](http://elm-lang.org/docs) 页面, 你可以找到许多学习Elm的资源

#### 1.如果你是刚开始学习Elm
建议你可以到 [Elm Complete Guide](http://elm-lang.org/guide/core-language)进行学习，
并且使用 elm-repl 及 Online Editor来帮助你学习。

#### 2.如果你想要观看一些影片来学习
可以到[Pragmatics Studio's Elm tutorial](https://pragmaticstudio.com/elm)

#### 3.在你阅读完 Elm Complete Guide后, 你可以接着阅读
[Elm's Syntax](http://elm-lang.org/docs/syntax) 以及

[Elm's Style Guide](http://elm-lang.org/docs/style-guide). 

(需要注意的是，elm的语句是对缩排敏感的)(类似python)

#### 4.为了更了解如何开发一个大型的Elm程式，你可以阅读
[Elm Architecture Tutorial](https://github.com/evancz/elm-architecture-tutorial/)

#### 5.你也可以到 
[cs223 Functional Programming course](https://www.classes.cs.uchicago.edu/archive/2015/winter/22300-1/Home.html) 
此为芝加哥大学的课程，裡面讲了许多有关 Elm 与 纯函式编程, 但该课程使用的是 Elm 0.14.1 或许有点跟最新版本的Elm有些差异，但不用担心，
你可以随时回来阅读Elm的syntax与style-guide.

#### 6.更多的教学
例如 [Elm for the Frontend Right Now](http://bendyworks.com/elm-frontend-right-now/), 
[Checkboard Grid Tutorial](https://github.com/TheSeamau5/elm-checkerboardgrid-tutorial), 
[Building HTML by Parsing Parameters](http://blog.jessitron.com/2015/08/an-elm-example-reading-url-parameters.html) 
在reddit上的讨论 [/r/elm](http://reddit.com/r/elm) 以及 [mailing list](https://groups.google.com/forum/?fromgroups#!forum/elm-discuss)


#### 7.但最重要的是，看完后不要忘记自己写code! 下面是一些简单的程式，你可以开始试着练习

* 1.写出一个会侦测你的滑鼠指标位于萤幕的左半边或右半边，并且在萤幕中央显示(左方或右方)的程式。

* 2.写出一个会在萤幕上随机位置显示小黑点的程式，并且带有重设、暂停、继续等按钮

* 3.写出一个输入框，让Gitgub使用者输入后，可显示名称，avatar图片，与程式语言清单

* 4.写出一个贪食蛇游戏(并且可显示最高分数)


另外: 如果你在写elm程式时陷入困境,可将你的问题于[mailing list](https://groups.google.com/forum/?fromgroups#!forum/elm-discuss)发问   或是到irc上的 #elm IRC, freenode.net频道发问。


# 语言核心

  [Values](#values)
  
  [Functions](#functions)
  
  [If Expressions](#if-expressions)
  
  [Lists](#list)
  
  [Tuples](#tuples)
  
  [Records](#records)
  
  
## Values

我们先来看一下，下面的例子
```
> "hello"
"hello"

> "hello" ++ "world"
"helloworld"

> "hello" ++ " world"
"hello world"
```
Elm 使用 (++) 来连接字串


Elm的数学部分和其他语言类似

```
> 2 + 3 * 4
14

> (2 + 3) * 4
20

和JavaScript不同， Elm 具有floating point division (/)和 integer division (//)，分别用来计算具有小数或只有整数部分

> 9 / 2
4.5

> 9 // 2
4

```
## Functions
让我们写一个 isNegative的函式， 其具有参数可接受数字，并且确认他是否小于零，并返回 True 或 False.
```
> isNegative n = n < 0
<function>

> isNegative 4
False

> isNegative -7
True

> isNegative (-3 * -4)
False

```
和JavaScript、Python、Java的函式写法不同. 不使用逗点来分隔参数，而是使用空格。

所以 `(add(3,4))` 将为 `(add 3 4)`
此种作法将可避免一个函式的参数区块具有许多逗点，当你习惯后，你会发现他看起来比较简洁。 你可以使用 elm-html package 来理解。

#If Expressions

使用条件表达式
```
> if True then "hello" else "world"
"hello"

> if False then "hello" else "world"
"world"
 if then else 用来分隔条件，我们不用再加上任何`{}`符号

需要注意的一点是:Elm 的numbers、strings、lists 不可用来进行类似 boolean 的比较

接着下们的表达式可以用来区别，是否值大于9000

> over9000 powerLevel = \
|   if powerLevel > 9000 then "It's over 9000!!!" else "meh"
<function>

> over9000 42
"meh"

> over9000 100000
"It's over 9000!!!"
```
使用backslash `\` 于 REPL ˋ中，可以让我们进行断行，让function的主要部分写在名字之后的下一行，可以让我们更容易阅读, 
建议在所有functions 和 values 中都用此种写法去写。

## List

Lists 是在Elm中最常见的资料结构. 类似于JavaScript 或 Java中的阵列结构,保存一系列的相关同型别资料。

可以查看有关List可以使用的function [List](http://package.elm-lang.org/packages/elm-lang/core/3.0.0/List)
```
> names = [ "Alice", "Bob", "Chuck" ]
["Alice","Bob","Chuck"]

> List.isEmpty names
False

> List.length names
3

> List.reverse names
["Chuck","Bob","Alice"]

> numbers = [1,4,3,2]
[1,4,3,2]

> List.sort numbers
[1,2,3,4]

> double n = n * 2
<function>

> List.map double numbers
[2,8,6,4]
再次强调，List中的每个内容都是相同型别

```
对比一些物件导向语言, Elm 的 functions 和 data 是分开存在的。为了具有模组化 ， Elm 使用了许多模组， 当我们使用` List.isEmpty` 
我们是从List module 中去调用该方法，List module 和lists具有很大的关係。

## Tuples

Tuples 是在Elm中，另外一种很有用的资料结构.tuple 裡面包含一系列的固定值，可以有不同资料型别.当你要从function返回不同资料时可用逗点分隔，
下面的例子中，这个 function会取得 name 并返回一个message给user:
```
> import String

> goodName name = \
|   if String.length name <= 20 then \
|     (True, "name accepted!") \
|   else \
|     (False, "name was too long; please limit it to 20 characters")

> goodName "Tom"
(True, "name accepted!")
```

但是，当你的程式开始变得複杂时，我们会建议使用records来取代 tuples。

## Records

 record 是具有 key-value pairs 的资料结构, 类似于 JavaScript 或 Python中的物件(Object)，你将会发现他在Eml中很好用，
 
 下面有些范例
```
> point = { x = 3, y = 4 }
{ x = 3, y = 4 }

> point.x
3

> bill = { name = "Gates", age = 57 }
{ age = 57, name = "Gates" }

> bill.name
"Gates"
```
 Elm 把 .x (x 为 key 值) 也做成了一个函数，所以我们不只可以用bill.name 也可以用 .name bill 来取得同样的值。
 ```
 > .name bill
"Gates"

> List.map .name [bill,bill,bill]
["Gates","Gates","Gates"]
```
当 functions 和 records 结合时, 你可以使用以下写法，更为简洁
```
> under70 {age} = age < 70
<function> 

> under70 bill
True

> under70 { species = "Triceratops", age = 68000000 }
False
```


从范例中我们可以传递任何 record 进去， 当他有一个  number 型态的age field 

It is often useful to update the values in a record.
```
> { bill | name = "Nye" }
{ age = 57, name = "Nye" }

> { bill | age = 22 }
{ age = 22, name = "Gates" }
```
当你更新资料时，Elm不会覆盖旧资料，而是新建一笔新的record，当你更新十笔资料的其中一笔时，
Elm会用有效率的方式连同其他九笔一同更新。

#### 比较 Records 与 Objects

Records 在 Elm 类似于 JavaScript的物件(Object), 但有一些关键点不同。 以下为records的不同之处:

* 你不可以使用不存在的field.

* field不可为 undefined 或是 null.

* 你不可以使用 this 或 self 等关键字来创造递迴的 records 

Elm 鼓励你把逻辑和资料分开，因为Elm想把这个在一般物件导向程式中所会遇到的问题避免掉。

Records 也支援 [structural typing](https://en.wikipedia.org/wiki/Structural_type_system)

这个意思为 Elm 在必要的 fields 存在时可以使用在任何情况. 这给我们很大的弹性


# Model in elm


这一章节将带领你，处理複杂的资料时可以有良好的方式去处理，也可以方便未来去重构，以下将从 “contracts”开始讲起。

## Contracts

我们在定义个程式的整体模型时，其中的资料型态占了很重要的部分，想像他们是一份会被编译器检查的合约，并且写着类似“我只接受字串” 
确保不会有其他的资料型态进入。这在 Elm 中是避免执行时期的错误是很重要的因素。

注意: 在elm中“types” 意思为 “types as they appear in Elm”.这与 Java 中的type有很大的区别! 许多程序员只有在 Java、JavaScript or Python or Ruby使用type，有时他们觉得type是很不必要的，因为使用的type最后编译完，还是会得到有关type相关的错误讯息
这是什麽原因?

我们写下的 contracts 为“type annotations” 也是我们写出我们资料长的什麽样子的地方。
```
fortyTwo : Int
fortyTwo =
  42


names : List String
names =
  [ "Alice", "Bob", "Chuck" ]


book : { title: String, author: String, pages: Int }
book =
  { title = "Demian", author = "Hesse", pages = 176 }
```
这裡我们写了一些常会使用到的资料型别， fortyTwo 为一个 integer, names是一个list of strings,而 book 是一个 record with certain fields. 

```
import String


longestName : List String -> Int
longestName names =
  List.maximum (List.map String.length names)


isLong : { record | pages : Int } -> Bool
isLong book =
  book.pages > 400
```

在上面这个范例 longestName ,我们要求输入的值为一个 list of strings. 假如有人想要输入一个 list of integers 或是 books, 其中的 String.length function将会中断,因为我们定义了 contract。我们还指定了 longestName function 将要返回一个 Int ，所以当我们接他的返回值用在其他地方时，可以保证他会是一个数字

其中的isLong example 做的是同样的事情，他要求一个 record with a field 名称为 pages 型态为 integers.当其他人输入任何资料时，都需要一个 pages field!

上面两个范例中，我们写了 contracts 说明 “我需要你输入某种型态的值, 而我也会返回给你同型态的值.” 这将是 Elm 摆脱执行时期发生错误的关键， 只要我们遵守条件，我们永远可以知道该function需要什麽型态的值，以及将会返回什麽型态的值。

## Enumerations(列举)

创造一个自订的资料型态，并列举他可能的值，想像我们建造一个 todo list 并且想要再建造一个 filter 来过滤哪些task是看的见的

我们可以如下定义三种显示方式
```
type Visibility = All | Active | Completed
```

如同上面定义的方式，未来我们要传递资料的 type 为 Visibility 时，可能的值只能上面三种的其中一种。

我们使用case-expressions来让我们在接收到不同的值时做不同的事，和JavaScript 中的switch-statements类似,但 case-expression 不同的是，你不需要在每个case的结尾写上break

```
toString : Visibility -> String
toString visibility =
    case visibility of
      All ->
          "All"

      Active ->
          "Active"

      Completed ->
          "Completed"


-- toString All == "All"
-- toString Active == "Active"
-- toString Completed == "Completed"
```
这个 case-expression 意思为,如果传入的 visibility为 All 则回传"ALL" ，以此类推。

## State Machines(状态机)

接着我们想要显示一个使用者是否有登入， 我们可以建造一个小型的state machine 让使用者可以在匿名以及登入后的使用者名称做切换。

```
type User = Anonymous | LoggedIn String
```

需要注意的是， LoggedIn 中的值有额外的资讯!意思是当type为LoggedIn 将可接收到一个字串的值. 我们可以
在Anonymous或LoggedIn 使用case-expressions判断，之后再用 LoggedIn 字串的值，产生不同图片
```
userPhoto : User -> String
userPhoto user =
    case user of
      Anonymous ->
          "anon.png"

      LoggedIn name ->
          "users/" ++ name ++ "/photo.png"
```

假如他们没有登入，我们产生"anon.png", 假如他们已登入，即产生对应的图片. 假设我们现在有数个user，并且想要一次产生他们的图片

```
activeUsers : List User
activeUsers =
    [ Anonymous
    , LoggedIn "Tom"
    , LoggedIn "Steve"
    , Anonymous
    ]
```

我们可用map的方式，一次产生不同图片
```
photos =
    List.map userPhoto activeUsers

-- photos =
--     [ "anon.png"
--     , "users/Tom/photo.png"
--     , "users/Steve/photo.png"
--     , "anon.png"
--     ]
```

所有的使用者如此一来都有了对应的图，这是一个简单的  state machine 范例， 但你可以想像，假设使用者有五种不同的状态，我们可以精确的定义好Model，让错误的发生率降低。

## Tagged Unions

接着我们试着把一系列不同的资料型态以紧密的方式结合在一起。或称(ADTs)

假设我们在主控台上创造一系列的小工具. 其中一个为点阵图，另一个为 log data，最后一个为时间图， Type unions 让他们可以简单的结合在一起
:

```
type Widget
    = ScatterPlot (List (Int, Int))
    | LogData (List String)
    | TimePlot (List (Time, Int))
```
你可以想像是把三种不同的type放一起. 每个type有一个标籤 ，像是 ScatterPlot 及 LogData.这麽做可以区隔他们. 
接着我们将输出 widget 如同以下范例:

```
view : Widget -> Element
view widget =
    case widget of
      ScatterPlot points ->
          viewScatterPlot points

      LogData logs ->
          flow down (map viewLog logs)

      TimePlot occurrences ->
          viewTimePlot occurrences
```
根据不同种类的widget， 我们将会输出不同的东西， 如果我们想要进一歩让 time plots 展示为一个 logarithmic scale(
对数刻度). 我们可以将 Widget 改为如下

```
type Scale = Normal | Logarithmic

type Widget
    = ScatterPlot (List (Int, Int))
    | LogData (List String)
    | TimePlot Scale (List (Time, Int))
```

现在 TimePlot 有了两个部分的 data，而每个 tag 可以有不同的 types.

## Banishing NULL

许多语言都有 null 的型态. 每次你觉得你的资料是一个字串，但其实你拥有的只是一个 null， 你需要检查吗? 这是否会对你的程式带来重大影响?下面将会对这类问题进行讨论。

Elm 使用了一个 type 叫做 Maybe，来避免了这个问题，你可以想像他把null明确的写出，所以我们可以知道何时需要去处理他。

```
type Maybe a = Just a | Nothing
```

这个type有一个引数 a ，我们可以对他引用任何想要的值.我们可以使用像是 (Maybe Int) 他将是一个整数或是Nothing。例如， 我们想要把字串解析成月份

```
String.toInt : String -> Result String Int


toMonth : String -> Maybe Int
toMonth rawString =
    case String.toInt rawString of
      Err message ->
          Nothing

      Ok n ->
          if n > 0 && n <= 12 then Just n else Nothing
```

这个 toMonth的 contract 明确的指出他将会返回一个整数，否则将不返回任何东西! 所以你将不用在烦恼会有null的产生。

## Recursive Data Structures(递迴性的资料结构)

假如你曾经在 C 或 Java中使用过  linked list 你将会认为在 Elm 中使用是很简单的.下面的是一个list的type. list 的最前面只能接受:
empty或是something followed by a list.我们可将这一个非正式的定义转为一个 type:

```
type List a = Empty | Node a (List a)
```
所以我们创造一个 type 名为 List.  list 可以是 empty 或是拥有一个 element (the head of the list) 以及 “the rest of the list” ( the tail of the list).

List 接受一个 type 当做 argument, 所以我们可以创造 (List Int) 或是 (List String) 以及其他， 如同以下范例
```
Empty
Node 1 Empty
Node 3 (Node 2 (Node 1 Empty))
```

他们都拥有同样的 type，所以可以被使用在同个地方。当我们在做 pattern match时 可以定义于 case所要做的事。 假设我们想计算List中所有数字的总和， 下面范例中的 function 定义了一些可能发生的情境。

```
sum : List Int -> Int
sum xs =
    case xs of
      Empty ->
          0

      Node first rest ->
          first + sum rest
```
假设我们得到一个 Empty value, 总和将为 0。 假设我们有一个 Node ，并且将元素一个个加到总合中，将会产生如` (sum (Node 1 (Node 2 (Node 3 Empty))))` 的情况，和下面范例相同:

```
sum (Node 1 (Node 2 (Node 3 Empty)))
1 + sum (Node 2 (Node 3 Empty))
1 + (2 + sum (Node 3 Empty))
1 + (2 + (3 + sum Empty))
1 + (2 + (3 + 0))
1 + (2 + 3)
1 + 5
6
```

接着我们可以试着产生二元树

```
type Tree a = Empty | Node a (Tree a) (Tree a)
```
A tree 可能为 empty或是一个 node 拥有一个 value 与 two children. 可看下面的范例，来学习更多关于 union types 的资料结构

http://elm-lang.org/examples/binary-tree

> 想像我们在 Java 做出这个范例.我们可能会使用 super class 和 两个 sub classes 来定义二元树。 想像我们是使用 JavaScript.
一开始看起来不会很困难，但当我们在重构时，你将会遇到许多隐藏的错误。

我们也可以 model 一个程式语言为 data ，在这个情况下,他将只处理有关 Boolean algebra:

```
type Boolean
    = T
    | F
    | Not Boolean
    | Or  Boolean Boolean
    | And Boolean Boolean

true = Or T F
false = And T (Not T)
```
当我们 model好可能的值之后，我们可以定义 functions 例如eval 用来执行 Boolean 让其为 True 或 False，可查看下面的连结范例

http://elm-lang.org/examples/boolean-expressions

# The Elm Architecture

这个教程 “The Elm Architecture” 你将会看到许多跟 [Elm][] 相关的程式, 包含 [TodoMVC][] 、 [dreamwriter][]以及正式上线的  [NoRedInk][] 、 [CircuitHub][]. 了解这个设计模式将对你在 Elm 中的程式或任何其他编程都很有帮助。

[Elm]: http://elm-lang.org/
[TodoMVC]: https://github.com/evancz/elm-todomvc
[dreamwriter]: https://github.com/rtfeldman/dreamwriter#dreamwriter
[NoRedInk]: https://www.noredink.com/
[CircuitHub]: https://www.circuithub.com/

 Elm 架构中的设计模式让你的元件可以有无限嵌套. 对于模组化、 程式码复用、 测试很有帮助，最终让你可以简单的设计出一个複杂但模组化的web程式。 下面将有八个范例

  1. [Counter](http://evancz.github.io/elm-architecture-tutorial/examples/1.html)
  2. [Pair of counters](http://evancz.github.io/elm-architecture-tutorial/examples/2.html)
  3. [List of counters](http://evancz.github.io/elm-architecture-tutorial/examples/3.html)
  4. [List of counters (variation)](http://evancz.github.io/elm-architecture-tutorial/examples/4.html)
  5. [GIF fetcher](http://evancz.github.io/elm-architecture-tutorial/examples/5.html)
  6. [Pair of GIF fetchers](http://evancz.github.io/elm-architecture-tutorial/examples/6.html)
  7. [List of GIF fetchers](http://evancz.github.io/elm-architecture-tutorial/examples/7.html)
  8. [Pair of animating squares](http://evancz.github.io/elm-architecture-tutorial/examples/8.html)




**注意**: 要运行这些范例需先, [安装 Elm](http://elm-lang.org/install) 以及 fork this repo. 每个范例都会教导你，该如何去运行它


## Elm中的基本设计模式概念

每个 Elm program 都有如下三个区块架构:


  * model
  * update
  * view


> 如果你还没学习过elm可以先参考 [language docs](http://elm-lang.org/docs) 与[the complete guide](http://elm-lang.org/docs#complete-guide)

```elm
-- MODEL

type alias Model = { ... }


-- UPDATE

type Action = Reset | ...

update : Action -> Model -> Model
update action model =
  case action of
    Reset -> ...
    ...


-- VIEW

view : Model -> Html
view =
  ...
```

这个教程都是由上面范例的这个设计模式 与一些小变化及插件所组成的。


## Example 1: A Counter

**[demo](http://evancz.github.io/elm-architecture-tutorial/examples/1.html) / [see code](examples/1/)**

第一个范例是一个简单的计数器，可以进行增加与减少

[The code](examples/1/Counter.elm) 由一个很简单的 model所组成， 我们要做的只是追踪一个会改变的数字

```elm
type alias Model = Int
```

当 model 更新时， 我们定义一系列 actions, 以及一个 `update` function用来接收 actions并执行相应的case

```elm 
type Action = Increment | Decrement

update : Action -> Model -> Model
update action model =
  case action of
    Increment -> model + 1
    Decrement -> model - 1
```

需要注意的是 `Action` [union type][] 并没有做任何事， 他只是描述了一个动作的型态. 假设有人想让计数器在点击某个按钮时可以让数字变double, 这将需要增加一个新的 `Action`类型，这可以保持我们的Model简洁，并且他人可以清楚的知道他可以对这个model进行何种操作

[union type]: http://elm-lang.org/learn/Union-Types.elm

 `view` our `Model`.我们使用 [elm-html][]来创造一个 HTML，其它包含一个 div 裡面装有一个 decrement button以及a div showing the current count与 an increment button.

[elm-html]: http://elm-lang.org/blog/Blazing-Fast-Html.elm

```elm
view : Signal.Address Action -> Model -> Html
view address model =
  div []
    [ button [ onClick address Decrement ] [ text "-" ]
    , div [ countStyle ] [ text (toString model) ]
    , button [ onClick address Increment ] [ text "+" ]
    ]

countStyle : Attribute
countStyle =
  ...
```
在 `view` 这个函式中的 `Address`我们将会在下一节提到! 在这裡我们使用了 `Model` 并产生一些 `Html`. 我们并没有手动去更动DOM，
这让这个 library [有了更好的自由度及优化][elm-html] 并且让画面 rendering的速度更快。 以及 `view`是一个function ，我们可使用 Elm中的 module system、 test frameworks与其他 libraries 来创造 views.

这种设计模式是Elm中的基本架构，接着的范例中都是以此种架构去进行 `Model`, `update`, `view`.


## Starting the Program

在elm程式中，都会有一个主体的部分，程式从此开始进行，如同以下的范例均是以 `Main.elm`为主体

```elm
import Counter exposing (update, view)
import StartApp.Simple exposing (start)

main =
  start { model = 0, update = update, view = view }
```

我们使用了 [`StartApp`](https://github.com/evancz/start-app) 来建造初始的 model 、 update 与 view functions. 这即是Elm's [signals](http://elm-lang.org/learn/Using-Signals.elm)的概念，所以你暂时还不用了解signals的概念。

其中的关键点在于 `Address`。 每个 event handler 于我们的 `view` function 之中会回传一个特别的  address. It just sends chunks of data along.而 `StartApp` package 监测每个来自 address 的讯息，并转送到 `update` function. 接着 model 被更新 ，然后[elm-html][] 把view更新

 Elm 程式中的单向资料流如同下图的概念

![Signal Graph Summary](diagrams/signal-graph-summary.png)

图片中的蓝色部分为 Elm 程式的核心，此即为我们先前提到的 model/update/view 概念。 未来在写Elm程式时，即可以此种架构去规划，让逻辑的部分完全与View分开。


## Example 2: A Pair of Counters

**[demo](http://evancz.github.io/elm-architecture-tutorial/examples/2.html) / [see code](examples/2/)**

在范例1中，我们建立了一个简单的计数器。但我们该如何扩展架构，当我们需要两个计数器时呢? 

 Elm架构中的优点是  **我们可以不更动程式码**来达成扩展架构。 当我们在上个范例创造 `Counter` 模组时,他把细节封装起来，所以我们可以把他用在别处。

```elm
module Counter (Model, init, Action, update, view) where

type Model

init : Int -> Model

type Action

update : Action -> Model -> Model

view : Signal.Address Action -> Model -> Html
```

创造模组化的code 是很抽象的。我们把一些 functionality 的部分提供出来并隐藏一些实做细节。在 `Counter` module外面，我们只看得到
一些基本的关于 `Model`, `init`, `Action`, `update`, 与 `view`。我们并不在乎他们是如何被实做的。 事实上,这是不可能被知道的
. 意思是当我们选择不把他公开时，其他人无法知道我们的实做细节。

所以我们可以複用 `Counter` module，并用他来创造 `CounterPair`，和先前一样，我们先从 `Model`开始:

```elm
type alias Model =
    { topCounter : Counter.Model
    , bottomCounter : Counter.Model
    }

init : Int -> Int -> Model
init top bottom =
    { topCounter = Counter.init top
    , bottomCounter = Counter.init bottom
    }
```

这个 `Model` 拥有两个区块分别为显示在萤幕的top和bottom。用来完整描述我们应用程式中的 state。 以及一个 `init` function 
让我们在未来更新`Model`所用。 

接着我们将定义 `Actions` ，将包含: reset all counters、 update the top counter与 update the bottom counter.

```elm
type Action
    = Reset
    | Top Counter.Action
    | Bottom Counter.Action
```

注意到的是，上面的 [union type][] 指向 `Counter.Action` type,但我们并不知道这些 actions，当我们创造 `update` function时， 我们才将
这些 `Counter.Actions` 指向正确的地方:

```elm
update : Action -> Model -> Model
update action model =
  case action of
    Reset -> init 0 0

    Top act ->
      { model |
          topCounter = Counter.update act model.topCounter
      }

    Bottom act ->
      { model |
          bottomCounter = Counter.update act model.bottomCounter
      }
```

最后，我们建造一个 `view` function用来在画面上显示两个 counters 与一个 reset button.

```elm
view : Signal.Address Action -> Model -> Html
view address model =
  div []
    [ Counter.view (Signal.forwardTo address Top) model.topCounter
    , Counter.view (Signal.forwardTo address Bottom) model.bottomCounter
    , button [ onClick address Reset ] [ text "RESET" ]
    ]
```

我们可以重複使用 `Counter.view` function 于两个 counters. 于每个 counter 我们创造一个 forwarding address.我们在这裡做的事为，这两个计数器会把传出的讯息以 `Top` or `Bottom` tag起来，让我们可以区分。

接着我们还可以让他更巢状化，我们可以使用 `CounterPair` module,指对外展示出一些 key values 与d functions, 再创造一个 `CounterPairPair` 或是任何你想要的。


## Example 3: A Dynamic List of Counters

**[demo](http://evancz.github.io/elm-architecture-tutorial/examples/3.html) / [see code](examples/3/)**

接着我们要来创造一系列的计数器，我们可使用add或remove来增加与减少画面上计数器的数量。

我们一样複用 `Counter` module ，如同上面的范例。 

```elm
module Counter (Model, init, Action, update, view)
```

接着我们可以直接开始设计 `CounterList` module，和之前一样 ，先从 `Model`开始:

```elm
type alias Model =
    { counters : List ( ID, Counter.Model )
    , nextID : ID
    }

type alias ID = Int
```

现在我们的model有一系列的counter,每个均拥有一个独特的ID，让我们可以区别他们，
(这些 ID 还带给我们于 rendering时具有最佳化的表现[`key`][key] )

我们的model 还包含了一个`nextID`这可以帮助我们在新增counter时，可以分配新的ID给他

[key]: http://package.elm-lang.org/packages/evancz/elm-html/latest/Html-Attributes#key

现在我们来定义一系列的`Actions` 用来传给 model。包含了 add counters、 remove counters与update certain counters.

```elm
type Action
    = Insert
    | Remove
    | Modify ID Counter.Action
```


现在我们可以定义`update` function.

```elm
update : Action -> Model -> Model
update action model =
  case action of
    Insert ->
      let newCounter = ( model.nextID, Counter.init 0 )
          newCounters = model.counters ++ [ newCounter ]
      in
          { model |
              counters = newCounters,
              nextID = model.nextID + 1
          }

    Remove ->
      { model | counters = List.drop 1 model.counters }

    Modify id counterAction ->
      let updateCounter (counterID, counterModel) =
            if counterID == id
                then (counterID, Counter.update counterAction counterModel)
                else (counterID, counterModel)
      in
          { model | counters = List.map updateCounter model.counters }
```

可以看下面的描述:

  * `Insert` &mdash; 首先我们创造了一个新的计数器， 放在所有以建造的计数器的最后。
  接着增加 `nextID` 来让下一次使用。

  * `Remove` &mdash;从许多计数器中移除最前面那个

  * `Modify` &mdash; 找寻这些计数器中与其符合的 ID, 我们在这个符合的计数器上执行这个 `Action`

最后是定义我们的 `view`.

```elm
view : Signal.Address Action -> Model -> Html
view address model =
  let counters = List.map (viewCounter address) model.counters
      remove = button [ onClick address Remove ] [ text "Remove" ]
      insert = button [ onClick address Insert ] [ text "Add" ]
  in
      div [] ([remove, insert] ++ counters)

viewCounter : Signal.Address Action -> (ID, Counter.Model) -> Html
viewCounter address (id, model) =
  Counter.view (Signal.forwardTo address (Modify id)) model
```

有趣的地方在于其中的 `viewCounter` function. 他使用先前的
`Counter.view` function，但这次，我们提供了一个 forwarding address 上面标住了所有被 rendered的counter的相关讯息。

当我们真正创造 `view` function时， 我们对所有counters进行了`viewCounter`的map动作，并且创造两个按钮:add 、remove ，直接传递到 the `address` 中

上面这种创造 ID的方法，可以用于任何你想要于子组件创造动态数字时，也可应用在其他范例，例如: list of user profiles 、 tweets 或是 newsfeed items 以及 product details中。


## Example 4: A Fancier List of Counters

**[demo](http://evancz.github.io/elm-architecture-tutorial/examples/4.html) / [see code](examples/4/)**

但是，如果我们想要不只是有一个移除按钮，而是想让每个按钮拥有自己专属的移除按钮呢? 


要这麽做的话，我们先保持原本的`view` function 不变，并且可以新增一个`viewWithRemoveButton`，如以下范例:
```elm
module Counter (Model, init, Action, update, view, viewWithRemoveButton, Context) where

...

type alias Context =
    { actions : Signal.Address Action
    , remove : Signal.Address ()
    }

viewWithRemoveButton : Context -> Model -> Html
viewWithRemoveButton context model =
  div []
    [ button [ onClick context.actions Decrement ] [ text "-" ]
    , div [ countStyle ] [ text (toString model) ]
    , button [ onClick context.actions Increment ] [ text "+" ]
    , div [ countStyle ] []
    , button [ onClick context.remove () ] [ text "X" ]
    ]
```

`viewWithRemoveButton` function 增加了一个额外的按钮，其中  increment/decrement 按纽送出讯息到 `actions` address 中，但移除按钮
送出讯息到 `remove` address中。 在 `remove` 讯息中写了类似下面的文字, &ldquo;任何拥有我的人请移除我!&rdquo; 

现在我们有了新的 `viewWithRemoveButton`，我们可以建造一个 `CounterList` module 用来放置每个独立的计数器， 其中 `Model` 和范例3的相同  

```elm
type alias Model =
    { counters : List ( ID, Counter.Model )
    , nextID : ID
    }

type alias ID = Int
```

但这裡的 actions 有一些改变，这裡我们想让他可以移除特定的按钮，所以 `Remove` case 现在拥有一个 ID。

```elm
type Action
    = Insert
    | Remove ID
    | Modify ID Counter.Action
```
其中的`update` function 和范例 3的相同。

```elm
update : Action -> Model -> Model
update action model =
  case action of
    Insert ->
      { model |
          counters = ( model.nextID, Counter.init 0 ) :: model.counters,
          nextID = model.nextID + 1
      }

    Remove id ->
      { model |
          counters = List.filter (\(counterID, _) -> counterID /= id) model.counters
      }

    Modify id counterAction ->
      let updateCounter (counterID, counterModel) =
            if counterID == id
                then (counterID, Counter.update counterAction counterModel)
                else (counterID, counterModel)
      in
          { model | counters = List.map updateCounter model.counters }
```

其中的 `Remove`， 我们过滤出了想要的ID


最后是 `view`:

```elm
view : Signal.Address Action -> Model -> Html
view address model =
  let insert = button [ onClick address Insert ] [ text "Add" ]
  in
      div [] (insert :: List.map (viewCounter address) model.counters)

viewCounter : Signal.Address Action -> (ID, Counter.Model) -> Html
viewCounter address (id, model) =
  let context =
        Counter.Context
          (Signal.forwardTo address (Modify id))
          (Signal.forwardTo address (always (Remove id)))
  in
      Counter.viewWithRemoveButton context model
```

在 `viewCounter` function中，我们建造了 `Counter.Context` 用来传递所有必要的 forwarding addresses。在两个情况，我们均标注了 `Counter.Action` 让我们知道该移除或修改哪个counter、


## Big Lessons So Far(到目前为止)

**Basic Pattern** &mdash; 所有东西都是围绕着 `Model`所建构的，包含 `更新` model, 以及将model转为 `view` ，都是根据这个设计模式在变动。

**Nesting Modules** &mdash; Forwarding addresses 让巢状化更加简单，把实做细节整个隐藏起来。 我们可以继续往下一层深入实做，而每一层只需要知道在他的上一层发生了什麽事就好。

**Adding Context** &mdash; 有时在 `更新` 或是 `检视` 我们的 model时，额外的资讯是很必要的。我们可以增加一些 `Context`到这些 functions 在避免 `Model`变得更複杂的情况下，将这些资讯传递进去。

```elm
update : Context -> Action -> Model -> Model
view : Context' -> Model -> Html
```

在巢状结构下的每一层， 我们可以导出一些特定的 `Context`给子模组使用。

**Testing is Easy** &mdash; 我们在这建立的所有function都是所谓的 [pure functions][pure].这让你在测试你的 `update` function时
变得很简单。 在这之中没有特定的步骤，你可以直接呼叫你想测试的函式与参数来进行测试。

[pure]: http://en.wikipedia.org/wiki/Pure_function


## Example 5: Random GIF Viewer

**[demo](http://evancz.github.io/elm-architecture-tutorial/examples/5.html) / [see code](examples/5/)**

我们展示了如何建立巢状的元件， 但，我们该如何执行一个HTTP request呢?如何跟 database 取得资料?在这个范例中使用了 [the `elm-effects` package][fx]来建立一个简单的元件，可以从 giphy.com取得随机的 gifs  其中包含 “funny cats” topic。

[fx]: http://package.elm-lang.org/packages/evancz/elm-effects/latest

在这个范例[the implementation](examples/5/RandomGif.elm)，与范例1很类似， `Model` 如下(非常典型)l:

```elm
type alias Model =
    { topic : String
    , gifUrl : String
    }
```

我们需要知道要找寻的 `topic` 以及 `gifUrl`。这个范例特别点在于`init` 与 `update`是一个暂时为空想的types:

```elm
init : String -> (Model, Effects Action)

update : Action -> Model -> (Model, Effects Action)
```

相较于直接返回一个新的 `Model`，为了让我们可以执行一些效果[the `Effects` API][fx_api]，可参考如下范例

[fx_api]: http://package.elm-lang.org/packages/evancz/elm-effects/latest/Effects

```elm
module Effects where

type Effects a

none : Effects a
  -- don't do anything

task : Task Never a -> Effects a
  -- request a task, do HTTP and database stuff
```

其中的 `Effects` type为一个 拥有许多不同 tasks的资料结构，将会在未来去执行，我们用下面的范例来展示 `update` 是如何执行的:

```elm
type Action
    = RequestMore
    | NewGif (Maybe String)


update : Action -> Model -> (Model, Effects Action)
update msg model =
  case msg of
    RequestMore ->
      ( model
      , getRandomGif model.topic
      )

    NewGif maybeUrl ->
      ( Model model.topic (Maybe.withDefault model.gifUrl maybeUrl)
      , Effects.none
      )

-- getRandomGif : String -> Effects Action
```

使用者可以触发一个 `RequestMore` action 于点击“More Please!” 按钮之后， 当server 回覆时将返回一个 `NewGif` action，这两个情景都写在`update` function中。

其中 `RequestMore` 将会先返回一个已存在的 model， 并且我们还使用了 `getRandomGif` function建造了一个 `Effects Action`。 在后面会讲到`getRandomGif`是如何定义的。现在我们只需要知道，当`Effects Action` 在执行时，他会产生大量的 `Action` values并且被导向到程式的各个部分。最后 `getRandomGif model.topic` 将产生向下面这样的action:

```elm
NewGif (Just "http://s3.amazonaws.com/giphygifs/media/ka1aeBvFCSLD2/giphy.gif")
```

并且返回一个`Maybe` 因为这个送往server的request可能会失败。 `Action`会被传回 `update` function. 所以假设向server的请求失败时，我们依然保持原有的 `model.gifUrl`.

在 `init`将会发生相同的事。他定义了一个初始的 model并且使用特定的topic向giphy.com’s API请求 GIF 图片。

```elm
init : String -> (Model, Effects Action)
init topic =
  ( Model topic "assets/waiting.gif"
  , getRandomGif topic
  )

-- getRandomGif : String -> Effects Action
```

当 random GIF effect 完成时， 他将会产生一个 `Action` 并且导向 `update` function.

> **Note:** 目前为止我们使用了 `StartApp.Simple` module 来源为[the start-app package](http://package.elm-lang.org/packages/evancz/start-app/latest)接着我们需要更新 `StartApp` module. 它可以用来处理更複杂的应用
. It has [a slightly fancier API](http://package.elm-lang.org/packages/evancz/start-app/latest/StartApp)他将可以处理 new `init` 与 `update` types.

其中需要注意的一点是 `getRandomGif` function 用来定义如何取得 random GIF，他使用了 [tasks][] 与 [the `Http` package][http], 下面的范例将会教导如何使用他们:

[tasks]: http://elm-lang.org/guide/reactivity#tasks
[http]: http://package.elm-lang.org/packages/evancz/elm-http/latest

```elm
getRandomGif : String -> Effects Action
getRandomGif topic =
  Http.get decodeImageUrl (randomUrl topic)
    |> Task.toMaybe
    |> Task.map NewGif
    |> Effects.task

-- 第一行创造了一个 HTTP GET request. 他试着
-- 去从  `randomUrl topic`取得JSON 
-- 并且使用 `decodeImageUrl`解析它，下方可以看到他们的定义
--
-- 接着我们使用了 `Task.toMaybe`来抓取任何潜在的错误 
-- 并且让 `NewGif` tag 的结果转为 `Action`.
-- 最后我们将它转为 `Effects` value 让它可以用在接下来的
-- `init` 或是 `update` functions中.


-- 给入一个 topic,与 URL 传给 giphy API.
randomUrl : String -> String
randomUrl topic =
  Http.url "http://api.giphy.com/v1/gifs/random"
    [ "api_key" => "dc6zaTOxFJmzC"
    , "tag" => topic
    ]


--  JSON decoder 将会接受大批的 JSON 并且
-- 取出其中的 `json.data.image_url` 
decodeImageUrl : Json.Decoder String
decodeImageUrl =
  Json.at ["data", "image_url"] Json.string
```

当我们写好这些后，未来，我们将可以使用 `getRandomGif` 于 `init`与 `update` functions中

其中有趣的一点是， `getRandomGif`所返回的task将永远不会失败，因为我们希望所有可能发生的失败都要被明确的处理，下面将会解释这点。

每个`Task` 有两个型态，分别为 failure type 与 success type。 举例来说:一个 HTTP task 可能有一个type 类似 `Task Http.Error String`
以此范例来说，它可能会失败于`Http.Error` 或是成功返回 `String`， 这让我们可以处理一系列的task并且不用处理错误发生。

现在，假设我们有一个 component 要求了一个  task, 但是这个 task 失败了。接下来会发生什麽事? 谁会被通知? 该如何复原它? 
我们创造了一个发生错误时的错误型态 `Never` 我们让任何可能发生的错误，都转到了 success type ，让他们可以明确地被处理。
在范例中，我们使用了 `Task.toMaybe : Task x a -> Task y (Maybe a)` 所以我们的 `update` function 可以精准的处理 HTTP failures的情况。



## Example 6: Pair of random GIF viewers

**[demo](http://evancz.github.io/elm-architecture-tutorial/examples/6.html) / [see code](examples/6/)**

一般的effects 可以被处理，但如果是*巢状的* effects呢?这个范例使用了和范例 5同样的程式，用来建立一对独立的GIF viewers.

在你看完 [the implementation](examples/6/RandomGifPair.elm)后，你会发现他和范例二有点类似， 其中的 `Model`定义了两个 `RandomGif.Model` 的值:

```elm
type alias Model =
    { left : RandomGif.Model
    , right : RandomGif.Model
    }
```

这让我们可以分别的处理它们。 其中的actions指是负责用来传递讯息到子组件用的。

```elm
type Action
    = Left RandomGif.Action
    | Right RandomGif.Action
```

我们使用 `Left` 与 `Right` 在我们的 `update` 与 `init` functions中

```elm
-- Effects.map : (a -> b) -> Effects a -> Effects b

update : Action -> Model -> (Model, Effects Action)
update action model =
  case action of
    Left msg ->
      let
        (left, fx) = RandomGif.update msg model.left
      in
        ( Model left model.right
        , Effects.map Left fx
        )

    Right msg ->
      let
        (right, fx) = RandomGif.update msg model.right
      in
        ( Model model.left right
        , Effects.map Right fx
        )
```

在每个分支中，我们使用了 `RandomGif.update` function 其可以回传一个 model 以及(effect)  `fx`。和先前一样先回传一个普通的model，
但我们需要在effects中做一些不同的事。我们这次不让他直接return，我们将使用 [`Effects.map`](http://package.elm-lang.org/packages/evancz/elm-effects/latest/Effects#map) function
将他们转为同类型的`Action`，和 `Signal.forwardTo`类似，让我们对values进行 tag的动作，让我们清楚的知道它该被导向哪裡。

而`init` function也做一样的事， 我们提供一个topic 给每个 random GIF viewer 并且得到回传的初始 model 与 effects。

```elm
init : String -> String -> (Model, Effects Action)
init leftTopic rightTopic =
  let
    (left, leftFx) = RandomGif.init leftTopic
    (right, rightFx) = RandomGif.init rightTopic
  in
    ( Model left right
    , Effects.batch
        [ Effects.map Left leftFx
        , Effects.map Right rightFx
        ]
    )

-- Effects.batch : List (Effects a) -> Effects a
```

在这个范例，我们不止使用 `Effects.map` 来 tag 结果，我们还会使用 [`Effects.batch`](http://package.elm-lang.org/packages/evancz/elm-effects/latest/Effects#batch) function 来让他们溷在一起。
 每个 requested tasks 将会独立的运行，所以 left 与 right effects将会同一时间一起运作。


## Example 7: List of random GIF viewers

**[demo](http://evancz.github.io/elm-architecture-tutorial/examples/7.html) / [see code](examples/7/)**

这个范例让你有一系列的 random GIF viewers 你可以创造你自己的topics，并且，我们仍然使用之前的 `RandomGif` module。

当你看完 [the implementation](examples/7/RandomGifList.elm) 你会发现他和 范例 3是相对应的。我们将所有子model放在相同list ，
并用ID来分辨与连结它们， 唯一改变的地方在于:在 `init` 与 `update` function中的 `Effects` ， 将使用 `Effects.map` 与 `Effects.batch`把他们放在一起。


如果你对下面这个章节有任何的问题，你可以在这个repo创造一个issue来解决你的问题。


## Example 8: Animation

**[demo](http://evancz.github.io/elm-architecture-tutorial/examples/8.html) / [see code](examples/8/)**

现在我们知道拥有tasks的 components 可以被巢状的使用， 但要怎麽把它应用在动画中呢?

有趣的是， 它的做法和先前的做法类似! 

这个范例是两个可以点击的四方体， 当你点击后， 它会旋转90度。总体来说这裡的code 源自于 范例 2 和 范例 6 
我们将所有跟动画相关的逻辑放在`SpinSquare.elm` 我们重複使用的部分放在 `SpinSquarePair.elm`. 

根据这个范例 [in `SpinSquare`](examples/8/SpinSquare.elm) 第一件要做的事为处理 model:

```elm
type alias Model =
    { angle : Float
    , animationState : AnimationState
    }


type alias AnimationState =
    Maybe { prevClockTime : Time,  elapsedTime: Time }


rotateStep = 90
duration = second
```

我们核心的model为 `angle` 指出了四方体的当前角度，而`animationState` 用来指出目前的动画，假如现在没有动画，它将是 `Nothing`
但假如现在有动画，它将会是:
  
  * `prevClockTime` &mdash; 可以让我们知道与上次的影格相距多少毫秒(milliseconds) 。
  * `elapsedTime` &mdash;指出 数字0 与 `已经过时间`两者之差距，用来了解动画进行了多久。

而`rotateStep` 用来宣告每次点击他转了多少角度，你可以随意去改变它，不会对你程式造成影响。

有趣的事情发生在 `update`中:

```elm
type Action
    = Spin
    | Tick Time


update : Action -> Model -> (Model, Effects Action)
update msg model =
  case msg of
    Spin ->
      case model.animationState of
        Nothing ->
          ( model, Effects.tick Tick )

        Just _ ->
          ( model, Effects.none )

    Tick clockTime ->
      let
        newElapsedTime =
          case model.animationState of
            Nothing ->
              0

            Just {elapsedTime, prevClockTime} ->
              elapsedTime + (clockTime - prevClockTime)
      in
        if newElapsedTime > duration then
          ( { angle = model.angle + rotateStep
            , animationState = Nothing
            }
          , Effects.none
          )
        else
          ( { angle = model.angle
            , animationState = Just { elapsedTime = newElapsedTime, prevClockTime = clockTime }
            }
          , Effects.tick Tick
          )
```

我们需要处理两种 `Action` :

  - `Spin` 当一个 user 点击shape并且 requesting a spin。 接着在 `update` function中，假设现在没有动画在进行，我们会request 一个 clock tick，并且保持原来的状态，但假装已经有事情在作用了。
  - `Tick` 当我们取得了 clock tick 我们将需要取得 animation step.在 `update` function中 ，我们需要去更新 `animationState`. 
  -第一件事，我们会去检查当下是否有动画在进行， 假如有，我们会使用当下的 `elapsedTime` 去确认 `newElapsedTime`的值。
并且在其中加入 `time diff`。

假设现在的elapsed time 大于 `duration` 我们将会停止动画，并且暂停 requesting new clock ticks.
假设小于， 我们会更新现在的 animation state 并且 request another clock tick。



最后，我们会有`view` function! 在这个范例有一个不错的动画 ，但其实我们只是以线性的方式去递增`elapsedTime`。这是如何发生的?

其中 `view` 的程式码是源自 [`elm-svg`](http://package.elm-lang.org/packages/evancz/elm-svg/latest/) 为了做出其他更有趣并且可点击产生动画的形状. 
在view程式码中 `toOffset` 将会计算目前所旋转的偏移量 `AnimationState`.

```elm
-- import Easing exposing (ease, easeOutBounce, float)

toOffset : AnimationState -> Float
toOffset animationState =
  case animationState of
    Nothing ->
      0

    Just {elapsedTime} ->
      ease easeOutBounce float 0 rotateStep duration elapsedTime
```

我们使用的是[@Dandandan](https://github.com/Dandandan)’s [easing package](http://package.elm-lang.org/packages/Dandandan/Easing/latest) 让我们可以简单的做到一些动画 [all sorts of cool easings](http://easings.net/)包含数字,颜色,点,或是任何其他你想要的东西。.

`ease` function 会取得一个数字在 0 与 `duration`间。 接着把它转换为 0 与 `rotateStep` 间的数字
并且提供一个 easing， 在范例中，我们提供了 `easeOutBounce` 意思为我们slide from 0 to `duration`，我们将会获得一个数字在 0 and 90 之间，并且具有easing 效果。

接着在下面的连结试试 `easeOutBounce` 吧 [other easings](http://package.elm-lang.org/packages/Dandandan/Easing/latest/Easing)


我们使用 `SpinSquarePair`将大部分的东西结合再一起，但他们其实和范例  2 与范例 6 类似。

以上即是我们使用这个  library所进行的animation ! 如果有任何不清楚的地方请欢迎提出来!

> Note: 我期待我们可以于这个核心概念上做一些更酷的东西 。 如果你有任何更好的想法，请让我们知道!



# Reactivity

在上一章，我们学习了有关Elm 的架构，于这一章，
我们将谈到如何与 servers进行沟通、使用 websockets等等， 下面这张图展示了一些基本概念

![456](https://cloud.githubusercontent.com/assets/11001914/15096410/be52f858-1528-11e6-846a-b2b53a98f41d.png)


我们程式主要逻辑都在Elm Architecture被描述到了，让我们可以达到 stateless functions 与 immutability。这裡我们将会谈到有关 
signals ，用来对事件进行路由的动作。

当我们想要产生一些effect时，我们会建立一个与核心逻辑分开的service， 每个 service 会负责不同的 task，例如 与资料库进行连接，或使用
websockets等等，我们将这些都写在 tasks中。

把这些 services 分开，对我们有很大的帮助，最明显的帮助是在未来进行测试时会更为简单。

#Signals

Signals 负责事件的导向，它将会使用到 Elm Architecture。 在前面的 start-app package我们把这些细节隐藏了， 它只是很简单的在 signals外面包上了一层。

你可以想像 signals 是一个固定在运行的程式网络，从input收到讯息后将它转向，最终，把产生的讯息输出到画面上。

![485](https://cloud.githubusercontent.com/assets/11001914/15097373/a175170c-154b-11e6-9ad6-cdb3e009f855.png)

上图是Elm programs中处理程序的流向，我们程式的所有状态都存在 foldp中，我们主要使用 signals 来进行event的导向。

>Note:你可能会想: “全部的状态都保存在同个地方?! 那怎麽处理关于 encapsulation的问题呢?!?!” 在你关掉这个 tab之前，你可以想像这就像是 一个管理 database 的人: 管理所有 state最困难的地方在于保持它的一致性。 我们要如何保证在一个元件中所做的改变会正确的传递到另一个地方呢? 怎麽知道它所存取的state是最新的呢? 当在你的系统中开始有更多的元件时，这些问题将会变得更加的複杂。 以你以前写Javascript的经验中，
state 中的不一致 大概是产生 bugs的最主要原因吧。

在 Elm中 我们把一致性的问题从模组化分开。其中的foldp是一个集中储存资料的中心，可确保一致性。 而 Elm Architecture 可以保证
我们的程式模组化。把这些概念分开，我们将可以做得更好。

我们使用下图中的 relatively focused API于 [Signal module API](http://package.elm-lang.org/packages/elm-lang/core/3.0.0/Signal)来建立这个网络:

```
map : (a -> b) -> Signal a -> Signal b

filter : (a -> Bool) -> a -> Signal a -> Signal a

merge : Signal a -> Signal a -> Signal a

foldp : (a -> s -> s) -> s -> Signal a -> Signal s
```

建议你先看完[signal examples](http://elm-lang.org/examples) 来对这些 API 有基本的概念之后再继续，我们将会谈到如何将这些基本的导向机制转为可以执行 HTTP requests的services 以及其他更多的功能。

> Note:当你想要写一个很好的模组化程式时，建议你尽量少用signals ， 而使用普通的 functions与values。假设你未来在使用
signal 时遇到了困难， 你可以问问自己 “我将如何将这些转为 functions 与 values?”

## Tasks

Tasks 用来描述一些可能会失败的非同步操作，像是HTTP requests或是对database写资料等等，许多有关浏览器的api在elm中都称为tasks

* [elm-http](http://package.elm-lang.org/packages/evancz/elm-http/3.0.0/) —  servers 操作
* [elm-history](https://github.com/TheSeamau5/elm-history/) — 改变 browser history
* [elm-storage](https://github.com/TheSeamau5/elm-storage/) — 本地存储

Tasks 类似轻量化的 threads ， 所以你可以有一系列的 tasks 同时运行， 并且在他们任何一个发生中断时跳过它。

这个范例将会使用 elm-http package 来建立一个常见的 HTTP requests程式， 像是 [zip codes](http://elm-lang.org/examples/zip-codes) 
以及 [querying flickr](http://elm-lang.org/examples/flickr) 其中的API比 XMLHttpRequest 还要好用，
并且比 JavaScript’s promises有更好的错误处理。 

开始之前，请先安装  evancz/task-tutorial package 并在你的资料夹中执行下面的 command:

```
elm-package install evancz/task-tutorial -y
elm-package install evancz/elm-html -y
elm-package install evancz/elm-http -y
elm-package install evancz/elm-markdown -y
```

使用[ TaskTutorial](http://package.elm-lang.org/packages/evancz/task-tutorial/1.0.3/TaskTutorial)，可以帮我们建立一些基本的功能

#### Basic Example

下面是一个简单的 function 可以印出值到 console 中:

```
print : a -> Task x ()
```

我们给予 print function 一个 value， 它将返回一个 Task 它可以在未来被执行，并印出这个value ， 其中的x 用来显示错误发生的类型,
我们现在先不用关注它，之后会再讲到。

为了真正执行一个 task，我们将它转向到 [port](http://elm-lang.org/guide/interop) 将ports想像成 是你可以要求elm runtime为你做的一些事。
在这裡 ，它的意思为执行这个 task.下面的范例中将  print和 ports 放在一起，用来每秒印出现在的时间。

```
import Graphics.Element exposing (show)
import Task exposing (Task)
import TaskTutorial exposing (print)
import Time exposing (second, Time)


-- A signal that updates to the current time every second
clock : Signal Time
clock =
  Time.every second


-- Turn the clock into a signal of tasks
printTasks : Signal (Task x ())
printTasks =
  Signal.map print clock


-- Actually perform all those tasks
port runner : Signal (Task x ())
port runner =
  printTasks


main =
  show "Open your browser's Developer Console."
```
当初始化这个 module时，我们将会发现每秒将会印出现在的时间，printTasks signal 创造了许多 tasks， 但是这并没有对他自己做任何事
。就像是在现实生活中，创造 task 不代表task真的有发生。我可以在代办事项写上许多的 “买更多牛奶” ，但我仍然需要动身去超市买，否则它将不会自动出现在我的冰箱。

在Elm中的 tasks 在我们将他转交给 port 之前他并不会去真正执行。 不像是 JavaScript中的 callback，elm的 runtime 仅仅只是执行了这个 task。

我们可以传给port 一个 task 或是一个 signal 带有许多 tasks。 当你给的是 signal时，所有的 tasks将会被执行，原因是为了避免 overlapping。

####Chaining Tasks

在上面的范例中，我们使用了[print](http://package.elm-lang.org/packages/evancz/task-tutorial/1.0.3/TaskTutorial#print)
但如果我们想要执行更加複杂的task呢? 参考以下的步骤:

首先介绍 [getCurrentTime](http://package.elm-lang.org/packages/evancz/task-tutorial/1.0.3/TaskTutorial#getCurrentTime)它可以比 print做更多的事情!

```
getCurrentTime : Task x Time
```

这是一个单纯给你现在时间的 task，当你执行它时， 它会告诉你现在是几点，现在我们要做的是执行 `getCurrentTime`并且执行 `print`
先让我们看一下完整版的样子，在一一去做介绍:

```
import Graphics.Element exposing (show)
import Task exposing (Task, andThen)
import TaskTutorial exposing (getCurrentTime, print)


port runner : Task x ()
port runner =
  getCurrentTime `andThen` print


main =
  show "Open the Developer Console of your browser."
```
首先， 注意到其中伊个不常用的反引号，它可以将普通的function转为 infix operators。 和其他范例相同， (add 3 4) 与 (3 `add` 4)同样意思。

所以(getCurrentTime `andThen` print) 与 (andThen getCurrentTime print)为相同意思。 当使用反引号时，它让我们阅读起来更像是一般英文的用法。

现在我们知道andThen 是一个普通的 function 并且拥有两个参数，让我们看一下它的型别:

```
andThen : Task x a -> (a -> Task x b) -> Task x b
```

第一个参数是我们想要执行的Task，即为getCurrentTime。第二个参数是一个 callback用来建造一个新的 task。
(在这裡的意思为将现在的时间印出来)

看一下下面稍为详细的 task chain将对你有帮助:

```
printTime : Task x ()
printTime =
  getCurrentTime `andThen` print


printTimeVerbose : Task x ()
printTimeVerbose =
  getCurrentTime `andThen` \time -> print time
```

这两个的意思相同，但是第二个比较明确的指出:我们在等待一个时间，并且将他印出

其中的andThen function 在使用 tasks 很重要，它让我们可以创造複杂的Task chains
接下来的范例它将会很常见

#### Communicating with Mailboxes
我们现在执行了 tasks但把结果丢掉。但假如我们想从 server取得一些资讯并用到我们的程式中呢?
我们可以使用 [Mailbox](http://package.elm-lang.org/packages/elm-lang/core/3.0.0/Signal#Mailbox)
就像是我们在建构 UIs 并希望他回传值时一样 ，下面是在 [Signal module](http://package.elm-lang.org/packages/elm-lang/core/3.0.0/Signal)中的一些定义:

```
type alias Mailbox a =
    { address : Address a
    , signal : Signal a
    }

mailbox : a -> Mailbox a
```

 mailbox 拥有两个键值对: (1)  一个address 用来传递讯息(2)一个 signal 当我们收到讯息时更新它。当我们建立需要提供一个初始值
给Signal.

在这裡的send function 是传送讯息给 mailbox主要的方式

```
send : Address a -> a -> Task x ()
```

你提供一个address与 value，当 task 被执行时， value 会出现在相应的 mailbox。
就像是真实的信箱，接着看一下，下面的范例:

```
import Graphics.Element exposing (Element, show)
import Task exposing (Task, andThen)
import TaskTutorial exposing (getCurrentTime, print)


main : Signal Element
main =
  Signal.map show contentMailbox.signal


contentMailbox : Signal.Mailbox String
contentMailbox =
  Signal.mailbox ""


port updateContent : Task x ()
port updateContent =
  Signal.send contentMailbox.address "hello!"
```
程式一开始只显是一个空的字串，其为在 mailbox中的初始值，接着我们立刻执行 updateContent task 
它送出了讯息到contentMailbox。当他抵达时，contentMailbox.signal 的值进行了更新，接着画面显示了 "hello!" 。


现在，我们对andThen 与 Mailbox 有了进一步的了解，接着让我们看一些更实用的范例!

#### HTTP Tasks


我们在web app 使用中最常做的事就是与servers做沟通，  elm-http library 提供了大部分你所需要的函式，
下面先来介绍有关 Http.getString function

```
Http.getString : String -> Task Http.Error String
```

我们提供一个 URL，它会创造一个 task 用来取得一些资源，最后 x 会是 error type! 这个 task 有可能会产生 Http.Error 或是 succeed且产生一个 String.

下面的函式用来载入 在e Elm Package Catalog中的README packages

```
import Http
import Markdown
import Html exposing (Html)
import Task exposing (Task, andThen)


main : Signal Html
main =
  Signal.map Markdown.toHtml readme.signal


-- set up mailbox
--   the signal is piped directly to main
--   the address lets us update the signal
readme : Signal.Mailbox String
readme =
  Signal.mailbox ""


-- send some markdown to our readme mailbox
report : String -> Task x ()
report markdown =
  Signal.send readme.address markdown


-- get the readme *and then* send the result to our mailbox
port fetchReadme : Task Http.Error ()
port fetchReadme =
  Http.getString readmeUrl `andThen` report


-- the URL of the README.md that we desire
readmeUrl : String
readmeUrl =
  "https://raw.githubusercontent.com/elm-lang/core/master/README.md"
```

有趣的部分发生在 fetchReadme port。 我们尝试从 readmeUrl取得资源，假如成功了，我们将他转送到 readme mailbox。 假如失败，则没有任何讯息会送出。
假如server 收到了 README 的回覆，我们会看到画面从空白转为 elm-lang/core readme中的内容!

#### More Chaining

我们已经看到 andThen 用来将两个 tasks 连接在一起，但我们要如何连接更多的 tasks呢?最终，这将会看起来有点奇怪， 所以你可以使用一些
indentation 的方式，让它看起来好一点。 让我们看下面的范例是如何做到的:

```
import Graphics.Element exposing (show)
import Task exposing (Task, andThen, succeed)
import TaskTutorial exposing (getCurrentTime, print)
import Time exposing (Time)


getDuration : Task x Time
getDuration =
  getCurrentTime
    `andThen` \start -> succeed (fibonacci 20)
    `andThen` \fib -> getCurrentTime
    `andThen` \end -> succeed (end - start)


fibonacci : Int -> Int
fibonacci n =
  if n <= 2 then
    1
  else
    fibonacci (n-1) + fibonacci (n-2)


port runner : Task x ()
port runner =
  getDuration `andThen` print


main =
  show "Open the Developer Console of your browser."
```
这看起来很自然，取得现在的时间，并且执行 fibonacci function，之后再次取得现在的时间，最后传回开始与结束时间的差距。

你可能会有疑问: “why is start in scope two tasks later?” 原因是，这裡的箭头是一个匿名函式， 所以假如我们把括号放再 getDuration function，它将会看起来像这样:

```
getDuration : Task x Time
getDuration =
  getCurrentTime
    `andThen` (\start -> succeed (fibonacci 20)
    `andThen` (\fib -> getCurrentTime
    `andThen` (\end -> succeed (end - start))))
```
现在你可以看到我们之前讲的 indentation奇怪的地方! 你将会常看到这种链式的设计模式， 因为它可以保存许多变数在同一个范围内，
让许多 tasks使用。

#### 错误处理(Error Handling)

到目前为止我们只在乎成功的task，但如果HTTP request 返回的是一个 404或是一个不能被解析的 JSON 格式呢? 
我们有两种主要的方式可以处理这种类型的 tasks所发生的错误，第一种是使用 onError function:

```
onError : Task x a -> (x -> Task y a) -> Task y a
```

这看起来跟 andThen很类似，但他只有在发生错误时才会被触发， 所以假如我们想从一个错误的 JSON request回复时,我们可以这样写:

```
import Graphics.Element exposing (show)
import Http
import Json.Decode as Json
import Task exposing (Task, andThen, onError, succeed)
import TaskTutorial exposing (print)


get : Task Http.Error (List String)
get =
  Http.get (Json.list Json.string) "http://example.com/hat-list.json"


safeGet : Task x (List String)
safeGet =
  get `onError` (\err -> succeed [])


port runner : Task x ()
port runner =
  safeGet `andThen` print


main =
  show "Open the Developer Console of your browser."
```
有了这个 get task，虽然我们可能产生 Http.Error的错误，但当我们加入了 recovery with onError最后我们仍然可以执行 safeGet task 

当一个 task 永远会被成功的执行时，  牵制  error type是不可能的， 因为type 可能是任何类型，我们永远不会知道，因为他从来不会发生，
这就是为什麽我们要用一个可以是任意型别的 x 于 safeGet中。

第二种错误处理的方式为使用 Task.toMaybe 与 Task.toResult

```
toMaybe : Task x a -> Task y (Maybe a)
toMaybe task =
  Task.map Just task `onError` \_ -> succeed Nothing


toResult : Task x a -> Task y (Result x a)
toResult task =
  Task.map Ok task `onError` \msg -> succeed (Err msg)
```
实质上这是把所有错误转为一个success case， 让我们看下面这个范例

```
import Graphics.Element exposing (show)
import Http
import Json.Decode as Json
import Task exposing (Task, andThen, toResult)
import TaskTutorial exposing (print)


get : Task Http.Error (List String)
get =
  Http.get (Json.list Json.string) "http://example.com/hat-list.json"


safeGet : Task x (Result Http.Error (List String))
safeGet =
  Task.toResult get


port runner : Task x ()
port runner =
  safeGet `andThen` print


main =
  show "Open the Developer Console of your browser."
```

使用了 safeGet 我们可以根据 Result type来处理错误，当你再处理一些特定的API实，它们将十分有用。

#### 进阶阅读(Further Learning)

现在我们对于andThen的链式tasks以及错误处理有了基本的概念，接着你可以试着阅读下面这两个范例:

* [zip codes](http://elm-lang.org/examples/zip-codes)
* [flickr](http://elm-lang.org/examples/flickr)



# Interop

这一章节主要在讲如何将 Elm 的程式嵌入到 HTML 中，以及如何与 JavaScript进行沟通。

## HTML Embedding

Elm 可以直接被嵌入一个 <div>标籤中，这让你可以轻鬆的把 Elm程式与其他 JS project做整合。可以参考下面的范例:

假设我们有一个简单的程式 [Stamper.elm](https://gist.github.com/evancz/8456627#file-stamper-elm) 
让你在点击滑鼠时于画面上留下一个[图形](http://elm-lang.org/examples/stamps)

使用下面的指令编译它:
```
elm-make Stamper.elm
```
将会产生一个名为 elm.js的档桉。 这个 JS 档桉包含了所有嵌入到HTML所需要的要素。

在EmbeddedElm.html档桉中，我们于`<body>` 标籤下方增加一个，`<script>`标籤 并含有以下的程式码:

```
// get an empty <div>
var div = document.getElementById('stamper');

// embed our Elm program in that <div>
Elm.embed(Elm.Stamper, div);
```
Elm.embed function 需要两个参数 :

1.一个 Elm module，并且所有名字的最前面都包含的Elm字样，来避免命名空间污染，所以原来的Stamper模组变为Elm.Stamper。

2.一个<div>标嵌用来包住我们要嵌入的程式

这样就够了!

需要注意的是 Window.dimensions 以及 Mouse.position 作用范围只有在该 <div>中，没有包含到整个页面。
这代表 Stamper中的程式仍然会填满整个 <div> 并且当你点击时给予回应。

#### 另一种嵌入Elm程式的方式(Other ways to embed Elm

下面这个范例将程式嵌入<div>中，但它仍然可以在全萤幕中创造 Elm 元件 ，而另外一个是完全没有图形的:

```
// fullscreen version of Stamper
Elm.fullscreen(Elm.Stamper);

// Stamper with no graphics
Elm.worker(Elm.Stamper);
```

在你指定了HTML的输出档桉后，你也可以让他自动去产生 HTML
```
elm-make Stamper.elm --output=Main.html
```

## Ports

Ports 是常见的与 JavaScript沟通的方式，让你可以方便的传递讯息，所以你可以在你随时想要的时候使用 JavaScript。

你可以参考这个[范例](https://github.com/evancz/elm-html-and-js) 
与这个[范例](https://gist.github.com/evancz/8521339) 
在这个文件中将讲解你可以使用ports做哪些事情。

#### From JavaScript to Elm

当你想要从JavaScript 送讯息到 Elm， 你可以如下使用incoming port :

```
port addUser : Signal (String, UserRecord)
```

我们有一个signal 在 Elm中，名为 addUser 它将会被 JavaScript的某些程式更新。为了送讯息到这个 port
我们需要写一些如下的东西到 JavaScript中:
```
myapp.ports.addUser.send([
    "Tom",
    { age: 32, job: "lumberjack" }
]);

myapp.ports.addUser.send([
    "Sue",
    { age: 37, job: "accountant" }
]);
```
这将会传送两个更新讯息给Elm，并自动转为值。

## From Elm to JavaScript

从 Elm 送讯息到 JavaScript，你可以如下定义一个 outgoing port :

```
port requestUser : Signal String
port requestUser =
    signalOfUsersWeWantMoreInfoOn
```

在这个范例，我们使用了一个Elm中的 signal并将它的每个值传送到 JavaScript。 在 JavaScript 这边，为了处理这些传来的讯息我们订阅了这个 port:
```
myapp.ports.requestUser.subscribe(databaseLookup);

function databaseLookup(user) {
    var userInfo = database.lookup(user);
    myapp.ports.addUser.send(user, userInfo);
}
```
我们订阅了 requestUser port 并且会对 database 进行存取， 当我们取得回传值时，我们将它传递到 Elm中，并且使用另一个 port。
有时你可能会需要对一个  port取消订阅，如同以下范例:
```
myapp.ports.requestUser.unsubscribe(databaseLookup);
```

你可以查看这两个范例
https://github.com/evancz/elm-html-and-js
https://gist.github.com/evancz/8521339

##Customs and Border Protection

你需要注意传送给Ports的值， Elm 是一种静态语言，所以每个 port 都拥有 border protection用来避免 type errors 
 Ports 也做了一些资料转换， 让你在 Elm 与 JS间有很好的资料结构。
 
 可以传送给 ports 的资料型态是很有弹性的，包含所有有效的 [JSON](http://www.json.org/) 值，与以下所列的 Elm 型态:
 
Booleans and Strings – 在 Elm and JS都适用!

Numbers – Elm ints and floats correspond to JS numbers

Lists – 对应到 JS arrays

Arrays – 对应到 JS arrays

Tuples – 对应到 fixed-length, mixed-type JS arrays

Records – 对应到 JavaScript objects

Signals – 对应到 event streams in JS

Maybes – Nothing and Just 42 correspond to null and 42 in JS

Json – [Json.Encode.Value](http://package.elm-lang.org/packages/elm-lang/core/3.0.0/Json-Encode#Value) corresponds to arbitrary JSON

每个转换都必须是对称且为正确的资料型态，假如是一个错误的型态，它将会立即于 JS 抛出一个错误。
有了border check 之后， Elm 将可以保证你不会遇到任何执行时所产生的 type errors。

