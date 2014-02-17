import pygame
import sys
import time

pygame.init()

# Convert measures in mm to pixels
def getPixels(mm):
	ppi = 72
	im = 25.4	# 1 inch = 25.4 mm 
	return int(round(mm*ppi/im))


# Draw a sequence of bars along an horizontal line
def drawbars(thickness, space, height, valign):
	maxright = A4w - right_border
	cursor = left_border
	while cursor < maxright:
		pygame.draw.rect(screen, black, (cursor,valign, thickness, height), 0)
		cursor = cursor + thickness + space
		#print (thickness)
		#print (cursor)


A4w = getPixels(210)
A4h = getPixels(297)
black = [0,0,0]
white = [255,255,255]
gray = [100,100,100]
circle = 175

barsize = [ getPixels(0.5), getPixels(1), getPixels(1.5), getPixels(2), getPixels(2.5)]
layout_width = getPixels(circle)


bar_height = getPixels(15)
bar_distance = getPixels(10)
top_border = bottom_border = left_border = right_border = getPixels(10)




size = [A4w,A4h]
screen = pygame.display.set_mode(size)

screen.fill(white)

myfont = pygame.font.SysFont("monospace", 12)

# Print cut markers
pygame.draw.line(screen, gray, [left_border,top_border], [left_border, A4h-bottom_border])
pygame.draw.line(screen, gray, [left_border+layout_width,top_border], [left_border+layout_width, A4h-bottom_border])


# Draw the layout
va = 0
for count in range(2):
	for bs in barsize:
		no_bars = int (layout_width / bs / 2)
		space = (layout_width-(bs*no_bars))/no_bars
		va+=70
		drawbars(bs, space, bar_height, va)
		# Add a label to the bar line
		label_text = "No. bars: "+str(no_bars)+" - Thickness(px): "+str(bs)+" - Spacing(px): "+str(space)
		label = myfont.render(label_text , 1, (150,150,150))
		screen.blit(label, (left_border, va+bar_height+3))

pygame.display.update()

time.sleep(3)
pygame.image.save(screen, "optical_encoder_layout.bmp")
