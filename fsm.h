/*
 * Copyright 2018 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#ifndef FSM_H
#define FSM_H

typedef short Signal;
typedef struct Event Event;
typedef struct Fsm Fsm;
typedef void (*State)(Fsm *, Event const *);
 
/* Event base class */
struct Event
{
    Signal sig;
};
 
/* Finite State Machine base class */
struct Fsm
{
    State state__; /* the current state */
};
 
/* "inlined" methods of Fsm class */
#define FsmCtor_(me_, init_) ((me_)->state__ = (State)(init_))
#define FsmInit(me_, e_)     (*(me_)->state__)((me_), (e_))
#define FsmDispatch(me_, e_) (*(me_)->state__)((me_), (e_))
#define FsmTran_(me_, targ_) ((me_)->state__ = (State)(targ_))

#endif // FSM_H

