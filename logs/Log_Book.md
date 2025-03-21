# C to RISC-V compiler project log book
---
## Team members
||Elson Tho|Ahmed Ali Hamid|
|---|---|---|
|**CID:**|02381489|02427719|
|**Github username:**|3lson|Avalors|

## Purpose
- The puropse of this log-book is to document our teams progress on this Compilers project, demonstrating our commitment, effort and time-spent and also providing an accurate reflection of our time-management skills.
- Each day's efforts will be briefly described under the corresponding date with associated commits referenced, followed by gantt charts documenting our overall progress at the end of each week.
- We will embed images demonstrating our team-work and cooperation throughout the project as well demonstrating our unbridled commitment to creating this compiler.

## Overview

---
## <ins>Week 1: 15/02/2025</ins>

### 15/02/2025 (4 hours)
  - Began dissection requirements and specification of project by reading the repo documents
  - Organised the project features in [Jira](https://www.atlassian.com/software/jira?campaign=22164754770&adgroup=172507794645&targetid=kwd-855725830&matchtype=e&network=g&device=c&device_model=&creative=642044761145&keyword=jira&placement=&target=&ds_eid=700000001558501&ds_e1=GOOGLE&gad_source=1&gclid=CjwKCAiAk8G9BhA0EiwAOQxmfqMJyZ9nSJDKApTWyEVDu_iEnuYc3nuD4ZbWXnNVnPoVkTjY2Pn47RoCB9oQAvD_BwE) seperated by basic, intermediate and advanced features.
  - Began setting up repo, creating logs folder and log book page.
  - Running initial test script

<div align="center">

|![alt text](https://github.com/3lson/HADESRedDragonC_Compiler/blob/restructure/logs/images/Screenshot%202025-02-15%20164326.png)|
|:--:|
|*img: Day 1 working on time management on jira.com on teams*|

</div>

### 16/02/2025 (8 hours)
  - Understanding the implementation of the AST construction
  - Implemented the IfElse statement (Basic Features)
  - Began implementation of variables of int type

### 17/02/2025 (6 hours)
  - Completed variable of int type implementation (Basic Features)
  - Merged IfElse and variable of int type implementations


<div align = "center" >

|![alt text](https://github.com/3lson/HADESRedDragonC_Compiler/blob/restructure/logs/images/image-2.png)|
|:--:|
|*img: progress so far on jira project backlog*|

</div>

### 18/02/2025 (2 hours)
  - Completed most of the arithmetic, bitwise, and logical implementation
  - Added extra folder `arith_no_params` to test fundamental operations with of functions without parameters (at this stage local vars not implemented yet) (extra 20 test cases -removed in final)

### 19/02/2025 (2 hours)
  - Implemented the unary operations
  - Added extra folder `unary` to test the unary operations (extra 6 test cases - removed in final)

### 20/02/2025 (4 hours)
  - constant_initializer.c test case passsed enabling initalization assignment [int x = 12345;]
  - dual_var.c test case passed enabling variable to variable assignment [y = x;]
  - attempted to integrate arithoperator to pass integer test cases (failed horribly)

## 21/02/2025 (3 hours)
  - fixed parameter handling as per ILP32D conventions
  - passed all test case in integer folder
  - passed ADD0.c & ADD1.c test cases by enabling arithoperator functionality
  - Added multiparameter handling

### 22/02/2025 (6 hours)
  - expression_initializer.c passed by implmenting assignment to arithmetic expressions [ x = y + 10; ]
  - scoped_var.c passed by implementing scoped variable handling  [int x = 10; {int x = 5;} return x;]
  - while_zero.c and while_once.c test case passed enabling condition evaluations of [ while(0), while(x)]

### 23/02/2025 (4 hours)
  - while_multiple.c test case passed enabling [ while(x>10) ]
  - fixed scopeLevel for if and while statements, ensuring they can also access variables in lower scope level initializations.


---
<div align = "center" >
<b>Basic Features complete</b>
</div>

---

<div align = "center" >

|![alt text](https://github.com/3lson/HADESRedDragonC_Compiler/blob/restructure/logs/images/Gantt_chart.png)|
|:--:|
|*img: Gantt Chart Progress after Week 1*|

</div>

<div align = "center" >

|![alt text](https://github.com/3lson/HADESRedDragonC_Compiler/blob/restructure/logs/images/Intermediate_sprint.png)|
|:--:|
|*img: Intermediate Sprint Start*|

</div>

Above was our initial sprint start for the intermediate features. However as you will see in the image below the sprint was extended due to an agreement to restructure our implementation to minimise the use of flags and populate using stacks and more classes (especially in separate contexts to avoid crowded `context.hpp` 

<div align = "center" >

|![alt text](https://github.com/3lson/HADESRedDragonC_Compiler/blob/restructure/logs/images/Intermediate_Revised.png)|
|:--:|
|*img: New Intermediate Sprint*|

</div>

### 27/02/2025 (8 hours)
  - [Beginning of the restructure of the repo](https://github.com/3lson/HADESRedDragonC_Compiler/commit/3609b8b6316531dd0489d2c02d2798c5b00ac897)
  - Moved the hpp files and code gen files into respective folders as per logical sense (reference to test case) - i.e control_flow for if statements

### 28/02/2025 (6 hours)
  - [Added functions with parameters](https://github.com/3lson/HADESRedDragonC_Compiler/commit/dd30a96133349bea22fb1b3a7046c7d4fe98bfe8)
  - Added a parameter handling class which and new context classes for function handling (top function class having returnvalue class and parameter class)
  - Add the concept of stack offset to store values and free registers for use efficiently

### 01/03/2025 (2 hours) 
  - Committed the function with parameters that I started on 28th
  - [Fixed the `dual_var` test case](https://github.com/3lson/HADESRedDragonC_Compiler/commit/3c70286e96549a9b032fde7c5a1b47672f883eb4)

### 02/03/2025 (6 hours)
  - [Implemented Arithmetic Operations](https://github.com/3lson/HADESRedDragonC_Compiler/commit/6e606f8f2654c1b13dab6d3bcd78987ead4b4fad)
  - [Implement Unary Operations](https://github.com/3lson/HADESRedDragonC_Compiler/commit/6e606f8f2654c1b13dab6d3bcd78987ead4b4fad)
  - [Added custom test cases for arithmetic of those not provided in seen](https://github.com/3lson/HADESRedDragonC_Compiler/commit/6e606f8f2654c1b13dab6d3bcd78987ead4b4fad)

### 03/03/2025 (8 hours)
  - [Refactor basic features and some intermediate started](https://github.com/3lson/HADESRedDragonC_Compiler/commit/feef033985529ee6563c9b5135ff90353913d610)
  - Fixed ifelse issue with condition evaluation
  - Implement while loops from the prev branch
  - Implemented double, float, unsigned declaration and operations

### 04/03/2025 (6 hours)
  - [Implemented function calls with and without parameters and also internal and external calls](https://github.com/3lson/HADESRedDragonC_Compiler/commit/28b81501b7b7aa8fa70a424d6562de3bbdb2397f)
  - Add some test cases for different assignment types (`+=`, `*=`)
  - Tried to implement ternary operations (Not working yet)

### 05/03/2025 (4 hours)
  - [Tried to implement ternary operations (Not working yet)]((https://github.com/3lson/HADESRedDragonC_Compiler/commit/28b81501b7b7aa8fa70a424d6562de3bbdb2397f))
  - Completed function calls

### 06/03/2025 (8 hours)
  - [Tried to implement break and continue(needs fixing)](https://github.com/3lson/HADESRedDragonC_Compiler/commit/fc01e5044f55f22d99574250560fa7e076ab106d)
  - Implemented for loops
  - Implemented do while loops
  - recursive test case for functions fixed
  - character literal in lexer added

### 07/03/2025 (8 hours)
  - [Implemented array initialisation, access, and declaration](https://github.com/3lson/HADESRedDragonC_Compiler/commit/48d8a6ba9858b3233756b0825fd378f909c32d6c)
  - Fixed ternary operator
  - Implement bracket precedence on arithmetics
  - Implemented and added new test cases for binary, floats, arithmetic operations

### 08/03/2025 (4 hours)
  - Tried to fix increment and decrement (not working)
  - Found out increment issue was not store the change of the identifier back onto the stack and therefore not increment properly hence the root problem to **for loops**, **break and continue**
  - Implemented functions that take up to 8 parameters

### 09/03/2025 (6 hours)
  - [Fixed increment, decrement](https://github.com/3lson/HADESRedDragonC_Compiler/commit/11c57d6344aaaf1d2b6cd37aa25aa9a7fc759b4f)
  - break and continue statements fixed
  - reading and writing of an array
  - multiple functions calling each other fixed

### 10/03/2025 (10 hours)
  - [Implement global scopes](https://github.com/3lson/HADESRedDragonC_Compiler/commit/f240cdb9513e473375f8d15f303cd53b4f694a03)

### 11/03/2025 (2 hours)
  - Clean up unnecessary functions implemented in earlier stages that are now redundant

### 12/03/2025 (4 hours)
  - Tried to implement enums (not working yet)

### 13/03/2025 (6 hours) 
  - [Implemented enums](https://github.com/3lson/HADESRedDragonC_Compiler/commit/442c074d168f4c105e2dadc7185bec7c31b8f0ef)
  - Updated logbook

### 18/03/2025 (8 hours)
  - [Implement switch cases](https://github.com/3lson/HADESRedDragonC_Compiler/commit/81fd4d01bfc0d5269958a753080dc1dbd687a26d)

---
<div align = "center" >
<b>Intermediate Features complete</b>
</div>

---

<div align = "center" >

|![alt text](https://github.com/3lson/HADESRedDragonC_Compiler/blob/restructure/logs/images/FinalWeek.png)|
|:--:|
|*img: Final Week Sprint*|

</div>

### 13/03/2025 (4 hours)
  - [Implement sizeof operators](https://github.com/3lson/HADESRedDragonC_Compiler/commit/e945f4885fc978bfb0920eac0ae1bd23c568e764)

### 14/03/2025 (8 hours)
  - Worked on pointer declarations, addressof, operations, deference

### 15/03/2025 (4 hours)
  - Worked on TypeDef

### 16/03/2025 (8 hours)
  - [Implemented pointers and typedef](https://github.com/3lson/HADESRedDragonC_Compiler/commit/903655109843e8be5eb12849528ffe5ecf03380d)

### 17/03/2025 (8 hours)
  - [Implemented strings and completed typedef issue](https://github.com/3lson/HADESRedDragonC_Compiler/commit/4a2f98e1ce402add3b10a969e59efaa943ef4ea7)

### 18/03/2025 (6 hours)
  - Started struct implementation
  - Started some extra feature implementations with extra test cases
  - [Implemented functions that take more than 8 params](https://github.com/3lson/HADESRedDragonC_Compiler/commit/280006099423fe1d539eb2dd9e8687e0785feb12)
  - Implemented strings for global scope
  - Implemented typedef for arrays
  - Implemented sizeof on typedef
  - Added extra test cases like nested if, for, while loops

### 19/03/2025 (8 hours)
  - Worked on trying to implement structs

### 20/03/2025 (24 hours)
  - [Implemented structs, but with issue in sizeof](https://github.com/3lson/HADESRedDragonC_Compiler/commit/d168d8e6214e2b2f109479a5698b51637767f5de)
  - [Fixed the sizeof and all seen test cases passed!](https://github.com/3lson/HADESRedDragonC_Compiler/commit/f0d4097c157588a1ef2843630bc670d235df2d54)
  - Add padding for structs when sizeof is called
  - Members of different data types on structs implemented

### 21/03/2025 (12 hours)
  - Final clean up for submission
  - Added plenty of extra test cases to TRY and break the compiler :)


<div align = "center" >

|![alt text](https://github.com/3lson/HADESRedDragonC_Compiler/blob/restructure/logs/images/AdvancedComplete.png)|
|:--:|
|*img: Completed Final Week Sprint*|

</div>

---
<div align = "center" >
<b>Advanced Features complete</b>
</div>

---

All the seen test case are passed! However, I have added plenty of extra test cases on some features on tested and extra implemented features. Over the summer, this codebase will be augmented to add the unassessed extra features. 



