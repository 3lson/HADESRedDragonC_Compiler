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

[Insert image here]

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





