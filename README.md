# ca_project3

<b>Problem 1</b> (Cache Simulation)
Get the following benchmarks among MiBench benchmarks, and perform cache simulation with gem5 for those benchmarks.
 - basicmath_small
 - dijkstra_small (with input.dat)
 - sha (with input_large.asc)

(a) For config 1 ~ 4, do cache simulation with given benchmarks and submit files which is produced from simulation.

(b) Modify gem5 configuration to use random replacement policy. For config 5 ~ 8, do cache simulation with given benchmarks and submit files which is produced from simulation.

<br/>
<b>Extra 1)</b>
Read paper Aamer Jaleel, Kevin B. Theobald, Simon C. Steely, Jr., and Joel Emer. 2010. High performance cache replacement using re-reference interval prediction (RRIP). SIGARCH Comput. Archit. News 38, 3 (June 2010), 60-71. DOI=http://dx.doi.org/10.1145/1816038.1815971, then <b>implement SRRIP policy in gem5 as srrip.hh and srrip.cc. For config 9 ~ 12, do cache simulation with given benchmarks and submit files which is produced from simulation.</b>

<br/><br/><br/>
<b>Problem 2</b> (Finding Best Cache Configuration)
Based on simulation statistics, what is the best configuration among config 1~8 for each benchmarks? Write your detailed answer and explanation on report.xxx

<br/>
<b>Extra 2)</b>
Based on simulation statistics, what is the best configuration among config 1~12 for each benchmarks? Write your detailed answer and explanation on report.xxx


# 좋은 캐시의 조건
--> AMAT( Average Memory Access Time)이 작아야함.

AMAT = Hit Time + Miss rate*Miss Penalty
