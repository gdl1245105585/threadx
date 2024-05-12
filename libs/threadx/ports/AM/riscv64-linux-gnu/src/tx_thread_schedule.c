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

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _tx_thread_schedule                                 Linux/GNU       */ 
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function waits for a thread control block pointer to appear in */
/*    the _tx_thread_execute_ptr variable.  Once a thread pointer appears */
/*    in the variable, the corresponding thread is resumed.               */
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
/*    tx_linux_mutex_lock                                                 */
/*    tx_linux_mutex_unlock                                               */
/*    _tx_linux_debug_entry_insert                                        */
/*    _tx_linux_thread_resume                                             */
/*    tx_linux_sem_post                                                   */
/*    sem_trywait                                                         */
/*    tx_linux_sem_wait                                                   */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    _tx_initialize_kernel_enter          ThreadX entry function         */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  09-30-2020     William E. Lamie         Initial Version 6.1           */
/*                                                                        */
/**************************************************************************/
extern TX_THREAD * recovery_thread;
void _tx_thread_synch_return();
VOID   _tx_thread_schedule(VOID)
{
   iset(1);
   while (_tx_thread_execute_ptr == TX_NULL);
   iset(0);

   // Setup the current thread pointer
   _tx_thread_current_ptr = _tx_thread_execute_ptr;

   // Increment the run count for this thread
   _tx_thread_current_ptr->tx_thread_run_count++;

   // Setup time-slice, if present
   _tx_timer_time_slice = _tx_thread_current_ptr->tx_thread_time_slice;

   #ifdef TX_ENABLE_EXECUTION_CHANGE_NOTIFY
      _tx_execution_thread_enter()  // Call the thread execution enter function
   #endif


   //There neet to determen if there is interrupt frame and synch frame;
   // void* sp = _tx_thread_execute_ptr -> tx_thread_stack_ptr;
   // if(*(int*)sp == 0)
   // {
   //    _tx_thread_synch_return();
   // }
   // else 
   // {
      recovery_thread = _tx_thread_execute_ptr ;
      yield();   
   // }
}

void _tx_thread_synch_return()
{
      recovery_thread = _tx_thread_execute_ptr;
      yield();   //the recovery thread is not current

}