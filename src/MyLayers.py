import torch
from torch import nn
import random
class Flatten(nn.Module):
  def forward(self, input_tensor):
    if input_tensor.ndim == 3:
      return input_tensor.view(1, -1)[0]
    elif input_tensor.ndim == 4:
      output_tensor = input_tensor.view(input_tensor.shape[0], -1)
      return output_tensor
    else:
      print("Error in Layer:Flatten")
      return input_tensor

class Log(nn.Module):
  def __init__(self):
    super().__init__()

  def forward(self, x):
    print("shape:", x.shape)
    return x

class Bias(nn.Module):
  def __init__(self) -> None:
    super().__init__()
    bias_value = torch.randn((1))
    self.bias_layer = nn.Parameter(bias_value)

  def forward(self, x):
    re_x = x + self.bias_layer
    return re_x
