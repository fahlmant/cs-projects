#Name: Taylor Fahlman
#Email: fahlmant@onid.oregonstate.edu
#Class: CS344-001
#Assignment: 1
#Resources:http://stackoverflow.com/questions/13442574/how-do-i-determine-if-sys-stdin-is-redirected-from-a-file-vs-piped-from-another
#http://www.macroption.com/skewness-formula/
#http://www.macroption.com/kurtosis-formula/
#https://docs.python.org/2/library/fileinput.html
#http://stackoverflow.com/questions/3877209/how-to-convert-an-array-of-strings-to-an-array-of-floats-in-numpy
#http://docs.scipy.org/doc/numpy/reference/generated/numpy.array.html
#http://docs.scipy.org/doc/numpy/reference/generated/numpy.mean.html
#http://docs.scipy.org/doc/numpy/reference/generated/numpy.std.html
#http://docs.scipy.org/doc/scipy-0.14.0/reference/generated/scipy.stats.skew.html
#https://docs.scipy.org/doc/scipy-0.7.x/reference/generated/scipy.stats.kurtosis.html

import sys
import fileinput
import numpy
import scipy
import scipy.stats
import os, stat
import math

#initiats variables
sum = 0
counter = 0

#function to calculate standard deviation
def cal_std_dev(mean, num_list, counter):
    #initilized answer and variance array variables
    x = 0
    y = 0
    tot_var = 0
    variance = [None] * counter

    #for each entry, calulated variance by subtracting the mean from the number and squaring the answer
    for x in range(counter):
        variance[x] = ((int(num_list[x]) - mean) * (int(num_list[x]) - mean))

    #adds up each variance
    for y in range(counter):
        tot_var += variance[y]
       
    #converts sum to float, divides by count of numbers, takes the square root and returns answer
    tot_var += 0.00
    tot_var /= counter
    tot_var = tot_var ** (0.5)
    return tot_var

#function to calculate skew
def cal_skew(mean, num_list, counter):
    #initilized all variables
    skew = 0
    var_skew_sq = [None] * counter
    var_skew_cubed = [None] * counter
    tot_sq = 0
    tot_cubed = 0
    sqr_count = math.sqrt(counter) 
    #add the square of variance and cube of variance
    for x in range(counter):
        var_skew_sq[x] =  ((int(num_list[x]) - mean)) ** 2
        var_skew_cubed[x] = ((int(num_list[x]) - mean) * (int(num_list[x]) - mean) * (int(num_list[x]) - mean))

    #sums up the square and cube of variance
    for y in range(counter):
        tot_sq += var_skew_sq[y]
        tot_cubed += var_skew_cubed[y]

    #does finally calculation of skew 
    skew = (sqr_count * (tot_cubed/tot_sq ** (1.5)))


    return skew

#Function to calculate kurtuosis
def cal_kur(mean, num_list, counter):
    
    #initilized all variables
    kur = 0
    var_kur_sq = [None] * counter
    var_kur_quad = [None] * counter
    tot_quad = 0
    tot_sq = 0

    #finds each element of the second and fourth movemnt
    for x in range(counter):
        var_kur_sq[x] = (int(num_list[x]) - mean) ** 2
        var_kur_quad[x] = ((int(num_list[x]) - mean) **4)

    #adds up each element in the second and fourth movement
    for y in range(counter):
        tot_sq += var_kur_sq[y]
        tot_quad += var_kur_quad[y]

    #does final calculation and returns the answer
    kur = (counter * tot_quad)/(tot_sq ** 2)

    return kur
    
#checks if a file was redirected or not
mode = os.fstat(0).st_mode
if(stat.S_ISREG(mode) is False):
    print "Enter a list of numbers of 3 or greater. Press Ctrl-D to end input"

#creates a list of numbers for each line in the file or that the user givers
lines = list(fileinput.input())

#adds up all the nubmers giver
for x in range (len(lines)):
    sum += int(lines[x])
    counter += 1

#calculates all the nmbers needed for output
avg = sum + 0.00
avg /= counter
std_dev = cal_std_dev(avg, lines, counter)
skew = cal_skew(avg, lines, counter)
kur = cal_kur(avg, lines, counter)

#prints my answer
print "My Cal: " + str(counter) + " " + str(sum) + " " + str(avg) + " " + str(std_dev) + " " + str(skew) + " " + str(kur)

#Creates a numpy array and the does the calculations using nympy and scipy
comp_list = numpy.array(map(int, lines))
comp_sum = numpy.sum(comp_list)
comp_mean = numpy.mean(comp_list)
comp_std_dev = scipy.std(comp_list)
comp_skew = scipy.stats.skew(comp_list, bias=True)
comp_kur = scipy.stats.kurtosis(comp_list, fisher=False, bias=True)
print "Lib Calc: " + str(counter) + " " + str(comp_sum) + " " + str(comp_mean) + " " + str(comp_std_dev) + " " + str(comp_skew) + " " + str(comp_kur)
