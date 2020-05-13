import os
from subprocess import Popen, PIPE
import sys


def check(num_of_tries, in_file):
    res_lst = list()
    num_of_tries = int(num_of_tries)
    n = num_of_tries
    abs_er = 0
    rel_er = 0
    if num_of_tries <= 0:
        raise ValueError("The number of tries should be more than zero")
    time = []

    while num_of_tries != 0:
        if not os.path.exists("build/integral"):
            raise Exception("\"integral\" is not found in your build folder")
        if not os.path.exists(in_file):
            raise Exception("\"{}\" is not found".format(in_file))
        try:
            cpp_prog = Popen('./build/integral {}'.format(in_file), shell=True,
                             stdout=PIPE, stdin=PIPE)
        except:
            return "Error!"

        result_ar = cpp_prog.stdout.readline()
        if result_ar == b'':
            return "Error! There is no output from cpp program"
        res = float(str(result_ar).split()[1][:-3])
        result_time = cpp_prog.stdout.readline()
        if num_of_tries == n:
            abs_er = float(str(cpp_prog.stdout.readline()).split()[2][:-3])
            rel_er = float(str(cpp_prog.stdout.readline()).split()[2][:-3])

        if len(res_lst) != 0:
            if abs(res_lst[0] - res) > abs_er or abs(res_lst[0] - res)/res_lst[0] > rel_er:
                raise Exception("The results are not the same!!!")
        else:
            res_lst.append(res)

        time.append(int(str(result_time).split()[2][:-3]))
        num_of_tries -= 1

    minimal = min(time)

    print("Minimal time: ", minimal)

    return "All results are the same"


if __name__ == "__main__":
    print(check(sys.argv[1], sys.argv[2]))
    # check(1, "input.txt")
