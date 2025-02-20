color(red).
color(blue).
color(green).

neighbor(isfahan, yazd).
neighbor(isfahan, fars).
neighbor(isfahan, chahar_mahal_bakhtiari).
neighbor(isfahan, lorestan).
neighbor(isfahan, markazi).
neighbor(yazd, fars).
neighbor(fars, chahar_mahal_bakhtiari).
neighbor(chahar_mahal_bakhtiari, lorestan).
neighbor(lorestan, markazi).
neighbor(lorestan, hamedan).
neighbor(kordestan, hamedan).
symmetric_neighbor(X, Y) :- neighbor(X, Y).
symmetric_neighbor(X, Y) :- neighbor(Y, X).

dfs_coloring([], _, []).
dfs_coloring([Region | Remaining], Assigned, [Region-Color | Solution]) :-
    color(Color),
    valid_assignment(Region, Color, Assigned),
    dfs_coloring(Remaining, [Region-Color | Assigned], Solution).

valid_assignment(Region, Color, Assigned) :-
    forall(symmetric_neighbor(Region, Neighbor), \+ memberchk(Neighbor-Color, Assigned)).

mapcoloringiran(Solution) :-
    Regions = [isfahan, yazd, fars, chahar_mahal_bakhtiari, lorestan, markazi, hamedan, kordestan],
    dfs_coloring(Regions, [], Solution).
