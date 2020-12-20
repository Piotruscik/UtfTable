#include <iostream>
#include <stdio.h>
#include <cstring>
#include <stdarg.h>
#include <stdlib.h>

class UtfTable {
  private:
  typedef unsigned char __Char [6];
  typedef __Char* __Line;
  typedef struct{
    int pos;
    unsigned char align, color, bgColor;
  } __Column;
  typedef struct {
    unsigned char r, g, b;
  } __Color;
  __Line top, sep, none, down, tmpBufferC;
  char* tmpBuffer;
  __Column* cols;
  __Line* lines;
  __Color colors [256];
  int colCnt, lineCnt, cap, lineLen, currCol, colorCnt, allocLines;
  bool topFlushed;

  int writeColorSequence(char* dst, unsigned char c, bool bg) {
    if (c == 0) {
      memcpy(dst, "\x1B[1;0m", 6);
      return 6;
    }
    if (c < 9) {
      memcpy(dst, "\x1B[1;??m", 7);
      dst[4] = bg ? '4' : '3';
      dst[5] = c == 8 ? '0' : '0' + c;
      return 7;
    }
    int l;
    __Color color = this->colors[(int)c];
    if (bg) {
      l = sprintf(dst, "\x1B[48;2;%d;%d;%dm", color.r, color.g, color.b);
    } else {
      l = sprintf(dst, "\x1B[1;31m\x1B[38;2;%d;%d;%dm", color.r, color.g, color.b);
    }
    return l;
  }

  int convFromUtf8(__Char* ret, const char* c, unsigned char color, char bgColor) {
    int posC = -1;
    int pos = 0;
    int l = strlen(c);
    for (int i = 0; i < l; i++) {
      if ((c[i] & 192) != 128) { //10xxxxxx
        pos = 0;
        posC++;
        memset(&ret[posC][1], 0, 3);
        ret[posC][4] = color;
        ret[posC][5] = bgColor;
      }
      if (pos > 3) {
        ret[posC][0] = 0;
        return posC; //invalid char
      }
      if (posC > this->lineLen) return this->lineLen;
      ret[posC][pos++] = c[i];
    }
    ret[posC + 1][0] = 0;
    return posC + 1;
  }

  __Char* allocConvFromUtf8(const char* c) {
    __Char* ret = (__Char*)malloc((this->lineLen + 1) * sizeof(__Char));
    ret[this->lineLen + 1][0] = 0;
    this->convFromUtf8(ret, c, 0, 0);
    return ret;
  }

  char* convToUtf8(const __Char* c) {
    int posC = 0;
    int l = 0;
    unsigned char color = 0;
    unsigned char bgColor = 0;
    while(c[posC][0] != 0) {
      if (c[posC][4] != color) {
        color = c[posC][4];
        l += this->writeColorSequence(&this->tmpBuffer[l], color, false);
        if (color == 0) bgColor = 0;
      }
      if (c[posC][5] != bgColor) {
        bgColor = c[posC][5];
        l += this->writeColorSequence(&this->tmpBuffer[l], bgColor, true);
        if (bgColor == 0) {
          color = 0;
          if (c[posC][4] != color) {
            color = c[posC][4];
            l += this->writeColorSequence(&this->tmpBuffer[l], color, false);
          }
        }
      }
      this->tmpBuffer[l++] = c[posC][0];
      if (c[posC][1] != 0) this->tmpBuffer[l++] = c[posC][1];
      if (c[posC][2] != 0) this->tmpBuffer[l++] = c[posC][2];
      if (c[posC][3] != 0) this->tmpBuffer[l++] = c[posC][3];
      posC++;
    }
    if(color != 0 || bgColor != 0) {
      l += this->writeColorSequence(&this->tmpBuffer[l], 0, true);
    }
    this->tmpBuffer[l] = 0;
    return this->tmpBuffer;
  }

  void makeCols(const char* cols) {
    int l = strlen(cols);
    int l2 = 0;
    for (int i = 0; i < l; i++) {
      char c = cols[i];
      if (c == 'L' || c == 'R' || c == 'C'|| c == 'P') l2++;
    }
    this->colCnt = l2;
    this->cols = (__Column*)malloc(l2 * sizeof(__Column));
    int pos = -1;
    l2 = 0;
    for (int i = 0; i <= l; i++) {
      char c = cols[i];
      if ((c & 192) != 128) pos++;
      if (c == 'L' || c == 'R'|| c == 'C' || c == 'P') {
        this->cols[l2].pos = pos;
        this->cols[l2].color = 255;
        this->cols[l2].bgColor = 255;
        this->cols[l2++].align = c;
      }
    }
  }

  void reallocIfFull() {
    if (this->lineCnt == this->cap) {
      this->cap *= 2;
      this->lines = (__Line*)realloc(this->lines, this->cap * sizeof(__Line));
    }
  }

  UtfTable* newLine(const __Line l) {
    if (this->allocLines <= this->lineCnt) {
      this->lines[this->lineCnt] = (__Line)malloc((this->lineLen + 1) * sizeof(__Char));
    }
    memcpy(this->lines[this->lineCnt++], l, (this->lineLen + 1) * sizeof(__Char));
    this->reallocIfFull();
    this->currCol = 0;
    return this;
  }

  UtfTable* setColor(__Line dst, const unsigned char color, char bg) {
    for (int i = 0; i < lineLen; i++)
      dst[i][4 + bg] = color;
    return this;
  }

  UtfTable* setColors(__Line dst, const char* chars, const unsigned char* colors, char bg) {
    int len = strlen(chars);
    for (int i = 0; i < len; i++)
      if (chars[i] >= '0' && chars[i] <= '9')
        dst[i][4 + bg] = colors[chars[i] - '0'];
    return this;
  }


  public:
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

  UtfTable(const char* top, const char* cols, const char* sep, const char* none, const char* down) {
    int l = strlen(top);
    this->lineLen = 0;
    for (int i = 0; i < l; i++) {
      if ((top[i] & 192) != 128) { //10xxxxxx
        this->lineLen++;
      }
    }
    this->tmpBufferC = (__Line)malloc((this->lineLen + 1) * sizeof(__Char));
    memset(this->tmpBufferC, 0, (this->lineLen + 1) * sizeof(__Char));
    this->top  = this->allocConvFromUtf8(top);
    this->sep  = this->allocConvFromUtf8(sep);
    this->none = this->allocConvFromUtf8(none);
    this->down = this->allocConvFromUtf8(down);
    this->makeCols(cols);
    this->lineCnt = 0;
    this->cap = 100;
    this->lines = (__Line*)malloc(cap * sizeof(__Line));
    this->tmpBuffer = (char*)malloc((this->lineLen + 1) * 40 * sizeof(char));
    this->currCol = 999999;
    this->colorCnt = 9;
    this->allocLines = 0;
    this->topFlushed = false;
  }

  UtfTable* newLine(const char* c) {
    __Line newL = this->lines[this->lineCnt++];
    if (this->allocLines > this->lineCnt) {
      this->convFromUtf8(newL, c, 0, 0);
      newL[this->lineLen + 1][0] = 0;
    } else {
      newL = this->lines[this->lineCnt - 1] = this->allocConvFromUtf8(c);
    }
    for (int i = 0; i < this->lineLen; i++) {
      newL[i][4] = this->none[i][4];
      newL[i][5] = this->none[i][5];
    }
    this->reallocIfFull();
    this->currCol = 0;
    return this;
  }

  UtfTable* newLine() {
    return this->newLine(this->none);
  }

  UtfTable* newLines(int n) {
    for (int i = 0; i < n; i++)
      this->newLine(this->none);
    return this;
  }

  UtfTable* newSep() {
    this->newLine(this->sep);
    this->currCol = 999999;
    return this;
  }

  UtfTable* render() {
    if (!this->topFlushed)
      std::cout << this->convToUtf8(this->top) << std::endl;
    for (int i = 0; i < this->lineCnt; i++)
      std::cout << this->convToUtf8(this->lines[i]) << std::endl;
    std::cout << this->convToUtf8(this->down) << std::endl;
    return this;
  }

  UtfTable* flush() {
    if (!this->topFlushed)
      std::cout << this->convToUtf8(this->top) << std::endl;
    this->topFlushed = true;
    for (int i = 0; i < this->lineCnt; i++)
      std::cout << this->convToUtf8(this->lines[i]) << std::endl;
    if (this->lineCnt > this->allocLines)
      this->allocLines = this->lineCnt;
    this->lineCnt = 0;
    this->currCol = 999999;
    return this;
  }

  UtfTable* val(int offset, int lineId, int colId, const char* v) {
    if (lineId < 0) lineId += this->lineCnt;
    if (colId < 0) colId += this->colCnt;
    if (lineId >= this->lineCnt) this->newLines(lineId - this->lineCnt + 1);
    this->currCol = colId + 1;
    int len = this->convFromUtf8(this->tmpBufferC, v, this->cols[colId].color, this->cols[colId].bgColor);
    __Column* col = &this->cols[colId];
    int from;
    switch (col->align) {
      case 'P':
        from = col->pos - len;
        for (int i = 0; i < len; i++) {
          if (this->tmpBufferC[i][0] == '.') {
            from = col->pos - i;
            break;
          }
        }
      break;
      case 'R':
        from = col->pos - len + 1;
      break;
      case 'C':
        from = col->pos - (len - 1) / 2;
      break;
      default: // L
        from = col->pos;
      break;
    }
    from += offset;
    if (from < 0) from = 0;
    if (from + len > this->lineLen) {
      len = this->lineLen - from;
    }
    for (int i = 0; i < len; i++) {
      if (tmpBufferC[i][4] == 255) tmpBufferC[i][4] = this->lines[lineId][from + i][4];
      if (tmpBufferC[i][5] == 255) tmpBufferC[i][5] = this->lines[lineId][from + i][5];
    }
    memcpy(&this->lines[lineId][from], tmpBufferC, len * sizeof(__Char));
    return this;
  }

  UtfTable* val(int lineId, int colId, const char* v) {
    return this->val(0, lineId, colId, v);
  }

  UtfTable* val(int colId, const char* v) {
    return this->val(0, -1, colId, v);
  }

  UtfTable* val(const char* v) {
    if (this->currCol >= this->colCnt) {
      this->newLine();
    }
    return this->val(0, -1, this->currCol, v);
  }

  UtfTable* valf(int offset, int lineId, int colId, const char* f, ...) {
    va_list args;
    va_start(args, f);
    vsnprintf(this->tmpBuffer, this->lineLen * 4 * sizeof(char), f, args);
    va_end(args);
    return this->val(offset, lineId, colId, this->tmpBuffer);
  }

  UtfTable* valf(int lineId, int colId, const char* f, ...) {
    va_list args;
    va_start(args, f);
    vsnprintf(this->tmpBuffer, this->lineLen * 4 * sizeof(char), f, args);
    va_end(args);
    return this->val(lineId, colId, this->tmpBuffer);
  }

  UtfTable* valf(int colId, const char* f, ...) {
    va_list args;
    va_start(args, f);
    vsnprintf(this->tmpBuffer, this->lineLen * 4 * sizeof(char), f, args);
    va_end(args);
    return this->val(colId, this->tmpBuffer);
  }

  UtfTable* valf(const char* f, ...) {
    va_list args;
    va_start(args, f);
    vsnprintf(this->tmpBuffer, this->lineLen * 4 * sizeof(char), f, args);
    va_end(args);
    return this->val(this->tmpBuffer);
  }

  UtfTable* color(int colId, unsigned char color) {
    if (colId < 0) colId += this->colCnt;
    if (colId >= this->colCnt) colId = 0;
    this->cols[colId].color = color;
    return this;
  }

  UtfTable* color(unsigned char color) {
    return this->color(this->currCol, color);
  }

  UtfTable* bgColor(int colId, unsigned char color) {
    if (colId < 0) colId += this->colCnt;
    this->cols[colId].bgColor = color;
    return this;
  }

  UtfTable* bgColor(unsigned char color) {
    return this->bgColor(this->currCol, color);
  }

  UtfTable* setTopColor   (const unsigned char color) { return this->setColor(this->top,  color, 0); }
  UtfTable* setLineColor  (const unsigned char color) { return this->setColor(this->none, color, 0); }
  UtfTable* setSepColor   (const unsigned char color) { return this->setColor(this->sep,  color, 0); }
  UtfTable* setDownColor  (const unsigned char color) { return this->setColor(this->down, color, 0); }
  UtfTable* setTopBgColor (const unsigned char color) { return this->setColor(this->top,  color, 1); }
  UtfTable* setLineBgColor(const unsigned char color) { return this->setColor(this->none, color, 1); }
  UtfTable* setSepBgColor (const unsigned char color) { return this->setColor(this->sep,  color, 1); }
  UtfTable* setDownBgColor(const unsigned char color) { return this->setColor(this->down, color, 1); }

  UtfTable* setTopColors   (const char* c, const unsigned char* colors) { return this->setColors(this->top,  c, colors, 0); }
  UtfTable* setLineColors  (const char* c, const unsigned char* colors) { return this->setColors(this->none, c, colors, 0); }
  UtfTable* setSepColors   (const char* c, const unsigned char* colors) { return this->setColors(this->sep,  c, colors, 0); }
  UtfTable* setDownColors  (const char* c, const unsigned char* colors) { return this->setColors(this->down, c, colors, 0); }
  UtfTable* setTopBgColors (const char* c, const unsigned char* colors) { return this->setColors(this->top,  c, colors, 1); }
  UtfTable* setLineBgColors(const char* c, const unsigned char* colors) { return this->setColors(this->none, c, colors, 1); }
  UtfTable* setSepBgColors (const char* c, const unsigned char* colors) { return this->setColors(this->sep,  c, colors, 1); }
  UtfTable* setDownBgColors(const char* c, const unsigned char* colors) { return this->setColors(this->down, c, colors, 1); }

  unsigned char rgb(unsigned char r, unsigned char g, unsigned char b) {
    for (int i = 9; i < this->colorCnt; i++) {
      __Color c = this->colors[i];
      if (c.r == r && c.g == g && c.b == b)
        return i;
    }
    this->colors[this->colorCnt++] = {r, g, b};
    return this->colorCnt - 1;
  }

  ~UtfTable() {
    free(this->top);
    free(this->sep);
    free(this->none);
    free(this->down);
    free(this->cols);
    for (int i = 0; i < this->lineCnt && i < this->allocLines; i++)
      free(this->lines[i]);
    free(this->lines);
    free(this->tmpBufferC);
    free(this->tmpBuffer);
  }

};
