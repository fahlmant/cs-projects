#Name: Taylor Fahlman
#Email: fahlmant@onid.oregonstate.edu
#Class: CS344-001
#Assignment: 1
#Resources:http://stackoverflow.com/questions/2405292/how-to-check-if-text-is-empty-spaces-tabs-newlines-in-python
#http://stackoverflow.com/questions/6797984/how-to-convert-string-to-lowercase-in-python
#http://stackoverflow.com/questions/4435169/good-way-to-append-to-a-string
import sys
import fileinput 
import os, stat

#sorts list give, stores z at the 0th, and a at the nth
def sort_list(list):
    counter = 0
    size = len(list)
    sorted = size * [None]
    for x in range(len(list)): 
        sorted[counter] = min(list)
        list.remove(min(list))
        counter = counter+1
    
    
    return sorted

#sorts list give by max number at the top
def int_sort_list(list):
    counter = 0
    size = len(list)
    sorted = size * [None]
    for x in range (len(list)):
        sorted[counter] = max(list)
        list.remove(max(list))
        counter += 1

    return sorted

#sees if a file was redirected or not
mode = os.fstat(0).st_mode
if(stat.S_ISREG(mode) is False):
    print "Enter in your text and press Ctrl-D to end input"

#converts input to a list
word_list = list(fileinput.input())
final_list = [None]
list_element = ""
count = 0
#appends each char on the word until space in encountered
for lines in word_list:
    for words in lines:
        if(words.isspace() is False):
            if(words.isalpha()):
                list_element += str(words)
                list_element = list_element.lower()
        else:
            final_list += [None]
            final_list[count] = list_element
            list_element = ""
            count += 1
            

#removes the None element from the list
length = len(final_list)
final_list.remove(None)


#print word_list
sorted_list = sort_list(final_list)

count = 0
var = 0

#prints alpha sorted list with a at the top
print "Alpha sorted"
int_sorted_list = len(sorted_list) * [None]
for x in range(len(sorted_list)):
    var = sorted_list[x]
    count = sorted_list.count(sorted_list[x])
    print sorted_list[x] + ": " + str(count)
    int_sorted_list[x] = str(count) + "," + str(sorted_list[x])

#prints int num sorted by biggest num first
final_int_list = int_sort_list(int_sorted_list)
print "Number sort"
for x in range(len(final_int_list)):
    print final_int_list[x]


