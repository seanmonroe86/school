(*	Student: Sean Monroe
	PID:	 1571224
	Class:	 COP 4555
	Assignment 2 - Recursion
	All code written in this assignment is my own. *)

//================= 1. Evaluate an Abstract Syntax Tree =====================//
type Exp =
 Num of int
 |Neg of Exp
 |Sum of Exp * Exp
 |Diff of Exp * Exp
 |Prod of Exp * Exp
 |Quot of Exp * Exp

type 'a option = None | Some of 'a

let rec evaluate o =
 let auxeval f a b =
  match evaluate a with
  |None -> None
  |Some x -> match evaluate b with
             |None -> None
             |Some 0 when (f 6 3 = 2) -> None
             |Some y -> Some (f x y)
 match o with
 |Num n -> Some n
 |Neg e -> auxeval (-) (Num 0) e
 |Sum (a, b) -> auxeval (+) a b
 |Diff (a, b) -> auxeval (-) a b
 |Prod (a, b) -> auxeval (*) a b
 |Quot (a, b) -> auxeval (/) a b



//=============================== Testing ===================================//
printfn "Evaluating an Abstract Syntax Tree\n"
printfn "evaluate (Sum (Neg (Num 5), Num 0)) = %A"
 (evaluate (Sum (Neg (Num 5), Num 0)))
printfn "evaluate (Prod (Num 3, Diff(Num 5, Num1))) = %A"
 (evaluate (Prod (Num 3, Diff(Num 5, Num 1))))
printfn "evaluate (Quot (Num 8, Sum(Num 3, Neg (Num1)))) = %A"
 (evaluate (Quot (Num 8, Sum(Num 3, Neg (Num 1)))))
printfn "evaluate (Diff (Num 3, Quot (Num 5, Prod (Num 7, Num 0)))) = %A"
 (evaluate (Diff (Num 3, Quot (Num 5, Prod (Num 7, Num 0)))))



//================== 2. Exponentiation in C-F Grammar  ======================//
// It's simple to retain the unambiguous property of the original grammar by
//  being sure any added productions don't call back to 'previous' productions,
//  as well as the following productions only being called by the inserted one.
//  This can be done by having its operands only be literals or parenthetical
//  expressions. To have a higher precedence, the exponentiation must occur
//  'later' in the chain of productions so that its operation will be evaluated
//  before being used in adjacent evaluations. With both of these constraints,
//  right-associativity is intrinsic to the production as both of its operands
//  must be fully evaluated before performing the operation itself, and its
//  operation is evaluated to a literal value before being used in the
//  remainder of the expression.
//
// E -> E+T | E-T | T
// T -> T*F | T/F | F
// F -> G^G | G
// G -> i | (E)



//======================= 3. Showing Ambiguity ==============================//
// u = if a then if b then print c else print d
// S => if E then S else S =>
//      if a then S else S =>
//      if a then if E then S else S =>
//      if a then if b then S else S =>
//      if a then if b then print E else S =>
//      if a then if b then print c else S =>
//      if a then if b then print c else print E =>
//      if a then if b then print c else print d
//
// S => if E then S =>
// 	    if a then S =>
// 	    if a then if E then S else S =>
// 	    if a then if b then S else S =>
// 	    if a then if b then print E else S =>
// 	    if a then if b then print c else S =>
// 	    if a then if b then print c else print E =>
// 	    if a then if b then print c else print d



//========================= 4. Pseudo Parser ================================//
// Using code similar to the notes, a simple addition may be added to avoid the
//   dangling ELSE ambiguity: a check within the S() function is performed
//   after eating a THEN and completing the following S(), to determine if it's
//   followed by an ELSE. If so, continue as normal - there is no ambiguity. If
//   there is no ELSE, then end the parent S() call. This way the program will
//   not terminate early due to a missing ELSE. Breaking early will guarantee
//   that no tokens will be evaluated earlier than expected. This is
//   functionally equivalent to completing all IF-THEN statements with an ELSE
//   followed by an empty code block.
//
// Some trivial code is included for some detailed error messages, showing the
//   context of the error's location as well as how many semicolons into the
//   expression the parser went, displayed in code as 'lineNum' but never
//   explicitly printed as such; it's just counting semicolons.
//
// int lineNum = 0;
// int tok = nextToken();
//
// void advance() {
//   tok = nextToken();
// }
//
// void eat(int t) {
//   if (tok == t) advance();
//   else error("%d: Invalid token type %s", lineNum, t.toString());
// }
//
// void S() {
//   switch (tok) {
//     case IF:
//       advance(); E(); eat(THEN); S();
//       if (tok != ELSE) break;
//       else { eat(ELSE); S(); break; }
//
//     case BEGIN:
//       advance(); S(); L(); break;
//
//     case PRINT: advance(); E(); break;
//
//     default:
//       error("%d: Unrecognized symbol %s", lineNum, tok.toString());
//   }
// }
//
// void L() {
//   switch (tok) {
//     case END:
//       advance(); break;
//
//     case SEMICOLON:
//       lineNum++; advance(); S(); L(); break;
//
//     default:
//       error("%d: Incomplete expression", lineNum);
//   }
// }
// 
// void E() {
//   if (tok == EOF) accept();
//   else error("%d: Incomplete file", lineNum);
// }

