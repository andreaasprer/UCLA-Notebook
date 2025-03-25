import { useState } from 'react';

function Square({value, onSquareClick}) {
  return (
    <button className="square" onClick={onSquareClick}>
      {value}
    </button>
  );
}

export default function Board() {
  const [xIsNext, setXIsNext] = useState(true);
  const [squares, setSquares] = useState(Array(9).fill(null));

  // First rule: three items per player
  const [xCount, setXCount] = useState(0);
  const [oCount, setOCount] = useState(0);
  
  // Allow movement of squares
  const [selectedIndex, setSelectedIndex] = useState(null);

  function isAdjacent(src, dest) {
    const adjacentMoves = {
      0: [1, 3, 4],
      1: [0, 2, 3, 4, 5],
      2: [1, 4, 5],
      3: [0, 1, 4, 6, 7],
      4: [0, 1, 2, 3, 5, 6, 7, 8],
      5: [1, 2, 4, 7, 8],
      6: [3, 4, 7],
      7: [3, 4, 5, 6, 8],
      8: [4, 5, 7]
    }
 
    // return whether if the destination were moving to is in the list for that index it was in.
    return adjacentMoves[src]?.includes(dest);
  }

  function isMovable(src, dest) {
    const nextSquares = squares.slice();
    nextSquares[dest] = nextSquares[src];
    nextSquares[src] = null;
  
    // If the move results in a win, allow it
    if (calculateWinner(nextSquares)) return true;
  
    // Check if the player has 3 pieces and one is in the center
    const hasCenterPiece = squares[4] === (xIsNext ? "X" : "O");
    if ((xIsNext && xCount === 3) || (!xIsNext && oCount === 3)) {
      if (hasCenterPiece) {
        // Enforce center movement rule
        return src === 4 && isAdjacent(src, dest);
      }
    }
  
    return true; // Otherwise, the move is valid
  }
  
  

  function handleClick(i) {
    if (calculateWinner(squares)) return;
    
    const nextSquares = squares.slice();

    // Handle movement of selected index
    if (selectedIndex !== null && (squares[selectedIndex] === (xIsNext ? "X" : "O"))) {
      if (squares[i] === null && isAdjacent(selectedIndex, i) && isMovable(selectedIndex, i)) {
        nextSquares[i] = nextSquares[selectedIndex];
        nextSquares[selectedIndex] = null;
        setSelectedIndex(null);  
        setSquares(nextSquares);
        setXIsNext(!xIsNext);      
      } 
      return;
    }

    // Selecting a piece to move
    if (squares[i] === (xIsNext ? "X" : "O")) {
      setSelectedIndex(i);
      return;
    }

    // Place pieces. Limit to 3 per player
    if (xIsNext && xCount < 3 && squares[i] == null) {
        nextSquares[i] = 'X';
        setXCount(xCount + 1);
    }
    else if (!xIsNext && oCount < 3 && squares[i] == null) {
      nextSquares[i] = 'O';
      setOCount(oCount + 1);
    } 
    else return;
    setSquares(nextSquares);
    setXIsNext(!xIsNext);
  }

  const winner = calculateWinner(squares);
  let status;
  if (winner) {
    status = 'Winner: ' + winner;
  } else {
    status = 'Next player: ' + (xIsNext ? 'X' : 'O');
  }

  return (
    <>
      <div className="status">{status}</div>
      <div className="board-row">
        <Square value={squares[0]} onSquareClick={() => handleClick(0)} />
        <Square value={squares[1]} onSquareClick={() => handleClick(1)} />
        <Square value={squares[2]} onSquareClick={() => handleClick(2)} />
      </div>
      <div className="board-row">
        <Square value={squares[3]} onSquareClick={() => handleClick(3)} />
        <Square value={squares[4]} onSquareClick={() => handleClick(4)} />
        <Square value={squares[5]} onSquareClick={() => handleClick(5)} />
      </div>
      <div className="board-row">
        <Square value={squares[6]} onSquareClick={() => handleClick(6)} />
        <Square value={squares[7]} onSquareClick={() => handleClick(7)} />
        <Square value={squares[8]} onSquareClick={() => handleClick(8)} />
      </div>
    </>
  );
}

function calculateWinner(squares) {
  const lines = [
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8],
    [0, 3, 6],
    [1, 4, 7],
    [2, 5, 8],
    [0, 4, 8],
    [2, 4, 6],
  ];
  for (let i = 0; i < lines.length; i++) {
    const [a, b, c] = lines[i];
    if (squares[a] && squares[a] === squares[b] && squares[a] === squares[c]) {
      return squares[a];
    }
  }
  return null;
}
