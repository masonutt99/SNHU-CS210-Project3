
from ast import If
from operator import ifloordiv
import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def MultiplicationTable(num):
    for i in range(10):
        print(num, " X ", i + 1, " = ",  (num * (i+1)), "\n")
    return 0;

def inputValidation(message):                               #not used because it is checked in cpp and user input is not collected in python
    while True:
        try:
            num = int(input(message))       
        except ValueError:
            print("Not an integer! Try again.")
            continue
        else:
            return num 
            break 

def DoubleValue(n):
    return n*2;

#reads from the provided list then prints out occurences
def produceList():
    file = open(r'C:\Users\mason\source\repos\Project3\x64\Release\CS210_Project_Three_Input_File.txt', "r")     #opens file to be read

    wordCount = dict()                                                                                           #creates diction to store word and number of occurences

    for word in file:                                                                                            #iterates line by line 
       
        if word.strip().lower() in wordCount:                                                                    # strip removes newline and lower brings the characters to lowercase which makes all the words look the same even if Eggplant and eggplant
            wordCount[word.strip().lower()] = wordCount[word.strip().lower()] + 1                                # adds one to the dictionary every occurence
        else:
            wordCount[word.strip().lower()] = 1                                                                  #creates first occurence of word

    sortedDict = sorted(wordCount.items(), key = lambda x:x[1], reverse = True)                                  #sorted in descending order for clearity
    #print(sortedDict)
    for i in range(len(sortedDict)):                                                                                 #prints the key and number associated with it 
        print(sortedDict[i][0], ":", sortedDict[i][1])                                                           #Use Python to display the final result of items and their corresponding numeric value on the screen.
        #print(key, ":", wordCount[key])

    file.close()    #closes the file

#returns -1 if error input 
#returns number of occurences of user input 
def itemFreq(inp):
    file = open(r'C:\Users\mason\source\repos\Project3\x64\Release\CS210_Project_Three_Input_File.txt', "r")     #opens file to be read

    wordCount = dict()                                                                                           #creates diction to store word and number of occurences

    found = False

    for word in file:                                                                                            #iterates line by line 
       
        if word.strip().lower() in wordCount:                                                                    # strip removes newline and lower brings the characters to lowercase which makes all the words look the same even if Eggplant and eggplant
            wordCount[word.strip().lower()] = wordCount[word.strip().lower()] + 1                                # adds one to the dictionary every occurence
        else:
            wordCount[word.strip().lower()] = 1                                                                  #creates first occurence of word
    for key in wordCount.keys():
        if(key == inp):  
            #print(key, ": ", wordCount[inp])
            found = True

    if not found:
        file.close()
        return -1                                               #returns -1 if error input 
    else:
        file.close()
        return wordCount[inp]                                   #returns number of occurences of user input 


def writeToFile():
    file = open(r'C:\Users\mason\source\repos\Project3\x64\Release\CS210_Project_Three_Input_File.txt', "r")     #opens file to be read
    newFile = open('frequency.dat', 'w')                                                                         # opens a file to write to 
    wordCount = dict()                                                                                           #creates diction to store word and number of occurences

    for word in file:                                                                                            #iterates line by line 
       
        if word.strip().lower() in wordCount:                                                                    # strip removes newline and lower brings the characters to lowercase which makes all the words look the same even if Eggplant and eggplant
            wordCount[word.strip().lower()] = wordCount[word.strip().lower()] + 1                                # adds one to the dictionary every occurence
        else:
            wordCount[word.strip().lower()] = 1                                                                  #creates first occurence of word
    


    sortedDict = sorted(wordCount.items(), key = lambda x:x[1], reverse = True)                                  #sorted in descending order for clearity
    #print(sortedDict)
    for i in range(len(sortedDict)):                                                                                 #prints the key and number associated with it 
        #print(sortedDict[i][0], ":", sortedDict[i][1])                                                           #Use Python to display the final result of items and their corresponding numeric value on the screen.
        #print(key, ":", wordCount[key])
        #Use Python to display the final result of items and their corresponding numeric value on the screen.
        newFile.write(str(sortedDict[i][0]) + " " + str(sortedDict[i][1]) + '\n')

    newFile.close()
    file.close()    #closes the file