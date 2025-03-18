## GDtoIG
This is a proof-of-concept of  a tool that converts Geometry Dash level data to an Impossible Game level.

Only a few object IDs are defined, therefore **most levels will not convert properly**. The Impossible Game also doesn't support object rotation, and its color triggers are extreme limited. Obviously GD-specific mechanics such as portals, orbs, and pads aren't and will never be supported.

## Usage
Take a **fully decoded** Geometry Dash level string, and place it in a plaintext file on line 1. Then run the following

    gdtoig yourfile.txt
   
  where "yourfile.txt" is whatever file you placed the GD level file in. The program will then output an Impossible Game level folder with the same name.

## Credits
I referenced the level "Object IDs New" (99784974) by Colon to get the object IDs needed for this project. I also referenced his video "[How I Made a Geometry Dash Website](https://www.youtube.com/watch?v=tC-TZX0AAck) for basic information on GD's file format.

I used commit 21f0e59 of [libImpossibleLevel](https://github.com/MysticAx0lotl/libImpossibleLevel) additionally
