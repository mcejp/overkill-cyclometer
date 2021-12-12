/*[ Options ]*/
// Sensor groove diameter. Recommend sensor diameter + 2
SensorGrooveDiameter = 7.5;

// Holder length. Recommend equal to sensor length
HolderLength = 30;

// Holder thickness
HolderThickness = 12;

// Distance
Distance = 13;

// Bend radius
BendRadius = 25;

// Number of grooves
NumGrooves = 2;

// Groove width. Recommend zip tie width + 1
GrooveWidth = 6;

// Groove depth
GrooveDepth = 2;


ClearanceNeeded = Distance + SensorGrooveDiameter + GrooveDepth;
echo(ClearanceNeeded=ClearanceNeeded);

difference() {
    // Bounding box:
    // Distance + BendRadius x HolderThickness x HolderLength
    BboxX = Distance + BendRadius;
    BboxY = HolderThickness;
    translate([0, -BboxY/2, 0])
        cube([BboxX, BboxY, HolderLength]);

    union() {
        // Sensor cut-out
        translate([0, 0, -HolderLength / 2])
            cylinder(h=HolderLength * 2, d=SensorGrooveDiameter);
        // Attachment cut-out
        translate([Distance + BendRadius, 0, -HolderLength / 2])
            cylinder(h=HolderLength * 2, r=BendRadius, $fn=50);

        // Cut-out grooves
        if (NumGrooves >= 1) {
            GrooveSpacingZ = HolderLength / NumGrooves;
            for (i = [0 : NumGrooves-1]) {
                GrooveZ = GrooveSpacingZ * (0.5 + i);
                for (y = [-1, 1]) {
                    GrooveY = y * HolderThickness / 2;

                    // Long groove
                    translate([0, GrooveY, GrooveZ])
                        cube([BboxX * 2, GrooveDepth, GrooveWidth], center=true);
                    // Diagonal cut
                    CutWidth = HolderThickness / 2 - SensorGrooveDiameter / 2 - GrooveDepth / 2;
                    CutOuterY = y * (HolderThickness / 2 - GrooveDepth / 2);
                    translate([0, CutOuterY, GrooveZ])
                        rotate([0, 0, 45])
                        cube([CutWidth * sqrt(2), CutWidth * sqrt(2), GrooveWidth], center=true);
                    // Cut slightly into sensor space
                    //translate([0, GrooveY, GrooveZ])
                    //    cube([SensorDiameter / 2, BboxY, GrooveWidth], center=true);
                }
            }
        }
    }
}
