-- Taylor Fahlman (fahlmant)
--

module HW2 where

import Prelude hiding (Num) --hide Num

data Cmd = SetPen Mode
         | Move Expr Expr
         | Define Macro [Var] Prog
         | Call Macro [Expr]

type Num  = Int
type Var  = String
type Macro = String
data Expr = Variable Var | Number Num | Pair Expr  Expr
data Mode = Up | Down
type Prog = [Cmd]

-- define line (x1, y1, x2, y2) {
--   pen up;
--   move (x1, y1);
--   pen down;
--   move (x2, y2);
-- }
line :: Num -> Num -> Num -> Num -> Prog
line x1 y1 x2 y2 = [Define "line" ["x1", "y1", "x2", "y2"] [SetPen Up, SetPen Down]]


-- define nix (x, y, w, h) {
--   line(x,   y, x+w, y+h);
--   line(x+w, y, x,   y+h);
-- }
nix :: Num -> Num -> Num -> Num -> Prog
nix x y w h = [Define "nix" ["x", "y", "w", "h"] [line x y (x+w) (y+h), line (x+w) y x (y+h)]]


