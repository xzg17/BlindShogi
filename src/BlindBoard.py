from Extra import *
import cshogi
from copy import deepcopy

class BlindBoard:

  def __init__(self, sfen = None):
    self.board = cshogi.Board(sfen)
    self.blind = cshogi.Board()
    self.ill = [9, 9]
    self.blindness = 0
    self.df = 0.5 #discount factor
    self.history_piece_boards = [[[[0.0 for i in range(9)] for j in range(9)] for k in range(14)], [[[0.0 for i in range(9)] for j in range(9)] for k in range(14)]]
    self.check_history_board = [[[[0.0 for j in range(9)] for i in range(9)]], [[[0.0 for j in range(9)] for i in range(9)]]]
    self.checked_history_board = [[[[0.0 for j in range(9)] for i in range(9)]], [[[0.0 for j in range(9)] for i in range(9)]]]
    self.lost_history_board = [[[[0.0 for j in range(9)] for i in range(9)]], [[[0.0 for j in range(9)] for i in range(9)]]]# history_piece_board の欠陥を埋めるため。より直接的な特徴量のため精度向上を期待できるかも
    self.current_invalid_board = [[[0.0 for j in range(9)] for i in range(9)]]
    self.no_check_invalid_drop_history_board = [[[[0.0 for j in range(9)] for i in range(9)]], [[[0.0 for j in range(9)] for i in range(9)]]]
    self.previous_board = [[], []] # check_history_board用 cshogi.Board.piece_board


  def piece_boards(self, turn = -1):#return rotated boards
    if turn == -1:
      t = self.board.turn
    else:
      t = turn
    boards = [[[0.0 for i in range(9)] for j in range(9)] for k in range(14)]
    if t:
      for i in range(14):
        for p1 in range(9):
          for p2 in range(9):
            if self.board.pieces[p1 * 9 + p2] == i + 17:
              boards[i][8 - p1][8 - p2] = 1.0
    else:
      for i in range(14):
        for p1 in range(9):
          for p2 in range(9):
            if self.board.pieces[p1 * 9 + p2] == i + 1:
              boards[i][p1][p2] = 1.0
    return boards

  def hand_boards(self, turn = -1):
    if turn == -1:
      t = self.board.turn
    else:
      t = turn
    boards = [[[0.0 for i in range(9)] for j in range(9)] for k in range(38)]
    hands = deepcopy(self.board.pieces_in_hand[t])
    for i in range(hands[0]):
      boards[i] = [[1.0 for i in range(9)] for j in range(9)]
    for i in range(hands[1]):
      boards[i + 18] = [[1.0 for i in range(9)] for j in range(9)]
    for i in range(hands[2]):
      boards[i + 22] = [[1.0 for i in range(9)] for j in range(9)]
    for i in range(hands[3]):
      boards[i + 26] = [[1.0 for i in range(9)] for j in range(9)]
    for i in range(hands[4]):
      boards[i + 30] = [[1.0 for i in range(9)] for j in range(9)]
    for i in range(hands[5]):
      boards[i + 34] = [[1.0 for i in range(9)] for j in range(9)]
    for i in range(hands[6]):
      boards[i + 36] = [[1.0 for i in range(9)] for j in range(9)]
    if t:
      boards = rotate_boards(boards)
    return boards #length:38

  def illegal_boards(self, turn = -1):
    if turn == -1:
      t = self.board.turn
    else:
      t = turn
    boards = [[[0.0 for i in range(9)] for j in range(9)] for k in range(18)]
    for i in range(self.ill[t]):
      boards[i] = [[1.0 for i in range(9)] for j in range(9)]
    for i in range(self.ill[1 - t]):
      boards[i + 9] = [[1.0 for i in range(9)] for j in range(9)]
    return boards

  def check_board(self):
    if self.board.is_check():
      return [[[1.0 for i in range(9)] for j in range(9)]]
    else:
      return [[[0.0 for i in range(9)] for j in range(9)]]

  def is_game_over(self):
    return self.board.is_game_over() or self.ill[0] < 0 or self.ill[1] < 0

  def pseudo_legal_moves(self):
    if not self.blindness:
      self.set_blind()
    return self.blind.pseudo_legal_moves

  def push_usi(self, usi):
    move = self.board.move_from_usi(usi)
    info = int(self.board.is_legal(move))
    to_row = int(usi[2]) - 1
    to_col = int(usi_dict[usi[3]]) - 1
    to_pos = to_row * 9 + to_col
    if info:
      #self
      self.previous_board[self.board.turn] = self.blind_pieces(self.board.turn)
      info = self.board.pieces[to_pos]
      for p1 in range(9):
        for p2 in range(9):
          self.no_check_invalid_drop_history_board[self.board.turn][0][p1][p2] *= self.df
          self.check_history_board[self.board.turn][0][p1][p2] *= self.df
          self.checked_history_board[self.board.turn][0][p1][p2] *= self.df
          self.lost_history_board[self.board.turn][0][p1][p2] *= self.df
          for i in range(14):
            self.history_piece_boards[self.board.turn][i][p1][p2] *= self.df
            if self.board.pieces[p1 * 9 + p2] == i + 17:
              self.history_piece_boards[self.board.turn][i][p1][p2] += 1.0
      if info:
        info %= 8
      else:
        info = 8
        self.lost_history_board[1 - self.board.turn][0][to_row][to_col] += 1.0
      self.invalid_board = [[[0.0 for j in range(9)] for i in range(9)]]
      self.previous_board[self.board.turn] = self.blind_pieces(self.board.turn)
      self.board.push(move)

      #opponent
      if self.board.is_check():
        kpos = -1
        for i in range(81):
          if self.board.pieces[i] == 8 + self.board.turn * 16:
            kpos = i
            break
        self.checked_history_board[self.board.turn][0][i // 9][i % 9] += 1.0

        previous_pieces = self.previous_board[1 - self.board.turn]
        current_pieces = self.blind_pieces(1 - self.board.turn)
        null_hands = ((0, 0, 0, 0, 0, 0, 0), (0, 0, 0, 0, 0, 0, 0))
        previous = cshogi.Board()
        current = cshogi.Board()
        previous.set_pieces(previous_pieces, null_hands)
        current.set_pieces(current_pieces, null_hands)
        previous.turn =  1 - self.board.turn
        current.turn =  1 - self.board.turn
        check_set = set()
        for move in current.legal_moves:
          usi = cshogi.move_to_usi(move)
          to_row = int(usi[2]) - 1
          to_col = int(usi_dict[usi[3]]) - 1
          if not previous_pieces[to_row * 9 + to_col]:
            check_set.add(usi[2:4])
        for move in previous.legal_moves:
          usi = cshogi.move_to_usi(move)
          check_set.discard(usi[2:4])
        for to_usi in check_set:
          to_row = int(to_usi[0]) - 1
          to_col = int(usi_dict[to_usi[1]]) - 1
          self.check_history_board[1 - self.board.turn][0][to_row][to_col] += 1.0
    else:
      self.invalid_board[0][to_row][to_col] += 1.0
      self.ill[self.board.turn] -= 1
      if self.board.is_check():
        pass
      elif usi[1]== "*":
        self.no_check_invalid_drop_history_board[self.board.turn][0][to_row][to_col] = 1.0
        pass
    self.blindness = 0
    return info #0:反則, 1:歩, 2:香, 3:桂, 4:銀, 5:角, 6:飛, 7:金, 8:無

  def pseudo_push_usi(self, usi):#return rotated boards (length:52)
    hands_dict = {"P":0, "L":1, "N":2, "S":3, "G":4, "B":5, "R":6}
    pseudo_board = deepcopy(self.board.pieces)
    pseudo_hands = deepcopy(self.board.pieces_in_hand[self.board.turn])
    move_to = int(usi[2]) * 9 + int(usi_dict[usi[3]]) - 10
    if usi[1] == "*":
      pseudo_hands[hands_dict[usi[0]]] -= 1
      if self.board.turn:
        pseudo_board[move_to] = drop_dict[usi[0]] + 16
      else:
        pseudo_board[move_to] = drop_dict[usi[0]]
    else:
      move_from = int(usi[0]) * 9 + int(usi_dict[usi[1]]) - 10
      if usi[-1] == "+":
        pseudo_board[move_to] = pseudo_board[move_from] + 8
      else:
        pseudo_board[move_to] = pseudo_board[move_from]
      pseudo_board[move_from] = 0
    piece_boards = [[[0.0 for i in range(9)] for j in range(9)] for k in range(14)]
    hans_boards = [[[0.0 for i in range(9)] for j in range(9)] for k in range(38)]
    if self.board.turn:
      for i in range(14):
        for p1 in range(9):
          for p2 in range(9):
            if pseudo_board[p1 * 9 + p2] == i + 17:
              piece_boards[i][8 - p1][8 - p2] = 1.0
    else:
      for i in range(14):
        for p1 in range(9):
          for p2 in range(9):
            if pseudo_board[p1 * 9 + p2] == i + 1:
              piece_boards[i][p1][p2] = 1.0
    for i in range(pseudo_hands[0]):
      hans_boards[i] = [[1.0 for i in range(9)] for j in range(9)]
    for i in range(pseudo_hands[1]):
      hans_boards[i + 18] = [[1.0 for i in range(9)] for j in range(9)]
    for i in range(pseudo_hands[2]):
      hans_boards[i + 22] = [[1.0 for i in range(9)] for j in range(9)]
    for i in range(pseudo_hands[3]):
      hans_boards[i + 26] = [[1.0 for i in range(9)] for j in range(9)]
    for i in range(pseudo_hands[4]):
      hans_boards[i + 30] = [[1.0 for i in range(9)] for j in range(9)]
    for i in range(pseudo_hands[5]):
      hans_boards[i + 34] = [[1.0 for i in range(9)] for j in range(9)]
    for i in range(pseudo_hands[6]):
      hans_boards[i + 36] = [[1.0 for i in range(9)] for j in range(9)]
    piece_boards += hans_boards
    if self.board.turn:
      piece_boards = rotate_boards(piece_boards)
    return piece_boards #length:52

  def blind_pieces(self, turn):
    if turn == self.board.turn and self.blindness:
      return self.blind.pieces
    else:
      pieces = [0 for i in range(81)]
      l = self.board.pieces
      if turn:
        for i in range(81):
          if 17 <= l[i]:
            pieces[i] = 0
      else:
        for i in range(81):
          if l[i] < 17:
            pieces[i] = 0
      return pieces

  def set_blind(self):
    if not self.blindness:
      l = self.board.pieces
      t = self.board.pieces_in_hand
      if self.board.turn:
        for i in range(81):
          if l[i] < 17:
            l[i] = 0
      else:
        for i in range(81):
          if 17 <= l[i]:
            l[i] = 0
      self.blind.set_pieces(l, t)
      self.blind.turn = self.board.turn
      self.blindness = 1
    return self.blind.pieces
  
  def reset_blind(self):
    self.blindness = 0

  def convert_kif_to_lists(self, kif):#rotated 局面数*入力特徴量数*9*9と出力のセット
    win = 1
    if kif[-7] == "+":
      win = 0
    val = 1 - win
    piece_boards_list = []
    hand_boards_list = []
    illegal_boards_list = []
    check_boards_list = []

    current_invalid_boards_list = []

    history_piece_boards_list = []
    check_history_boards_list = []
    checked_history_boards_list = []
    lost_history_boards_list = []
    no_check_invalid_drop_history_boards_list = []

    simple_predict_boards_list = []

    move_list = [] #ここに出力 指し手用
    simple_predict_list = [] #ここに出力 簡易予測用
    value_list = [] #ここに出力 形成判断用
    
    i = 1
    usi_kif = []
    s = ""
    for char in kif:
      s += char
      if not i % 7:
        if s[1] == "0":
          p = s[5] + s[6]
          usi = piece_dict1[p] + "*" + s[3] + usi_str[int(s[4])]
        else:
          usi = s[1] + usi_str[int(s[2])] + s[3] + usi_str[int(s[4])]
          if s[5] == "N" or s[5] == "R" or s[5] == "U" or s[5] == "T":
            usi += "+"
        if usi[-1] == "+" and self.board.piece(sq_dict[usi[0] + usi_dict[usi[1]]]) % 16 >= 9:
          usi = usi[:4]
        move_num = usi_to_int(usi, self.board.turn)
        if win:
          val = self.board.turn
        else:
          val = 1 - self.board.turn
        move_numbers = [0.0 for i in range(2187)]
        move_numbers[move_num] = 1.0
        
        move_list.append(move_numbers)
        value_list.append([val])
        simple_predict_list.append([1.0])

        piece_boards_list.append(self.piece_boards())
        hand_boards_list.append(self.hand_boards())
        illegal_boards_list.append(self.illegal_boards())
        check_boards_list.append(self.check_board())
        current_invalid_boards_list.append(rotate_boards(self.current_invalid_board, self.board.turn))

        history_piece_boards_list.append(rotate_boards(self.history_piece_boards[self.board.turn], self.board.turn))
        check_history_boards_list.append(rotate_boards(self.check_history_board[self.board.turn], self.board.turn))
        checked_history_boards_list.append(rotate_boards(self.checked_history_board[self.board.turn], self.board.turn))
        lost_history_boards_list.append(rotate_boards(self.lost_history_board[self.board.turn], self.board.turn))
        no_check_invalid_drop_history_boards_list.append(rotate_boards(self.no_check_invalid_drop_history_board[self.board.turn], self.board.turn))

        simple_predict_boards = self.pseudo_push_usi(usi)
        simple_predict_boards_list.append(simple_predict_boards)
        #data_info_list.append(None)
        info = self.push_usi(usi)
        if info:
          if info != 8:
            simple_predict_list[-1][0] = 0.0
            if 2 <= len(simple_predict_list):
              simple_predict_list[-2][0] = 0.0
        else:
          simple_predict_list[-1][0] = 0.0
          if 2 <= len(simple_predict_list):
            simple_predict_list[-2][0] = 0.0
        s = ""
      i += 1
    simple_predict_list[-1][0] = 0.0
    if 2 <= len(simple_predict_list):
      simple_predict_list[-2][0] = 0.0
    return (
      piece_boards_list, hand_boards_list, illegal_boards_list, check_boards_list, current_invalid_boards_list, 
      history_piece_boards_list, check_history_boards_list, checked_history_boards_list, lost_history_boards_list, no_check_invalid_drop_history_boards_list,
      simple_predict_boards_list,
      move_list, simple_predict_list, value_list
    )

  def debug(self):
    print("This is a function for me, a developer")
    pass
