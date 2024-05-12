/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */ 
/** ThreadX Component                                                     */ 
/**                                                                       */
/**   Thread                                                              */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


#define TX_SOURCE_CODE


/* Include necessary system files.  */

#include "tx_api.h"
#include "tx_thread.h"
#include "tx_timer.h"

 #include <stdio.h>
// #include <stdlib.h>

#include "am.h"
 #include <assert.h>
/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _tx_thread_context_save                             Linux/GNU       */ 
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function saves the context of an executing thread in the       */ 
/*    beginning of interrupt processing.  The function also ensures that  */ 
/*    the system stack is used upon return to the calling ISR.            */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    None                                                                */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    None                                                                */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _tx_linux_debug_entry_insert                                        */ 
/*    tx_linux_mutex_lock                                                 */ 
/*    _tx_linux_thread_suspend                                            */ 
/*    tx_linux_mutex_unlock                                               */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    ISRs                                                                */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  09-30-2020     William E. Lamie         Initial Version 6.1           */
/*                                                                        */
/**************************************************************************/
int save_flag;
TX_THREAD * recovery_thread;
VOID   _tx_timer_interrupt(VOID);
TX_THREAD * save_thread;
static Context* ev_handler(Event e, Context *c) {
      switch (e.event) {
            case EVENT_YIELD: {
                  //printf("in yield\n");
                  if(save_flag)
                  {
                        // Context *temp = (Context*)malloc(sizeof(Context));
                        // _tx_thread_current_ptr->tx_thread_stack_ptr = temp;
                        // *temp = *c;
                        
                        assert(recovery_thread);
                        save_thread->tx_thread_stack_ptr = c;
                        save_thread = NULL;
                        save_flag = 0;
                       // printf("save out %p restore to %p %p\n",c,recovery_thread -> tx_thread_stack_ptr,c->uc.uc_mcontext.gregs[REG_RIP]);
                        
                        c = recovery_thread -> tx_thread_stack_ptr;
                        //printf("%p\n",c->uc.uc_mcontext.gregs[REG_RIP]);

                        break;
                  }      
                  else  
                  {
                        //printf("restore :%p\n",recovery_thread -> tx_thread_stack_ptr);
                        

                        
                        // Context * temp = recovery_thread -> tx_thread_stack_ptr;
                        c = recovery_thread -> tx_thread_stack_ptr;
                       // printf("%p\n",c->uc.uc_mcontext.gregs[REG_RIP]);
                        //printf("restore sp :%p\n",recovery_thread -> tx_thread_stack_ptr);
                        // memcpy(c,recovery_thread -> tx_thread_stack_ptr, sizeof(Context));
                        // memset(recovery_thread -> tx_thread_stack_ptr,0,sizeof(Context));
                       // c->GPRSP = sp;
                       // printf("restore out %p %p %p\n",c,&c->uc.uc_mcontext.gregs[REG_RIP],c->uc.uc_mcontext.gregs[REG_RIP]);
                        break; 
                  }
                  
            }
            case EVENT_IRQ_TIMER: {
                 // printf("time irq\n");

                  _tx_timer_interrupt();
                  /* Call the ThreadX system timer interrupt processing.  */
                  

                  // /* Call ThreadX context save for interrupt preparation.  */
                  // _tx_thread_context_save();

                  // /* Call ThreadX context restore for interrupt completion.  */
                  // _tx_thread_context_restore();
                  break;
            } 
            default:printf("Unhandled event ID = %d\n", e.event); assert(0); break;
      }
      return c;
}

void __am_cte_init() {
  cte_init(ev_handler);
}

void _tx_thread_not_nested_save();
void _tx_thread_nested_save();
void _tx_thread_idle_system_save();


VOID   _tx_thread_context_save(VOID)
{
//       //printf("save in\n");
//       if ((_tx_thread_current_ptr) && (_tx_thread_system_state == 0))
//       {
//             save_flag++;
//             yield();   //stack_pointer may cause the memory leak
//       }

       _tx_thread_system_state++;
}


// VOID   _tx_thread_context_save(VOID)
// {
//       if(_tx_thread_system_state == 0)  //not nested store
//       {
//             _tx_thread_not_nested_save();
//       }
//       else
//       {
//             _tx_thread_nested_save();
//       }
// }
// 
// void _tx_thread_not_nested_save()
// {
//       _tx_thread_system_state++;
//       if(_tx_thread_current_ptr == NULL)   //question
//             _tx_thread_idle_system_save();
//       else 
//       {
//             save_flag++;
//             yield();   //stack_pointer may cause the memory leak
//       }
           
// }


// void _tx_thread_nested_save()
// {
//       _tx_thread_system_state++;
//       save_flag++;
//       yield();
// }

// void _tx_thread_idle_system_save()
// {
// #ifdef TX_ENABLE_EXECUTION_CHANGE_NOTIFY
//       _tx_execution_isr_enter()                     // Call the ISR execution enter function
// #endif

// }
      
