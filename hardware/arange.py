#!/usr/bin/env python2

# Random placement helpers because I'm tired of using spreadsheets for doing this
#
# Kevin Cuzner

import math
from pcbnew import *

def place_circle(refdes, start_angle, center, radius, component_offset=0, hide_ref=False, lock=False):
    """
    Places components in a circle
    refdes: List of component references
    start_angle: Starting angle
    center: Tuple of (x, y) mils of circle center
    radius: Radius of the circle in mils
    component_offset: Offset in degrees for each component to add to angle
    hide_ref: Hides the reference if true, leaves it be if None
    lock: Locks the footprint if true
    """
    pcb = GetBoard()
    deg_per_idx = 360 / float(len(refdes))
    print deg_per_idx
    for idx, rd in enumerate(refdes):
        part = pcb.FindModuleByReference(rd)
        angle = (deg_per_idx * idx + start_angle) % 360;
        print "{0}: {1}".format(rd, angle)
        xmils = center[0] + math.cos(math.radians(angle)) * radius
        ymils = center[1] + math.sin(math.radians(angle)) * radius
        part.SetPosition(wxPoint(FromMils(xmils), FromMils(ymils)))
        part.SetOrientation((angle+90) * -10)
        if hide_ref is not None:
            part.Reference().SetVisible(not hide_ref)
    print "Placement finished. Press F11 to refresh."

a = ['LED9', 'LED10', 'LED11', 'LED12', 'LED13', 'LED14', 'LED15', 'LED16', 'LED17', 'LED18', 'LED19', 'LED20', 'LED21', 'LED22', 'LED23', 'LED24']
b = ['LED1', 'LED2', 'LED3', 'LED4', 'LED5', 'LED6', 'LED7', 'LED8']
center = [3937.00787, 3937.00787]
place_circle(a, 0, center, 750, 0, False)
place_circle(b, 0, center, 400, 0, False)
