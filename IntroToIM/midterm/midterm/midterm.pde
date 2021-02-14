import processing.sound.*;    //importing sound library

PImage whiteHouse, sanitizer, laser, corona, trumpBack, americaFlag, fence;     //all images needed
PImage spritesheet;      //sprites of trump
boolean gameOn;        //condition for game
float prevFrame = 0;      //initializing value for previous frame
float randX, randY;      //random numbers for coordinates of creation of corona particles
ArrayList <Laser> lasers;    //initializing arraylist for sanitizer bullets
ArrayList <Corona> coronas;    //initializing array list for corona particles
int score = 0;          //initializing score to 0
PFont f;              //f object for all the texts in the game
int luck;            //randomizing number to make corona particles start motion towards the left or the right
int buttonX, buttonY;      // Position of button
int buttonWidth, buttonHeight;     //dimensions of play button
color buttonColor, baseColor;    //colors of play button
color buttonHighlight;
color currentColor;
boolean buttonOver;
boolean instructions;        //condition for whether instructions page is open or not
SoundFile click, squirt, pop, trumpSound, anthem;      //all sounds in the game

Trump trumps;      //initializing trump character 


//button logic inspired from https://processing.org/examples/button.html

void setup() {
  size(720,477);
  
  instructions = true;      //start game with instructions page
  buttonOver = false;      //start with condition of button pressed false
  gameOn = false;          //don't start game till play is clicked
  
  
  f = createFont("Raleway-Bold.ttf",72);      //aesthetic font that fits teh theme
  
  whiteHouse = loadImage("house4.png");      //white house background pic
  spritesheet = loadImage("trump.png");    //sprites of trump
  sanitizer = loadImage("sanitizer.png");    //sanitizer image
  laser = loadImage("laser.png");            //sanitizer bullet image
  corona = loadImage("corona3.png");          //corona particle image
  trumpBack = loadImage("trumpbackground.jpg");      //trump face when loses image
  americaFlag = loadImage("americaFlag3.jpg");      //america flag background in the beginning with the instructions image
  fence = loadImage("fence4.png");      //black fence image
  
  click = new SoundFile (this, "click.mp3");      //sound when you click
  squirt = new SoundFile (this, "squirt.mp3");       //sound when you shoot
  pop = new SoundFile (this, "pop.mp3");      //sound when you kill corona particle
  trumpSound = new SoundFile (this, "no.mp3");      //long sound playing when you lose until you click anywhere to restart
  anthem = new SoundFile (this, "anthem (6).mp3");      //8bit anthem background music
  
  trumps = new Trump(width/2, height -40);        //creates instance of class trump
  lasers = new ArrayList();        //initializes sanitizer bullets list
  coronas = new ArrayList();      //initializes coronas list
  
  buttonColor = color(0);
  buttonHighlight = color(51);
  baseColor = color(102);
  currentColor = baseColor;
  buttonWidth = 150;
  buttonHeight = 60;
  buttonX = width/2;
  buttonY = 3*height/4 + 30;        //initializations of the button color, color when hovered upon, dimensions, and position
  
  anthem.loop();      //keep the anthem playing on loop always
  trumpSound.amp(0.001);      //reduce the amplitude of trump sound to nothing so it is not heard now
  trumpSound.loop();      //keep the trump sound playing continuously in the background
  
  rectMode(CENTER);
  imageMode(CENTER);
}

void draw() {
  
  if (gameOn == true && instructions == false) {      //if game is one the instructions page is not opened
    //trumpSound.pause();
    background(whiteHouse);
    image(fence, width/6, height -145, width/3, 80);
    image(fence, width/3 + width/6, height -145, width/3, 80);
    image(fence, 2*width/3 + width/6, height -145, width/3, 80);      //draw the fence three times side by side
    
    if (keyPressed) {
        if (keyCode == DOWN || key == 's') {
          keyCode = DOWN;                    //handling keyCode when key = s is pressed instead, because I use keyCode throughout teh code
          trumps.direction = 0;
          trumps.move();
        }
          
        else if (keyCode == LEFT || key == 'a') {
          keyCode = LEFT;
          trumps.direction = 3;
          trumps.move();
        }
        else if (keyCode == RIGHT || key == 'd') {
          keyCode = RIGHT;
          trumps.direction = 1;
          trumps.move();
        }
        
        else if (keyCode == UP || key == 'w') {
          keyCode = UP;
          trumps.direction = 2;
          trumps.move();                                    //handling the moements of trump, whether using keys or using w, a, s, d
        } 
        else {
          trumps.direction = trumps.direction;
        }
    }
      
      if (trumps.direction == 3) {
        pushMatrix();
        translate(trumps.x - 23, trumps.y + 15);
        //rotateY(radians(180));
        image(sanitizer, 0, 0);
        popMatrix();                      //draw sanitizer direction right
      }
      
       if (trumps.direction == 2) {
        image(sanitizer, trumps.x + 20, trumps.y + 8);      //draw sanitizer direction up
      }
      
  
      image(trumps.sprites[trumps.direction][trumps.step], trumps.x, trumps.y);      //drawing trump himself
      trumps.update();                    //calling on gravity
      
      if (trumps.direction == 1) {
        image(sanitizer, trumps.x + 23, trumps.y + 15);      //draw sanitizer direction left
      }
      
      if (trumps.direction == 0) {
        image(sanitizer, trumps.x - 15, trumps.y + 20);        //draw sanitizer direction down
      }
      
      if (frameCount % 100 == 0) {
        if (coronas.size() < 8) {            //setting limit of 8 coronas at a time
           luck = (int)random(100);
           randX = random(100, width - 100);
           randY = random (100, height - (190 + trumps.h));
           
           
           Corona temp = new Corona(randX, randY, luck);
           coronas.add(temp);
        }
      }                                                   //create coronas after a certain number of frames at random starting positions and random starting direction of left or right
      
      for (int i = coronas.size()-1; i >= 0; i--) {
        Corona current = coronas.get(i);
        current.display();
        current.move();                                    //call on functional methods of corona class for each of them
        
        if (current.checkTrump(trumps.x, trumps.y)) {          //checking if corona collided with trump
          anthem.stop();          //stop the background music
          gameOn = false;          //game condition false
          break;                //break from the conditions to enter others
        }
      }
      
      for (int i = lasers.size()-1; i >= 0; i--) {
        Laser laser = lasers.get(i);
        laser.display();
        laser.fly();                //call on functional methods of sanitizer bullets for each object
        
        if (laser.checkEdges()) {        //check if laser is out of frame to remove it
          lasers.remove(laser);
        }
        
        for (int j = coronas.size()-1; j >= 0; j--){        //iterate through all coronas
          Corona important = coronas.get(j);
          if (laser.checkCollision(important.coronaX, important.coronaY, important.coronaWidth)) {      //if bullet hits corona
            pop.amp(0.1);
            pop.play();      //make pop sound
            coronas.remove(important);       //remove hit corona
            lasers.remove(laser);           //remove the bullet that hit it too
            score += 10;        //increment score by 10
          }
          //pop.stop();
        }
        
      }
      
      textAlign(CORNER);
      String Score = "Score: ";          //constantly show score at the corner
      //fill(0);
      //rect(width - 130 , height - 100, textWidth(Score) + 10, 50);
      textFont(f,20);
      fill(255);
      
      
      text(Score + score, width - 115, height - 20);        //score text bottom right
    
  }
  
  else if (instructions == true && gameOn == false) {        //starting phase of instructions pre-game
    
    background(255);
    update();
  
    if (buttonOver) {
      fill(buttonHighlight);            //if mous hovers over button change color
    } 
    else {
      fill(buttonColor);
    }
    
    image(americaFlag, width/2, height/2);        //image of flag with game instructions on it
    
    stroke(255);
    rect(buttonX, buttonY, buttonWidth, buttonHeight, 20);      //play button
    
    textFont(f,25); 
    textAlign(CENTER, CENTER);
    fill(255);
    String play = "PLAY";          //text in play button to clarify it
    text(play, buttonX , buttonY - 3);
  }
  
  else if (instructions == false && gameOn == false) {      //if player loses
    anthem.stop();      //stop background music
    //trumpSound.play();
    trumpSound.amp(0.8);      //increase trump saying no to be heard

    
    
    background(trumpBack);      //trump's face
    textAlign(CENTER);
    
    textFont(f,40); 
    //same shade as in the flag
    fill(#BF0A30);
    String first = "'This was unexpected...'";
    text(first, width/2 , (height/4) - 90);
    
    textFont(f,24);
    //same shade as in the flag
    fill(#002868);
    String second = "CLICK ANYWHERE TO TRY AGAIN";
    text(second, width/2 - 5, height/2 + 215);      //game over text
    
    textAlign(CORNER);
    textFont(f,20);
    fill(0);
    String third = "Score: ";
    text(third + score, width - 115, height -20);      //final score text
    
   
  }
}

void keyPressed()
{
   if(key == ' '){
      if (frameCount - prevFrame > 15) {      //only allow jumping constantly after certain number of frames
        prevFrame = frameCount;
        trumps.jump();      
      }
   }
   
   if(key == 'e') {          //shoot sanitizer bullet
   trumps.recoil();           //recoil when trump shoots
      if (frameCount - prevFrame > 20) {        //only allow multiple shooting after certain number of frames if key is held
        squirt.amp(0.2);        //play squirt sound
        squirt.play();
        prevFrame = frameCount;
        Laser temp = new Laser(trumps.x, trumps.y, trumps.direction);        //create new bullet
        lasers.add(temp);      //add it to teh list
      }
    }
}

void update() {
  if ( overButton(buttonX, buttonY, buttonWidth, buttonHeight) ) {      //check if mouse is over the button to change color
    buttonOver = true;
  } 
  else {
    buttonOver = false;
  }
}

void keyReleased() {
  if(key == ' ') {          //keep trump in correct direction and keep moving even while/after jumping
    if (trumps.direction == 0) {
        keyCode = DOWN;              
      }
        
      if (trumps.direction == 3 ) {
        keyCode = LEFT;
      }
      if (trumps.direction == 1) {
        keyCode = RIGHT;
      }
      
      if (trumps.direction == 2) {
        keyCode = UP;
      } 
  }
  
  if(key == 'e') {        //keep trump in correct direction and keep moving even while/after shooting
    //squirt.stop();
    if (trumps.direction == 0) {
        keyCode = DOWN;
      }
        
      if (trumps.direction == 3 ) {
        keyCode = LEFT;
      }
      if (trumps.direction == 1) {
        keyCode = RIGHT;
      }
      
      if (trumps.direction == 2) {
        keyCode = UP;
      } 
  }
}

boolean overButton(int x, int y, int buttonWidth, int buttonHeight)  {            //check if mouse is over button
  if (mouseX >= x - buttonWidth/2 && mouseX <= x + buttonWidth/2 && mouseY >= y - buttonHeight/2 && mouseY <= y + buttonHeight/2) {
    return true;
  } else {
    return false;
  }
}

void mousePressed() {
  if (buttonOver) {      //check if mouse is clicked over button then start game
    
      click.amp(0.3);
      click.play();
      instructions = false;
      
     if (gameOn == false){        //if mouse is clicked when the game is off, turn it on and reset everything to zero and empty lists
        //trumpSound.stop();
        //instructions = false;
        score = 0;
        gameOn = true;
        anthem.amp(0.4);
        anthem.loop();        //replay background music
        trumpSound.amp(0.001);
        for (int i = coronas.size()-1; i >= 0; i--) {       //reset coronas list
          coronas.remove(i); 
        }
        for (int i = lasers.size()-1; i >= 0; i--) {         //reset bullets list
          lasers.remove(i);   
        }
      
    }
    
  }
  
}
