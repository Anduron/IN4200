import numpy as np
import matplotlib.pyplot as plt
import os

def fig_path(fig_id):
    """
    Where to save the figure of the benchmarks
    """
    FIGURE_PATH = "./results"
    return os.path.join(FIGURE_PATH + "/", fig_id)

def run_benchmark(filename, graph_files, N_bench, max_num_threads, fsave):
    """
    1. filename: Name of file containing function to benchmark
    2. graph_files: List of names of graph files
    3. N_bench: Number of repetitions in the benchmark
    4. max_num_threads: The maximum number of threads on which you want to benchmark
    5. fsave: name of file to save
    Compiles and runs benchmark.c then creates figures of the results and saves them
    in result folder.
    """

    os.system('make benchmark.x')
    os.system('make benchmarkOMP.x')
    fig = plt.figure(figsize=(8,6))


    for graph_file in graph_files:
        times = np.zeros(max_num_threads)
        num_threads = np.linspace(1, max_num_threads, max_num_threads, dtype = np.int)

        for i in range(max_num_threads):
            print(f"\nRunning with {i+1} threads")
            file = filename + " "
            if i == 0:
                os.system('./benchmark.x ' + file + " " + graph_file + " " + str(N_bench))
                times[i] = np.loadtxt('time.txt')
            else:
                os.system('export OMP_NUM_THREADS=' + str(i+1))
                os.system('./benchmarkOMP.x ' + file + " " + graph_file + " " + str(N_bench))
                times[i] = np.loadtxt('time.txt')
        plt.plot(num_threads, times, 'o:', label = graph_file[5:])
    plt.title("benchmark of " + filename)
    plt.xlabel("Number of threads")
    plt.ylabel("Time [ms]")
    plt.legend(loc='best')
    plt.show()
    fig.savefig(fig_path(fsave), dpi = 300)

    os.system("rm -f time.txt")
    os.system("make clean")

    return 0

def main():
    """
    be aware that in the third call we rund n2 - 300 times
    (500 is alot on read_graph_from_file2 web-NotreDame)
    tune these number as seen fit. Take care to not use more threads than you have.
    """
    n1 = 1000
    n2 = 500 # WARNING: this might take a long time
    n_thread = 8
    graph_files_rg1 = ["data/test_graph.txt", "data/test_graph100.txt"]
    graph_files_cm1 = ["data/test_graph.txt", "data/test_graph100.txt"]
    graph_files_rg2 = ["data/test_graph.txt", "data/test_graph100.txt", "data/web-NotreDame.txt"]
    graph_files_cm2 = ["data/test_graph.txt", "data/test_graph100.txt", "data/web-NotreDame.txt"]
    graph_files_tnw = ["data/test_graph.txt", "data/test_graph100.txt", "data/web-NotreDame.txt"]

    run_benchmark("read_graph_from_file1.c", graph_files_rg1, n1, n_thread, "read1_test.png")
    run_benchmark("count_mutual_links1.c", graph_files_cm1, n1, n_thread, "count1_test.png")
    run_benchmark("read_graph_from_file2.c", graph_files_rg2, n2-300, n_thread, "read2_test.png")
    run_benchmark("count_mutual_links2.c", graph_files_cm2, n2, n_thread, "count2_test.png")
    run_benchmark("top_n_webpages.c", graph_files_tnw, n2, n_thread, "top_n_test.png")
    return 0

if __name__ == '__main__':
    main()
