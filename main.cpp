#include "utftable.h"

void example1() {
  std::cout << "\n\nExample 1: Column alignments\n";
  UtfTable *tbl = new UtfTable(
    "┌──────────┬──────────┬──────────┬──────────┐",
    "│ L        │        R │     C    │      P   │",
    "├──────────┼──────────┼──────────┼──────────┤",
    "│          │          │          │          │",
    "└──────────┴──────────┴──────────┴──────────┘");
  tbl->val("Left")   ->val("Right")  ->val("Center") ->val("Point");
  tbl->newSep();
  tbl->val("1.1")    ->val("2.2")    ->val("3.3")    ->val("4.4");
  tbl->val("1.111")  ->val("2.222")  ->val("3.333")  ->val("4.444");
  tbl->val("111.111")->val("222.222")->val("333.333")->val("444.444");
  tbl->render();
  delete tbl;
}

void example2() {
  std::cout << "\n\nExample 2: Offset\n";
  UtfTable *tbl = new UtfTable(
    "┌──────────┬──────────┬──────────┬──────────┐",
    "│ L        │        R │     C    │      P   │",
    "├──────────┼──────────┼──────────┼──────────┤",
    "│          │          │          │          │",
    "└──────────┴──────────┴──────────┴──────────┘");
  tbl->val("Left")   ->val("Right")  ->val("Center") ->val(3, -1, 3, "Point");
  tbl->newSep();
  tbl->val("1.1")    ->val("2.2")    ->val("3.3")    ->val("4.4");
  tbl->val("1.111")  ->val("2.222")  ->val("3.333")  ->val("4.444");
  tbl->val("111.111")->val("222.222")->val("333.333")->val("444.444");
  tbl->render();
  delete tbl;
}

void example3() {
  std::cout << "\n\nExample 3: Line/column position\n";
  UtfTable *tbl = new UtfTable(
    "┌──────────┬──────────┬──────────┬──────────┐",
    "│ L        │        R │     C    │      P   │",
    "├──────────┼──────────┼──────────┼──────────┤",
    "│          │          │          │          │",
    "└──────────┴──────────┴──────────┴──────────┘");
  tbl->val("Left")   ->val("Right")  ->val("Center") ->val(3, -1, 3, "Point");
  tbl->newSep();
  tbl->newLines(4);
  tbl->val(2, -4, "2,-4");
  tbl->val(3, -3, "3,-3");
  tbl->val(4, -2, "4,-2");
  tbl->val(5, -1, "5,-1");
  tbl->val(-1, 0, "-1,0");
  tbl->val(-2, 1, "-2,1");
  tbl->val(-3, 2, "-3,2");
  tbl->val(-4, 3, "-4,3");
  tbl->render();
  delete tbl;
}

void example4() {
  std::cout << "\n\nExample 4: Different border style\n";
  UtfTable *tbl = new UtfTable(
    "╔════════╦════════╦════════╦════════╗",
    "║ L      ║      R ║   C    ║    P   ║",
    "╠════════╬════════╬════════╬════════╣",
    "║        ║        ║        ║        ║",
    "╚════════╩════════╩════════╩════════╝");
  tbl->val("Left")   ->val("Right")  ->val("Center") ->val(3, -1, 3, "Point");
  tbl->newSep();
  tbl->val("1.1")    ->val("2.2")    ->val("3.3")    ->val("4.4");
  tbl->val("1.111")  ->val("2.222")  ->val("3.333")  ->val("4.444");
  tbl->val("111.111")->val("222.222")->val("333.333")->val("444.444");
  tbl->render();
  delete tbl;
}

void example5() {
  std::cout << "\n\nExample 5: Different line in the middle\n";
  UtfTable *tbl = new UtfTable(
    "╔════════╦════════╦════════╦════════╗",
    "║ L      ║      R ║   C    ║    P   ║",
    "╠════════╬════════╬════════╬════════╣",
    "║        ║        ║        ║        ║",
    "╚════════╩════════╩════════╩════════╝");
  tbl->val("Left")   ->val("Right")  ->val("Center")  ->val(3, -1, 3, "Point");
  tbl->newSep();
  tbl->val("1.1")    ->val("2.2")    ->val("3.3")     ->val("4.4");
  tbl->newLine("╠════════╬════════╣        ║        ║");
  tbl                                ->val(2, "3.333")->val("4.444");
  tbl->val("111.111")->val("222.222")->val("333.333") ->val("444.444");
  tbl->render();
  delete tbl;
}

void example6() {
  std::cout << "\n\nExample 6: Int values with valf()\n";
  UtfTable *tbl = new UtfTable(
    "╔════════╦════════╦════════╦════════╗",
    "║ L      ║      R ║   C    ║    P   ║",
    "╠════════╬════════╬════════╬════════╣",
    "║        ║        ║        ║        ║",
    "╚════════╩════════╩════════╩════════╝");
  tbl->val("Left")   ->val("Right")  ->val("Center")  ->val(3, -1, 3, "Point");
  tbl->newSep();
  for (int i = 0; i < 24; i++) {
    tbl->valf("%d", i);
  }
  tbl->render();
  delete tbl;
}

void example7() {
  std::cout << "\n\nExample 7: Flush\n";
  UtfTable *tbl = new UtfTable(
    "╔════════╦════════╦════════╦════════╗",
    "║ L      ║      R ║   C    ║    P   ║",
    "╠════════╬════════╬════════╬════════╣",
    "║        ║        ║        ║        ║",
    "╚════════╩════════╩════════╩════════╝");
  tbl->val("Left")   ->val("Right")  ->val("Center")  ->val(3, -1, 3, "Point");
  tbl->newSep();
  for (int i = 0; i < 24; i++) {
    tbl->valf("%d", i);
    if (i % 7 == 6) {
      tbl->flush();
      std::cout << "...flush..." << std::endl;
    }
  }
  tbl->render();
  delete tbl;
}

void example8() {
  std::cout << "\n\nExample 8: Colored values\n";
  UtfTable *tbl = new UtfTable(
    "╔════════╦════════╦════════╦════════╗",
    "║ L      ║      R ║   C    ║    P   ║",
    "╠════════╬════════╬════════╬════════╣",
    "║        ║        ║        ║        ║",
    "╚════════╩════════╩════════╩════════╝");
  tbl->color(0, tbl->clBlack)->bgColor(0, tbl->clGreen);
  tbl->color(1, tbl->clBlack)->bgColor(1, tbl->clBlue);
  tbl->color(2, tbl->clBlack)->bgColor(2, tbl->clMagenta);
  tbl->color(3, tbl->clBlack)->bgColor(3, tbl->clCyan);
  tbl->val("Left")   ->val("Right")  ->val("Center") ->val(3, -1, 3, "Point");
  tbl->newSep();
  tbl->color(0, tbl->clGreen)  ->bgColor(0, tbl->clInherit);
  tbl->color(1, tbl->clBlue)   ->bgColor(1, tbl->clInherit);
  tbl->color(2, tbl->clMagenta)->bgColor(2, tbl->clInherit);
  tbl->color(3, tbl->clCyan)   ->bgColor(3, tbl->clInherit);
  tbl->val("1.1")    ->val("2.2")    ->val("3.3")    ->val("4.4");
  tbl->val("1.111")  ->val("2.222")  ->val("3.333")  ->val("4.444");
  tbl->val("111.111")->val("222.222")->val("333.333")->val("444.444");
  tbl->render();
  delete tbl;
}

void example9() {
  std::cout << "\n\nExample 9: Different background for odd/even lines\n";
  UtfTable *tbl = new UtfTable(
    "╔════════╦════════╦════════╦════════╗",
    "║ L      ║      R ║   C    ║    P   ║",
    "╠════════╬════════╬════════╬════════╣",
    "║        ║        ║        ║        ║",
    "╚════════╩════════╩════════╩════════╝");
  char colors [7]{
    tbl->clGreen,
    tbl->clBlue,
  };
  const char* odd  = "0000000000000000000000000000000000000";
  const char* even = "1111111111111111111111111111111111111";
  tbl->val("Left")->val("Right")->val("Center")->val(3, -1, 3, "Point");
  tbl->newSep();
  for (int i = 0; i < 8; i++) {
    tbl->setLineBgColors(i % 2 == 0 ? odd : even, colors);
    tbl->valf("%d,1", i)->valf("%d,2", i)->valf("%d,3", i)->valf("%d,4", i);
  }
  tbl->render();
  delete tbl;
}

void example10() {
  std::cout << "\n\nExample 10: Colored lines and background\n";
  UtfTable *tbl = new UtfTable(
    "╔════════╦════════╦════════╦════════╗",
    "║ L      ║      R ║   C    ║    P   ║",
    "╠════════╬════════╬════════╬════════╣",
    "║        ║        ║        ║        ║",
    "╚════════╩════════╩════════╩════════╝");
  char colors [7]{
    tbl->clGreen,
    tbl->clRed,
    tbl->clYellow,
    tbl->clBlue,
    tbl->clCyan,
    tbl->clMagenta,
    tbl->clWhite,
  };
  tbl->setTopColors   ("2111111112111111112111111112111111112", colors);
  tbl->setSepColors   ("4333333334333333334333333334333333334", colors);
  tbl->setLineColors  ("0........0........0........0........0", colors);
  tbl->setDownColors  ("6555555556555555556555555556555555556", colors);
  tbl->setLineBgColors(".55555555.55555555.55555555.55555555.", colors);
  tbl->setSepBgColors (".5......5.5......5.5......5.5......5.", colors);
  tbl->val("Left")   ->val("Right")  ->val("Center") ->val(3, -1, 3, "Point");
  tbl->newSep();
  tbl->setLineBgColors(".33333333.33333333.33333333.33333333.", colors);
  tbl->val("1.1")    ->val("2.2")    ->val("3.3")    ->val("4.4");
  tbl->val("1.111")  ->val("2.222")  ->val("3.333")  ->val("4.444");
  tbl->val("111.111")->val("222.222")->val("333.333")->val("444.444");
  tbl->render();
  delete tbl;
}

void example11() {
  std::cout << "\n\nExample 11: RGB colors\n";
  UtfTable *tbl = new UtfTable(
    "╔════════╦════════╦════════╦════════╗",
    "║ L      ║      R ║   C    ║    P   ║",
    "╠════════╬════════╬════════╬════════╣",
    "║        ║        ║        ║        ║",
    "╚════════╩════════╩════════╩════════╝");
  char colors [37];
  for (int i = 0; i < 37; i++) {
    colors[i] = tbl->rgb(255, i * 7, 0);
  }
  const char* parts[4] = {
    "0123456789...........................",
    "..........0123456789.................",
    "....................0123456789.......",
    "..............................0123456"
  };
  for (int i = 0; i < 4; i++) {
    tbl->setTopColors (parts[i], &colors[i * 10]);
    tbl->setSepColors (parts[i], &colors[i * 10]);
    tbl->setLineColors(parts[i], &colors[i * 10]);
    tbl->setDownColors(parts[i], &colors[i * 10]);
  }
  tbl->val("Left")   ->val("Right")  ->val("Center") ->val(3, -1, 3, "Point");
  tbl->newSep();
  tbl->val("1.1")    ->val("2.2")    ->val("3.3")    ->val("4.4");
  tbl->val("1.111")  ->val("2.222")  ->val("3.333")  ->val("4.444");
  tbl->val("111.111")->val("222.222")->val("333.333")->val("444.444");
  tbl->render();
  delete tbl;
}

void example12() {
  std::cout << "\n\nExample 12: Pixel art with background colors :)\n";
  UtfTable* tbl = new UtfTable(
    "                     ",
    "                     ",
    "                     ",
    "                     ",
    "                     ");
  char colors[8] = {
    tbl->rgb(85,  0,   0),
    tbl->rgb(170, 128, 0),
    tbl->rgb(255, 192, 0),
    tbl->rgb(255, 255, 255),
    tbl->rgb(0,   0,   0),
    tbl->rgb(255, 0,   0),
    tbl->clDefault,
    tbl->rgb(200, 100,   0)
  };
  tbl
  ->setLineBgColors("666666666616666666666", colors)->newLine()
  ->setLineBgColors("666666660222066666666", colors)->newLine()
  ->setLineBgColors("666666012222210666666", colors)->newLine()
  ->setLineBgColors("612222234323432222216", colors)->newLine()
  ->setLineBgColors("660222222272222222066", colors)->newLine()
  ->setLineBgColors("666660225222522066666", colors)->newLine()
  ->setLineBgColors("666662225555522266666", colors)->newLine()
  ->setLineBgColors("666662222111222266666", colors)->newLine()
  ->setLineBgColors("666622210000012226666", colors)->newLine()
  ->render();
  delete tbl;
}

int main() {
  example1();
  example2();
  example3();
  example4();
  example5();
  example6();
  example7();
  example8();
  example9();
  example10();
  example11();
  example12();

  return 0;
}
