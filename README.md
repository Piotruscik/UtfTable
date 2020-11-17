UtfTable
===============

A convenient tool to make pretty-formatted, colorful output in C++ console applications.
 * Light-weight - one .h file, less than 12 kB / 400 lines.
 * Self-contained, no additional dependencies.
 * Easy to integrate - just include `utftable.h` and that's all.
 * Supports utf-8 characters, up to 4 bytes.
 * 12 examlpes showing all features included in `main.cpp`

![screenshot](/Screenshot.png)

```
static const unsigned char clInherit = 255;
static const unsigned char clDefault = 0;
static const unsigned char clRed     = 1;
static const unsigned char clGreen   = 2;
static const unsigned char clYellow  = 3;
static const unsigned char clBlue    = 4;
static const unsigned char clMagenta = 5;
static const unsigned char clCyan    = 6;
static const unsigned char clWhite   = 7;
static const unsigned char clBlack   = 8;
```
Constants for basic colors. \
`clInherit` is used by default for values (added by `val`/`valf`) and it means that each character will take its foreground and/or background color from line.


```
UtfTable(const char* top, const char* cols, const char* sep, const char* none, const char* down)
```
The constructor, taking 5 strings as arguments:
 * `top`  - The upper part of table border.
 * `cols` - Column definitions. The only characters that matter here are `L`, `R`, `C` and `P` for left, right, center and point alignment respectively, but it can also contain border as background for nicer look (see **example 1**).
 * `sep`  - Line separator, usually placed after first line (which is table header).
 * `none` - An empty line.
 * `down` - The bottom part of table border.
All arguments must have same length (in characters, not bytes).


```
UtfTable* newLines(int n)
UtfTable* newLine()
UtfTable* newLine(const char* c)
```
Three ways to create new lines.\
`newLines(n)` create `n` lines at once and `newLine()` does the same as `newLines(1)`.
The last variant takes `c` argument as empty line apperance, overriding `none` from constructor (see **example 5**).


```
UtfTable* newSep()
```
Adds a line separator - similar to `newLine()`, but fills the line with `sep` from constructor arguments instead of `none`.


```
UtfTable* render()
```
Prints the table to standard output.\
If `flush()` was used before, it will only print the part that wasn't flushed yet.


```
UtfTable* flush()
```
Prints currently stored part of the table (see **example 7**) except the bottom border.\
Can be useful for large amounts of output data to see its part before whole table is ready or to save memory.\
It deletes all rendered lines, which can affect behavior of `val`/`valf` calls with lineId argument. Also the top border will only be rendered in first call and it won't be rendered by `render()` if `flush()` was called before.


```
UtfTable* val(int offset, int lineId, int colId, const char* v)
UtfTable* val(int lineId, int colId, const char* v)
UtfTable* val(int colId, const char* v)
UtfTable* val(const char* v)
```
Puts a value into a table column.\
Arguments:
 * `v`      - The value to be added.
 * `colId`  - The column index. If not provided, the internal column index will be used. If negative (`-n`), it will take `n`th column from the right (see **example 3**). Sets internal column index to `colId+1`. If not provided, it will take the internal column index and automatically create new line if it exceeds quantity of columns.
 * `lineId` - Number of line. If negative (`-n`), it takes `n`th line from the bottom (see **example 3**). Default is `-1`.
 * `offset` - Horizontal offset of the value (see **example 2**). Default is `0`.


```
UtfTable* valf(int offset, int lineId, int colId, const char* f, ...)
UtfTable* valf(int lineId, int colId, const char* f, ...)
UtfTable* valf(int colId, const char* f, ...)
UtfTable* valf(const char* f, ...)
```
Same as `val`, but instead of `v` argument, it takes format and additional arguments, like `printf()` (see **example 6**).


```
UtfTable* color(int colId, unsigned char color)
UtfTable* color(unsigned char color)
```
Sets value foreground color (see **example 8**). `colId` works same as in `val()` and `valf()`.


```
UtfTable* bgColor(int colId, unsigned char color)
UtfTable* bgColor(unsigned char color)
```
Sets value background color (see **example 8**). `colId` works same as in `val()` and `valf()`.


```
UtfTable* setTopColors   (const char* c, const char* colors)
UtfTable* setDownColors  (const char* c, const char* colors)
UtfTable* setLineColors  (const char* c, const char* colors)
UtfTable* setSepColors   (const char* c, const char* colors)
```
Sets up to 10 colors for given part of the table. (see **examples 10 and 11**).\
`setLineColor()` and `setSepColor()` only affect new lines, not already existing ones.\
Length of `c` argument should be equal to line length and characters 0-9 are indices in colors array.


```
UtfTable* setTopBgColors (const char* c, const char* colors)
UtfTable* setDownBgColors(const char* c, const char* colors)
UtfTable* setLineBgColors(const char* c, const char* colors)
UtfTable* setSepBgColors (const char* c, const char* colors)
```
Same as above, but set background colors (see **examples 9, 10 and 12**).


```
char rgb(unsigned char r, unsigned char g, unsigned char b)
```
Takes rgb values and returns table's internal index of the color. (see **examples 11 and 12**).\
Needs terminal support of color sequences like `\x1B[38;2;r;g;bm`.\
Maximum number of allowed different rgb colors is 246, because table characters use 1 byte for color index and 10 values are reserved for basic colors.

