# Chess2

A basic chess algorithm/bot written in C.

Implemented Features:

- Initialisation and display of a chess board.
- Movement of pawns and captures of opposing pieces.
- Scoring system for pieces and a rudimentary calculation of a positions value based on potential captures.

Currently Implementing:

- Resolving issues with segmentation faults at high depths.
- Removing the bots optimistic attitude and replacing it with a pessimistic one to evaluate a position (The bot will likely assume it's opponent will make the worst possible moves.)
- Currently limited to just pawns but more piece movement and thus potential moves will be added later.