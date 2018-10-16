'''
Task :
Create a window containing the string "Hello World! " (the trailing space is significant).
Make the text appear to be rotating right by periodically removing one letter
from the end of the string and attaching it to the front.
When the user clicks on the (windowed) text, it should reverse its direction.
'''

#import Our Packages
import pygame, sys
from pygame.locals import *


#Our Colors
white = (255, 255, 255)
black = (0, 0, 0)
green = (0, 255, 0)
blue = (0, 0, 255)
red = (255, 0, 0)
ceil = (19, 229, 240)
yellow = (255, 255, 25)
red2 = (219.3,2.6,14.27)

#initialize all imported pygame modules
pygame.init()

#Size of Display Window
XSIZE = 200
YSIZE = 55


TEXT = "Just Do It! "
FONTSIZE = 45

LEFT = False
RIGHT = True

#Starting Motion direction
DIR = RIGHT

TIMETICK = 180
TICK = USEREVENT + 2


TEXTBOX = pygame.Rect(10, 10, XSIZE, YSIZE)

#repeatedly create an event on the event queue
#set_timer(eventid, milliseconds)
pygame.time.set_timer(TICK, TIMETICK)

#Initialize a window or screen for display
window = pygame.display.set_mode((XSIZE, YSIZE))

#Set the current window caption
pygame.display.set_caption("Animation")

#create a Font object from the system fonts
#SysFont(name, size, bold=False, italic=False)
font = pygame.font.SysFont(None, FONTSIZE)

# Get a reference to the currently set display surface
screen = pygame.display.get_surface()


def rotate():
    index = DIR and -1 or 1
    global TEXT
    TEXT = TEXT[index:] + TEXT[:index]


def click(position):
    #test if a point is inside a rectangle
    #collidepoint((x, y))
    #If The User Click on the text , The Direction'll changes
    if TEXTBOX.collidepoint(position):
        global DIR
        DIR = not DIR


def draw():
    #render used to draw text on a new Surface
    surface = font.render(TEXT, True,green, (0, 0, 0))
    global TEXTBOX

    TEXTBOX = screen.blit(surface, TEXTBOX)


def input(event):
    if event.type == QUIT:
        sys.exit(0)
    elif event.type == MOUSEBUTTONDOWN:
        click(event.pos)
    elif event.type == TICK:
        draw()
        rotate()


while True:
    input(pygame.event.wait())

    #Update the full display Surface to the screen
    pygame.display.flip()
