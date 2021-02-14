

class Corona {
  float coronaX, coronaY;
  float xSpeed;
  float ySpeed;
  float xDirection, yDirection;
  float coronaWidth, coronaHeight;
  int rand;
  
  
  Corona(float _x, float _y, int _rand) {
    
    coronaX = _x;
    coronaY = _y;
    
    coronaWidth = 100;
    coronaHeight = 100;
    
    xDirection = 1;
    yDirection = 1;
    
    xSpeed = 2;
    ySpeed = 2;
    
    rand = _rand;
    
  }
  
  void display() {
    image(corona, coronaX, coronaY, coronaWidth, coronaHeight);      //display corona image
  }
  
  void move() {
    
    if (rand > 50) {              //if random number is this then move in right direction
      coronaX += (xSpeed * xDirection);
      coronaY += (ySpeed * yDirection);
    }
    
    else {                    //if random number is less tha or equal to 50, move in the left direction
      coronaX -= (xSpeed * xDirection);
      coronaY -= (ySpeed * yDirection);
    }
    
    if ((coronaX + (coronaWidth/2) > width) || (coronaX - (coronaWidth/2) < 0)) {      //if corona hits either walls horizontally switch direction of motion to bounce
      xDirection *= -1;
    }
    
    if ((coronaY + (coronaHeight/2) > height) || (coronaY - (coronaHeight/2) < 0)) {        //if corona hits either walls vertically switch direction of motion to bounce
      yDirection *= -1;
    }
   
  }
  
  boolean checkTrump(float _x, float _y) {          //check if it collided with trump
     float otherX = _x;
     float otherY = _y;
     if (dist(coronaX, coronaY, otherX, otherY) < coronaWidth/2) {
       return true;
     } 
     else {
       return false;
     }
  }


}
