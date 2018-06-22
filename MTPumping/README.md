## Multipumping example

We obtain the example code for utilizing multipumping. 
The example code are stored in example.cc testbench.cc. To run the code, only
needs "vivado_hls -f build_prj.tcl".

The example performs 2 10x16 matrix multiplication. Its resource usage as
below.

```shell
================================================================
== Utilization Estimates
================================================================
* Summary: 
+---------------------+---------+-------+---------+--------+
|         Name        | BRAM_18K| DSP48E|    FF   |   LUT  |
+---------------------+---------+-------+---------+--------+
|DSP                  |        -|      -|        -|       -|
|Expression           |        -|      -|        0|     329|
|FIFO                 |        -|      -|        -|       -|
|Instance             |        -|      0|        0|       0|
|Memory               |        -|      -|        -|       -|
|Multiplexer          |        -|      -|        -|      57|
|Register             |        0|      -|      403|      32|
+---------------------+---------+-------+---------+--------+
|Total                |        0|      0|      403|     418|
+---------------------+---------+-------+---------+--------+
|Available SLR        |     2160|   2760|   663360|  331680|
+---------------------+---------+-------+---------+--------+
|Utilization SLR (%)  |        0|      0|    ~0   |   ~0   |
+---------------------+---------+-------+---------+--------+
|Available            |     4320|   5520|  1326720|  663360|
+---------------------+---------+-------+---------+--------+
|Utilization (%)      |        0|      0|    ~0   |   ~0   |
+---------------------+---------+-------+---------+--------+
```

## Addapt to ap_fixed type
example_ap.cc
testbench_ap.cc
build_prj_ap.tcl
