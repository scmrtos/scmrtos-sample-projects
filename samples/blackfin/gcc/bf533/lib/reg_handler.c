//------------------------------------------------------------------------------
//*    Copyright (C) 2000 Analog Devices Inc., All Rights Reserved.
//*    This contains Analog Devices Background IP and Development IP as
//*    defined in the ADI/Intel Collaboration Agreement.
//*    
//*    Registration of new Exception handling routines.
//*
//------------------------------------------------------------------------------
//*    bfin-elf port by Harry E. Zhurov, Copyright (c) 2016

#include <sys/excause.h>
#include <ccblkfn.h>
#include <exc.h>

static __inline void
disable_int(int which)
{
  unsigned int bits = ~(1<<which);
  unsigned int mask = cli();
  mask &= bits;
  sti(mask);
}

static __inline void
enable_int(int which)
{
  unsigned int bit = 1<<which;
  unsigned int mask = cli();
  mask |= bit;
  sti(mask);
}

/*
** Register an interrupt handler within the EVT.
** Return previous value if there was one.
*/

ex_handler_fn register_handler(interrupt_kind kind, ex_handler_fn fn)
{
  return register_handler_ex(kind, fn, EX_INT_ENABLE);
}


/*
** Extended function to register an interrupt handler within the EVT.
** Returns the old handler.
**
** If enabled == EX_INT_ALWAYS_ENABLE, install fn (if fn != EX_INT_IGNORE
** and fn != EX_INT_DISABLE), and then enable the interrupt in IMASK then
** return.
**
** If fn == EX_INT_iGNORE, disable the interrupt
** If fn == EX_INT_DEFAULT, delete the handler entry in the EVT and disable
**   the interrupt in IMASK
** Otherwise, install the new interrupt handler.  Then,
**  If enabled == EX_INT_DISABLE, disable the interrupt in IMASK
**  If enabled == EX_INT_ENABLE, enable the interrupt in IMASK
**  otherwise leave the interrupt status alone.
*/
ex_handler_fn register_handler_ex(interrupt_kind kind, ex_handler_fn fn,
                                  int enable){
  volatile ex_handler_fn *evt = 
    (volatile ex_handler_fn *)EX_EVENT_VECTOR_TABLE;
  ex_handler_fn old;
  if (ik_emulation <= kind && kind <= ik_ivg15) {
    old = evt[kind];

    /* Always want to come out of this fn with the interrupt enabled */
    if (enable == EX_INT_ALWAYS_ENABLE) {
      if (fn != EX_INT_IGNORE && fn != EX_INT_DISABLE) {
        evt[kind] = fn;
      }
      enable_int(kind);
      return old;
    }

    if (fn == EX_INT_IGNORE) {
      disable_int(kind);
    } else if (fn == EX_INT_DEFAULT) {
      disable_int(kind);
      evt[kind] = 0;
    } else {
      if (enable == EX_INT_DISABLE) {
        disable_int(kind);
      } 
      evt[kind] = fn;
      if (enable == EX_INT_ENABLE) {
        enable_int(kind);
      }
    }
    return old;
  }
  return EX_INT_IGNORE;
}
 
