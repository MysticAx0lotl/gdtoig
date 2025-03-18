## GDtoIG
This is a proof-of-concept of  a tool that converts Geometry Dash level data to an Impossible Game level.

Only a few object IDs are defined, therefore **most levels will not convert properly**. The Impossible Game also doesn't support object rotation, and its color triggers are extremely limited. Obviously GD-specific mechanics such as portals, orbs, and pads aren't and will never be supported.

Do also note that Impossible Game's scroll speed and jump height are both very different to GD, therefore you will most definitely need to manually edit the generated level if you want anything remotely playable. IG also seems to have either an xpos limit or object limit *much* smaller than GD's, so a lot of longer levels will crash the game (even if they open properly in the editor).

Fade transitions and color changes are currently unimplemented but are planned.

## Usage
Take a **fully decoded** Geometry Dash level string, and place it in a plaintext file on line 1. Then run the following

    gdtoig yourfile.txt
   
  where "yourfile.txt" is whatever file you placed the GD level file in. The program will then output an Impossible Game level folder with the same name.

## Compiling
Simply run `make` in the same directory as the Makefile

## Credits
The level "Object IDs New" (99784974) and the video "[How I Made a Geometry Dash Website](https://www.youtube.com/watch?v=tC-TZX0AAck)", both by Colon, were extremely useful references for this project. 

I used commit 21f0e59 of [libImpossibleLevel](https://github.com/MysticAx0lotl/libImpossibleLevel) additionally
