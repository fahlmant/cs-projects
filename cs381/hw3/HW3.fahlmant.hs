-- Taylor Fahlman (fahlmant)
-- Evan Tschuy (tschuye)

module HW3 where

import MiniMiniLogo
import Render


--
-- * Semantics of MiniMiniLogo
--

-- NOTE:
--   * MiniMiniLogo.hs defines the abstract syntax of MiniMiniLogo and some
--     functions for generating MiniMiniLogo programs. It contains the type
--     definitions for Mode, Cmd, and Prog.
--   * Render.hs contains code for rendering the output of a MiniMiniLogo
--     program in HTML5. It contains the types definitions for Point and Line.

-- | A type to represent the current state of the pen.
type State = (Mode,Point)

-- | The initial state of the pen.
start :: State
start = (Up,(0,0))

-- | A function that renders the image to HTML. Only works after you have
--   implemented `prog`. Applying `draw` to a MiniMiniLogo program will
--   produce an HTML file named MiniMiniLogo.html, which you can load in
--   your browswer to view the rendered image.
draw :: Prog -> IO ()
draw p = let (_,ls) = prog p start in toHTML ls


-- Semantic domains:
--   * Cmd:  State -> (State, Maybe Line)
--   * Prog: State -> (State, [Line])


-- | Semantic function for Cmd.
--
--   >>> cmd (Pen Down) (Up,(2,3))
--   ((Down,(2,3)),Nothing)
--
--   >>> cmd (Pen Up) (Down,(2,3))
--   ((Up,(2,3)),Nothing)
--
--   >>> cmd (Move 4 5) (Up,(2,3))
--   ((Up,(4,5)),Nothing)
--
--   >>> cmd (Move 4 5) (Down,(2,3))
--   ((Down,(4,5)),Just ((2,3),(4,5)))
--
cmd :: Cmd -> State -> (State, Maybe Line)
cmd (Pen Down) (_,    p) = ((Down, p    ), Nothing        )
cmd (Pen Up)   (_,    p) = ((Up,   p    ), Nothing        )
cmd (Move x y) (Up,   p) = ((Up,   (x,y)), Nothing        )
cmd (Move x y) (Down, p) = ((Down, (x,y)), Just (p, (x,y)))


-- | Semantic function for Prog.
--
--   >>> prog (nix 10 10 5 7) start
--   ((Down,(15,10)),[((10,10),(15,17)),((10,17),(15,10))])
--
--   >>> prog (steps 2 0 0) start
--   ((Down,(2,2)),[((0,0),(0,1)),((0,1),(1,1)),((1,1),(1,2)),((1,2),(2,2))])
prog :: Prog -> State -> (State, [Line])
prog []     s = (s, [])
prog (x:xs) s = case cmd x s of
    (s', Just x') -> (\(s, xs) -> (s, x':xs)) $ prog xs s'
    (s', Nothing) -> prog xs s'

--
-- * Extra credit
--

boxN :: Int -> Int -> Int -> Prog
boxN h x y = [Pen Up, Move x y, Pen Down,
           Move (x+h) y, Move (x+h) (y+h), Move x (y+h), Move x y]

drawN :: Int -> Int -> Int -> Prog
drawN h x y = [Pen Up, Move x y, Pen Down,
          Move x (y+h), Move (x+h) (y+h), Move (x+h) y]

horiz :: Int -> Int -> Int -> Prog
horiz h x y = [Pen Up, Move x y, Pen Down, Move (x+h) y]

vert :: Int -> Int -> Int -> Prog
vert h x y = [Pen Up, Move x y, Pen Down, Move x (y+h)]

-- | This should be a MiniMiniLogo program that draws an amazing picture.
--   Add as many helper functions as you want.
amazing :: Prog
amazing = boxN 5 1 4 ++ steps 1 6 4 ++ drawN 3 8 4 ++ drawN 3 11 4 ++ boxN 3 15 4 ++ steps 1 18 4
        ++ horiz 3 20 7 ++ steps 3 20 4 ++ horiz 3 20 4 ++ vert 3 24 4 ++ drawN 3 25 4
        ++ boxN 3 29 4 ++ steps 3 29 1 
