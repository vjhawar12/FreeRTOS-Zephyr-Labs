# Lab 1: Task Creation and Scheduling Investigation

The purpose of Lab 1 was to investigate task creation and the differences between preemptive scheduling and cooperative scheduling, both with time slicing.

## Preemptive Scheduling

Preemptive scheduling allows a higher-priority task to interrupt a lower-priority task while it is still running. This behavior was demonstrated in `lab1_preemptive_time_slicing_uart_log.txt` and `lab1_preemptive_time_slicing.png`. The medium- and low-priority tasks were intentionally written as three-step sequences so that interruptions could be clearly observed in the UART log.

For example:

```text
[0 ms] HIGH 0
[1 ms] MED 0 Step 1
[1001 ms] HIGH 1
[1392 ms] MED 0 Step 2
```

At 0 ms, the following tasks are eligible to run:

```text
- HIGH 0
- MED 0 Step 1
- LOW 0 Step 1
```

We can observe that **HIGH 0** prints first because it has the highest priority, followed by **MED 0 Step 1**. The low-priority task does not appear in this portion of the log, showing that lower-priority work can be delayed significantly when higher-priority tasks remain ready to run. Around 1000 ms, only HIGH is scheduled to print again, so it prints. We then see that **MED 0 Step 2**, which was scheduled earlier but interrupted by HIGH, prints now.

## Cooperative Scheduling

Cooperative scheduling, in contrast, does **not** interrupt a running task simply because a higher-priority task is ready. Instead, a task runs until it voluntarily yields or blocks. This is seen in `lab1_cooperative_time_slicing_uart_log.txt` and `lab1_cooperative_time_slicing.png`.

Example:

```text
[0 ms] HIGH 0
[1 ms] MED 0 Step 1
[1390 ms] MED 0 Step 2
[2780 ms] MED 0 Step 3
[4169 ms] HIGH 1
```

We see that **MED 0 Steps 1–3** are not interrupted, despite being lower priority than HIGH. However, HIGH still prints before MED initially because it has higher priority. This demonstrates the key difference between cooperative and preemptive scheduling: under cooperative scheduling, task switching depends on the currently running task giving up the CPU rather than being forcibly interrupted.

## Observations

1. **Preemptive scheduling** improves responsiveness to higher-priority work.
2. **Cooperative scheduling** allows a task to complete uninterrupted once it begins running.
3. Under **preemptive scheduling**, low-priority tasks may experience long delays or starvation if higher-priority tasks run frequently.
4. Under **cooperative scheduling**, system responsiveness can suffer if a running task does not yield often enough.