# IN4200: Home Exam 1, Spring 2020

**Counting Mutual Web Linkage Occurences**

**Candidate 15224**

**Disclaimer**
This project was embarked on in collaboration with candidate 15244.
Our individual programs may therefore bear a strong resemblance in
both presentation and content.

### Contents
- Data

  - test_graph.txt
    - A small web graph of 8 nodes

  - test_graph100.txt
    - A web graph of 100 nodes

  - web-NotreDame.txt
    - The NotreDame dataset (web graph of 325729 nodes)


- results

  - count1_test.png
    - image file of results from benchmarking [count_mutual_links1.c]

  - count2_test.png
    - image file of results from benchmarking [count_mutual_links2.c]

  - read1_test.png
    - image file of results from benchmarking [read_graph_from_file1.c]

  - read2_test.png
    - image file of results from benchmarking [read_graph_from_file2.c]

  - top_n_test.png
    - image file of results from benchmarking [top_n_webpages.c]


- src

  - [count_mutual_links1.c]
    - file containing a function for finding mutual link occurences and number of involvements from a web graph read by [read_graph_from_file1.c] using matix format

  - [count_mutual_links1.h]
    - the header file for [count_mutual_links1.c]

  - [count_mutual_links2.c]
    - file containing a function for finding mutual link occurences and number of involvements from a web graph read by [read_graph_from_file2.c] using CRS format

  - [count_mutual_links2.h]
    - the header file for [count_mutual_links2.c]

  - [helper_func.h]
    - A header file containing functions used in main for printing a table or vector

  - [read_graph_from_file1.c]
    - file containing a function for reading a web graph using matrix format

  - [read_graph_from_file1.h]
    - the header file for [read_graph_from_file1.c]

  - [read_graph_from_file2.c]
    - file containing a function for reading a web graph using CRS format

  - [read_graph_from_file2.h]
    - the header file for [read_graph_from_file2.c]

  - [top_n_webpages.c]
    - file containing different functions for finding the top n webpages based on number of involvements found by either [count_mutual_links1.c] or [count_mutual_links2.c]

  - [top_n_webpages.h]
    - the header file for [top_n_webpages.c]


- Files in main folder

  - [benchmark.c]
    - file for benchmarking (timing) the functions created during this exam, found in the src folder

  - [hpc_analytics.py]
    - file for running several benchmarks across different number of threads (compiles and runs [benchmark.c])

  - [main.c]
    - file for running and printing the main results of the functions found in src folder that was created during this exam

  - [test.c]
    - file for running tests on the functions found in src folder to insure the correctness of the functions implemented during this exam.


## Usage

- [benchmark.c]
  - when in IN4200_HE1_15224 type into terminal: "make benchmark.x" "./benchmark.x filename graph_file N_bench" or "make benchmarkOMP.x" "./benchmarkOMP filename graph_file N_bench" to run parallel code, where filename is the name of the function you want to benchmark e.g. "count_mutual_links1.c", graph_file is the filename of the web graph on which you want to benchmark, and N_bench is the number of repetitions run during benchmarking

- [src/count_mutual_links1.c]
  - the pragmas in this function may not run properly at UiO servers. I have added pragmas that can run at UiO in the comments above the current pragmas.

- [src/count_mutual_links2.c]
  - the pragmas in this function may not run properly at UiO servers. I have added pragmas that can run at UiO in the comments above the current pragmas.


- [hpc_analytics.py]
  - when in IN4200_HE1_15224 type into terminal: "python3 hpc_analytics.py"
  - go into the program to change number of benchmarks, number of threads, or list of graph files

- [main.c]
  - when in IN4200_HE1_15224 type into terminal: "make main.x" "./main.x" or "make mainOMP.x" "./mainOMP.x" to run parallel code

- [test.c]
  - when in IN4200_HE1_15224 type into terminal: "make test.x" "./test.x filename" or "make testOMP.x" "./testOMP.x filename" to run parallel code, where filename is the name of the function you want to test e.g. "count_mutual_links1.c"
