
// 扩展精度: w = 80, s = 1, k = 15, n = 63, 1个整数位(对于规格化数据, 它等于1; 对于非规格化数据, 它等于0)
int main() {
  // bias = 2^(k-1) - 1 = 2^14 - 1


  // 问题1: 最小正的非规格化数据
  // 此问题的二进制编码形式为: 0b 0        0...0           0    0...01
  //                          1个符号位 15个阶码位(k=15) 整数位 小数位: 62个0, 1个1
  // 所以:
  // M = 2^-63
  // E = 1 - bias = 1 - 2^14 + 1 = 2 - 2^14 = -(2^14 - 2)
  // 值:  2^-63 * 2^(1-bias)
  // 十进制: 2^-63 * 2^(1-2^14+1) = 2^-63 * 2^-(2^14 - 2) = 2 ^ (-61 -2^14)


  // 问题2: 最小正的规格化数据
  // 此问题的二进制编码形式为: 0b 0        0...01                1        0...0
  //                          1个符号位 15个阶码位(14个0, 1个1) 1个整数位 小数位: 63个0
  // 所以
  // M = 1.0
  // E = exp - bias = 1 - bias = -(2^14 - 2)
  // 值: 2^(1-bias)
  // 十进制: 2^(-2^14 + 2)


  // 问题3: 最大规格化数
  // 此问题的二进制编码形式为: 0b 0        1...10                 1         1...1
  //                          1个符号位 15个阶码位(14个0 1个1)   1个整数位   小数位: 63个1
  // M = 1 + (1 - 2^-63) = 2 - 2^-63
  // exp = 2^15 - 2 = 2(2^14 - 1) = 2*bias
  // E = exp - bias = 2bias - bias = bias
  // 值: (2 - 2^-63) * 2^bias
  // 十进制: (2 - 2^-63) * 2^(2^14-1)
}