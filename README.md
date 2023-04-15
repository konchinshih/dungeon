# OOP Project #1 -- Dungeon

**For better reading experience:** [Link](https://hackmd.io/@konchin/dungeon)

**Github Respository:** [Link](https://github.com/konchinshih/dungeon)

**Youtube Result Video:** [Link](https://youtu.be/J-fNEkmGHEo)

## Functions

### Basic Functions

- [x] Movement
- [x] Showing Status
- [x] Pick up Items
- [x] Fighting System
- [x] NPC
- [x] Game Logic
- [x] Character Class Design
- [x] Trading System

### Optional Enhancement

- [x] Type Counter
- [x] Map Generator
- [x] Cool Down
- [x] DOT Effects
- [x] Level, EXP System
- [x] More Complex Damage Formula
- [x] Better UI(with ANSI Escape Code)

## Implementation

整個遊戲主要分成幾個主要的 Class
* Game -- 遊戲本體
* IO System -- 輸入輸出界面
* Map -- 地圖及房間生成
* Room -- 地圖上的房間
* Entity -- 實體，包含角色和敵人
* Inventory -- 屬於 Entity 負責裝 Item
* Attribute -- Entity 的各種屬性
* Item -- 裝備以及道具
* Combat -- 負責戰鬥界面的子結構
* Ability -- 戰鬥用的技能
* Effect -- 技能能賦予的效果
* NPC -- 可以對話及交易的NPC


### Game

負責遊戲主要的流程控制

> `run()` call graph
> ![](https://i.imgur.com/L01yMTb.png)


### IO System

所有的 input / output 相關的都用 function 包裝在這個 class 裡面，方便之後進行更換 (TUI or GUI)。
ask 開頭的是 input ，print 開頭的是 output 。
實做上回傳的一定是 valid input，invalid 的會在這一層就 reject 掉。
清空畫面跟文字顏色用的都是 ANSI Escape Code 。

> member functions
> ![](https://i.imgur.com/fXCgjyY.png)


### Map

我設計的地圖一開始只有初始位置 (0, 0) 一個 Room ，其他的 Room 會在 Main Character 移動時自動生成，所以地圖理論上是可以無限延伸的。

初始的 50 個 Room 的種類是固定的，之後每 50 個 Room 的種類也是固定的，會放在一個 Room Pool 裡面並打亂順序，當 Main Character 走到沒有走過的座標時才會從 Pool 裡面放入地圖。

> functions and attributes
> ![](https://i.imgur.com/yzA0bxp.png)


### Room

房間總共有 Nothing, Treasure, Monster, NPC, Boss 五種，其中 Treasure 和 Monster 只能互動一次，NPC 可以互動多次，而在打贏 Boss 裡面的王之後遊戲就會結束。

> inheritance diagram
> ![](https://i.imgur.com/OuMyxVZ.png)


### Entity

主要被 Character 和 Monster(Boss) 所繼承，除了紀錄 Class, Name 以外，也有自己獨立的 Inventory 跟 Attribute 等等。

> inheritance diagram
> ![](https://i.imgur.com/1KN9DMu.png)

> collaboration diagram
> ![](https://i.imgur.com/fYkc3Eb.png)


### Inventory

放的是屬於各個 Entity 的 Item ，當 Item 的 Class 對應到 Entity 的 Class 時候加入 Item 會增加 Entity 的數值。

> functions and attributes
> ![](https://i.imgur.com/CsAMyxF.png)


### Attribute

存放 Entity 的像是 HP, ATK, Crit 之類的數值，在 Item 裡面也有，多載了一些 operator 方便這些數值管理。

> functions and attributes
> ![](https://i.imgur.com/8aBjZ3X.png)


### Item

存在 Inventory 裡面可以提昇 Entity 數值的道具或武器。


> inheritance diagram
> ![](https://i.imgur.com/lwjDf1l.png)

> functions and attributes
> ![](https://i.imgur.com/OGB55tw.png)


### Combat

在 Main Character 遇到 Monster Room 的時候會建構，負責 Combat 相關的內容，例如 Monster 的行為模式、戰鬥流程、傷害計算等等。
另外我設計的 Combat system 是半實時的，Entity 在施放 Ability 的時候會有 Cool Down ，而需要等候該 Cool Down 的時間才能繼續行動。
主要是用 C++ 的 `thread` library 的 `this_thread::sleep_for` 來呈現技能 Cool Down。

傷害計算公式則是比較複雜

$\begin{align}
&Damage=TotalATK\times MotionValue\times CritMultiplier\times ClassMultiplier\times LevelMultiplier
\end{align}$

$\begin{align}
TotalATK=BaseATK\times ATK\%+FlatATK
\end{align}$

$\begin{align}
MotionValue=BaseMotionValue+ AbilityLevel\times MotionValueGrow
\end{align}$

$\begin{align}
CritMultiplier=1.0+IsCrit\times CritDamage\%
\end{align}$

$\begin{align}
ClassMultiplier=\begin{cases}
2.0&\text{if the Attacker counters the Target or the Target is Berserker}\\
0.5&\text{if the Target counters the Attacker}\\
1.5&\text{if the Attacker is Berserker}\\
1.0&otherwise
\end{cases}
\end{align}$

$\begin{align}
&OriginLevelMultiplier = 1.0+0.2\times(AttackerLevel-TargetLevel)\\
&LevelMultiplier=\begin{cases}
1.5&OriginLevelMultiplier>1.5\\
0.5&OriginLevelMultiplier<0.5\\
OriginLevelMultiplier&otherwise
\end{cases}
\end{align}$

> collaboration diagram
> ![](https://i.imgur.com/wjSowPb.png =360x)

## Result

> 開始畫面
> ![](https://i.imgur.com/fGAnWO7.png)

> 戰鬥畫面
> ![](https://i.imgur.com/UaLcuLy.png)

> 查看狀態
> ![](https://i.imgur.com/HkWgnE0.png)

> 技能升級
> ![](https://i.imgur.com/soUlWUP.png)

> 向 NPC 購買道具
> ![](https://i.imgur.com/m316JSO.png)

> 打王
> ![](https://i.imgur.com/B9gAUR7.png)

> 過關
> ![](https://i.imgur.com/ZV4bzzR.png)

> 失敗
> ![](https://i.imgur.com/pDgD94w.png)

## Discussion

**寫的不夠符合 OCP 原則**

主要是選項的地方，如果我想要加選項的話要改很多在 code 裡面列舉出來的東西，修改的時候比較繁瑣，之後可以研究一下要怎麼盡可能解決這個問題。

**遊戲性可以更好**

因為 Class 的相剋是參考 Fate/Grand Order 的設定，因此希望之後可以將 7 或更多個 Class 都實做出來，也可以增加更多的敵人和道具。
另外傷害計算也還有可以優化的部份，像是 Resistance 和 Defense 應該分開並做的更 enemy specific 。Attack interval 的曲線和 Monster、 Boss 血量分配也沒有經過經過大量測試來驗證是否合理，可能要取得更多測試結果才有辦法優化這些部份。

**操作界面可以更直覺**

在一開始我花了非常多時間研究 multi-thread 以及一些 platform specific 的 input method ，做了一個半成品的 TUI，後來因為時間關係沒有做完就還是寫了一般 text-based 選選項的這種 IO interface。
在實做時我希望之後可以把 TUI 完成之後補上，因此將 IO System 整個和其他部份的 code 盡量隔開。

## Conclusion

這次的專案我認為花的時間比想像中久很多，很大的一部分原因是因為一開始架構沒有想清楚，導致寫到一半一直砍掉重來。在拿給其他人做 Code Review 之後發現架構又有可以改進的地方，前前後後打掉重寫了約 3 次。

我認為我對於 C++ 語法還有很多的特性還不夠熟悉，像是 Smart pointer 的 unique_ptr 因為忘記 std::move 就吃了好多次 Compile Error ，而 address sanitizer 更是讓我吃了好幾次 Runtime Error，整天在 memory leak。
IO 界面的地方也用 C++20 的 Concept 配上 operator overload 寫了好幾個版本，到最後因為排版不便得問題才直接將 ANSI Escape Code 寫進去而不包裝。

整體來說這次學到了很多不管是語法還是架構設計的部份，下次如果還有做類似專題的機會一定要先規劃好時間及架構再開始實做。
