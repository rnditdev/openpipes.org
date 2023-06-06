import cadquery as cq
from cadquery import exporters
import math

result=cq.Workplane("front")
result2=cq.Workplane("front")

#Empty:19.8, 16.5
#Filled:19, 16

def plate(x,y,y_offset, line1, line2, line3, fontsize_center):
    result1=cq.Workplane("front").center(x, y).box(19, 16, 0.8)
    return result1

def text(x,y,y_offset, line1, line2, line3, fontsize_center):
    result2 = cq.Workplane("front").center(x, y+5).text(line1,5 , 0.25)
    result2 = result2+cq.Workplane("front").center(x, y+y_offset).text(line2.upper(), 0.8*fontsize_center, 0.25)
    result2 = result2+cq.Workplane("front").center(x, y-5).text(line3, 5, 0.25)
    return result2

array=[["HW","Prinz", "8",0,5],
["HW","Gedeckt", "8",0,4.1],
["HW","Gemsh", "8",0,4.5],
["HW","Oktav", "4",0,5],
["HW","Flöte", "4",0,5],
["HW","Quint", "2,2/3  4",0,5],
["HW","Oktav", "2",0,5],
["HW","Oktav", "1",0,5],
["HW","Mixt", "1,1/3  1",0,5],

["POS","Gedackt", "8",0,4.1],
["POS","Prinz", "4",0,5],
["POS","Flöte", "4",0,5],
["POS","Oktav", "2",0,5],
["POS","Mixt 1", "2",0,5],

["P","Kontrab", "16",0,4],
["P","Posaun.", "16",0,4.5]
]


array_= [
["HW","Praestant","16",0,4],
["HW","Principal","8",0,4.5],
["HW","Holzflöte","8",0,4],
["HW","Röhrflöte","8",0,3.9],
["HW","Gambe","8",0,5],
["HW","Octave","4",0,5],
["HW","Spitzflöte","4",0,4],
["HW","Quinte 2","2/3",0,4.5],
["HW","Octave","2",0,5],
["HW","Mixt m","2/3",0,5],
["HW","Mixtm" , "1/3",0,5],
["HW","Trompete","16",0,4.2],
["HW","Trompete","8",0,4.5],
["SCH","Bourdon","16",0,4.5],
["SCH","Principal","8",0,4.2],
["SCH","NachtH.G","8",0,4],
["SCH","Corno d","8",0,4.5],
["SCH","Viola","8",0,5],
["SCH","Vox cele","8",0,4.5],
["SCH","Geigenpr","4",0,4.2],
["SCH","Querflöte","4",0,4],
["SCH","Naz 2 2/3","2",0,4.2],
["SCH","Flageolett","2",0,3.7],
["SCH","Tierce 1","3/5",0,4.8],
["SCH","Larigot 1","1/3",0,4.5],
["SCH","Plein Jeu","2",0,4.2],
["SCH","Scharff 4f","1",0,4],
["SCH","Tromp.H","8",0,4.5],
["SCH","Hautbois","8",0,4.5],
["SCH","Clairon","4",0,4.5],
["SOL","Jubalfl","8",0,5    ],
["SOL","Trichterfl","4",0,4],
["SOL","Corn a p","8",0,4.5],
["SOL","Tr Cham","8",0,4.5],
["SOL","EnglischH","8",0,3.8],
["PED","Untersatz","32",0,4],
["PED","Contrab","16",0,4.5],
["PED","Subbaß","16",0,5],
["PED","Octavb","8",0,4.5],
["PED","Gedackt","8",0,4.5],
["PED","Posaune", "32",0,4.5],
["PED","Posaune","16",0,4.5],
["PED","Trompete","8",0,4.2]]




counter = 0
rowlen=5
for i in range(0,int((math.ceil(len(array)/rowlen)))):
    for j in range(0,rowlen):
        if ((i*rowlen+j)<len(array)):
            result = result+plate(i*21, j*18, array[i*rowlen+j][3], array[i*rowlen+j][0], array[i*rowlen+j][1], array[i*rowlen+j][2],array[i*rowlen+j][4])
            result2 = result2+text(i*21, j*18, array[i*rowlen+j][3], array[i*rowlen+j][0], array[i*rowlen+j][1], array[i*rowlen+j][2],array[i*rowlen+j][4])



#i=1
#j=0
#rowlen=5
#result = result+plate(i*25, j*18, array[i*rowlen+j][3], array[i*rowlen+j][0], array[i*rowlen+j][1], array[i*rowlen+j][2],array[i*rowlen+j][4])
#result = result+text(i*25, j*18, array[i*rowlen+j][3], array[i*rowlen+j][0], array[i*rowlen+j][1], array[i*rowlen+j][2],array[i*rowlen+j][4])


exporters.export(result, 'labels.stl')
exporters.export(result2, 'letters.stl')
