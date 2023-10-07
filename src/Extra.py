import numpy as np
sq_list = ['11', '12', '13', '14', '15', '16', '17', '18', '19', '21', '22', '23', '24', '25', '26', '27', '28', '29', '31', '32', '33', '34', '35', '36', '37', '38', '39', '41', '42', '43', '44', '45', '46', '47', '48', '49', '51', '52', '53', '54', '55', '56', '57', '58', '59', '61', '62', '63', '64', '65', '66', '67', '68', '69', '71', '72', '73', '74', '75', '76', '77', '78', '79', '81', '82', '83', '84', '85', '86', '87', '88', '89', '91', '92', '93', '94', '95', '96', '97', '98', '99']
sq_dict = {'11': 0, '12': 1, '13': 2, '14': 3, '15': 4, '16': 5, '17': 6, '18': 7, '19': 8, '21': 9, '22': 10, '23': 11, '24': 12, '25': 13, '26': 14, '27': 15, '28': 16, '29': 17, '31': 18, '32': 19, '33': 20, '34': 21, '35': 22, '36': 23, '37': 24, '38': 25, '39': 26, '41': 27, '42': 28, '43': 29, '44': 30, '45': 31, '46': 32, '47': 33, '48': 34, '49': 35, '51': 36, '52': 37, '53': 38, '54': 39, '55': 40, '56': 41, '57': 42, '58': 43, '59': 44, '61': 45, '62': 46, '63': 47, '64': 48, '65': 49, '66': 50, '67': 51, '68': 52, '69': 53, '71': 54, '72': 55, '73': 56, '74': 57, '75': 58, '76': 59, '77': 60, '78': 61, '79': 62, '81': 63, '82': 64, '83': 65, '84': 66, '85': 67, '86': 68, '87': 69, '88': 70, '89': 71, '91': 72, '92': 73, '93': 74, '94': 75, '95': 76, '96': 77, '97': 78, '98': 79, '99': 80}
usi_dict = {"a": "1", "b": "2", "c": "3", "d": "4", "e": "5", "f": "6", "g": "7", "h": "8", "i": "9"}
rotate_dict = {"a": "i", "b": "h", "c": "g", "d": "f", "e": "e", "f": "d", "g": "c", "h": "b", "i": "a", "1": "9", "2": "8", "3": "7", "4": "6", "5": "5", "6": "4", "7": "3", "8": "2", "9": "1", "+": "+", "P": "P", "L": "L", "N": "N", "S": "S", "G": "G", "B": "B", "R": "R", "*": "*"}
usi_str = "0abcdefghi"
piece_dict1 = {"FU": "P", "KY": "L", "KE": "N", "GI": "S", "KI": "G", "KA": "B", "HI": "R"}
drop_dict = {"P":1, "L":2, "N":3, "S":4, "B":5, "R":6, "G":7}

def rotate_boards(boards: list[list[list[float]]], rotate: int = 1) -> list[list[list[float]]]:
  if rotate:
    length = len(boards)
    rotated_boards = [[[0.0 for k in range(9)]for j in range(9)] for i in range(length)]
    for i in range(length):
      for j in range(9):
        for k in range(9):
          rotated_boards[i][8 - j][8 - k] = boards[i][j][k]
    return rotated_boards
  else:
    return boards

def soft_max_choice(arr, t):
  arr /= t
  arr -= arr.max()
  probs = np.exp(arr)
  probs /= probs.sum()
  return np.random.choice(len(arr), p = probs)

def usi_to_int(usi, turn):
  dir = 0
  move_to = int(usi[2]) * 9 + int(usi_dict[usi[3]]) - 10
  if usi[1] == "*":
    dir = 19 + drop_dict[usi[0]]
    if turn:
      move_to = 80 - move_to
  else:
    x_to = move_to % 9
    y_to = move_to / 9
    move_from = int(usi[0]) * 9 + int(usi_dict[usi[1]]) - 10
    x_from = move_from % 9
    y_from = move_from / 9
    if turn:
      if x_to < x_from:
        if y_to < y_from:
          dir = 5
        elif y_to > y_from:
          dir = 7
        else:
          dir = 6
      elif x_to > x_from:
        if y_to < y_from:
          if x_from - x_to == -2 and y_from - y_to == 1:
            dir = 8
          else:
            dir = 0
        elif y_to > y_from:
          if x_from - x_to == -2 and y_from - y_to == 1:
            dir = 9
          else:
            dir = 2
        else:
          dir = 1
      else:
        if y_to < y_from:
          dir = 3
        elif y_to > y_from:
          dir = 4
      move_to = 80 - move_to
    else:
      if x_to < x_from:
        if y_to < y_from:
          if x_from - x_to == 2 and y_from - y_to == 1:
            dir = 9
          else:
            dir = 2
        elif y_to > y_from:
          if x_from - x_to == 2 and y_from - y_to == -1:
            dir = 8
          else:
            dir = 0
        else:
          dir = 1
      elif x_to > x_from:
        if y_to < y_from:
          dir = 7
        elif y_to > y_from:
          dir = 5
        else:
          dir = 6
      else:
        if y_to < y_from:
          dir = 4
        elif y_to > y_from:
          dir = 3
    if usi[-1] == "+":
      dir += 10
  return 81 * dir + move_to

def usi_to_viewer(kif):
  local_drop_dict = {"P": "FU", "L": "KY", "N": "KE", "S": "GI", "G": "KI", "B": "KA", "R": "HI"}
  local_piece_list = ["ZZ", "FU", "KY", "KE", "GI", "KA", "HI", "KI", "OU", "TO", "NY", "NK", "NG", "UM", "RY"]
  viewer = "&kifu="
  board = cshogi.Board()
  t_sign = "+-"
  for usi in kif:
    move = board.move_from_usi(usi)
    if usi[1] == "*":
      viewer += t_sign[board.turn]
      viewer += "00"
      viewer += usi[2] + usi_dict[usi[3]]
      viewer += local_drop_dict[usi[0]]
    else:
      viewer += t_sign[board.turn]
      viewer += usi[0] + usi_dict[usi[1]]
      viewer += usi[2] + usi_dict[usi[3]]
      p = board.pieces[int(usi[0]) * 9 + int(usi_dict[usi[1]]) - 10] % 16
      if usi[-1] == "+":
        p += 8
      viewer += local_piece_list[p]
    if board.is_legal(move):
      board.push(move)
  print(viewer)
  print()
  return viewer
