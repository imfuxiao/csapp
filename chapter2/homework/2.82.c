

// 我们在一个int类型为32位的机器上运行程序. 这些值已补码的形式表示, 而且它们都是算数右移的. unsigned类型的值也是32位的.
// 我们随机生成x与y的值, 并把它们转为无符号数, 显示如下:

#include <stdlib.h>
#include <printf.h>

// Create some arbitrary values
//int x = random();
//int y = random();

// Covert to unsigned
//unsigned ux = (unsigned ) x;
//unsigned uy = (unsigned ) x;

int main() {
  // 对于下面每个C表达式, 你要指出每个表达式的值是否总是为1, 如果总是为1, 请描述其中的数学原理. 否则, 列举出一个使它为0的参数示例.
  // A. (x < y) == (-x > -y)
  // false = 0. 当 x = TMin, -x = TMin, y = 1, -y = -1, TMin < -1. 所以A不成立

  // B. ((x+y) << 4) + y - x == 17 * y + 15 * x
  // true = 1. (x + y) << 4 + y - x = (x + y) * 16 + y - x = 17 * y + 15 * x

  // C. ~x + ~y + 1 == ~(x + y)
  // true = 1.
  // -y = ~y + 1
  // ~x = -x - 1
  // ~x + ~y + 1 => -x - 1 -y => - (x + y) - 1 == ~(x + y)

  // D. (ux - uy) == -(unsigned)(y - x)
  // true = 1
  // (ux - uy) == -(unsigned)(y - x)
  // => -(ux - uy) == (unsigned)(y - x)
  // => uy - ux == (unsigned)(y - x)
  // P63页. 2.14

  // E. ((x >> 2) << 2) <= x
  // 1.
  // x = 0 时, 条件成立
  // x < 0 时, x >> 2 没有加 bias. x >> 2会偏小, 所以表达式成立
  // x > 0 时, x >> 2 向零舍入, 值偏小, 所以表达式成立.
}