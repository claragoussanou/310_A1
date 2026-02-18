NOTES (lecture notes)
- Each process has a PCB that contains: pID, process state, save area (space)
- PCB array is indexed by hash(pID)
- when switching from P1 to P2, save P1 registers to PCBArray[P1].SaveArea

✩ scheduler picks which picks which process to run
- preemptive: processes may be kicked off CPU
- non-preemptive: processes only voluntarily leave the CPU

- The scheduler runs when: 1. process starts/terminates (system call) 2. process performs an I/O (system call) 3. I/O completes (I/O interrupt) 4. timer expires (timer interrupt)
- good scheduler for interactive: short response time
- good scheduler for batch: high throughput (# jobs completed)
- scheduling policies: FCFS / SJF / RR

- one process with multiple threads
- concurrency gives non-deterministic results :(
- Multithreading: divide process between multiple threads and share data (global variables and heap, NOT local/read-only variables)
- critical section = mutual exclusion, i.e. one thread at a time, no simultaneous access to shared ressource
- pthread_create() || pthread_exit() || pthread_join()
- Pthread_mutex_lock(mutex) || Pthread_mutex_unlock(mutex)
- create a deadlock by entouring a section with two thread locks


NOTES (assignment instructions)
- 
