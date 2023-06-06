import cadquery as cq
from cadquery import exporters
import math

result=cq.Workplane("front")
result2=cq.Workplane("front")

def plate(x,y, line1, y_offset, fontsize_center):
    result1=cq.Workplane("front").center(x, y).circle(7.5).extrude(1)
    result1 = result1 - cq.Workplane("front").center(x, y+y_offset).text(line1, fontsize_center, 0.5)
    return result1

def text(x,y, line1, y_offset, fontsize_center):
    result2 = cq.Workplane("front").center(x, y+y_offset).text(line1, fontsize_center, 0.5)
    return result2

array=[["1",0, 10],
["2",0,10],
["3",0, 10],
["4",0,10],
]

counter = 0
rowlen=4
xseparation = 25
yseparation = 18

xcenter = -((math.ceil(len(array)/rowlen)-1)*xseparation)/2
ycenter= -float(((rowlen-1)*yseparation))/2
for i in range(0,(math.ceil(len(array)/rowlen))):
    for j in range(0,rowlen):
        if ((i*rowlen+j)<len(array)):
            result = result+plate(xcenter + i*25, ycenter+j*18,  array[i*rowlen+j][0],array[i*rowlen+j][1], array[i*rowlen+j][2])
            result2 = result2+text(xcenter + i*25, ycenter + j*18, array[i*rowlen+j][0],array[i*rowlen+j][1], array[i*rowlen+j][2])



exporters.export(result, 'labels.stl')
exporters.export(result2, 'letters.stl')