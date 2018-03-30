$fn=50;
renderBracket=2;
if(renderBracket < 2) {
difference() {
    union() {
cylinder(r=38, h=6);
     translate([35, 0, 0])
     cylinder(r=7, h=6); 
           translate([-35, 0, 0])
     cylinder(r=7, h=6);     
    }
    
    translate([40, 0, 2])
    cube(center=true,[10, 2, 2]);
        translate([-40, 0, 2])
    cube(center=true,[10, 2, 2]);
    
    translate([35, 0, 3])
    cylinder(r=5, h=3); 
    translate([-35, 0, 3])
    cylinder(r=5, h=3); 
    
    translate([35, 0, 1])
    cylinder(r=3.05, h=3); 
    translate([-35, 0, 1])
    cylinder(r=3.05, h=3); 
    
    translate([0, 0, 3])
cylinder(r=35, h=3);
    cylinder(d=37, h=3);
}
difference() {
translate([-15, 20, 0])
cube([30, 26, 3]);
translate([-12, 20, 0])
cube([24, 23, 3]);
}
mirror([0, 1, 0])
difference() {
translate([-15, 20, 0])
cube([30, 26, 3]);
translate([-12, 20, 0])
cube([24, 23, 3]);
}
}
translate([0, 0, 13.8])
if(renderBracket > 0) {

difference() {
    union() {
import("02_bottom.stl");
    translate([35, 0, -10.715])
    cylinder(r=4.6, h=8);
     translate([-35, 0, -10.715])
cylinder(r=4.6, h=8);   
        
    }
        translate([32.5, 0,  -8.715])
    cube(center=true,[5, 2, 2]);
        translate([-32.5, 0,  -8.715])
    cube(center=true,[5, 2, 2]);
    translate([0, 0, -15])
    cylinder(d=42, h=10);
    
    
    for(i = [0 : 4]) {
    rotate([0, 0, -75-23*i])
        translate([0, -2, -10.8])
    cube([27, 4, 2]);
    }
    
translate([35, 0, -11.715])
    cylinder(r=3.1, h=7);
translate([-35, 0, -11.715])
cylinder(r=3.1, h=7);
}
}