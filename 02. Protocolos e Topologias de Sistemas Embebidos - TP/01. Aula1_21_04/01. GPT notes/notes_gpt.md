## Reconstructed lecture notes

This class was really **two parts**:

1. **Course/admin introduction** from `TP0.pdf`: course scope, prerequisites, assessment, planning, support rules.  
2. **Technical lecture** from `SIOPTR T1.pdf` + the SRTs: fundamentals of real-time systems, task models, preemption, activation models, and an introduction to scheduling approaches. 

### Part A — course introduction

The course is about **real-time operating systems and real-time systems**, with focus on scheduling, shared resources, OS support for real-time requirements, and kernel-related topics. It assumes prior familiarity with computer architecture, OS usage/management, data structures, advanced C, and basic Linux. Assessment has **two lab moments**, weighted **40% and 60%**.  

### Part B — actual technical lesson

#### 1) What makes a system “real-time”

The professor’s central idea was:

> A system is not correct only because it computes the right value.
> It must also produce that value **at the right time**.

The slides define real-time systems as systems where timing requirements are as important as functional requirements. Missed deadlines can cause failure, especially in safety-critical systems. Examples used include aircraft control, medical devices, automotive software, industrial control, telecom, and consumer electronics. 

### Beginner explanation

Think of a normal program like a student submitting homework: correctness matters.
A real-time system is like an **airbag**: correctness matters, but **being late can be equivalent to being wrong**.

---

#### 2) Deadline as the key concept

The lecture emphasized the **deadline (D)** as one of the most important concepts: the instant by which the result must be delivered. The meaning of missing a deadline depends on how critical the activity is. 

### Beginner explanation

A deadline is not “when it would be nice to finish.”
It is the last instant where the result still has value.

---

#### 3) Soft vs hard real-time

The lecture classified systems as:

* **Soft real-time**: timing matters, but occasional misses may be tolerated.
* **Hard real-time**: at least one deadline miss is unacceptable or potentially dangerous.

The slide also links hard real-time to safety-critical systems and stresses **worst-case assumptions**, not average-case behavior. 

### Beginner explanation

Soft real-time: late video frame = annoying.
Hard real-time: late brake command = dangerous.

---

#### 4) Why “average” is not enough

This was a repeated verbal emphasis in the SRT: the lecturer kept returning to **worst-case reasoning**.

The slide deck explicitly says that for critical systems the system must work in the **worst-case scenario**, and that timing analysis and schedulability analysis are needed to guarantee deadlines before deployment. 

### Beginner explanation

If a task usually takes 2 ms but sometimes takes 12 ms, and the deadline is 5 ms, the average tells you almost nothing useful.

---

#### 5) Example: airplane control system

The lecture used an airplane control example to illustrate a real-time control loop:

* **Sense** the environment and system state
* **Compute** control algorithms
* **Actuate** outputs

The slides also mention **jitter** in sampling and the need to account for execution time of computing activities. 

### Beginner explanation

This is the classic control loop:

**sensor -> decision -> action**

If any stage is too late, the whole control action may be useless.

---

#### 6) Example: mine pump control system

A more concrete case study followed: a **mine pump control system**.

The slides distinguish:

* **Functional requirements**
  such as turning pump on/off, evacuating the mine when methane/CO/airflow conditions become dangerous.
* **Timing requirements**
  such as reading methane every 8 ms with deadline 3 ms, CO every 10 ms with deadline 6 ms, airflow every 10 ms with deadline 10 ms, etc. 

### Why this matters

This example shows the engineering split:

* Functional question: *What should the system do?*
* Real-time question: *How fast must each thing happen?*

---

#### 7) Real-time computing model

The lecture then shifted from examples to abstraction.

A real-time application was presented as a **recurrent reactive model**: recurring activities called **tasks** process inputs and produce outputs. The simplest pattern is **sense-compute-actuate**. Tasks may be:

* **Periodic**: repeat at fixed intervals
* **Sporadic**: event-driven, but with a minimum inter-arrival time / maximum arrival frequency
* **Aperiodic**: event-driven, no guaranteed arrival spacing 

### Beginner explanation

A task is just a recurring unit of work.

Examples:

* periodic: sample temperature every 10 ms
* sporadic: alarm handler that cannot happen faster than some bound
* aperiodic: arbitrary user request

---

#### 8) Simple task model and notation

The lecture introduced the simple periodic task model with the following parameters:

* **Ci**: WCET, worst-case execution time
* **Ti**: period
* **Di**: relative deadline
* **Oi**: offset
* **Ri**: worst-case response time
* activation, start, finish, response time, absolute deadline per job 

The SRT additionally stressed that a **job** is one execution instance of a task.

### Beginner explanation

A task is the template.
A **job** is one actual run of that task.

---

#### 9) Assumptions in the simple model

The lecture explicitly said this is a **very restrictive model**:

* fixed task set
* all tasks periodic
* initially independent
* overheads ignored
* deadlines equal to periods in the base model
* fixed WCET 

Then the professor clarified an important engineering nuance in the SRT:

* overheads are often folded into WCET
* caches/pipelines may be ignored or constrained in critical systems
* in critical systems, WCET may require static analysis
* in soft real-time, average values may sometimes be used

This matches the slide content. 

---

#### 10) Preemption

A major part of the lecture was **preemption**.

When tasks share a CPU, the system may be:

* **Preemptive**: a running task can be interrupted by a more urgent one
* **Non-preemptive**: a task runs until completion of its job
* **Limited-preemptive**: preemption allowed only at specific points 

The lecture emphasis was:

* preemption helps urgent tasks run quickly
* non-preemptive execution reduces context-switch overhead and can be more predictable
* shared resources complicate preemption because a task holding a lock may not be safely preemptable 

### Beginner explanation

Preemption is like interrupting a less urgent conversation because the fire alarm went off.

---

#### 11) Why shared resources matter

The SRT repeatedly connected preemption to **locks**, **resource sharing**, and **deadlock/blocking-like situations**.

The practical lesson was not a full resource-sharing protocol yet. It was an intuition:

* two tasks cannot safely write the same shared data at the same time
* if one task holds a lock needed by another, timing can be affected badly
* priority alone is not enough if resource access is not controlled

---

#### 12) Task activation models

The lecture then formalized two activation styles:

* **Time-triggered** -> periodic tasks
  easier to analyze, good for control, but may waste CPU
* **Event-triggered** -> sporadic/aperiodic tasks
  more flexible, less predictable, need control over event rate/bandwidth 

The SRT adds a useful verbal point: the required period often comes from the **physics of the system**.

### Beginner explanation

You do not choose a control task period randomly.
The dynamics of the real plant often dictate it.

---

#### 13) Scheduling: what it is trying to do

Scheduling was introduced as the problem of managing concurrent tasks competing for resources.

The slides define two essential scheduling ingredients:

* an algorithm to decide resource order
* a way to predict worst-case behavior

A task set is **schedulable** if there exists at least one schedule that guarantees the temporal requirements. The lecture also stressed **determinism** and **predictability**. 

### Beginner explanation

Scheduling is not just “who runs next?”
It is also: “can I prove everyone important finishes in time?”

---

#### 14) Categories of scheduling approaches

The lecture introduced three broad families:

* **Static / offline**
* **Hybrid**: characteristics known offline, schedule decided online
* **Fully online / best effort** 

The lecturer said the course would mainly focus on the middle ground later, but briefly introduced examples now.

---

#### 15) Cyclic executive

The first scheduling strategy discussed was the **cyclic executive**.

The slides describe it as:

* tasks decomposed into functions
* functions mapped into **minor cycles**
* the whole repeating schedule forms the **major cycle**
* fully deterministic, low overhead
* but hard to build/maintain, poor robustness to changes, and best when periods are harmonic  

The SRT further emphasized:

* a small execution-time change may force rearrangement of the whole schedule
* CPU utilization in the example was only 75%
* long task periods can inflate the major cycle badly

### Beginner explanation

A cyclic executive is like a rigid timetable printed in advance.
Very predictable. Very fragile when requirements change.

---

#### 16) More flexible scheduling mentioned, but not yet taught deeply

The lecture only introduced by name:

* **Fixed-Priority Scheduling**
* **Earliest Deadline First (EDF)** 

These were announced, not fully developed in this class.

---

#### 17) Round robin

The final concrete strategy introduced was **round robin**:

* FIFO queue
* each task gets a fixed **quantum**
* when quantum expires, it goes to the back of the queue
* fair CPU sharing, no priorities
* but urgent tasks may be delayed 

The lecturer also connected this idea to **communications/media sharing**, where multiple nodes share a common resource and collisions or unfair access must be controlled.

### Beginner explanation

Round robin is fair, but fairness is not the same as real-time correctness.

---

#### 18) Closing quiz / reflection

The lecture ended with three conceptual questions:

* Is real-time always fast?
* Can late results be wrong?
* Is average enough? 

The professor’s verbal answer in the SRT was essentially:

* **Real-time is not “always fast”**; it is **timely relative to the application**
* **Late results can be wrong**
* **Average is not enough**

---

## Difficult parts explained simply

### WCET

Worst-case execution time is the **slowest acceptable upper bound** for how long a task may take.

Analogy: not your average commute time, but the time budget you need if traffic is bad and being late is unacceptable.

### Response time

Response time is not just the task’s own execution time.
It also includes **waiting** caused by other tasks, blocking, or preemption.

### Period vs deadline

* **Period**: how often work is released
* **Deadline**: by when the result must be ready

They are often equal in simple models, but not always.

### Sporadic vs aperiodic

* **Sporadic**: irregular, but bounded
* **Aperiodic**: irregular and not bounded enough for straightforward worst-case analysis

### Determinism vs predictability

* **Determinism**: same input -> same behavior
* **Predictability**: behavior also stays within known timing bounds

---

## Mistakes / inconsistencies / unclear points corrected

### 1) Notes: “soft e hard time”

Correction: the lecture used **Soft Real-Time** and **Hard Real-Time**, and the slide explicitly says soft can also be described as **soft (or firm)** in that context. 

### 2) Notes: periodic / sporadic / aperiodic wording is confused

Correction:

* periodic = fixed interval
* sporadic = event-driven with bounded arrival rate
* aperiodic = no such bound
  That distinction is explicit in the slide deck. 

### 3) Notes: “major cycle e o menor possível”

Needs clarification. In the cyclic executive example, the **major cycle** is the complete repeating schedule, commonly tied to the least common multiple of task periods in simple constructions; the **minor cycle/frame** is the smaller repeated slot structure. The notes mix these two ideas.

### 4) Notes: “75% nao é muito bom, ideal é sempre ao máximo”

This reflects the lecturer’s commentary on the example, but it should **not** be turned into a universal rule. In real systems, leaving slack can be useful for overheads, uncertainty, fault handling, and mode changes. So:

* **As lecture reconstruction**: yes, he criticized the example’s utilization.
* **As engineering rule**: no, “always maximize utilization” is too strong.

### 5) Notes: “deadlock prevention is easy”

This came from the slide’s comparison in favor of non-preemptive execution, not as a blanket statement that deadlocks disappear in all designs. The safer interpretation is: **non-preemptive designs simplify some synchronization problems**. 

### 6) Notes: “average enough?”

The lecture’s intended answer is **no**, especially for hard real-time, because guarantees require worst-case reasoning. 

### 7) SRT uncertainty

Some transcript portions are clearly ASR-corrupted, especially:

* “aperiodic/sporadic” pronunciations
* “preemption/non-preemptive”
* “schedulability”
* “WCET / response time”

In those cases, the slide deck was necessary to disambiguate.

---

## Exam questions

### Theoretical

1. Define a real-time system and explain why correctness has both value and time dimensions.
2. Distinguish hard real-time from soft real-time.
3. What is a deadline? Why can a late result be considered wrong?
4. Explain the sense-compute-actuate model.
5. Define WCET, period, deadline, offset, and response time.
6. Explain preemptive, non-preemptive, and limited-preemptive execution.
7. Compare time-triggered and event-triggered task activation.
8. What does it mean for a task set to be schedulable?
9. What is determinism? What is predictability?
10. Explain the main advantages and disadvantages of a cyclic executive.

### Short answer

1. What is a job?
2. What is the difference between periodic and sporadic tasks?
3. Why is worst-case analysis central in hard real-time systems?
4. Why can resource sharing complicate preemption?
5. What is a quantum in round robin?
6. Why can round robin be unfair to urgent tasks even though it is “fair” in CPU time?
7. Why can caches/pipelines complicate timing analysis?
8. Why may time-triggered systems underutilize CPU?

### Conceptual understanding

1. A task usually finishes in 2 ms, but sometimes in 9 ms. Deadline is 5 ms. Is the average useful enough?
2. A logger and a flight-control task share a CPU. Which should be allowed to preempt which, and why?
3. Why can a correct result become useless after the deadline?
4. Why might an engineer choose a non-preemptive design even if preemption seems more responsive?
5. Why does the physics of the controlled plant affect task periods?

---

## Mind map

```text
Lecture 1
├─ Course intro
│  ├─ scope
│  ├─ prerequisites
│  ├─ assessment
│  └─ planning
├─ Real-time fundamentals
│  ├─ correctness = value + time
│  ├─ deadlines
│  ├─ soft vs hard RT
│  └─ worst-case reasoning
├─ Examples
│  ├─ airplane control
│  └─ mine pump control
├─ Real-time computing model
│  ├─ tasks
│  ├─ jobs
│  ├─ sense-compute-actuate
│  ├─ periodic
│  ├─ sporadic
│  └─ aperiodic
├─ Task parameters
│  ├─ C
│  ├─ T
│  ├─ D
│  ├─ O
│  └─ R
├─ Execution semantics
│  ├─ preemptive
│  ├─ non-preemptive
│  ├─ limited preemptive
│  └─ shared resources / locks
├─ Activation models
│  ├─ time-triggered
│  └─ event-triggered
└─ Scheduling intro
   ├─ schedulability
   ├─ determinism
   ├─ predictability
   ├─ static / hybrid / online
   ├─ cyclic executive
   ├─ fixed priority (introduced)
   ├─ EDF (introduced)
   └─ round robin
```

---

## 5 questions to test your understanding

1. Why is a result that is functionally correct still considered wrong in a hard real-time system if it arrives too late?
2. What is the practical difference between a periodic task and a sporadic task?
3. Why does preemption improve responsiveness, but also complicate reasoning about shared resources?
4. In a cyclic executive, why can one task with a long period make the full schedule awkward?
5. Why is “average execution time” not a safe basis for hard real-time guarantees?

---

## Oral exam simulation

### Level 1

1. What is a real-time system?
2. What is a deadline?
3. Give one example of a hard real-time system and justify it.

### Level 2

4. Explain the difference between soft and hard real-time using consequences of deadline misses.
5. Explain periodic, sporadic, and aperiodic tasks.
6. What is WCET and why is it more relevant than average execution time?

### Level 3

7. Define schedulability in engineering terms, not just textbook terms.
8. Explain how preemption changes response time.
9. Why does a shared lock change the simple picture of priority-based execution?

### Level 4

10. Why is determinism not the same thing as predictability?
11. Under what conditions is a cyclic executive attractive?
12. Why can round robin be acceptable in some shared systems but weak for urgent real-time tasks?

### Level 5

13. Suppose a low-priority task is writing to a shared structure and a high-priority task becomes ready. Why is “just preempt it” sometimes unsafe?
14. Why does the physics of the controlled system influence task periods and deadlines?
15. In what sense is “real-time” relative rather than absolute?

---

## One-page cheat sheet

### Core rule

**Real-time correctness = correct value + correct time**

### Must-know terms

* **Task**: recurring unit of work
* **Job**: one execution instance of a task
* **WCET (C)**: worst-case execution time
* **Period (T)**: release interval
* **Deadline (D)**: latest acceptable completion time
* **Offset (O)**: phase shift / initial release offset
* **Response time (R)**: release-to-finish delay including waiting

### Task types

* **Periodic** -> fixed interval
* **Sporadic** -> event-driven, bounded arrival rate
* **Aperiodic** -> event-driven, no strong arrival bound

### Activation models

* **Time-triggered**: easier analysis, may waste CPU
* **Event-triggered**: flexible, harder analysis

### Execution modes

* **Preemptive**: urgent task can interrupt current one
* **Non-preemptive**: current task runs to completion
* **Limited preemptive**: preemption only at safe points

### Scheduling goals

* meet all deadlines
* predict worst-case behavior
* guarantee deterministic/predictable timing

### Scheduling families

* **Static / offline**
* **Hybrid**
* **Fully online / best effort**

### Strategies introduced

* **Cyclic Executive**

  * * deterministic, low overhead
  * * fragile, hard to maintain, likes harmonic periods
* **Fixed Priority**

  * introduced only
* **EDF**

  * introduced only
* **Round Robin**

  * fair CPU sharing
  * weak for urgent tasks

### Engineering mantras from the lecture

* Worst case matters more than average
* Late can mean wrong
* Real-time does not mean “fast”; it means “on time”
* Timing requirements often come from the physics of the plant
* Shared resources break naive scheduling intuition

---

## Final summary

### Key concepts

The lecture built the foundation that **real-time systems are about timed correctness**, not just functional correctness. It introduced deadlines, task models, WCET-based reasoning, preemption, activation models, and the purpose of scheduling. It then gave intuition for cyclic executive and round robin as two contrasting scheduling approaches. 

### Key terminology

Real-time system, deadline, hard real-time, soft real-time, task, job, periodic, sporadic, aperiodic, WCET, response time, preemption, schedulability, determinism, predictability, cyclic executive, major cycle, minor cycle, round robin, quantum.  

### Typical exam traps

* Saying “real-time means very fast”
* Confusing **period** with **deadline**
* Confusing **sporadic** with **aperiodic**
* Using **average execution time** instead of WCET
* Thinking “fair” scheduling automatically means “good” real-time scheduling
* Assuming preemption always solves urgency without creating resource-sharing problems

### Real-world applications

The lecture explicitly connected the theory to aircraft control, medical equipment, automotive software, industrial control, telecommunications, and embedded cyber-physical systems. It also used mine pumping and communication-resource sharing as concrete intuitions. 

## Ação (1 passo)

Escolhe **uma** destas opções para eu continuar com precisão:
**A)** transformar isto em apontamentos de estudo ultra-limpos em português
**B)** fazer agora um **quiz oral interativo** baseado só nesta aula

## Objetivo

Fechar a próxima iteração sem misturar reconstrução da aula com treino de exame.

## Como pensar

A melhor decisão depende do teu objetivo imediato:

* se queres **consolidar conteúdo**, faz primeiro os apontamentos finais
* se queres **testar retenção**, vai já para o oral

## Pitfalls & troubleshooting

* Ir direto para exercícios sem fixar vocabulário pode confundir period/deadline/WCET
* Misturar o que foi só “introduzido” com o que foi realmente “ensinado”
* Tratar observações informais do professor como regras universais
* Confiar demasiado nas notas quando o SRT e os slides dizem algo mais preciso

