#Doubletry.py file

from record import Record

class doubleHashTable:
    def __init__(self):
        self.size = int(input("Enter the Size of the hash table : "))
        self.table = list(None for i in range(self.size))
        self.elementCount = 0
        self.comparisons = 0
   

    def isFull(self):
        if self.elementCount == self.size:
            return True
        else:
            return False
      
    
    def h1(self, element):
        return element % self.size
       
       
    def h2(self, element):
        return 5-(element % 5)
           

    def insert(self, record):
        if self.isFull():
            print("Hash Table Full")
            return False
           
        isStored = False
        position = self.h1(record.get_number())
           
        if self.table[position] == None:
            self.table[position] = record
            isStored = True
            self.elementCount += 1
       
        else:
            i=0
            print("Collision has occured" )
            while self.table[position] != None and   i <= self.size:
                position = (self.h1(record.get_number()) + i*self.h2(record.get_number()))% self.size
                i+=1           
            self.table[position] = record
            isStored = True
            self.elementCount += 1
                    
        return isStored


    def search(self, record):
        found = False
        position = self.h1(record.get_number())
        

        if(self.table[position] != None):
            self.comparisons += 1
            if (self.table[position].get_name() == record.get_name() and self.table[position].get_number() == record.get_number()):
                print("Phone number found at position {}".format(position) + " and total comparisons are " + str(1))
                return position
           
            else:
                i = 1
                while i <= self.size:
                    position = (self.h1(record.get_number()) + i*self.h2(record.get_number())) % self.size
                    if(self.table[position] != None):
                        self.comparisons += 1
                        if (self.table[position].get_name() == record.get_name() and self.table[position].get_number() == record.get_number()):
                            found = True
                            break                                      
                        else:
                            found = False
                            i += 1
                    
                if found:
                    print("Phone number found at position {}".format(position))
                else:
                    print("Record not Found")
                return found   
   
    def display(self):
        print("\n")
        for i in range(self.size):
            print("Hash Value: "+str(i) + "\t\t" + str(self.table[i]))
        print("The number of phonebook records in the Table are : " + str(self.elementCount))

