import cadquery as cq

lid_thickness = 2
lid_height = 15 - lid_thickness
lid_radius = 14.5 - lid_thickness

cylinder = (
    cq.Workplane("XY")
    .circle(lid_radius)
    .extrude(lid_height)
)

pitch = 20
thread_radius = lid_radius
thread_height = lid_height + 2

torus = cq.Solid.makeTorus(
    32, 12,
    pnt=cq.Vector(0,0,lid_height),
    dir=cq.Vector(0,0,1),
    angleDegrees1=0,
    angleDegrees2=360
)


text = cq.Workplane("XY").workplane(offset=13.5).text("A",15 , 2)

text2 = cq.Workplane("XY").workplane(offset=12.5).text("A",17 , 2)

cylinder = cylinder.faces("-Z").shell(lid_thickness)+text2-text







