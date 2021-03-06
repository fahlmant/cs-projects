-- Taylor Fahlman (fahlmant)
-- Evan Tschuy (tschuye)

module HW2 where

import Prelude hiding (Num) --hide Num
import Text.Printf


data Cmd = SetPen Mode
         | Move Expr Expr
         | Define Macro [Var] Prog
         | Call Macro [Expr]

type Num  = Int
type Var  = String
type Macro = String
data Expr = Variable Var | Number Num | Add Expr  Expr deriving(Show)
data Mode = Up | Down
type Prog = [Cmd]

-- define line (x1, y1, x2, y2) {
--   pen up;
--   move (x1, y1);
--   pen down;
--   move (x2, y2);
-- }
line = Define "line" ["x1", "y1", "x2", "y2"] [SetPen Up, Move (Variable "x1") (Variable "y1"), SetPen Down, Move (Variable "x2") (Variable "y2")]


-- define nix (x, y, w, h) {
--   line(x,   y, x+w, y+h);
--   line(x+w, y, x,   y+h);
-- }
nix = Define "nix" ["x", "y", "w", "h"] [Call "line" [(Variable "x"), (Variable "y"), (Add (Variable "x") (Variable "w")), (Add (Variable "y") (Variable "h"))],
           Call "line" [(Add (Variable "x") (Variable "w")), (Variable "y"), (Variable "x"), (Add (Variable "y") (Variable "h"))] ]


steps :: Int -> Prog
steps 0 = []
steps n = [Call "line" [Number (n), Number (n), Number (n-1), Number (n)],
           Call "line" [Number (n-1), Number (n), Number (n-1), Number (n-1)] ] ++ steps (n-1)

macroName :: Cmd -> [Macro]
macroName (Define name _ _) = [name]
macroName _ = []

macros :: Prog -> [Macro]
macros [] = []
macros p = macroName (head p) ++ macros (tail p)


-- TODO intersperse or intercalate could make this waaay less verbose
prettyVar :: [Var] -> String
prettyVar [] = ""
prettyVar [v] = v
prettyVar v = head v ++ "," ++ prettyVar (tail v)

pretty :: Prog -> String
pretty [] = ""
pretty cmds = prettyCmd (head cmds) ++ pretty (tail cmds)

prettyTabs :: Prog -> String
prettyTabs [] = "\t"
prettyTabs [cmd] = "\t" ++ prettyCmd cmd
prettyTabs cmds = "\t" ++ prettyCmd (head cmds) ++ prettyTabs (tail cmds)

prettyExpr :: Expr -> String
prettyExpr (Variable v) = v
prettyExpr (Number n) = show n
prettyExpr (Add x y) = prettyExpr x ++ "," ++ prettyExpr y

prettyExprs :: [Expr] -> String
prettyExprs [] = ""
prettyExprs [v] = prettyExpr v
prettyExprs v = prettyExpr (head v) ++ "+" ++ prettyExprs (tail v)

prettyMode :: Mode -> String
prettyMode Up = "up"
prettyMode Down = "down"

prettyCmd :: Cmd -> String
prettyCmd (Define name varlist innerProg) = printf "define %s (%s){\n%s}\n" name (prettyVar varlist) (prettyTabs innerProg)
prettyCmd (Move e1 e2) = printf "move (%s,%s);\n" (prettyExpr e1) (prettyExpr e2)
prettyCmd (Call name exprlist) = printf "call %s (%s);\n" name (prettyExprs exprlist) -- what to do about spaces?
prettyCmd (SetPen m) = printf "pen %s;\n" (prettyMode m)


optE :: Expr -> Expr
optE (Add (Number m) (Number n)) = Number (m + n)
optE (Add m n ) = Add (optE m) (optE n)
optE e = e

optP :: Prog -> Prog
optP [] = []
