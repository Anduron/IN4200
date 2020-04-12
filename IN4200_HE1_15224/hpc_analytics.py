import numpy as np
import matplotlib.pyplot as plt
import os

def fig_path(fig_id):
    """
    docstring
    """
    FIGURE_PATH = "./results"
    return os.path.join(FIGURE_PATH + "/", fig_id)

def run_benchmark(filename, graph_files, N_bench, max_num_threads, fsave):
    """
    docstring
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
    n1 = 1000
    n2 = 500 # WARNING: this might take a long time
    graph_files_rg1 = ["data/test_graph.txt", "data/test_graph100.txt"]
    graph_files_cm1 = ["data/test_graph.txt", "data/test_graph100.txt"]
    graph_files_rg2 = ["data/test_graph.txt", "data/test_graph100.txt", "data/web-NotreDame.txt"]
    graph_files_cm2 = ["data/test_graph.txt", "data/test_graph100.txt", "data/web-NotreDame.txt"]
    graph_files_tnw = ["data/test_graph.txt", "data/test_graph100.txt", "data/web-NotreDame.txt"]

    run_benchmark("read_graph_from_file1.c", graph_files_rg1, n1, 8, "read1_test.png")
    run_benchmark("count_mutual_links1.c", graph_files_cm1, n1, 8, "count1_test.png")
    run_benchmark("read_graph_from_file2.c", graph_files_rg2, n2, 8, "read2_test.png")
    run_benchmark("count_mutual_links2.c", graph_files_cm2, n2, 8, "count2_test.png")
    run_benchmark("top_n_webpages.c", graph_files_tnw, n2, 8, "top_n_test.png")
    return 0

if __name__ == '__main__':
    main()
