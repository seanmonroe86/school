(*	Student: Sean Monroe
	PID:	 1571224
	Class:	 COP 4555
	Assignment 1
	All code written in this assignment is my own. *)

//============= 1. Fraction addition and multiplication =======================//
// Takes a tuple - if second element 0, return first. Else, recurse with modulus.
let rec gcd = function
|(a, 0) -> a
|(a, b) -> gcd (b, a % b)

// Simplifies a fraction using the GCD of numer-/denominator.
let simp (a, b) =
 let neg g = function
 |(a, b) when (g < 0) -> (-a / g, -b / g)
 |(a, b) -> (a / g, b / g)
 neg (gcd (a, b)) (a, b)

// Organizes algorithm for accurate fraction addition, and simplifies it.
let (.+) (ax, ay) (bx, by) =
 simp ((ax * by) + (ay * bx), ay * by)

// Organizes algorithm for fraction multiplication, and simplifies it.
let (.*) (ax, ay) (bx, by) =
 simp (ax * bx, ay * by)



//================= 2. Reversal of a list's sublists =========================//
// One-line function to reverse lists within a list with anonymous function.
let revlists xs = List.map (fun x -> List.rev x) xs



//======================== 3. List interleave ================================//
// If any empty lists, return the other list. With two nonempty lists, cons the
//  head of the first to the head of the second, then recurse on the remainder.
let rec interleave = function
|([], ys) -> ys
|(xs, []) -> xs
|(x::xs, y::ys) -> x :: y :: interleave (xs, ys)



//============================== 4. List cutter ==============================//
// Helper function for gencut, to use output of recursion.
let assemble x (xs, ys) = (x::xs, ys)

// If n is 0, return an empty list with the remainder. If list is empty, return
//  two empty lists. Else return the head of the list cons first element, and
//  tail of list.
(*let rec gencut = function
|(0, xs) -> ([], xs)
|(_, []) -> ([], [])
|(n, x::xs) -> assemble x (gencut ((n - 1), xs))
*)
let rec gencut = function
|(0, xs) -> ([], xs)
|(_, []) -> ([], [])
|(n, x::xs) -> let (ys, zs) = gencut (n - 1, xs)
               (x::ys, zs)
// Calculate half-length of list, and call gencut. If list isn't even, return
//  empty lists.
let cut xs =
 let gen = function
 |odd when ((odd % 2) <> 0) -> ([],[])
 |eve -> gencut (eve / 2, xs)
 gen (List.length xs)



//==== 5. List 'perfect shuffle' =======//
// Simple call of interleaving a cut deck.
let shuffle xs = interleave (cut xs)



//==================== 6. List 'worst shuffle' ==========================//
// Recursive accumulator to shuffle a deck until it equals the target deck
//  and return accumulator value.
let countaux (ds, ts) =
 let rec accumulator = function
 |(_, []) -> -2
 |(acc, xs) when (xs = ts) -> acc
 |(acc, xs) -> accumulator (acc + 1, shuffle xs)
 accumulator (0, ds)

// Call countaux on a deck size n, but ensure it doesn't return 0 by
//  shuffling input deck once, and add that shuffle to the final counter.
let countshuffles = function
|0 -> 0
|n -> (countaux (shuffle [1 .. n], [1 .. n])) + 1



//========================= Test Cases =========================//

let revList1 = [[0;1;2];[3;4;5];[6;7;8]]
let revList2 = [["a";"b";"c"];["d";"e";"f"];["g";"h";"i"]]

let intList11 = [1;3;5;7]
let intList12 = [2;4;6;8]
let intList21 = ["one";"three";"five"]
let intList22 = ["two";"four";"six";"eight";"ten"]

printfn ""
printfn "Sean Monroe - 1571224 - F# Assignment 1"

printfn "1) Fraction addition and multiplication:"
printfn "   (-1,2) .+ (1,4) = %A" ((-1,2) .+ (1,4))
printfn "   (1,2) .* (-3,4) = %A" ((1,2) .* (-3,4))
printfn "   (1,2) .+ (-1,4) .* (3,4) .+ (1,2) = %A"
 ((1,2) .+ (-1,4) .* (3,4) .+ (1,2))
printfn "   (4,13) .+ (3,-5) .* (3,4) .+ (7,17) .* (11, 12) = %A"
 ((4,13) .+ (3,-5) .* (3,4) .+ (7,17) .* (11,12))
printfn ""

printfn "2) Reversal of sub-lists in lists:"
printfn "   revlists [[0;1;2];[3;4;5];[6;7;8]] = %A"
 (revlists revList1)
printfn "   revlists [[\"a\";\"b\";\"c\"];[\"d\";\"e\";\"f\"];[\"g\";\"h\";\"i\"]] = %A"
 (revlists revList2)
printfn ""

printfn "3) Interleaving two lists together:"
printfn "   interleave ([1;3;5;7],[2;4;6;8]) = %A"
 (interleave (intList11,intList12))
printfn "   interleave ([1;3;5;7],[2;4;6;8]) = %A"
 (interleave (intList21,intList22))
printfn ""

printfn "*** Lists for any cutting functions and their derivatives"
printfn "***  assume even lists. Therefore odd ones are rejected"
printfn "***  and replaced with empty lists. Empty lists and -1 will"
printfn "***  be the standard error for odd lists.\n"

printfn "4) Cutting an even list into equal lists:"
printfn "   cut [1..10] = %A" (cut [1..10])
printfn "   cut [1..30] = %A" (cut [1..30])
printfn "   cut [1..9] = %A" (cut [1..9])
printfn ""

printfn "5) Shuffling a list with one perfect 'out' shuffle:"
printfn "   shuffle [1..10] = %A" (shuffle [1..10])
printfn "   shuffle [1..52] = %A" (shuffle [1..52])
printfn "   shuffle [1..23] = %A" (shuffle [1..23])
printfn ""

printfn "6) Count the number of perfect shuffles to restore a deck:"
printfn "   countshuffles 4 = %d" (countshuffles 4)
printfn "   countshuffles 52 = %d" (countshuffles 52)
printfn "   countshuffles 17 = %d" (countshuffles 17)
printfn ""


