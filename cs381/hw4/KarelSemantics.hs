module KarelSemantics where

import Prelude hiding (Either(..))
import Data.Function (fix)

import KarelSyntax
import KarelState


-- | Valuation function for Test.
test :: Test -> World -> Robot -> Bool
test (Not    t) w  r        = not(test t w r)
test (Facing c) w  r        = c == (getFacing r)
test (Clear  d) w (p, c, i) = isClear (neighbor (cardTurn d c) p) w
test (Beeper  ) w  r        = hasBeeper (getPos r) w
test (Empty   ) _  r        = isEmpty r

-- | Valuation function for Stmt.
stmt :: Stmt -> Defs -> World -> Robot -> Result
stmt Shutdown   _ _ r = Done r
stmt Move       _ w (p, c, i) = let x = neighbor c p
                                in if (isClear x w)
                                      then OK w (setPos x (p, c, i))
                                      else Error ("Can't move there")
stmt PickBeeper _ w r = let p = getPos r
                        in if hasBeeper p w
                              then OK (decBeeper p w) (incBag r)
                              else Error ("No beeper to pick at: " ++ show p)
stmt PutBeeper  _ w r = let p = getPos r
                        in if isEmpty r
                              then Error ("No beeper to put")
                              else OK (incBeeper p w) (decBag r)
stmt (Turn d)      _ w (p, c, i) = let r' = setFacing (cardTurn d c) (p, c, i)
                                   in OK w r'
stmt (Call m)      _ _ _ = undefined
stmt (Iterate i s) _ _ _ = undefined
stmt (If t s1 s2 ) _ _ _ = undefined
stmt (While t s  ) _ _ _ = undefined
stmt (Block (x:xs)) _ _ _ = undefined

-- | Run a Karel program.
prog :: Prog -> World -> Robot -> Result
prog (m,s) w r = stmt s m w r
