# SetOperations.py file


class Set :    
    def __init__( self, initElementsCount ):
        self._s = []
        for i in range(initElementsCount) :
            e = int(input("Enter Element {}: ".format(i+1)))
            self.add(e)

    def get_set(self):
        return self._s

    def __str__(self):
      string = "\n{ "
      for i in range(len(self._s)):
           string = string + str(self._s[i])
           if i != len(self._s)-1:
             string =  string + " , "
      string = string + " }\n"
      return string

    def __len__( self ):
        return len( self._s )

    def __contains__( self, e ):
        for i in range(len(self.get_set())):
            if self.get_set()[i] == e:
                return True
        return False

    def isEmpty( self ):
        return len(self._s) == 0

    def add( self, e ):                  
        if e not in self :
            self._s.append( e )   

    def remove( self, e ):
        if e in self.get_set():
            self.get_set().remove(e)

    def __eq__( self, setB ):                 
        if len( self ) != len( setB ) :
            return False
        else :
            return self.isSubsetOf( setB )                  

    def isSubsetOf( self, setB ):           
     for e in setB.get_set() :
         if e not in self.get_set() :
             return False
     return True 

    def union( self, setB ):                 
     newSet = self  
     for e in setB :
         if e not in self.get_set() :
             newSet.add(e)
     return newSet                           

    def intersect( self, setB ):
        newSet = Set(0)
        for i in range(len(self.get_set())) :
            for j in range(len(setB.get_set())) :
                if self.get_set()[i] == setB.get_set()[j] :
                    newSet.add(self.get_set()[i])
        return newSet

    def difference( self, setB ):
        newSet = Set(0)
        for e in self.get_set() :
            if e not in setB.get_set():
                newSet.add(e)
        return newSet

    def __iter__( self ):
        return iter(self._s)