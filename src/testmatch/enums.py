from enum import Enum


class Arm(str, Enum):
    left = "left"
    right = "right"


class BowlType(str, Enum):
    med = "med"
    med_fast = "med_fast"
    fast_med = "fast_med"
    fast = "fast"
    offbreak = "offbreak"
    legbreak = "legbreak"
