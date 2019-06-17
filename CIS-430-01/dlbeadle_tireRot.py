# Donald Lee Beadle
# CS 430
# OOP Tire rotation

class Tire: 
  def __init__(self, location, brand, size, maxPSI, treadDepth):
    self.location = location
    self.brand = brand
    self.size = size
    self.maxPSI = maxPSI
    self.treadDepth = treadDepth
    
  def changeLocation(self, dest):
    temp = Tire("", "", "", 0, 0)
    # Even though the actual tires move, the attachment locations should be static 
    # to the vehicle.    
    #temp.location = self.location
    #self.location = dest.location
    #dest.location = temp.location
    temp.brand = self.brand
    self.brand = dest.brand
    dest.brand = temp.brand
    temp.size = self.size
    self.size = dest.size
    dest.size = temp.size
    temp.maxPSI = self.maxPSI
    self.maxPSI = dest.maxPSI
    dest.maxPSI = temp.maxPSI
    temp.treadDepth = self.treadDepth
    self.treadDepth = dest.treadDepth
    dest.treadDepth = temp.treadDepth

class Vehicle: 
  def __init__(self, name, make, model, tires):
    self.name = name
    self.make = make
    self.model = model
    self.tires = tires

  def setName(self, name): 
    self.name = name
  
  # Assuming a standard front to back rotation. 
  def rotateTires(self):
    print("Rotating tires front to back: LF to LR and RF to RR")
    self.tires[0].changeLocation(self.tires[2])
    self.tires[1].changeLocation(self.tires[3])
    
  def display(self):
    print self.name, self.make, self.model 
    for i in range(4): 
      print self.tires[i].location, self.tires[i].brand, self.tires[i].treadDepth

# MAIN    
def main():
  tires = [Tire("LF", "GoodYear", "195/60R15", 30, 8), 
            Tire("RF", "GoodYear", "195/60R15", 30, 8),
            Tire("LR", "Michelin", "195/60R15", 30, 6),
            Tire("RR", "Michelin", "195/60R15", 30, 6)]
  
  print "BEFORE rotate:"           
  myCar = Vehicle("Focus", "Ford", 2011, tires) 
  myCar.display()
  
  print "\n"
  
  print "AFTER rotate:"   
  myCar.rotateTires()
  myCar.display()
  
if __name__ == '__main__':
  main()
