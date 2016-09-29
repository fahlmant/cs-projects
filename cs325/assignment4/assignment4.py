#!/usr/bin/env python

from pulp import *
import math

def solve(f):
    prob = LpProblem("best fit curve for temps in corvallis", LpMinimize)

    # LP variables
    m = LpVariable("m", 0)
    x0 = LpVariable("x0", 0)
    x1 = LpVariable("x1", 0)
    x2 = LpVariable("x2", 0)
    x3 = LpVariable("x3", 0)
    x4 = LpVariable("x4", 0)
    x5 = LpVariable("x5", 0)

    prob += m

    for line in f:
        values = parse(line)
    # Contraints
        prob += x0 + \
           (x1 * values[0]) + \
           (x2 * math.cos((2 * math.pi * values[0]) / 365.25)) + \
           (x3 * math.sin((2 * math.pi * values[0]) / 365.25)) + \
           (x4 * math.cos((2 * math.pi * values[0]) / (365.25 * 10.7))) + \
           (x5 * math.sin((2 * math.pi * values[0]) / (365.25 * 10.7))) - values[1] <= m

    # Contraints
        prob += -x0 - \
           (x1 * values[0]) - \
           (x2 * math.cos((2 * math.pi * values[0]) / 365.25)) - \
           (x3 * math.sin((2 * math.pi * values[0]) / 365.25)) - \
           (x4 * math.cos((2 * math.pi * values[0]) / (365.25 * 10.7))) - \
           (x5 * math.sin((2 * math.pi * values[0]) / (365.25 * 10.7))) + values[1] <= m

    status = prob.solve()
    print LpStatus[status]
    # print value(prob.objective)

    print value(x0)
    print value(x1)
    print value(x2)
    print value(x3)
    print value(x4)
    print value(x5)

def parse(line):
    new_list = line.strip("\n")
    new_list = line.split(";")
    new_list = new_list[7:]
    new_list.reverse()
    new_list = map(float, new_list)
    return new_list

if __name__ == "__main__":
    f = open("Corvallis_data.csv")
    solve(f)
