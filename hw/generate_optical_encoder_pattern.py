import pygame
import sys
import time

def getPixels(mm):
	ppi = 72
	im = 25.4	# 1 inch = 25.4 mm 
	return int(round(mm*ppi/im))

def drawbars(thickness, height, line):
	maxright = A4w - right_border
	cursor = left_border
	while cursor < maxright:
		pygame.draw.rect(screen, black, (cursor,line, cursor+thickness, line+height), 0)
		cursor = cursor + (2*thickness)
		print (cursor)

A4w = getPixels(210)
A4h = getPixels(297)
black = [0,0,0]
white = [255,255,255]
circle = 175

c0_5 = getPixels(circle/circle/2)
c1 = getPixels(circle/circle)
c1_5 = getPixels(circle/(circle+(circle/2)))
c2 = getPixels(circle/2*circle)

layout_width = getPixels(circle)
bar_height = getPixels(15)
bar_distance = getPixels(10)
top_border = bottom_border = left_border = right_border = getPixels(20)




size = [A4w,A4h]
screen = pygame.display.set_mode(size)

screen.fill(white)

# Print cut markers
pygame.draw.line(screen, black, [left_border,top_border], [left_border, A4h-bottom_border])
pygame.draw.line(screen, black, [left_border+layout_width,top_border], [left_border+layout_width, A4h-bottom_border])

drawbars(c0_5, bar_height, 40)
pygame.display.update()

time.sleep(3)
pygame.image.save(screen, "optical_encoder_layout.bmp")
