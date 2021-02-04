/**
*  @file scmRTOS_CONFIG.h
*
*  scmRTOS project-level configuration.
*
*  Copyright © 2020 Anton B. Gusev
**/

#ifndef  scmRTOS_CONFIG_H
#define  scmRTOS_CONFIG_H

#ifndef __ASSEMBLER__

#include <stdint.h>

typedef uint16_t      timeout_t;
typedef uint_fast32_t tick_count_t;

#endif // __ASSEMBLER__

/// scmRTOS Process Count. Must be less than 31
#define  scmRTOS_PROCESS_COUNT                  4

/**
 * scmRTOS System Timer
 * Nested Interrupts enable macro. Value 1 means that interrupts are
 * globally enabled within System Timer ISR (this is default for Cortex-M3).
 */
#define scmRTOS_SYSTIMER_NEST_INTS_ENABLE   1

/// scmRTOS System Timer Tick Counter Enable
#define  scmRTOS_SYSTEM_TICKS_ENABLE        1

/// scmRTOS System Timer Hook
#define  scmRTOS_SYSTIMER_HOOK_ENABLE       0

/// scmRTOS Idle Process Hook
#define  scmRTOS_IDLE_HOOK_ENABLE           0

/**
 * scmRTOS Idle Process Stack size (in bytes)
 * (20 * sizeof(stack_item_t)) - it's a minimum allowed value.
 */
#define scmRTOS_IDLE_PROCESS_STACK_SIZE     (100 * sizeof(stack_item_t))

/**
 * scmRTOS Context Switch User Hook enable
 * Enable/disable user-defined hook called from system Context Switch Hook function.
 */
#define  scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE  0

/**
 * scmRTOS Debug enable
 * Enable/disable acquisition of some debug info:
 * stack usage information and information about the object that process is waiting for.
 */
#define scmRTOS_DEBUG_ENABLE                1

/**
 * scmRTOS Process Restart enable
 * Enable/disable process restarting facility.
 */
#define scmRTOS_PROCESS_RESTART_ENABLE      0

/**
 * PendSV_Handler optimization:
 *   0 - use near (+- 1Mb) call for os_context_switch_hook
 *   1 - use far call
 */
#define scmRTOS_CONTEXT_SWITCH_HOOK_IS_FAR     0

///    scmRTOS process with initial suspended state enable
#define scmRTOS_SUSPENDED_PROCESS_ENABLE  0

#endif // scmRTOS_CONFIG_H

