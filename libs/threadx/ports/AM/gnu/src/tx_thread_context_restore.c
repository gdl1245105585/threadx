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

#include "am.h"
#include <assert.h>

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _tx_thread_context_restore                          Linux/GNU       */ 
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function restores the interrupt context if it is processing a  */ 
/*    nested interrupt.  If not, it returns to the interrupt thread if no */ 
/*    preemption is necessary.  Otherwise, if preemption is necessary or  */ 
/*    if no thread was running, the function returns to the scheduler.    */ 
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
/*    sem_trywait                                                         */
/*    tx_linux_sem_post                                                   */ 
/*    tx_linux_sem_wait                                                   */ 
/*    _tx_linux_thread_resume                                             */ 
/*    tx_linux_mutex_recursive_unlock                                     */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    ISRs                                  Interrupt Service Routines    */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  09-30-2020     William E. Lamie         Initial Version 6.1           */
/*                                                                        */
/**************************************************************************/


extern bool save_flag;
extern TX_THREAD * recovery_thread;
void _tx_thread_not_nested_restore();
void _tx_thread_nested_restore();
void _tx_thread_idle_system_restore();
void _tx_thread_preempt_restore();
void _tx_thread_dont_save_ts();
void _tx_thread_no_preempt_restore();

VOID   _tx_thread_context_restore(VOID)
{
    iset(0);

    --_tx_thread_system_state;
    if(_tx_thread_system_state == 0)  //not nested store
    {
        _tx_thread_not_nested_restore();
    }
    else
    {
        _tx_thread_nested_restore();
    }
}

void _tx_thread_not_nested_restore()
{

      if(_tx_thread_current_ptr == 0)
      {
            _tx_thread_idle_system_restore();
            return;
      }
 
      if(_tx_thread_preempt_disable >0)
      {
            _tx_thread_no_preempt_restore();
            return ;
      }
           
      if(_tx_thread_execute_ptr != _tx_thread_current_ptr)
      {
            _tx_thread_preempt_restore();
            return;
      }
} 
void _tx_thread_nested_restore()
{
      recovery_thread = _tx_thread_current_ptr;
      yield();
}

void _tx_thread_idle_system_restore()
{
      _tx_thread_schedule();
}

void _tx_thread_preempt_restore()
{
      recovery_thread = _tx_thread_current_ptr;
      yield();
      if(_tx_timer_time_slice == 0)
      {
            _tx_thread_dont_save_ts();
      }
      else 
      {
            _tx_thread_current_ptr -> tx_thread_time_slice =  _tx_timer_time_slice;
            _tx_timer_time_slice =  0;
      }
            
}

void _tx_thread_dont_save_ts()
{
      _tx_thread_current_ptr =  TX_NULL;
      _tx_thread_idle_system_restore();

}

void _tx_thread_no_preempt_restore()
{
      save_flag++;
      yield();
      return ;
}