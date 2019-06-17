# Lee Beadle
# CS 470
# Connect Four Game
# This program implements a basic version of the game connect four. The number of
# columns and rows are predetermined and this program will not function with alterations
# to board size. Also, this program makes use of "Invent Your Computer Games with Python"
# by Al Sweigart and other online resources.

# Side-Note: This version only correctly identifies human wins when moves 0,1,2,3
# are selected in the horizontal order. This was working for vertical and diagonal 
# cases but I broke it and cannot find the error. 

# Numpy - scientific computing package for python
import numpy
import random

# Global Constants
ROWS = 6 # Number of rows
COLS = 7 # Number of columns
VALID_ROWS = ROWS - 3 # Possible vertical win locations
VALID_COLS = COLS - 3 # Possible vertical win locations
AXIS = 0 # Orientation of matrix

def buildBoard():
    board = numpy.chararray((ROWS, COLS))
    board[:] = "O"
    return board
    
# Used to flip the matrix orientation so that game moves fall to the bottom
def display(board):
    print(numpy.flip(board, AXIS))

def makeMove(board, r, move, player):
    board[r][move] = player
    
def validMove(board, move):
    if board[ROWS - 1][move] == "O":
        return board[ROWS - 1][move]
    else:
        print "INVALID MOVEMENT!!!"

def getNext(board, move):
    for r in range(ROWS):
        if board[r][move] == "O":
            return r

# Checks the current board state for a winning state. Four player icons in a 
# horizontal, vertical, or diagnoal positioning are considered a winning state. 
def checkBoardState(board, player):
    for c in range(VALID_COLS):
        for r in range(ROWS):
            if (board[r][c] == player and board[r][c+1] == player 
            and board [r][c+2] == player and board[r][c+3] == player):
                return True
            else:
                return False
                
    for c in range(COLS):
        for r in range(VALID_ROWS):
            if (board[r][c] == player and board[r+1][c] == player 
            and board [r+2][c] == player and board[r+3][c] == player):
                return True
            else:
                return False                

    for c in range(VALID_COLS):
        for r in range(VALID_ROWS):
            if (board[r][c] == player and board[r+1][c+1] == player 
            and board [r+2][c+2] == player and board[r+3][c+3] == player):
                return True
            else:
                return False

    for c in range(VALID_COLS):
        for r in range(3, ROWS):
            if (board[r][c] == player and board[r-1][c+1] == player 
            and board [r-2][c+2] == player and board[r-3][c+3] == player):
                return True
            else:
                return False

# Main Driver
def main():
    player1 = "H"
    computer = "C"
    turn = "p2" # Initialize first move to human player
    gameOver = False 
    header = "   0   1   2   3   4   5   6"
    winner = " WINS THE GAME!!!"
    
    board = buildBoard()
    print header    
    display(board)

    while gameOver is False:
        if turn == "p1":
            move = input("Your move: ")
            move = int(move)
        
            if validMove(board, move):
                r = getNext(board, move)
                makeMove(board, r, move, player1)
                turn = "p2"

                if checkBoardState(board, player1):
                    winner = "HUMAN" + winner
                    gameOver = True

        else:
            move = random.randint(0,6)
        
            if validMove(board, move):
                r = getNext(board, move)
                makeMove(board, r, move, computer)
                turn = "p1"
            
                if checkBoardState(board, computer):
                    winner = "COMPUTER" + winner
                    gameOver = True
        print ""
        print header    
        display(board)
    
        if gameOver == True:
            print winner

if __name__ == '__main__':
  main()