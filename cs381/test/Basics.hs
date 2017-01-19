module Basics where

-- Don't worry about this line. It's just hiding some functions that are
-- usually imported by default, but which I'm defining my own versions of
-- in this intro file.
import Prelude hiding (length,sum,product,map,foldr)


---------------------
-- Introduce Tools --
---------------------

-- * GHCi commands
--     :help, :load, :reload, :quit, :type, :info
-- * Hoogle
-- * doctest


---------------------
-- Getting Started --
---------------------

-- In GHCi:
--  * basic data types (Bool, Int, Float)
--  * numeric and boolean operators
--  * if-then-else expressions
--  * let-expressions


---------------------
-- Basic Functions --
---------------------

-- * defining and applying functions
-- * pattern matching
-- * partial application


-- | Add an integer to itself.
double :: Int -> Int
double x = x + x

-- | Is this integer zero?
isZero :: Int -> Bool
-- isZero x = x == 0
isZero 0 = True
isZero x = False


-- | Is this integer non-zero?
isNonZero :: Int -> Bool
--isNonZero 0 = False
--isNonZero _ = True

--isNonZero x = not(isZero x), equivalent to the next line
isNonZero = not . isZero

-- | Computes the average of two floating point numbers.
avg :: Float -> Float -> Float
avg x y = (x + y)/2.0

-- | Uses avg to compute half of a floating point number.
half :: Float -> Float
--half x = avg x 0
half = avg 0


-- In GHCi:
--  * infix vs. prefix application: operators are just functions!
--    * (+) x y = x + y
--    * avg x y = x `avg` y
-- * anonymous functions


----------------------
-- Basic Data Types --
----------------------

-- * a data type definition consists of:
--   * a new type name
--   * a set of cases, each with:
--     * a data constructor
--     * zero or more arguments
-- * more pattern matching
--   * top-level and case-expressions

-- | An example data type with two cases.
data Result = OK Int | Error
  deriving (Eq,Show)

-- | Safely divide two integers.
safeDiv :: Int -> Int -> Result
safeDiv _ 0 = Error
safeDiv x y = OK (x `div` y)

-- | Add two results.
addResults :: Result -> Result -> Result
addResults (OK x) (OK y) = OK (x+y)
addResults _      _      = Error
-- r1 r2 = case r1 of
--           OK x -> case r2 of
--                     OK y -> OK (x+y)
--                     Error -> Error
--                  Error -> Error
-- r1 r2 = case (r1, r2) of 
--           (OK x, OK y) -> OK (x+y)
--           _            -> Error


-- | Get the integer from an OK result, or return 0 on an error.
fromResult :: Result -> Int
fromResult (OK x) = x
fromResult Error = 0



-- The definition of Bool in the Haskell Prelude looks like this:
--   
--   data Bool = False | True



---------------
-- Recursion --
---------------

-- * recursive data type definitions
-- * recursive functions

-- | An example of a recursive data type.
data List = Nil
          | Cons Int List
  deriving (Eq,Show)

-- | Compute the length of a list.
listLength :: List -> Int
listLength Nil = 0
listLength (Cons h t) = 1 + listLentgh t

-- | Compute the sum of the integers in a list.
listSum :: List -> Int
listSum Nil = 0
listSum (Cons h t) = h + listSum t

-------------------
-- Haskell Lists --
-------------------

-- * Haskell's built-in list and string types
--   * cons, nil, and syntactic sugar
--   * more recursive functions

-- The definition of String in the Haskell Prelude looks like this:
--
--   type String = [Char]


-- | Compute the sum of a list.
length :: [a] -> Int
length [] = 0
length (_:t) = 1 + length t

-- | Compute the sum of an integer list.
sum :: [Int] -> Int
sum []  = 0
sum (h:t) = h + sum t

-- | Compute the product of the elements in a list.
product :: [Int] -> Int
product [] = 1
product (h:t) = h * product t

-- | Double all the elements in an integer list.
doubleAll :: [Int] -> [Int]
doubleAll [] = []
doubleAll (h:t) = (2 * h) : doubleAll t

-- | Flip all of the boolean values in a boolean list.
notAll :: [Bool] -> [Bool]
notAll [] = []
notAll (h:t) = not h : notAll t


----------------------------
-- Higher-Order Functions --
----------------------------

-- * map and foldr


-- | Map a function over the elements in a list.
map :: (a -> b) -> [a] -> [b]
map = undefined

-- | Reimplement doubleAll using map.
doubleAll' :: [Int] -> [Int]
doubleAll' l = undefined

-- | Reimplement notAll using map.
notAll' :: [Bool] -> [Bool]
notAll' l = undefined

-- | Fold a function over the elements of a list.
simpleFold :: (a -> a -> a) -> a -> [a] -> a
simpleFold = undefined

-- | Fold a function over the elements in a list, allowing the type of the
--   accumulated value to differ from the elements in the list.
foldr :: (a -> b -> b) -> b -> [a] -> b
foldr = undefined

-- | Reimplement sum using foldr.
sum' :: [Int] -> Int
sum' l = undefined

-- | Reimplement product using foldr.
product' :: [Int] -> Int
product' l = undefined
