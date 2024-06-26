from __future__ import with_statement
from threading import Thread, Lock, Condition, Semaphore
from os import _exit as quit
import time, random

####################################################### 
#                      
# Partner 1: Hanoom Lee
#
# Partner 2: Gisele Umutoni
# 
#######################################################


# Modify only the code of the class Club to make the program
# correct.

# Place your synchronization variables inside the Club instance.

# Make sure nobody is holding a Club synchronization variable
# while executing outside the Club code.


def hangout():
    time.sleep(random.randint(0, 2))


class Club:
    def __init__(self, capacity):
        self.goth_count = 0               # num goths in club
        self.hipster_count = 0            # num hipsters in club
        self.capacity = capacity          # only used for optional questions
        self.lock = Lock()
        self.signal = Lock()
        self.goth_condition = Condition(self.lock) # goths can enter
        self.hipster_condition = Condition(self.lock) #hipsters can enter

    def __sanitycheck(self):
        if self.goth_count > 0 and self.hipster_count > 0:
            print("sync error: bad social mixup! Goths = %d, Hipsters = %d" %  (self.goth_count, self.hipster_count))
            quit(1)
        if self.goth_count>self.capacity or self.hipster_count>self.capacity:
            print("sync error: too many people in the club! Goths = %d, Hipsters = %d" %  (self.goth_count, self.hipster_count))
            quit(1)
        if self.goth_count < 0 or self.hipster_count < 0:
            print("sync error: lost track of people! Goths = %d, Hipsters = %d" %  (self.goth_count, self.hipster_count))
            quit(1)

        
    def goth_enter(self):
        self.signal.acquire()
        self.lock.acquire()
        while self.hipster_count > 0 or self.goth_count >= self.capacity:
            self.goth_condition.wait() #wait for unlock until no hipsters remain, then lock
        self.goth_count +=1               
        self.lock.release() #release when done
        self.__sanitycheck()
        self.signal.release()



    def goth_exit(self):
        self.lock.acquire()
        self.goth_count -= 1
        if self.goth_count == 0 :
            self.hipster_condition.notify_all() #wakes up hipster threads (if goths are all out)
        self.__sanitycheck()
        self.lock.release() #release


    def hipster_enter(self):
        self.signal.acquire()
        self.lock.acquire()
        while self.goth_count > 0 or self.hipster_count >= self.capacity:
            self.hipster_condition.wait() #same logic as goth_enter
        self.hipster_count += 1
        self.lock.release() #release
        self.__sanitycheck()
        self.signal.release()

        
    def hipster_exit(self):
        self.lock.acquire()
        self.hipster_count -= 1
        if self.hipster_count == 0:
            self.goth_condition.notify_all() #same logic as goth_exit
        self.__sanitycheck()
        self.lock.release()



class Goth(Thread):
    def __init__(self, id):
        Thread.__init__(self)
        self.id = id

    def run(self):
        global daclub

        while True:
            print("goth #%d: wants to enter" % self.id)
            daclub.goth_enter()
            print("goth #%d: in the club" % self.id)
            print("goths in club: %d" % daclub.goth_count)
            hangout()
            daclub.goth_exit()
            print("goth #%d: left club" % self.id)
            print("goths in club: %d" % daclub.goth_count)
            
class Hipster(Thread):
    def __init__(self, id):
        Thread.__init__(self)
        self.id = id

    def run(self):
        global daclub

        while True:
            print("hipster #%d: wants to enter" % self.id)
            daclub.hipster_enter()
            print("hipster #%d: in the club" % self.id)
            print("hipsters in club: %d" % daclub.hipster_count)
            hangout()
            daclub.hipster_exit()
            print("hipster #%d: left club" % self.id)
            print("hipsters in club: %d" % daclub.hipster_count)


NUMGOTH = 3
NUMHIPSTER = 3
CAPACITY = NUMGOTH + NUMHIPSTER
daclub = Club(CAPACITY)


def main():
    for i in range(0, NUMGOTH):
        g = Goth(i)
        g.start()    
    for i in range(0, NUMHIPSTER):
        h = Hipster(i)
        h.start()    

if __name__ == "__main__":
    main()
