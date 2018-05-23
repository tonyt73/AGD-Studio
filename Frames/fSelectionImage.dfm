object SelectionImageFrame: TSelectionImageFrame
  Left = 0
  Top = 0
  Width = 113
  Height = 113
  Color = clBtnFace
  Ctl3D = True
  Padding.Left = 4
  Padding.Top = 4
  Padding.Right = 4
  Padding.Bottom = 4
  ParentBackground = False
  ParentColor = False
  ParentCtl3D = False
  TabOrder = 0
  object imgBitmap: TImage
    Left = 4
    Top = 4
    Width = 105
    Height = 105
    Align = alClient
    Stretch = True
    OnClick = imgBitmapClick
  end
end
