-- Taylor Fahlman (fahlmant)
--

module HW2 where

import Prelude

data Cmd = Pen Mode
         | Move Expr Expr
         | Define Macro Var Prog
         | Call Macro Expr

type Num  = Int
type Var  = String
type Macro = String
data Expr = Var | Num | Expr  Expr
data Mode = Up | Down
data Prog = Cmd Prog | Nil

