#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

#define CAUSE_MACHINE_ECALL 0xb
#define CAUSE_INTR_TIMER 0x8000000000000007

static Context* (*user_handler)(Event, Context*) = NULL;

/**
 * _syscall_(ecall) -> __am_asm_trap -> __am_irq_handle -> user_handler (do_event) -> do_syscall -> syscall_XXX (设置返回值Context->a0)
 * _syscall_  <- __am_asm_trap(mret) <- __am_irq_handle <- user_handler (do_event) <- do_syscall <-------|
 *   libos                   am                am               nanos                     nanos        nanos
*/
// __am_irq_handle 用于包装分发事件, 并交由 "事件处理回调函数 event handler" 处理
Context* __am_irq_handle(Context *c) {
    if (user_handler) {
        Event ev = {0};
        switch (c->mcause) {
            case CAUSE_INTR_TIMER: 
                ev.event = EVENT_IRQ_TIMER; 
                break;
            case CAUSE_MACHINE_ECALL:
                if (c->GPR1 == -1)
                    ev.event = EVENT_YIELD;
                else 
                    ev.event = EVENT_SYSCALL;
                // c->mepc 存在栈中, ecall 引起的异常需要将 mepc 指向其下一条指令
                c->mepc += 4; 
                break;
            default: ev.event = EVENT_ERROR; break;
        }
        // 调用 nanos 的 do_event
        c = user_handler(ev, c);
        assert(c != NULL);
    }

    return c;
}

// __am_asm_trap 负责保存上下文并调用 __am_irq_handle
extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
    // initialize exception entry 
    // 设置异常入口地址, __am_asm_trap 负责保存上下文并调用 __am_irq_handle,
    // __am_irq_handle 用于包装分发事件, 并交由 "事件处理回调函数 event handler" 处理
    asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

    // register event handler
    // 注册事件处理回调函数, 回调函数由 Nanos-lite 提供
    user_handler = handler;

    return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
    return NULL;
}

void yield() {
    asm volatile("li a7, -1; ecall");
}

bool ienabled() {
    return false;
}

void iset(bool enable) {
    if (enable) {
        asm volatile("csrsi mstatus, 8");
        asm volatile("csrs  mie, %0" : : "rK"(0x80));
    } else {
        asm volatile("csrci mstatus, 8");
        asm volatile("csrc  mie, %0" : : "rK"(0x80));
    }
}
