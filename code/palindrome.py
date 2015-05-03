import sys
import datetime
if __name__ == '__main__':
    time = datetime.datetime.now()

    try:
        txt = open("/Users/chuanruili/Desktop/file/ECE345/input1.txt")
    except:
        print "File does not exist!"
        sys.exit()    

    commons = None
    for line in txt:
        words = tuple(line.split()) 
        palindromes = set()# a set of lists of words
        print words
        # input line by line
        # odd
        for i in range(len(words)):
            w = words[i]
            lower = upper = i
            while lower>=0 and upper<len(words):
                if words[lower] == words[upper]:
                    palindromes.add(words[lower:upper+1])
                    lower-=1
                    upper+=1
                else:
                    break

        # even
        for i in range(len(words)-1):
            w = words[i]
            lower,upper = i,i+1
            while lower>=0 and upper<len(words):
                if words[lower] == words[upper]:
                    palindromes.add(words[lower:upper+1])
                    lower-=1
                    upper+=1
                else:
                    break

        #print "!!!!!!!!!!!!!"
        #print palindromes
        if commons == None:
            commons = palindromes
        else:
            commons &= palindromes
    longest,length = None,-float('inf')
    for e in commons:
        if len(e)>length:
            longest,length=e,len(e)
    print longest
    time = datetime.datetime.now() - time
    print time

