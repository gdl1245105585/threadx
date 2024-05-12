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

#define    TX_SOURCE_CODE


/* Include necessary system files.  */

#include "tx_api.h"
#include "tx_thread.h"
#include "tx_timer.h"
// #include <stdio.h>

#include "am.h"
#include <stdbool.h>
#include <assert.h>
/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _tx_thread_system_return                            Linux/GNU       */ 
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function is target processor specific.  It is used to transfer */ 
/*    control from a thread back to the system.  Only a minimal context   */ 
/*    is saved since the compiler assumes temp registers are going to get */ 
/*    slicked by a function call anyway.                                  */ 
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
/*    pthread_self                                                        */ 
/*    pthread_getschedparam                                               */ 
/*    pthread_equal                                                       */ 
/*    tx_linux_mutex_recursive_unlock                                     */ 
/*    tx_linux_mutex_unlock                                               */ 
/*    pthread_exit                                                        */ 
/*    tx_linux_sem_post                                                   */ 
/*    sem_trywait                                                         */
/*    tx_linux_sem_wait                                                   */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    ThreadX components                                                  */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  09-30-2020     William E. Lamie         Initial Version 6.1           */
/*                                                                        */
/**************************************************************************/
void _tx_thread_dont_save_ts(void);
extern bool save_flag;
VOID   _tx_thread_system_return(VOID)
{
   
   
  // printf("in return\n");
   // if(_tx_thread_current_ptr == NULL)
   // {

   // }
   // else 
   // {
   //    save_flag ++;
   //    yield();
   // }
   
  // printf("out return\n");
   iset(0);
#ifdef TX_ENABLE_EXECUTION_CHANGE_NOTIFY
   _tx_execution_thread_exit();                   // Call the thread execution exit function
#endif
   if (_tx_timer_time_slice){
      _tx_thread_current_ptr -> tx_thread_time_slice =  _tx_timer_time_slice;
      _tx_timer_time_slice =  0;
   }
   else{
      _tx_thread_dont_save_ts();
   }

}

