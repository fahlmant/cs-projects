import sys
import math
import time

def test():
    tests = []
    with open('test_cases_with_solutions.txt', 'r') as f:
        for line in f:
            tests.append(eval(line))

    num = 0
    for t in tests:
        question = []
        for i in range(len(t[0])):
            question.append((t[0][i], i))

        answer = div_and_con(question)

        if answer[0] != t[1] or answer[1] != t[2] or answer[2] != t[3]:
            print "test {} FAILED: Got {}, {}, {} "\
                    "expected {}, {}, {}".format(num, answer[0], answer[1], answer[2],
                                                 t[1], t[2], t[3])
        else:
            print "test {} PASSED: GOT {}, {}, {}".format(num, answer[0], answer[1], answer[2])

        num = num + 1

def benchmark():
    tests = []
    with open('test_cases_without_solutions.txt', 'r') as f:
        for line in f:
            tests.append(eval(line))
    averages = []
    test_num = 0
    for x in tests:
        times = []
        print len(x)
        for i in range(10):
            question = []
            old_time = time.time()
            for i in range(len(x)):
                question.append((x[i], i))
            div_and_con(question)
            new_time = time.time()
            times.append(new_time - old_time)

        averages.append(sum(times) / 10)
        test_num = test_num + 1

    for i in averages:
        print i


def solve():
    test = []
    answers = open('answers.txt', 'w')
    with open('test_cases_without_solutions.txt', 'r') as f:
        for line in f:
            test.append(eval(line))

    for x in test:
        question = []
        for i in range(len(x)):
            question.append((x[i], i))

        response = div_and_con(question)
        answers.write("{} {} {}\n".format(response[0], response[1], response[2]))

    answers.close()


def summation(array, type):
    s = 0
    sum_array = []
    if type == "prefix":
        for i in range(len(array)):
            s = s + array[i][0]
            sum_array.append((s, array[i][1]))
    elif type == "suffix":
        for i in range(len(array) - 1, -1, -1):
            s = s + array[i][0]
            sum_array.insert(0, (s, array[i][1]))

    return sum_array

def method2(array1, array2):
    s_a1 = sorted(array1)
    s_a2 = sorted(array2)

    print s_a1
    print s_a2

    sum_a1 = summation(s_a1, 'prefix')
    sum_a2 = summation(s_a2, 'suffix')

    len1 = len(array1)
    len2 = len(array2)

    best = (0, 0)
    i = 0
    k = len2 - 1

    s = sys.maxint

    while (i < len1 and k >= 0):
        # print "i = {}, k = {}".format(i, k)
        if abs(sum_a1[i] + sum_a2[k]) <= s:
            best = (i, k)
            s = abs(sum_a1[i] + sum_a2[k])
            # print "sum = {}".format(s)

        # print sum_a1[i] + sum_a2[k]
        if sum_a1[i] + sum_a2[k] > 0:
            k = k - 1
        else:
            i = i + 1

    # print s_a1[i], s_a2[k]
    big_array = array1 + array2

    return (big_array[best[0], (best[0] + best[1])], s, best[0], (best[0] + best[1]))
    # return [s]


def method3(array1, array2):

    array1_index = []
    array2_index = []
    # Store indexes for arrays
    for i in range(len(array1)):
        array1_index.append((array1[i][0], 1, array1[i][1]))
    for i in range(len(array2)):
        array2_index.append((-array2[i][0], 2, array2[i][1]))

    biglist = array1_index + array2_index
    sorted_biglist = sorted(biglist, key=lambda x: x[0]) #by first value

    best = None

    for x in range(len(sorted_biglist) - 1):
        if(sorted_biglist[x][1] == sorted_biglist[x+1][1]):
            continue

        if best is None or abs(sorted_biglist[x][0] - sorted_biglist[x+1][0]) < abs(best[0][2] - best[1][2]):
            best = (sorted_biglist[x], sorted_biglist[x+1], abs(sorted_biglist[x][0] - sorted_biglist[x+1][0]))

    if best[1][1]:
        best = (best[1], best[0], best[2])

    return (best[2], best[0][2], best[1][2])

def div_and_con(array):
    """
    Basic data structure:

    input: (array of tuples (value, index))

    return: (sum, left_index, right_index)

    Note: we are using method3
    """
    if len(array) < 2:
        return (abs(array[0][0]), array[0][1], array[0][1])

    n = int((len(array) / 2))
    left_sum = summation(array[:n], 'prefix')
    right_sum = summation(array[n:], 'suffix')
    l = div_and_con(array[:n])
    r = div_and_con(array[n:])
    m = method3(left_sum, right_sum)

    best = min(l, r, m, key=lambda x: x[0])

    return best

if __name__ == "__main__":
    # benchmark()
    solve()
    # test()
