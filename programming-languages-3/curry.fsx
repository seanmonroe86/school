(*	Student: Sean Monroe
	PID:	 1571224
	Class:	 COP 4555
	Assignment 2 - Recursion
	All code written in this assignment is my own. *)

//===================== 1. Inner Vector Product =============================//
// Check for either list to be empty and return 0.
// Otherwise multiply both list heads, and add the result to
//  the remainder of the lists being multiplied.
let rec inner xs = function
 |[] -> 0
 |_ when (xs = []) -> 0
 |y::ys -> ((List.head xs) * y) + (inner (List.tail xs) ys)



//======================== 2. Matrix Product ================================//
// Begin with transpose from Assignment 2.
// To multiply a matrix, one must repeat these actions:
//  - generate a product vector from multiplying two vectors
//  - sum the elements of a product vector and return an integer
//	- every row of matrix A corresponds to a row in solution matrix
//	- every column of matrix B (or row of transposed matrix B)
//	   corresponds to a column in solution matrix
// To do this, transpose B. For each row in A: cons the product vector's
//  sum with each row of B to a list, and cons this list to the recursive
//  call on multiply with the remainder of A to the whole of B.
let rec transpose = function
 |[] -> failwith "Transpose failed: Not a matrix.\n"
 |x::xs when (List.isEmpty x) -> []
 |M -> (List.map List.head M) :: (transpose (List.map List.tail M))

let rec multiply (A, B) =
 let rec prodRow = function
  |(_, []) -> []
  |(x, y::ys) -> (inner x y) :: (prodRow (x, ys))
 match A with
  |[] -> []
  |_ when (B = []) -> []
  |q::qs -> (prodRow (q, transpose B)) :: multiply (qs, B)



//====================== 3. Flatten Complexity ==============================//
// Flatten1
// Being a curried function using the first fold function with the Union "@"
//  operator, the recursion's location relative to the union operation is
//  important. The complexity of any union operation is O(n) where n is the
//  size of the first list operand. Flatten1 uses fold, and the recursion is
//  placed as the first operand in the unions. The complexity of the fold
//  recursion is O(n) where n is the length of the input list. Combined, for a
//  list of n lists of length 1, e.g. L = [[1];[2];...;[n]], to be folded, 
//  flatten1 L has a complexity of O(n^2).
//
// Flatten2
// Just as flatten1, using the union operator has flatten2's complexity
//  determined by the location of the recursion taking place relative to the
//  union operator. In flatten2, it's the second operand. This complexity is
//  O(n) as it's based on the size of the input list. The first operand of the
//  union still determinds the complexity of union, so union itself adds an
//  additional O(n) complexity. Combined, flatten2 has a total complexity of
//  O(n + n) or just O(n).
//
//  Experimentally this is clear. At n = 10000, flatten1 will take several
//  seconds compared to flatten2's fraction of a millisecond.
let rec fold f a = function
 |[] -> a
 |x::xs -> fold f (f a x) xs

let rec foldBack f xs a =
 match xs with
  |[] -> a
  |y::ys -> f y (foldBack f ys a)

let flatten1 xs = fold (@) [] xs
let flatten2 xs = foldBack (@) xs []

let rec split = function
 |[] -> []
 |x::xs -> [x] :: split xs



//====================== 4. Twice Composition ===============================//
// Two functions defined that will act together for demonstrating this problem
// in the testing section.
let twice f = f << f
let othertwice f = (fun x -> f (f x))
let successor n = n + 1

// It is demonstrated that for k twices in twice twice ... twice successor 0,
// an explicit alternative is k repetitions of 2.0 ** 2.0 ** ... ** 2.0.
// A recursive function can be made to replicate the math of the explicit form
// of multiple twice functions called on successor 0.
let rec exptwice = function
 |0 -> 1.0
 |n -> 2.0 ** (exptwice (n - 1))

// It should be noted that at k = 5, there are more than 20 thousand digits,
// and F# will complain about something called 'infinity' when attempting this
// explicity with floats, and will right out crash when attempting it
// recursively.



//====================== 5. Armstrong Numbers ===============================//
// An anytype stream used later to create an Armstrong number stream.
type 'a stream = CON of 'a * (unit -> 'a stream)

// Tests if n is an Armstrong number using interior functions to break
//  an integer into a list of its digits (ignoring leading 0s), and
//  to add the cubes of integers in a list.
let isarmstrong n =
 let rec cubes = function
  |[] -> 0
  |x::xs -> (x * x * x) + (cubes xs)
 let rec digits = function
  |0 -> []
  |i -> (digits (i / 10)) @ [i % 10]
 n = cubes (digits n)

// Returns the Armstrong number AFTER 'a'. If 'a' is itself an Armstrong
//  number, it returns the Armstrong number after it. This is to simplify
//  the stream function; (nextarm a) can be used, rather than
//  (nextarm ((nextarm a) + 1)).
let nextarm a =
 let rec next n =
  if (isarmstrong n) then n
  else next (n + 1)
 if (isarmstrong a) then next (a + 1)
 else next a

// The Armstrong number stream. n is the starting point of the search
// for Armstrong numbers. A stream of all of them will have n be -1.
let rec armstrong n = CON(nextarm n, fun() -> armstrong(nextarm n))
let armstrongnums = armstrong -1

// Generic take function for streams - makes a list of first k elements
//  in the given stream.
let rec take k (CON(a, ans)) =
 match k with
  |0 -> []
  |_ -> a :: (take (k - 1) (ans()))

// Generic drop function for streams - returns a new stream that is missing
//  the first k elements of the old stream.
let rec drop k (CON(a, ans)) =
 match k with
  |0 -> CON(a, ans)
  |_ -> drop (k - 1) (ans())



//============================= Testing =====================================//
printfn "\n1) Inner Vector Sum-of-Products"
printfn "inner [1..3] [4..6] = %i"
 (inner [1..3] [4..6])
printfn "inner [1..10] [11..20] = %i"
 (inner [0..10] [11..20])
printfn "inner [1;1;1;1;1] [1;1;1;1;1] = %i"
 (inner [1;1;1;1;1] [1;1;1;1;1])



printfn "\n2) Matrix Multiplication"
printfn "multiply ([[1..3];[4..6]], [[0;1];[3;2];[1;2]]) =\n %A\n"
 (multiply ([[1..3];[4..6]], [[0;1];[3;2];[1;2]]))
printfn "multiply ([[1..3];[4..6]], [[0..6];[3..9];[2..8]]) =\n %A\n"
 (multiply ([[1..3];[4..6]], [[0..6];[3..9];[2..8]]))
printfn "multiply ([[1];[2]], [[1..10]]) =\n %A\n"
 (multiply ([[1];[2]], [[1..10]]))



printfn "\n3) Complexity Analysis of Fold, FoldBack, and Flatten\n"
printfn "	The asymptotic complexity analysis is within the comments"
printfn " of this code. The experimental data and output follows."

printfn "Testing split [1..10]: %A" (split [1..10])
printfn "Testing flatten1 (split [1..10])): %A" (flatten1 (split [1..10]))
printfn "Testing flatten2 (split [1..10])): %A" (flatten2 (split [1..10]))

printfn "\ntestQuick = split [1..100]"
printfn "testShort = split [1..5000]"
printfn "testLong  = split [1..10000]"

let testQuick = split [1..100]    // 100
let testShort = split [1..5000]   // 5K
let testLong  = split [1..10000]  // 10K

printfn "\nflatten1 testQuick start----"
#time "on"
let resultQuick1 = flatten1 testQuick
#time "off"
printfn "flatten1 testQuick end------\n"

printfn "flatten1 testShort start----"
#time "on"
let resultShort1 = flatten1 testShort
#time "off"
printfn "flatten1 testShort end------\n"

printfn "flatten1 testLong start-----"
#time "on"
let resultLong1 = flatten1 testLong
#time "off"
printfn "flatten1 testLong end-------\n"

printfn "flatten2 testQuick start----"
#time "on"
let resultQuick2 = flatten2 testQuick
#time "off"
printfn "flatten2 testQuick end------\n"

printfn "flatten2 testShort start----"
#time "on"
let resultShort2 = flatten2 testShort
#time "off"
printfn "flatten2 testShort end------\n"

printfn "flatten2 testLong start-----"
#time "on"
let resultLong2 = flatten2 testLong
#time "off"
printfn "flatten2 testLong end-------\n"



printfn "\n4) Twice Composition\n"
printfn "  Demonstrating (twice (twice (... (twice successor)))...) 0"
printfn "   is equal to 2.0**k for k 'twice' functions used:"
printfn "   (twice (twice (twice successor))) 0 = %d"
 ((twice (twice (twice successor))) 0)
printfn "   2.0 ** 3.0 = %f" (2.0 ** 3.0)
printfn "   (twice (twice (twice (twice (twice successor))))) 0 = %d"
 ((twice (twice (twice (twice (twice successor))))) 0)
printfn "   2.0 ** 5.0 = %f" (2.0 ** 5.0)
printfn "  Demonstrating twice twice ... twice successor 0 is equal"
printfn "   to 2.0**2.0...**2.0 for k 'twice' functions used:"
printfn " --twice twice twice successor 0 = %d"
 (twice twice twice successor 0)
printfn "   2.0 ** 2.0 ** 2.0 = %f" (2.0 ** 2.0 ** 2.0)
printfn " --twice twice twice twice successor 0 = %d"
 (twice twice twice twice successor 0)
printfn "   2.0 ** 2.0 ** 2.0 ** 2.0 = %f"
 (2.0 ** 2.0 ** 2.0 ** 2.0)
printfn "  Demonstrating the function 'exptwice k' to be equivalent"
printfn "   to k repetitions of twice twice ... twice successor 0:"
printfn "   exptwice 0 = %f" (exptwice 0)
printfn "   exptwice 1 = %f" (exptwice 1)
printfn "   exptwice 2 = %f" (exptwice 2)
printfn " --exptwice 3 = %f" (exptwice 3)
printfn "   exptwice 4 = %f" (exptwice 4)
printfn " --exptwice 5 = %f" (exptwice 5)



printfn "\n5) Armstrong Number Stream"
printfn "2nd, 3rd, 4th A-Nums: take 3 (drop 1 armstrongnums) = %A"
 (take 3 (drop 1 armstrongnums))
printfn "4th, 5th A-Num: take 2 (drop 3 armstrongnums) = %A"
 (take 2 (drop 3 armstrongnums))
printfn "A-Nums 1-5: take 5 (drop 0 armstrongnums) = %A"
 (take 5 (drop 0 armstrongnums))

