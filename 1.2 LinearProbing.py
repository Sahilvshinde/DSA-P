#LinearProbing.py file

from record import Record
 
class hashTable:
   
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
   

    def hashFunction(self, element):
        return element%self.size
   
  
    def insert(self, record):
        if self.isFull():
            print("Hash Table Full")
            return False
           
        isStored = False
        num=record.get_number()
        position = self.hashFunction(num)
       
        if self.table[position] == None:
            self.table[position] = record
            isStored = True
            self.elementCount += 1
       
        else:
            
            while self.table[position] != None:
                position =(position+1)%self.size           
            self.table[position] = record
            isStored = True
            self.elementCount += 1
        return isStored
       
       
    def search(self, record):
        found = False
        
        position = self.hashFunction(record.get_number())
        
        if(self.table[position] != None):
            if(self.table[position].get_name() == record.get_name() and self.table[position].get_number() == record.get_number()):
                isFound = True
                print("Phone number found at position {} ".format(position) + " and total comparisons are " + str(1))
                return position
            
            while self.table[position] != None or self.comparisons <= self.size:
                    
                    if(self.table[position].get_name() == record.get_name() and self.table[position].get_number() == record.get_number()):
                        isFound = True
           
                        i = self.comparisons +1
                        print("Number found at position {} ".format(position) + " and total comparisons are " + str(i) )
                        return position 

                    position = (position+1)%self.size
                    self.comparisons += 1
                    
                    
                    if isFound == False:
                        print("Record not found")
                        return false

                               
 

    def display(self):
        print("\n")
        for i in range(self.size):
            print("Hash Value: "+str(i) + "\t\t" + str( self.table[i]) )


