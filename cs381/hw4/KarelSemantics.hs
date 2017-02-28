--ONIDS:
-- fahlmant
-- tschuye

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
stmt Shutdown     _ _ r = Done r
stmt Move         _ w (p, c, i) = let x = neighbor c p
                                  in if (isClear x w)
                                        then OK w (setPos x (p, c, i))
                                        else Error ("Blocked at: " ++ show x)
stmt PickBeeper   _ w r = let p = getPos r
                          in if hasBeeper p w
                                then OK (decBeeper p w) (incBag r)
                                else Error ("No beeper to pick at: " ++ show p)
stmt PutBeeper     _ w r = let p = getPos r
                           in if isEmpty r
                                 then Error ("No beeper to put.")
                                 else OK (incBeeper p w) (decBag r)
stmt (Turn d)      _ w (p, c, i) = let r' = setFacing (cardTurn d c) (p, c, i)
                                   in OK w r'
stmt (Call m)      d w r = case lookup m d of
                             Just m' -> stmt m' d w r
                             Nothing -> Error ("Undefined macro: " ++ m)
stmt (Iterate 0 _) _ w r = OK w r
stmt (Iterate i s) d w r = case stmt s d w r of
                           OK w' r' -> stmt (Iterate (i-1) s) d w' r'
                           otherwise -> otherwise
stmt (If t s1 s2 ) d w r = if test t w r
                              then stmt s1 d w r
                              else stmt s2 d w r
stmt (While t s  ) d w r = if test t w r
                               then case stmt s d w r of
                                 OK w' r' -> stmt (While t s) d w' r'
                                 otherwise -> otherwise
                            else OK w r
stmt (Block []   )  _ w r = OK w r
stmt (Block (x:xs)) d w r = case stmt x d w r of
                            OK w' r' -> stmt (Block xs) d w' r'
                            otherwise -> otherwise
-- | Run a Karel program.
prog :: Prog -> World -> Robot -> Result
prog (m,s) w r = stmt s m w r
