% Here are a bunch of facts describing the Simpson's family tree.
% Don't change them!

female(mona).
female(jackie).
female(marge).
female(patty).
female(selma).
female(lisa).
female(maggie).
female(ling).

male(abe).
male(clancy).
male(herb).
male(homer).
male(bart).

married_(abe,mona).
married_(clancy,jackie).
married_(homer,marge).

married(X,Y) :- married_(X,Y).
married(X,Y) :- married_(Y,X).

parent(abe,herb).
parent(abe,homer).
parent(mona,homer).

parent(clancy,marge).
parent(jackie,marge).
parent(clancy,patty).
parent(jackie,patty).
parent(clancy,selma).
parent(jackie,selma).

parent(homer,bart).
parent(marge,bart).
parent(homer,lisa).
parent(marge,lisa).
parent(homer,maggie).
parent(marge,maggie).

parent(selma,ling).



%%
% Part 1. Family relations
%%

% 1. Define a predicate `child/2` that inverts the parent relationship.

child(X,Y) :- parent(Y,X).


% 2. Define two predicates `isMother/1` and `isFather/1`.

isMother(X) :- parent(X, _), female(X).
isMother(X) :- parent(X, _), male(X).

% 3. Define a predicate `grandparent/2`.

grandparent(X,Z) :- parent(X,Y), parent(Y,Z).

% 4. Define a predicate `sibling/2`. Siblings share at least one parent.

sibling(X,Z) :- parent(Y,Z), parent(Y,X), X \= Z.

% 5. Define two predicates `brother/2` and `sister/2`.

brother(X,Y) :- male(X), sibling(X,Y), X \= Y.
sister(X,Y) :- female(X), sibling(X,Y), X \= Y.

% 6. Define a predicate `siblingInLaw/2`. A sibling-in-law is either married to
%    a sibling or the sibling of a spouse.

siblingInLaw(X,Y) :- sibling(X,Z), married(Z,Y).
siblingInLaw(X,Y) :- married(X,Z), sibling(Z,Y).

% 7. Define two predicates `aunt/2` and `uncle/2`. Your definitions of these
%    predicates should include aunts and uncles by marriage.

aunt(A,N) :- female(A), sibling(A,P), parent(P,N).
aunt(A,N) :- female(A), siblingInLaw(A,P), parent(P,N).
uncle(U,N) :- male(U), sibling(U,P), parent(P,N).
uncle(U,N) :- male(U), siblingInLaw(U,P), parent(P,N).

% 8. Define the predicate `cousin/2`.

cousin(X,Y) :- parent(P,X), aunt(P,Y).
cousin(X,Y) :- parent(P,X), uncle(P,Y).

% 9. Define the predicate `ancestor/2`.

ancestor(X,Y) :- parent(X,Y).
ancestor(X,Y) :- parent(X,C), ancestor(C,Y).

% Extra credit: Define the predicate `related/2`.

related_(X,Y) :- parent(X,Y).
related_(X,Y) :- sibling(X,Y).
related_(X,Y) :- cousin(X,Y).
related_(X,Y) :- siblingInLaw(X,Y).
related_(X,Y) :- married(X,Y).
related_(X,Y) :- grandparent(X,Y).
related_(X,Y) :- grandparent(Y,X).
related_(X,Y) :- parent(Y,X).

related(X,Y) :- related_(X,Y).
related(X,Y) :- related_(X,Z), related(Z,Y).

%%
% Part 2. Language implementation
%%

%% language syntax
% num	 ::= (any number literal)
% str	 ::= (any string literal)
% bool ::=	t   | f	         -- boolean literals
% prog ::=	cmd∗∗	           -- sequence of commands
% cmd 	::=	num | str | bool -- push a literal onto the stack
%         |	add | lte	       -- number addition/comparison
%         |	if(prog,prog)	   -- conditional branching
%%

%% example commands
% if(["foo"],[3]) -- parses progs
% lte             -- uses stack
% 5               -- int literal
%%

%% example stacks
% ["goodbye"]
% ["hello", 4]
% [f, t]
% [5,3,t]
%%

% 1. Define the predicate `cmd/3`, which describes the effect of executing a
%    command on the stack.

bool(t).
bool(f).

str(X) :- string(X).  % why not have some wrappers
num(X) :- integer(X). % wrappers fo dayz

raw(X) :- bool(X); str(X); num(X).

% push to stack
cmd(C,S1,S2) :- raw(C), append([C], S1, S2).

% add
cmd(C,S1,S2) :- C == add,
  [A,B|T] = S1,
  Res is A+B,
  append([Res], T, S2).

% lte
cmd(C,S1,S2) :- C == lte,
  [A,B|T] = S1, (
    A < B -> Res = t ;
    Res = f
  ),
  append([Res], T, S2).

% if(prog,prog)
cmd(if(P1,P2),[H|T],S2) :- (
    H == t -> prog(P1, T, S2) ;
    prog(P2, T, S2)
  ).

% 2. Define the predicate `prog/3`, which describes the effect of executing a
%    program on the stack.

% Si = intermediate, So = original, Sr = result
prog([H|[]],So,Sr) :- cmd(H, So, Sr).
prog([H|T],So,Sr) :- cmd(H, So, Si), prog(T, Si, Sr).
