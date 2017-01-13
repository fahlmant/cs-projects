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
double = undefined

-- | Is this integer zero?
isZero = undefined

-- | Is this integer non-zero?
isNonZero = undefined

-- | Computes the average of two floating point numbers.
avg = undefined

-- | Uses avg to compute half of a floating point number.
half = undefined


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
safeDiv = undefined

-- | Add two results.
addResults = undefined

-- | Get the integer from an OK result, or return 0 on an error.
fromResult = undefined



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
listLength = undefined

-- | Compute the sum of the integers in a list.
listSum = undefined


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
length = undefined

-- | Compute the sum of an integer list.
sum = undefined

-- | Compute the product of the elements in a list.
product = undefined

-- | Double all the elements in an integer list.
doubleAll = undefined

-- | Flip all of the boolean values in a boolean list.
notAll = undefined


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
