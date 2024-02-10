#ifndef ARCH_H__
#define ARCH_H__

/** 
 * riscv 触发异常后硬件的响应过程如下:
 * 1. 将当前PC值保存到mepc寄存器
 * 2. 在mcause寄存器中设置异常号
 * 3. 从mtvec寄存器中取出异常入口地址
 * 4. 跳转到异常入口地址
 * 
 * 上述保存程序状态以及跳转到异常入口地址的工作, 都是硬件自动完成的, 不需要程序员编写指令来完成相应的内容
 **/
struct Context {
    uintptr_t gpr[32], mcause, mstatus, mepc;
    void *pdir;
}; 

#define GPR1 gpr[17]	// a7 系统调用号
#define GPR2 gpr[10]	// a0 系统调用参数
#define GPR3 gpr[11]	// a1 系统调用参数
#define GPR4 gpr[12]	// a2 系统调用参数
#define GPRx gpr[10]	// a0 系统调用返回值
#endif
