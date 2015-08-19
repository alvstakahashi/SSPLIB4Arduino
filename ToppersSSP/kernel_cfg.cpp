/* kernel_cfg.c */
//#include "kernel_int.h"
#include "include/kernel_impl.h"
#include "include/task.h"
#include "include/time_event.h"
#include "include/cyclic.h"
#include "include/alarm.h"
#include "include/kernel_unrename.h"

#include "include/kernel_cfg.h"

#include "include/sample1.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  Task Management Functions
 */
void dummy(intptr_t arg);

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

const ATR     	_kernel_tinib_tskatr[TNUM_TSKID]    = {(TA_ACT),(TA_NULL),(TA_NULL),(TA_NULL),(TA_NULL)};
const uint_t	_kernel_init_rdypmap = 1U;
const intptr_t	_kernel_tinib_exinf[TNUM_TSKID]     = {(intptr_t)(0),(intptr_t)(0),(intptr_t)(0),(intptr_t)(0),(intptr_t)(0)};
 	  TASK    	_kernel_tinib_task[TNUM_TSKID];		//      = {(task1),(task2)};
const uint_t  	_kernel_tinib_epriority[TNUM_TSKID] = {INT_PRIORITY(1),INT_PRIORITY(2),INT_PRIORITY(3),INT_PRIORITY(4),INT_PRIORITY(5)};

/*
 *  Cyclic Handler Functions
 */

const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);
const uint_t _kernel_cycevtid_offset = 0;

const uint_t _kernel_cycinib_cycact = 0;
const intptr_t _kernel_cycinib_exinf[TNUM_CYCID] = {(intptr_t)(1),(intptr_t)(2),(intptr_t)(3),(intptr_t)(4),(intptr_t)(5)};
//const CYCHDR _kernel_cycinib_cychdr[TNUM_CYCID] = {(mrb_ssp_cyclic_call),(mrb_ssp_cyclic_call),(mrb_ssp_cyclic_call),(mrb_ssp_cyclic_call),(mrb_ssp_cyclic_call)};
        CYCHDR _kernel_cycinib_cychdr[TNUM_CYCID];	// = {(mrb_ssp_cyclic_call),(mrb_ssp_cyclic_call),(mrb_ssp_cyclic_call),(mrb_ssp_cyclic_call),(mrb_ssp_cyclic_call)};
//const RELTIM _kernel_cycinib_cyctim[TNUM_CYCID] = {(2000),(2000),(500),(1000),(50000)};
        RELTIM _kernel_cycinib_cyctim[TNUM_CYCID]; // = {(2000),(2000),(500),(1000),(50000)};
const RELTIM _kernel_cycinib_cycphs[TNUM_CYCID] = {(0),(0),(0),(0),(0)};

uint_t _kernel_cyccb_cycact;
EVTTIM _kernel_cyccb_evttim[TNUM_CYCID];


/*
 *  Alarm Handler Functions
 */

const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);
const uint_t _kernel_almevtid_offset = TNUM_CYCID;

//const ALMHDR _kernel_alminib_almhdr[TNUM_ALMID] = {(mrb_ssp_alarm_call),(mrb_ssp_alarm_call),(mrb_ssp_alarm_call),(mrb_ssp_alarm_call)};
      ALMHDR   _kernel_alminib_almhdr[TNUM_ALMID]; // = {(mrb_ssp_alarm_call),(mrb_ssp_alarm_call),(mrb_ssp_alarm_call),(mrb_ssp_alarm_call)};
const intptr_t _kernel_alminib_exinf[TNUM_ALMID] = {(intptr_t)(1),(intptr_t)(2),(intptr_t)(3),(intptr_t)(4)};

uint_t _kernel_almcb_almact;

/*
 *  Time Event Management
 */

#define TNUM_TMEVT 9

const uint_t _kernel_tnum_tmevt_queue = 9;

QUEUE _kernel_tmevt_queue[TNUM_TMEVT+1];
EVTTIM _kernel_tmevt_time[TNUM_TMEVT];
CBACK _kernel_tmevt_callback[TNUM_TMEVT];
uintptr_t _kernel_tmevt_arg[TNUM_TMEVT];


/*
 *  Stack Area for System
 */
/*
 *  非タスクコンテキスト用のスタック初期値
 */


/*
 *  Module Initialization Function
 */

void
_kernel_initialize_object(void)
{
	_kernel_initialize_time_event();
	_kernel_initialize_task();			//必要
//	_kernel_initialize_interrupt();		
//	_kernel_initialize_exception();		
	_kernel_initialize_cyclic();
	_kernel_initialize_alarm();
}

uint_t init_rdypmap_get(void)
{
	return(_kernel_init_rdypmap);
}

void tinib_task_set(int idx,TASK tsk)			/* タスクの起動番地 */
{
	_kernel_tinib_task[idx] = tsk;
}

void cycinib_cychdr_set(int idx,CYCHDR hdr,RELTIM tout)
{
	_kernel_cycinib_cychdr[idx] = hdr;
	_kernel_cycinib_cyctim[idx] = tout;
}

void alminib_almhdr_set(int idx,ALMHDR hdr)
{
	_kernel_alminib_almhdr[idx] = hdr;
}

#ifndef TARGET_COPYRIGHT
#define TARGET_COPYRIGHT
#endif /* TARGET_COPYRIGHT */



#ifdef __cplusplus
}
#endif

