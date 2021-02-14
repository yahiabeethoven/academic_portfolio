
class Trump {
  
  PImage[][] sprites;
  int direction = 1;
  int step = 0;
  int w, h;
  float x, y;
  float xspeed = 6;
  float yspeed = 6;
  float gravity;
  
  Trump(float _x , float _y){
  sprites = new PImage[4][6];
  
  w = spritesheet.width/6;
  h = spritesheet.height/4;
  
  gravity = 0.0001;

  for (int y=0; y < 4; y++) {
    for (int x=0; x< 6; x++) {
      sprites[y][x] = spritesheet.get(x*w, y*h, w, h);      //creating each instance's individual sprite from spritesheet
    }
  }

  x = _x;
  y =_y;
  
  }
  
  void update() {        //if trump is in the air make him go down through gravity
  
    if (y - h/2 < height - 190.5) {
      yspeed = yspeed + gravity;
      y += yspeed;
    }
  }
  
  void move() {
    if (direction == 0) {
      if (y + (h/2) < height) {    //move down until frame limit
          y += yspeed;
      }
    }
    if (direction == 1) {      //right till wall
      if (x + (w/2) < width) {
          x += xspeed;
        }
    }
    if (direction == 2) {      //up till fence
      if (y - (h/2) > height - 189) {
          y -= yspeed;
        }
    }
    if (direction == 3) {      //left till wall
      if (x - (w/2) > 0) {
          x -= xspeed;
        }
    }                                //move according to direction
    
    if (frameCount % xspeed == 0) {      //transition from one sprite to another
        step = (step+1) % 6;
    }
  }
  
  void recoil() {        //push trump slightly backwards when he shoots to be more realistic
    if (direction == 0) {      //down
      if (y - (h/2) > height - 189) {    //go up till fence
          y -= yspeed/4;
      }
    }
    if (direction == 1) {      //right
      if (x - (w/2) > 0) {      //left till wall
          x -= xspeed/4;
        }
    }
    if (direction == 2) {      //up
      if (y + (h/2) < height) {    //down till frame limit
          y += yspeed/4;
        }
    }
    if (direction == 3) {      //left
      if (x + (w/2) < width) {      //right till wall
          x += xspeed/4;
        }
    }
    
    //if (frameCount % xspeed == 0) {
    //    step = (step+1) % 6;
    //}
  }

  void jump() {
    
    if (y - (h/2) > height - 191) {      //if trump is not already flying make him jump
      y -= 90;
      
      if (direction == 3 ) {      //if he was moving to left push him slightly to left
        if (x - (w/2) > 0) {
          x-= 20;
        }
      }
      else if (direction == 1) {      //if he was moving to right push him slightly to right
        if (x + (w/2) < width) {
          x += 20;
        }
      }
    }
      
  }
  
  
}
