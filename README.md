# 🎨 2D Graphics Editor in C

A simple **terminal-based 2D Graphics Editor** built using **C programming**. The project allows users to create, manage, modify, and display basic geometric shapes on an ASCII-based canvas.

## 📌 Features

* 🟥 Add **Rectangle**
* ⚪ Add **Circle**
* 🔺 Add **Triangle**
* 📏 Add **Line**
* 🗑️ Delete shapes using their ID
* ✏️ Modify rectangle dimensions
* 📋 Display the list of stored shapes
* 🖼️ Render all active shapes on the terminal canvas
* 🔲 Automatic canvas border
* 💾 Supports up to **100 shapes**
* 📐 Uses a **25 × 80** character canvas

## 🛠️ Technologies Used

* **C Programming**
* `stdio.h`
* `stdlib.h`
* Structures
* 2D Arrays
* Functions
* Loops and Conditional Statements
* Coordinate Geometry
* Basic Graphics Algorithms

## 🧠 How It Works

The editor uses a two-dimensional character array as its drawing canvas:

```c
#define ROWS 25
#define COLS 80

char canvas[ROWS][COLS];
```

The canvas is initialized with `_` characters, while drawn pixels are represented using `*`.

Each shape is stored using a `Shape` structure containing information such as:

* Shape ID
* Shape type
* Coordinates
* Width and height
* Radius
* Active/inactive status

The program can store up to **100 shapes**.

## 📐 Supported Shapes

### 🟥 Rectangle

A rectangle is created using:

* Row
* Column
* Height
* Width

The program draws the four boundaries of the rectangle on the canvas.

### ⚪ Circle

A circle is created using:

* Center X
* Center Y
* Radius

The program calculates points around the circle and plots them onto the canvas.

### 🔺 Triangle

A triangle is created using three coordinate points:

```text
(x1, y1)
(x2, y2)
(x3, y3)
```

The three points are connected using line-drawing functions.

### 📏 Line

A line is created using two coordinate points:

```text
(x1, y1)
(x2, y2)
```

The program calculates the required number of steps and increments the X and Y coordinates to draw the line.

## 🎮 Menu

When the program starts, the following menu is displayed:

```text
=================================
      2D GRAPHICS EDITOR
=================================

1. Add Rectangle
2. Add Circle
3. Add Triangle
4. Add Line
5. Delete Shape
6. Modify Rectangle
7. Display Shape List
8. Show Canvas
9. Exit
```

The program continuously displays this menu until the user chooses to exit.

## 🗂️ Shape Management

Every shape receives a unique ID when it
