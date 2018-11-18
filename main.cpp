#include <stdio.h>
// #include <iostream>
#include "fsm.h"
#include <ctype.h>

 
typedef struct Keyboard Keyboard;
struct Keyboard
{
    Fsm super_; /* extend the Fsm class */
    /* ... other attributes of Keyboard */
};
 
void KeyboardCtor(Keyboard *me);
void Keyboard_initial(Keyboard *me, Event const *e);
void Keyboard_default(Keyboard *me, Event const *e);
void Keyboard_shifted(Keyboard *me, Event const *e);
 
typedef struct KeyboardEvt KeyboardEvt;
struct KeyboardEvt
{
    Event super_; /* extend the Event class */
    char code;
 };
 
/* signals used by the Keyboard FSM */
enum
{
    SHIFT_DEPRESSED_SIG,
    SHIFT_RELEASED_SIG,
    ANY_KEY_SIG,
 };
 
void KeyboardCtor(Keyboard *me)
{
    FsmCtor_(&me->super_, &Keyboard_initial);
}
  
void Keyboard_initial(Keyboard *me, Event const *e)
{
    /* ... initialization of Keyboard attributes */
    printf("Keyboard initialized");
    FsmTran_((Fsm *)me, &Keyboard_default);
 }
 
void Keyboard_default(Keyboard *me, Event const *e)
{
    switch (e->sig)
    {
       case SHIFT_DEPRESSED_SIG:
          printf("default::SHIFT_DEPRESSED");
          FsmTran_((Fsm *)me, &Keyboard_shifted);
          break;
       case ANY_KEY_SIG:
          printf("key %c", (char)tolower(((KeyboardEvt *)e)->code));
          break;
    }
}
 
void Keyboard_shifted(Keyboard *me, Event const *e)
{
    switch (e->sig)
    {
       case SHIFT_RELEASED_SIG:
          printf("shifted::SHIFT_RELEASED");
          FsmTran_((Fsm *)me, &Keyboard_default);
          break;
       case ANY_KEY_SIG:
          printf("key %c", (char)toupper(((KeyboardEvt *)e)->code));
          break;
    }
}

int main()
{
   Keyboard k;
   KeyboardCtor(&k);
   FsmInit((Fsm *)&k, 0);
   for (;;)
   {
      KeyboardEvt ke;
      printf("\nSignal<-");
      ke.code = getc(stdin); 
      getc(stdin);                      /* discard '\n' */
      switch (ke.code)
      {
         case '^': ke.super_.sig = SHIFT_DEPRESSED_SIG; break;
         case '6': ke.super_.sig = SHIFT_RELEASED_SIG; break;
         case '.': return 0;          /* terminate the test */
         default: ke.super_.sig = ANY_KEY_SIG; break;
      }
      FsmDispatch((Fsm *)&k, (Event *)&ke);  /* dispatch */
   }
   return 0;
}
