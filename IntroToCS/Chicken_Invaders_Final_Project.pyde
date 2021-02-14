add_library('minim')
import random, os, timeit
player1 = Minim(this)
r = 50 #this is the radius of the chicken

Dim = 30 #this is the dimension of each sqaure
path = os.getcwd()
game_over = False 
game_round = 1

# the code below will increase the rounds as the number of chickens in the list increase 
# if len(self.chicken) == 20:
    #game_round = 2 
# if len(self.chicken) == 40:
    #game_round = 3
# if len(self.chicken) == 80:
    #game_round = 4
     

class Game: #this is the main game class
    
    def __init__(self, w, h, g): #w = width of the screen and h = height of the screen
        
        self.w = w
        self.h = h
        self.chickens = [] #chickens are in the list 
        self.g = g
        self.score = 0
        self.spaceship = Spaceship(380, 400)
        self.bullets = []
        
        self.background_sound = player1.loadFile(path + "/soundtrack.mp3")
        self.background_sound.rewind()
        self.background_sound.play()
        self.lasersound = player1.loadFile(path + "/laser_sound.mp3")

    def display(self):
        fill(208, 208, 208)
        self.spaceship.show_spaceship()
        self.spaceship.update()
        self.spaceship.movement()
        
        for chicken in self.chickens:
            chicken.show_chicken()
            chicken.update()
            
        # self.chicken.movement()
        for bullet in self.bullets:
            bullet.showBullet()
            
    def update(self): 
        if not random.randint(0,10):
            x = random.randint(50,650) 
            tmp = True
            if len(self.chickens) <= 20:
                for chicken in self.chickens:
                    if not chicken.distance(x,-50) >= 2*r:
                        tmp = False
                if tmp:
                    self.chickens.append(Chickens(x, -50))
        print("hi")


class Chickens: 
    
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.img = loadImage(path + "/chickk/chickk/1.png")
        self.img2 = loadImage(path + "/chickk/chickk/2.png")
        self.img3 = loadImage(path + "/chickk/chickk/3.png")
        self.img4 = loadImage(path + "/chickk/chickk/4.png")
        self.vy = 0
        self.vx = 0
        self.img_w = 52
        self.img_h = 43
        self.images = [self.img, self.img2, self.img3, self.img4]
         

    def show_chicken(self): #this method displays the Game class in the main draw function
        # for i in range (len(self.images)):
        if frameCount % 40 > 30:
            image(self.images[0], self.x, self.y, self.img_w, self.img_h)
        elif frameCount % 40 > 28:
            image(self.images[1], self.x, self.y, self.img_w, self.img_h)
        elif frameCount % 40 > 25:
            image(self.images[2], self.x, self.y, self.img_w, self.img_h)
        else:
            image(self.images[3], self.x, self.y, self.img_w, self.img_h)
    
    def game_over(self): #this method will check for end game
        
        if self.y < 200: 
            return False 

    def gravity(self):
        if self.y >= game.g:
            self.vy = 1
        else:
            self.y += 1
                # if self.y >= game.g:
                #     self.vy = game.g - self.y
    
    def update(self):
        self.gravity()
        
        self.y += self.vy
        self.x += self.vx
        
    def distance(self, x, y):
        return ((self.x - x)**2 + (self.y - y)**2) **0.5
        
class Bullet:
    def __init__(self, x, y):
        self.x = x + 35
        self.y = y
        self.img = loadImage(path + "/laserred.png")
        
    def showBullet(self):
        self.moveBullet()
        image(self.img, self.x, self.y, 10, 20)
    
    def moveBullet(self):
        self.y -= 10

class Spaceship:
    
    def __init__(self, x, y):
        self.img = loadImage(path + "/spaceship1.png")
        self.img2 = loadImage(path + "/spaceship.png")
        self.x = x
        self.y = y
        self.vy = 0
        self.vx = 0
        self.img_w = 97
        self.img_h = 90
        self.images = [self.img, self.img2]
        self.key_handler = {LEFT: False, RIGHT:False, UP:False, DOWN:False}
        self.alive = True
        self.shoot = False
        # self.direction = DOWN
    
    def show_spaceship(self):
        if self.shoot:
            if frameCount % 10 == 0:
                game.lasersound.rewind()
                game.lasersound.play()
                game.bullets.append(Bullet(game.spaceship.x, game.spaceship.y))
                game.bullets.append(Bullet(game.spaceship.x + 25, game.spaceship.y))
            
        if self.key_handler[UP]:
            image(self.images[1], self.x, self.y, self.img_w, self.img_h + 130)
        elif self.key_handler[RIGHT]:
            image(self.images[1], self.x, self.y, self.img_w, self.img_h + 130)
        elif self.key_handler[LEFT]:
            image(self.images[1], self.x, self.y, self.img_w, self.img_h + 130)
        else:
            image(self.images[0], self.x, self.y, self.img_w, self.img_h)

        
    def gravity(self):
        if self.y >= game.g - 72:
            self.vy = 0
        else:
            if not self.key_handler[UP] and not self.key_handler[RIGHT] and not self.key_handler[LEFT]:
                self.y += 5
                # if self.y >= game.g:
                #     self.vy = game.g - self.y
    
    def update(self):
        self.gravity()
        
        self.y += self.vy
        self.x += self.vx
        
    def movement(self):
        
        global game, score
        stepx = 0
        stepy = 0
        
        if self.key_handler[LEFT]:

            if self.x > 0:
                stepx = -5
                # stepy = 0
            else:
                self.vx = 0
            # self.direction = LEFT
            
        if self.key_handler[RIGHT]:

            if self.x < 699:
                stepx = 5
                # stepy = 0
            else:
                self.vx = 0
            # self.direction = RIGHT
            
        if self.key_handler[UP]:

            if self.y > 0:
                # stepx = 0
                stepy = -5
            else:
                self.vy = 0
            # self.direction = UP
            
        # else:
        #     self.vy = 0
        #     stepy = 0
        #     self.direction = DOWN
        
        self.x += stepx
        self.y += stepy

        
score = 0
game = Game(800, 700, 700)

def setup(): #this is the basic set up of the board
    size(800,700)
    

    
    
def draw():#below is the draw function to display our game
    background(loadImage(path + "/background.jpg"))
    
    if Chickens.game_over != False: 
        game.display()
        game.update()
        textSize(13)
        text("Score: " + str(score), 10, 15)
    else: 
        fill(0,0,0)
        textSize(60)
        text("GAME OVER", 150, 300)
        textSize(30)
        # text("FINAL SCORE: "+str(game.score), 200, 350)
        # textSize(20)
        text("CLICK YOUR MOUSE TO PLAY AGAIN", 150, 400)
        

        

#Making sure that each key coincides with the correct direction    
        
def keyPressed():
    if key == 'w' or key == 'W':
        game.spaceship.shoot = True
            
    if keyCode == LEFT:
        # game.spaceship.direction = LEFT
        game.spaceship.key_handler[LEFT] = True
        
        
    if keyCode == RIGHT:
        # game.spaceship.direction = RIGHT
        game.spaceship.key_handler[RIGHT] = True

        
    if keyCode == UP:
        # game.spaceship.direction = UP
        game.spaceship.key_handler[UP] = True
        
    
        

def keyReleased():
    if key == 'w' or key == 'W':
        game.spaceship.shoot = False
    if keyCode == UP:
        game.spaceship.key_handler[UP] = False
    if keyCode == LEFT:
        game.spaceship.key_handler[LEFT] = False
    if keyCode == RIGHT:
        game.spaceship.key_handler[RIGHT] = False


#Restarting the game once the mouse has been clicked by the player    
              
def mouseClicked():
    global game
    game = Game(700, 900, 700)
    
    
