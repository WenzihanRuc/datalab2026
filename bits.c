/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    int ans;
    ans = ~(~x | ~y); //德摩根定律
    return ans;
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    int ans;
    ans = ~(x & y ) & (~((~x) & (~y)) );//排除都为1,都为0的情况
    return ans;
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!(x && y)){
        if(x) return 0;
        if(y) return 0;
        return 1;
    }
    int judge = 1;
    if( (x >> 31 ) ^ (y >> 31) ) judge = 0;
    return judge;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int ans,shift;
    shift = ((v >> 16) > 0) << 4;//如果移动16位之后还有1在，那么至少是16次方，相当于1左4位
    ans = shift;
    v = v >> shift;
    shift = ((v >> 8) > 0) << 3;
    ans = ans | shift; //这里或运算和加法等效，因为每次shift都是2的幂次方
    v = v >> shift;
    shift = ((v >> 4) > 0) << 2;
    ans = ans | shift;
    v = v >> shift;
    shift = ((v >> 2) > 0) << 1;
    ans = ans | shift;
    v = v >> shift;
    shift = ((v >> 1) > 0);
    ans = ans | shift;  
    return ans;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int byte_n = (x >> (n << 3)) & 0xFF;
    int byte_m = (x >> (m << 3)) & 0xFF; //取m字节和n字节
    int diff = byte_n ^ byte_m; //异或得到不同的位
    int ans = x ^ (diff << (n << 3)) ^ (diff << (m << 3)); //将不同的位放回原来的位置
    return ans;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned ans = 0, i = 32;
    while(i){
        ans = (v & 1) | (ans << 1);
        v = v >> 1;
        i--;
    }
    return ans;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int ans;
    ans = x >> n;
    int mask = ~(((1 << 31) >> n) << 1); //制造1111···0000掩码，使得右移后高位补0；向左1个位置表示原符号位平移后数字不变
    ans = ans & mask;
    return ans;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int ans = 0;
    int check;
    check =!(~(x>>16));//判断头16位是否全1
    ans += check << 4;//如果全1，那么ans加16，否则加0
    x = x << (check << 4);//x进行移动位置，若全1则删除这些前导，若不是则另加判断
    check = !(~(x>>24));//判断头8位是否全1，注意这个时候头8位可能和最初x不一样，下同。
    ans += check << 3;
    x = x << (check << 3);
    check = !(~(x>>28));
    ans += check << 2;
    x = x << (check << 2);
    check = !(~(x>>30));
    ans += check << 1;
    x = x << (check << 1);
    check = !(~(x>>31));
    ans += check;
    x = x << check;
    check = !(~(x>>31));
    ans += check;
    return ans;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    int sign = x & (1 << 31),num = 0;//符号位,num表示有效位数
    if (x == 0) return 0;
    if (x == 0x80000000) return 0xcf000000;
    if (sign) x = ~x + 1;
    int temp=x;
    while(temp){
        temp = temp >> 1;
        num++;
    }
    int ans;
    int storing = num;
    if(num > 24){
        int move = num - 24;
        int tail=x & ((1 << move)-1);
        int half=1 << (move-1);
        x = x >> move;
        if(tail > half) x = x + 1;//大于一半时进位
        else if(tail == half){
            if(x & 1) x = x + 1;
        }//四舍六入，正好一半时向偶数舍入
        num=24;
    }
    ans=sign + ((storing + 125)<<23) + (x << (24-num));
    //符号位：sign；位码：num-1；有效位：x
    return ans;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf >> 31;
    unsigned exponent = (uf >> 23) & 0xFF;
    unsigned fraction = uf & 0x7FFFFF;
    if(exponent == 0xFF) return uf; //处理NaN和无穷大
    if(exponent == 0){
        if(fraction == 0) return uf; //处理0
        fraction = fraction << 1;
    }
    else{
        exponent += 1;
        if(exponent == 0xFF) fraction = 0; //处理溢出为无穷大
    }
    return (sign << 31) | (exponent << 23) | fraction;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sign = uf2 >> 31;
    int exponent = ((uf2 >> 20) & 0x7FF) - 1023; // 算阶码，去偏移
    if (exponent < 0) return 0;
    if (exponent >=31) return 0x80000000; 
    int ans = 1 << exponent; // 隐含的1
    if (exponent <= 20) ans = ans + ((uf2 & 0xFFFFF) >> (20 - exponent));
    else ans = ans + ((uf2 & 0xFFFFF) << (exponent - 20)) + (uf1 >> (52 - exponent));
    if(sign) ans = ~ans + 1;
    return ans;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x > 127) return 0x7F800000; // +INF
    if(x >= -126 && x <= 127){
        return (x + 127) << 23; // 正常数
    }
    if(x >= -149){
        return 1 << 22 >> (-127 - x);
    }
    else return 0;
}
