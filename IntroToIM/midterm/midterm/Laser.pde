//code inspired from https://forum.processing.org/two/discussion/1324/how-to-create-a-bullet-array-for-asteroids-game
class Laser {

  int laserDirection;
  float laserX, laserY;
  float xSpeed;
  float ySpeed;
  float laserWidth, laserHeight;


  Laser(float _x, float _y, int direction) {
    
    laserDirection = direction;
    xSpeed = 8;
    ySpeed = 8;
    
    if (laserDirection == 0) {
      laserX = _x - 15;
      laserY = _y + 23;
    }
    if (laserDirection == 1) {
      laserX = _x + 23;
      laserY = _y + 15;
    }
    if (laserDirection == 2) {
      laserX = _x + 23;
      laserY = _y - 15;
    }
    if (laserDirection == 3) {
      laserX = _x - 23;
      laserY = _y + 15;
    }
                                          //initialize direction of laser so it remains so even if trump changes his direction later
    laserWidth = 60;
    laserHeight = 20;
    
   }
  
   void display() {
     if (laserDirection == 2){
       pushMatrix();
         translate(laserX, laserY - 20);
         rotate(HALF_PI);
         image(laser, 0, 0, laserWidth, laserHeight);
       popMatrix();
       
     }                                                  //rotate bullet to shoot up
     
     else if( laserDirection==0) {
     pushMatrix();
         translate(laserX, laserY + 25);
         rotate(HALF_PI);
         image(laser, 0, 0, laserWidth, laserHeight);
       popMatrix();
     }                                            //rotate bullet to shoot down
     
     else if ( laserDirection==1){
       image(laser, laserX + 28, laserY - 18, laserWidth, laserHeight);      //bullet shoot right
     }
     
     else if ( laserDirection==3){
       image(laser, laserX - 28, laserY - 18 , laserWidth, laserHeight);      //bullet shoot left
     }
   }
   
   void fly() {
     if (laserDirection == 3) {        //left
       laserX -= xSpeed;
     }
     
     if (laserDirection == 1) {        //right
       laserX += xSpeed;
     }
     
     if (laserDirection == 2) {        //up
       laserY -= ySpeed;
     }
     
     if (laserDirection == 0) {        //down
       laserY += ySpeed;
     }
                                                        //movement according to the direction
   }
   
   boolean checkCollision (float _x, float _y, float w) {      //check collision with corona coordinates
     float otherX = _x;
     float otherY = _y;
     if (dist(laserX, laserY, otherX, otherY + 10) < w/2 ) {
       return true;
     } 
     else {
       return false;
     }
   }
   
   boolean checkEdges() {
     if ((laserX - laserWidth/2 > width) || (laserX + laserWidth/2 < 0) || (laserY - laserHeight/2 > height) || (laserY + laserHeight/2 < 0)) {      //check if laser is outside frame to remove it
       return true;
     }
     else {
       return false;
     }
   }
  

}
