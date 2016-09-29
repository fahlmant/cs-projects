#!/usr/bin/env python

from itertools import combinations
from functools import reduce

# NUM_LOCKERS = 0
# NUM_KEYS = 0
# NUM_TENNIS = 0
# KEY_ARRAY = TENNIS_ARRAY = []

def run_tests(function):
    with open('./dp.txt', 'r') as f:
        for i in range(0, 8):
            test_num = f.readline().split()
            nums = f.readline().split()
            keys = [int(x) for x in f.readline().split()]
            tennis = [int(x) for x in f.readline().split()]
            answer = function(int(nums[0]), int(nums[1]), int(nums[2]), keys, tennis)
            f.readline()
            correct = int(f.readline())
            if answer != correct:
                print "Test {}, Got {}, expected {}".format(test_num[-1], answer, correct)
            else:
                print "Test {} passed".format(test_num[-1])
            f.readline()

def assignment_tests(test_file, function):
    num_lockers = 0
    num_keys = 0
    num_tennis = 0
    key_array = []
    tennis_array = []
    answers = []
    with open(test_file, "r") as f:
        for i in range(8):
            f.readline()
            nums = f.readline().split()
            key_array = [int(x) for x in f.readline().split()]
            tennis_array = [int(x) for x in f.readline().split()]
            num_lockers = int(nums[0])
            num_keys = int(nums[1])
            num_tennis = int(nums[2])
            answer = function(num_lockers, num_keys, num_tennis, key_array, tennis_array)
            print "{}: Test {} = {}".format(function.__name__, i, answer)
            answers.append(answer)
            f.readline()

    print "{}: {}".format(function.__name__, answers)

# Algorithm 1
def alg1(num_lockers, num_keys, num_tennis, keys, tennis):
    current_keys = []
    lengths = []
    for i in range(1, num_keys + 1):
        current_keys = current_keys + (list(combinations(range(num_keys), i)))

    for comb in current_keys:
        total = 0
        current_lockers = [0 for x in range(num_lockers)]
        for x in range(0, len(comb)):
            current_lockers[keys[comb[x]] - 1] = 1
        for i in range(0, num_tennis):
            #For each tennis ball
            #Get the position of the tennis ball
            pos = tennis[i] - 1
            distances = []
            #For each locker
            for j in range (num_lockers):
                #If the locker is open
                if(current_lockers[j] == 1):
                    #Find the distance between the ball and the locker
                    distances.append(((abs(pos - j)), j))
            #Find the minimum distance between ball and locker
            minimum_distance = reduce(lambda a,b: min(a, b), distances)
            locker_pos = minimum_distance[1]
            if(locker_pos < pos):
                for x in range (locker_pos, pos + 1):
                    current_lockers[x] = 1
            else:
                for x in range (pos, locker_pos):
                    current_lockers[x] = 1
        lengths.append(sum(int (i) for i in current_lockers))

    return min(lengths)

def least_calc(keyi, keyj, TENNIS):
    current_tennis = []
    for x in range(0, len(TENNIS)):
        if(TENNIS[x] >= keyj and TENNIS[x] < keyi):
            current_tennis.append(TENNIS[x])

    distances = []
    if not current_tennis:
        return 0
    if current_tennis and (keyi - keyj) == 1:
        return len(current_tennis)
    for i in range(len(current_tennis), 0, -1):
        left_key = 0
        right_key = 0
        for x in range(0, i):
            if(i != 0):
                if(x == 0):
                    right_key = right_key + (abs(current_tennis[i -1] - keyi))
                else:
                    right_key = right_key + (abs(current_tennis[i - (x+1)] - current_tennis[i - x]))
        for y in range(i, len(current_tennis)):
            if(y == 0):
                left_key = left_key + (abs(current_tennis[y] - keyj))
            else:
                left_key = left_key + (abs(current_tennis[y] - current_tennis[y-1]))
        distances.append(left_key + right_key)
    return min(distances)




def alg2(num_lockers, num_keys, num_tennis, keys, tennis):
    # Init DP table. Set values greater than highest locker.
    DP = [num_lockers + 1 for x in range(num_keys)]
    KEYS = keys
    TENNIS = tennis

    KEYS.sort()
    TENNIS.sort()
    # print KEYS
    # print TENNIS


    # Setup first key
    if TENNIS[0] < KEYS[0] or num_tennis == 1:
        DP[0] = abs(KEYS[0] - TENNIS[0]) + 1
    else:
        DP[0] = 0


    for i in range(1, num_keys):
        for j in range(0, i):
            # calculate least unopened
            least = least_calc(KEYS[i], KEYS[j], TENNIS)
            if DP[j] + least < DP[i]:
                DP[i] = DP[j] + least
    # print DP

    if num_tennis > 1 and TENNIS[num_tennis - 1] > KEYS[num_keys - 1]:
        DP[num_keys - 1] = DP[num_keys - 1] + (TENNIS[num_tennis - 1] - KEYS[num_keys - 1]) + 1

    # print DP

    return DP[num_keys - 1]

    # Find least function


    # return DP[num_keys]

if __name__ == "__main__":
    # run_tests(alg2)
    assignment_tests('dp_set1.txt', alg1)
    assignment_tests('dp_set2.txt', alg2)
