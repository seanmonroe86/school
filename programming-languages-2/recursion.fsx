(*	Student: Sean Monroe
	PID:	 1571224
	Class:	 COP 4555
	Assignment 2 - Recursion
	All code written in this assignment is my own. *)

//======================= 1. Cartesian Product ==============================//
let rec cartesian (l1, l2) =
 let rec loop = function
 |([], _) -> []
 |(x::xs, y) -> (x, y) :: loop (xs, y)
 match l2 with
 |[] -> []
 |y::ys -> loop (l1, y) @ cartesian (l1, ys)



//=========================== 2. Powerset ===================================//
let rec powerset = function
|[] -> [[]]
|x::xs -> let l = powerset xs
          l @ List.map (fun s -> x::s) l



//===================== 3. Matrix Transposition =============================//
let rec transpose = function
|[] -> failwith "Not a matrix.\n"
|x::xs when (List.isEmpty x) -> []
|M -> (List.map List.head M) :: (transpose (List.map List.tail M))



//======================== 4. Simple Sort Analysis ==========================//
// Step 1: The base cases are of type 'a list, which is the correct type for
// 		   the other recursive calls. They are sufficient to avoid any
// 		   conditions of the incoming list: a list of length 1 will cause an
// 		   error with the case "x1::x2::xs", so it must return the input list.
// Step 2: The non-base case is incorrectly implemented. After a comparison,
// 		   it concatenates the lesser of the first two elements of the input
// 		   list, then recurses to the remaining list. This will fail to sort a
// 		   whole list, instead only placing the lowest of the two first
// 		   elements into its place in the unsorted list, and continuing with
// 		   the next two elements (if there are any left).
// Step 3: The non-base case is calling the recursive function on a
// 		   'smaller'/'simpler' input, based on the previous input. It's obvious
// 		   when the pattern matching breaks an incoming list down to the first
// 		   two elements of the input list and the remainder of the list; the
// 		   remainder being that which is used as input for the next recursive
// 		   call.



//======================== 5. Merge Sort Analysis ===========================//
// merge
// Step 1: The base cases are of type 'a list, which is the correct type
//         required by the other recursive calls. The cases cover both an empty
//         first tuple element, and an empty second tuple element before
//         proceeding to the non-base cases.
// Step 2: The non-base case is correctly implemented, with a comparison
//         resulting in the lesser of two heads of already-recursively-sorted
//         lists being cons'd to the head of a new sorted list.
// Step 3: The non-base case is operating on a 'smaller'/'simpler' input, with
//         the recursive call being made on one full list and one less-one
//         list, eventually driving it to one of the empty list base cases.
//
// split
// Step 1: The base cases are of the return type 'a list * 'a list, and cover
//         the patterns expected to end the recursion: one of the tuple
//         elements being an empty list should return the other element. Two
//         empty lists are automatically covered by the first pattern match,
//         returning a blank list.
// Step 2: The non-base case is also of return type 'a list * 'a list. The
//         goal of split being ultimately to reduce a single list of any size
//         into lists each containing a single element, the return value is
//         correct.
// Step 3: The non-base case is operating recursively on a smaller input; with
//         an input list of length N, it recursively calls on a list of length
//         N-2.
//
// mergesort
// Step 1: The base cases are inadequate. While the empty list is accounted
//         for with a return of an empty list making the function 'a list -> 'a
//         list so far, it lacks the case of a single-element list. More notes
//         on the additional base case for the correction are made later.
// Step 2: The non-base case appears to return the correct type, apparently an
//         'a list type, however a note on this is made later. Otherwise it
//         correctly calls upon split, merge and mergesort and returns a list
//         type.
// Step 3: The non-base case makes recursive calls providing input that will
//         allow an infinite loop in the case of odd-length lists. This occurs
//         when split is called to divide the current list into equal-length
//         lists, with an additional element in the first element of the tuple
//         in the case of odd-length strings. However, when mergesort is called
//         upon a single-element list, it continues to attempt to split it,
//         further creating another single-element list * empty list tuple.
//         This additionally has the effect of isolating the input from the
//         output of mergesort, causing the type to become 'a list -> 'b list
//         when 'b:comparable, rather than 'a list -> 'a list when
//         'a:comparable.
//
// Correcting mergesort:
//         The erroneous typing as well as the infinite loop can be fixed
//         simply by adding in another base case to mergesort:
//         
//           |[a] -> [a]
//
//         This will prevent infinite recursive calls on single-element lists
//         and provide a hard-coded link between the input and output type of
//         mergesort, correctly having it inferred as being
//
//           'a list -> 'a list when 'a:comparable

let rec merge = function
|([], ys) -> ys
|(xs, []) -> xs
|(x::xs, y::ys) -> if x < y then x :: merge (xs, y::ys)
                   else y :: merge (x::xs, ys)

let rec split = function
|[] -> ([], [])
|[a] -> ([a], [])
|a::b::cs -> let (M, N) = split cs
             (a::M, b::N)

let rec mergesort = function
|[] -> []
|[a] -> [a]
|L -> let (M, N) = split L
      merge (mergesort M, mergesort N)



//========================= 6. Curried Functions ============================//
// Curry-fication function
// val curry : f:('a -> 'b) -> x:'a -> 'b
let curry f = (fun x -> f x)

// Uncurry-fication function
// val uncurry : f:('a -> 'b -> 'c) -> x:'a -> y:'b -> 'c
let uncurry f x = (fun y -> f x y)



//================================ Testing ==================================//

printfn "1. Cartesian Test"
printfn "cartesian ([\"a\";\"b\";\"c\"],[1;2]) = %A"
 (cartesian (["a";"b";"c"],[1;2]))
printfn "cartesian ([],[]) = %A"
 (cartesian ([],[]))
printfn "cartesian ([],[\"a\"]) = %A"
 (cartesian ([],["a"]))

printfn "\n2. Powerset Test"
printfn "powerset [1;2;3] = %A"
 (powerset [1;2;3])
printfn "powerset [\"a\";\"b\";\"c\"] = %A"
 (powerset ["a";"b";"c"])
printfn "powerset [] = %A"
 (powerset [])
printfn "powerset [999] = %A"
 (powerset [999])

printfn "\n3. Transpose Test"
printfn "transpose [[1;2;3];[4;5;6]] = %A"
 (transpose [[1;2;3];[4;5;6]])
printfn "transpose [[\"a\";\"b\";\"c\"];[\"x\";\"y\";\"z\"]] = %A"
 (transpose [["a";"b";"c"];["x";"y";"z"]])
printfn "transpose [[];[]] = %A"
 (transpose [[];[]])

printfn "\n5. Mergesort Test"
printfn "merge ([1;2;3],[4;5;6]) = %A"
 (merge ([1;2;3],[4;5;6]))
printfn "merge ([\"a\";\"b\";\"c\"],[\"x\";\"y\";\"z\"]) = %A"
 (merge (["a";"b";"c"],["x";"y";"z"]))
printfn "split [1;2;3;4;5;6] = %A"
 (split [1;2;3;4;5;6])
printfn "split [\"a\";\"b\";\"c\";\"x\";\"y\";\"z\"] = %A"
 (split ["a";"b";"c";"x";"y";"z"])
printfn "mergesort [3;4;5;8;9;876;5;6;65;434;4;678;8;6;432;2;46;90] = %A"
 (mergesort [3;4;5;8;9;876;5;6;65;434;4;678;8;6;432;2;46;90])
printfn "mergesort [\"a\";\"t\";\"aa\";\"e\";\"c\";\"n\";\"m\"] = %A"
 (mergesort ["a";"t";"aa";"e";"c";"n";"m"])
printfn "mergesort [] = %A"
 (mergesort [])
printfn "mergesort [999] = %A"
 (mergesort [999])

printfn "\n6. Curry/Uncurry Test"
printfn "let plus = uncurry (+)"
let plus = uncurry (+)
printfn "plus 2 3 = %A" (plus 2 3)
printfn "let cplus = curry plus"
let cplus = curry plus
printfn "let plus3 = cplus 3"
let plus3 = cplus 3
printfn "plus3 10 = %A" (plus3 10)

